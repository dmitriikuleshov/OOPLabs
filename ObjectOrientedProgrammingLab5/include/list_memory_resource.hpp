#include <cstddef>
#include <iostream>
#include <list>
#include <memory_resource>
#include <new>
#include <vector>

class ListMemoryResource : public std::pmr::memory_resource {
  private:
    std::list<void *> allocated_blocks;

  protected:
    // Allocate memory block
    void *do_allocate(size_t bytes, size_t alignment) override {
        void *ptr = ::operator new(bytes, std::align_val_t(alignment));
        allocated_blocks.push_back(ptr);
        return ptr;
    }

    // Deallocate memory block and mark it as free
    void do_deallocate(void *ptr, size_t bytes, size_t alignment) override {
        allocated_blocks.remove(ptr);
        ::operator delete(ptr, bytes, std::align_val_t(alignment));
    }

    // Check if the resource can handle specific allocation size/alignment
    // (basic always true)
    bool do_is_equal(
        const std::pmr::memory_resource &other) const noexcept override {
        return this == &other;
    }

  public:
    ~ListMemoryResource() {
        // Cleanup all remaining allocated blocks
        for (void *ptr : allocated_blocks) {
            ::operator delete(ptr);
        }
        allocated_blocks.clear();
    }

    // Public method to access the number of allocated blocks for testing
    size_t allocated_block_count() const { return allocated_blocks.size(); }
};
