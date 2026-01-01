#pragma once

#include <atomic>

#include <KernelExport.h>
#include <lock.h>
#include <ScopeExit.h>


class IntrSafePool {
private:
	static constexpr uint32 kGroupCount = 4;
	static constexpr uint32 kGroupMaxItemCount = 16;
	static constexpr uint32 kMinSizePow2 = 4;
	static constexpr size_t kMinSize = 1 << kMinSizePow2;

	template<uint32 maxItemCount>
	struct Group {
		uint32 count = 0;
		void *items[maxItemCount] {};

		void ReclaimAll(spinlock &lock);
		void *Alloc();
		void Free(void *ptr);
	};

	Group<kGroupMaxItemCount> fGroups[kGroupCount];
	Group<4096> fReclaimGroup;

	spinlock fSpinlock = B_SPINLOCK_INITIALIZER;
	std::atomic<int32> fLevel = 0;

public:
	void ReclaimAll();

	void *Alloc(size_t size);
	void Free(void *ptr);
	void Maintain();
};
