#include <cstddef>
#include <iostream>
#include <list>
#include <memory_resource>
#include <new>
#include <stack>
#include <vector>

class ListMemoryResource : public std::pmr::memory_resource {
  private:
    std::stack<void *> free_blocks;
    std::list<void *> allocated_blocks;

  protected:
    // Allocate memory block
    void *do_allocate(size_t bytes, size_t alignment) override {
        if (!free_blocks.empty()) {
            void *ptr = free_blocks.top();
            free_blocks.pop();
            allocated_blocks.push_back(ptr);
            return ptr;
        }
        void *ptr = ::operator new(bytes, std::align_val_t(alignment));
        allocated_blocks.push_back(ptr);
        return ptr;
    }

    // Deallocate memory block and mark it as free
    void do_deallocate(void *ptr, size_t bytes, size_t alignment) override {
        free_blocks.push(ptr);
        allocated_blocks.remove(ptr);
    }

    // Check if the resource can handle specific allocation size/alignment
    bool do_is_equal(
        const std::pmr::memory_resource &other) const noexcept override {
        return this == &other;
    }

  public:
    ~ListMemoryResource() {
        while (!free_blocks.empty()) {
            ::operator delete(free_blocks.top());
            free_blocks.pop();
        }
        for (void *ptr : allocated_blocks) {
            ::operator delete(ptr);
        }
        allocated_blocks.clear();
    }

    // Public method to access the number of allocated blocks for testing
    size_t allocated_block_count() const { return allocated_blocks.size(); }

    size_t free_block_count() const { return free_blocks.size(); }
};
