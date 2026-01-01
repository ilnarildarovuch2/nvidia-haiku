#include "TimerQueue.h"

#include <util/AutoLock.h>

#include "ContainerOf.h"
#include "KmsDriver.h"


// TODO: Cancel and delete all timers on add-on unload.

struct nvkms_timer_t final: public DPCCallback, private NvTimerQueue::TimerListItem {
private:
	NvTimerQueue &fQueue;
	spinlock fSpinlock = B_SPINLOCK_INITIALIZER;

	struct timer fTimer {};

	bool fTimerScheduled: 1;
	bool fDpcScheduled: 1;

	nvkms_timer_proc_t *fProc;
	void *fDataPtr;
	NvU32 fDataU32;
	bool fIsRefPtr;

	static int32 TimerHook(struct timer *timer);

	static class DPCQueue *DPCQueue() {return DPCQueue::DefaultQueue(B_NORMAL_PRIORITY);}

public:
	nvkms_timer_t(NvTimerQueue &queue, nvkms_timer_proc_t *proc, void *dataPtr, NvU32 dataU32, bool isRefPtr);
	~nvkms_timer_t();
	void Free();
	void Schedule(NvU64 usec);
	void DoDPC(class DPCQueue* queue) final;
};

nvkms_timer_t::nvkms_timer_t(NvTimerQueue &queue, nvkms_timer_proc_t *proc, void *dataPtr, NvU32 dataU32, bool isRefPtr):
	fQueue(queue),
	fTimerScheduled(false),
	fDpcScheduled(false),
	fProc(proc),
	fDataPtr(dataPtr),
	fDataU32(dataU32),
	fIsRefPtr(isRefPtr)
{
	if (fIsRefPtr) {
		auto refPtr = static_cast<struct nvkms_ref_ptr*>(fDataPtr);
		nvkms_inc_ref(refPtr);
	}
	fQueue.fTimerList.Insert(static_cast<TimerListItem*>(this));
}

nvkms_timer_t::~nvkms_timer_t()
{
	fQueue.fTimerList.Remove(static_cast<TimerListItem*>(this));
}

void nvkms_timer_t::Schedule(NvU64 usec)
{
	InterruptsSpinLocker locker(fSpinlock);
	if (usec == 0) {
		fDpcScheduled = true;
		DPCQueue()->Add(this);
	} else {
		fTimerScheduled = true;
		add_timer(&fTimer, TimerHook, usec, B_ONE_SHOT_RELATIVE_TIMER);
	}
}

void nvkms_timer_t::Free()
{
	// assert(!fIsRefPtr)
	{
		InterruptsSpinLocker locker(fSpinlock);
		if (fTimerScheduled) {
			cancel_timer(&fTimer);
			fTimerScheduled = false;
		}
		if (fDpcScheduled) {
			DPCQueue()->Cancel(this);
			fDpcScheduled = false;
		}
	}
	delete this;
}

int32 nvkms_timer_t::TimerHook(struct timer *timer)
{
	nvkms_timer_t &nvkmsTimer = ContainerOf(*timer, &nvkms_timer_t::fTimer);
	SpinLocker locker(nvkmsTimer.fSpinlock);
	if (nvkmsTimer.fTimerScheduled) {
		nvkmsTimer.fTimerScheduled = false;
		DPCQueue()->Add(&nvkmsTimer);
	}
	return B_HANDLED_INTERRUPT;
}

void nvkms_timer_t::DoDPC(class DPCQueue* queue)
{
	void *dataPtr;
	{
		InterruptsSpinLocker locker(fSpinlock);
		if (!fDpcScheduled) {
			return;
		}
		fDpcScheduled = false;
		if (fIsRefPtr) {
			auto refPtr = static_cast<struct nvkms_ref_ptr*>(fDataPtr);
			dataPtr = nvkms_dec_ref(refPtr);
			if (dataPtr == NULL) {
				locker.Unlock();
				delete this;
				return;
			}
		} else {
			dataPtr = fDataPtr;
		}
	}
	{
		MutexLocker lock(&NvHaikuKmsDriver::Instance().Locker());
		fProc(dataPtr, fDataU32);
	}
	if (fIsRefPtr) {
		delete this;
	}
}


NvTimerQueue::NvTimerQueue()
{
}

NvTimerQueue::~NvTimerQueue()
{
}

status_t NvTimerQueue::Init()
{
	return fDpcQueue.Init("NvTimerQueue", B_URGENT_DISPLAY_PRIORITY, 0);
}

void NvTimerQueue::Fini()
{
	fDpcQueue.Close(true);
}

nvkms_timer_handle_t *NvTimerQueue::Alloc(nvkms_timer_proc_t *proc, void *dataPtr, NvU32 dataU32, NvU64 usec)
{
	nvkms_timer_t *timer = new(std::nothrow) nvkms_timer_t(*this, proc, dataPtr, dataU32, false);
	if (timer == NULL) {
		return NULL;
	}
	timer->Schedule(usec);
	return timer;
}

NvBool NvTimerQueue::AllocWithRefPtr(nvkms_timer_proc_t *proc, struct nvkms_ref_ptr *ref_ptr, NvU32 dataU32, NvU64 usec)
{
	nvkms_timer_t *timer = new(std::nothrow) nvkms_timer_t(*this, proc, ref_ptr, dataU32, true);
	if (timer == NULL) {
		return NV_FALSE;
	}
	timer->Schedule(usec);
	return NV_TRUE;
}

void NvTimerQueue::Free(nvkms_timer_handle_t *handle)
{
	if (handle == NULL) {
		return;
	}
	handle->Free();
}
