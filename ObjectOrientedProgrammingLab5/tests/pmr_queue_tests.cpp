#include "list_memory_resource.hpp"
#include "pmr_queue.hpp"
#include <gtest/gtest.h>

// ListMemoryResource Tests
TEST(ListMemoryResourceTest, AllocateDeallocate) {
    ListMemoryResource resource;

    void *ptr1 = resource.allocate(64);
    void *ptr2 = resource.allocate(128);
    EXPECT_EQ(resource.allocated_block_count(), 2);

    resource.deallocate(ptr1, 64);
    resource.deallocate(ptr2, 128);
    EXPECT_EQ(resource.allocated_block_count(), 0);
}

TEST(ListMemoryResourceTest, DestructorCleansUp) {
    {
        ListMemoryResource resource;
        void *ptr1 = resource.allocate(64);
        void *ptr2 = resource.allocate(128);
        EXPECT_EQ(resource.allocated_block_count(), 2);
    }
}

// PmrQueue Tests
TEST(PmrQueueTest, PushPop) {
    ListMemoryResource resource;
    PmrQueue<int, std::pmr::polymorphic_allocator<int>> queue{&resource};

    queue.push(10);
    queue.push(20);
    queue.push(30);

    EXPECT_EQ(queue.front(), 10);

    queue.pop();
    EXPECT_EQ(queue.front(), 20);

    queue.pop();
    EXPECT_EQ(queue.front(), 30);

    queue.pop();
    EXPECT_TRUE(queue.empty());
}

TEST(PmrQueueTest, Clear) {
    ListMemoryResource resource;
    PmrQueue<int, std::pmr::polymorphic_allocator<int>> queue{&resource};

    queue.push(10);
    queue.push(20);
    queue.push(30);
    queue.clear();

    EXPECT_TRUE(queue.empty());
}

TEST(PmrQueueTest, Iteration) {
    ListMemoryResource resource;
    PmrQueue<int, std::pmr::polymorphic_allocator<int>> queue{&resource};

    queue.push(10);
    queue.push(20);
    queue.push(30);

    int expected[] = {10, 20, 30};
    int i = 0;
    for (auto it = queue.begin(); it != queue.end(); ++it) {
        EXPECT_EQ(*it, expected[i++]);
    }
}

TEST(PmrQueueTest, CopyConstructor) {
    ListMemoryResource resource;
    PmrQueue<int, std::pmr::polymorphic_allocator<int>> queue1{&resource};
    queue1.push(10);
    queue1.push(20);

    PmrQueue<int, std::pmr::polymorphic_allocator<int>> queue2 = queue1;

    EXPECT_EQ(queue2.front(), 10);
    queue2.pop();
    EXPECT_EQ(queue2.front(), 20);
}

TEST(PmrQueueTest, MoveConstructor) {
    ListMemoryResource resource;
    PmrQueue<int, std::pmr::polymorphic_allocator<int>> queue1{&resource};
    queue1.push(10);
    queue1.push(20);

    PmrQueue<int, std::pmr::polymorphic_allocator<int>> queue2 =
        std::move(queue1);

    EXPECT_EQ(queue2.front(), 10);
    queue2.pop();
    EXPECT_EQ(queue2.front(), 20);
    EXPECT_TRUE(queue1.empty());
}

TEST(PmrQueueTest, ComplexType) {
    struct Complex {
        int a;
        double b;
        std::string c;

        bool operator==(const Complex &other) const {
            return a == other.a && b == other.b && c == other.c;
        }
    };

    ListMemoryResource resource;
    PmrQueue<Complex, std::pmr::polymorphic_allocator<Complex>> queue{
        &resource};

    queue.push({1, 1.1, "one"});
    queue.push({2, 2.2, "two"});

    Complex expected[] = {{1, 1.1, "one"}, {2, 2.2, "two"}};
    int i = 0;
    for (auto it = queue.begin(); it != queue.end(); ++it) {
        EXPECT_EQ(*it, expected[i++]);
    }
}

TEST(PmrQueueTest, BackInsertionAndAccess) {
    ListMemoryResource resource;
    PmrQueue<int, std::pmr::polymorphic_allocator<int>> queue{&resource};

    queue.push(1);
    queue.push(2);
    queue.push(3);

    EXPECT_EQ(queue.front(), 1);
    queue.pop();
    EXPECT_EQ(queue.front(), 2);
}

int main(int argc, char **argv) {

    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}