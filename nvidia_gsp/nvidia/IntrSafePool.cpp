#include "IntrSafePool.h"

#include <malloc.h>
#include <bit>

#include <util/AutoLock.h>


template<uint32 maxItemCount>
void IntrSafePool::Group<maxItemCount>::ReclaimAll(spinlock &lock)
{
	while (count > 0) {
		if (count > maxItemCount) {
			panic("IntrSafePool: overflowed: %" B_PRIu32 "\n", count);
		}
		count--;
		void *ptr = items[count];
//		dprintf("IntrSafePool::Reclaim(%p)\n", ptr);
		items[count] = nullptr;
		release_spinlock(&lock);
		enable_interrupts();
		free(ptr);
		disable_interrupts();
		acquire_spinlock(&lock);
	}
}

template<uint32 maxItemCount>
void *IntrSafePool::Group<maxItemCount>::Alloc()
{
	if (count == 0) {
		return nullptr;
	}
	count--;
	void *ptr = items[count];
	items[count] = nullptr;
	return ptr;
}

template<uint32 maxItemCount>
void IntrSafePool::Group<maxItemCount>::Free(void *ptr)
{
	if (count >= maxItemCount) {
		panic("IntrSafePool: overflow");
	}
	items[count] = ptr;
	count++;
}

void IntrSafePool::ReclaimAll()
{
	InterruptsSpinLocker _(&fSpinlock);

	fReclaimGroup.ReclaimAll(fSpinlock);
	for (uint32 i = 0; i < kGroupCount; i++) {
		auto &group = fGroups[i];
		group.ReclaimAll(fSpinlock);
	}
}

void *IntrSafePool::Alloc(size_t size)
{
	SpinLocker _(&fSpinlock);

	fLevel++;
	ScopeExit se([this] {fLevel--;});

	uint32 n = 0;
#if 0
	if (size > kMinSize) {
		n = std::bit_width(size - 1) - kMinSizePow2;
	}
#endif
	size_t groupSize = kMinSize;
	while (groupSize < size) {
		n++;
		groupSize *= 2;
	}
	for (uint32 i = n; i < kGroupCount; i++) {
		auto &group = fGroups[i];
		void *ptr = group.Alloc();
		if (ptr != nullptr) {
//			dprintf("IntrSafePool::Alloc(%#" B_PRIxSIZE ":%#" B_PRIxSIZE ", i: %" B_PRIu32 "): %p\n", size, groupSize, i, ptr);
			return ptr;
		}
	}
	panic("IntrSafePool: underflow");
	return nullptr;
}

void IntrSafePool::Free(void *ptr)
{
	SpinLocker _(&fSpinlock);

	fLevel++;
	ScopeExit se([this] {fLevel--;});

//	dprintf("IntrSafePool::Free(%p)\n", ptr);
	fReclaimGroup.Free(ptr);
}

void IntrSafePool::Maintain()
{
	InterruptsSpinLocker _(&fSpinlock);

	int32 oldLevel = fLevel++;
	ScopeExit se([this] {fLevel--;});
	if (oldLevel > 0) {
		return;
	}

	fReclaimGroup.ReclaimAll(fSpinlock);
	size_t size = kMinSize;
	for (uint32 i = 0; i < kGroupCount; i++) {
		auto &group = fGroups[i];
		while (group.count < kGroupMaxItemCount) {
			release_spinlock(&fSpinlock);
			enable_interrupts();
			void *ptr = calloc(1, size);
			disable_interrupts();
			acquire_spinlock(&fSpinlock);
			group.items[group.count] = ptr;
//			dprintf("IntrSafePool::Reserve(): %p\n", ptr);
			group.count++;
		}
		size *= 2;
	}
}
