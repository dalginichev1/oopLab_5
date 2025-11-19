#include "customAllocator.hpp"

#include <iostream>

FixedCustomMemoryResource::FixedCustomMemoryResource(size_t memory_size) : pool_size(memory_size) {
    memory_pool = static_cast<char*>(::operator new(memory_size));
}

FixedCustomMemoryResource::~FixedCustomMemoryResource() {
    ::operator delete(memory_pool);
}

void* FixedCustomMemoryResource::do_allocate(size_t bytes, size_t align) {
    for (auto& block : blocks) {
        if (!block.is_allocated && block.size >= bytes) {
            block.is_allocated = true;
            return block.ptr;
        }
    }

    if (current_offset + bytes <= pool_size) {
        void* ptr = memory_pool + current_offset;
        current_offset += bytes;

        blocks.emplace_back(ptr, bytes, true);
        return ptr;
    }

    throw std::bad_alloc();
}

void FixedCustomMemoryResource::do_deallocate(void* ptr, size_t bytes, size_t align) {
    if (ptr == nullptr)
        return;

    for (auto& block : blocks) {
        if (block.ptr == ptr) {
            block.is_allocated = false;
            return;
        }
    }
}

bool FixedCustomMemoryResource::do_is_equal(const std::pmr::memory_resource& other) const noexcept {
    return this == &other;
}