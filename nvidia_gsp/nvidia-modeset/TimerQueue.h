#pragma once

extern "C" {
#include <nvidia-modeset-os-interface.h>
}

#include <DPC.h>

#include <util/DoublyLinkedList.h>


class NvTimerQueue {
private:
	friend struct nvkms_timer_t;

	DPCQueue fDpcQueue;

	class TimerListItem: public DoublyLinkedListLinkImpl<TimerListItem> {};

	DoublyLinkedList<TimerListItem> fTimerList;

	spinlock fSpinlock = B_SPINLOCK_INITIALIZER;

public:
	NvTimerQueue();
	~NvTimerQueue();

	status_t Init();
	void Fini();

	nvkms_timer_handle_t *Alloc(nvkms_timer_proc_t *proc, void *dataPtr, NvU32 dataU32, NvU64 usec);
	NvBool AllocWithRefPtr(nvkms_timer_proc_t *proc, struct nvkms_ref_ptr *ref_ptr, NvU32 dataU32, NvU64 usec);
	void Free(nvkms_timer_handle_t *handle);
};
