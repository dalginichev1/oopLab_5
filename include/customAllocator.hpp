#pragma once

#include <memory_resource>
#include <list>

class FixedCustomMemoryResource : public std::pmr::memory_resource
{
    private:
        struct MemoryBlock
        {
            size_t size = 0;
            void* ptr;
            bool is_allocated;

            MemoryBlock(void* p, size_t s, bool u = true) : ptr(p), size(s), is_allocated(u) {}
        };

        char* memory_pool;
        size_t pool_size;
        std::list<MemoryBlock> blocks;


    protected:
        void *do_allocate(size_t bytes, size_t align) override;
        void do_deallocate(void *p, size_t bytes, size_t align) override;
        bool do_is_equal(const std::pmr::memory_resource& other) const noexcept override;
    
    public:
        FixedCustomMemoryResource(size_t memory_size);
        ~FixedCustomMemoryResource();
};