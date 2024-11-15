#include "list_memory_resource.hpp"
#include "pmr_queue.hpp"
#include <gtest/gtest.h>
#include <memory_resource>
#include <string>

TEST(PmrQueueTest, IntQueuePushAndFront) {
    ListMemoryResource memory_resource;
    PmrQueue<int> intQueue(&memory_resource);

    intQueue.push(10);
    intQueue.push(20);
    intQueue.push(30);

    EXPECT_EQ(intQueue.front(), 10);
}

TEST(PmrQueueTest, IntQueuePop) {
    ListMemoryResource memory_resource;
    PmrQueue<int> intQueue(&memory_resource);

    intQueue.push(10);
    intQueue.push(20);
    intQueue.pop();
    EXPECT_EQ(intQueue.front(), 20);

    intQueue.pop();
    EXPECT_TRUE(intQueue.empty());
}

TEST(PmrQueueTest, IntQueueIterator) {
    ListMemoryResource memory_resource;
    PmrQueue<int> intQueue(&memory_resource);

    intQueue.push(1);
    intQueue.push(2);
    intQueue.push(3);

    int expected_value = 1;
    for (auto it = intQueue.begin(); it != intQueue.end(); ++it) {
        EXPECT_EQ(*it, expected_value);
        expected_value++;
    }
}

TEST(PmrQueueTest, IntQueueEmpty) {
    ListMemoryResource memory_resource;
    PmrQueue<int> intQueue(&memory_resource);

    EXPECT_TRUE(intQueue.empty());
}

struct ComplexType {
    int id;
    std::string name;
    double value;

    ComplexType(int id, const std::string &name, double value)
        : id(id), name(name), value(value) {}

    bool operator==(const ComplexType &other) const {
        return id == other.id && name == other.name && value == other.value;
    }
};

TEST(PmrQueueTest, ComplexTypeQueuePushAndFront) {
    ListMemoryResource memory_resource;
    PmrQueue<ComplexType> complexQueue(&memory_resource);

    ComplexType item1(1, "Item1", 10.5);
    ComplexType item2(2, "Item2", 20.75);

    complexQueue.push(item1);
    complexQueue.push(item2);

    EXPECT_EQ(complexQueue.front(), item1);
}

TEST(PmrQueueTest, ComplexTypeQueuePopAndReuse) {
    ListMemoryResource memory_resource;
    PmrQueue<ComplexType> complexQueue(&memory_resource);

    ComplexType item1(1, "Item1", 10.5);
    ComplexType item2(2, "Item2", 20.75);

    complexQueue.push(item1);
    complexQueue.push(item2);
    complexQueue.pop();

    EXPECT_EQ(complexQueue.front(), item2);

    complexQueue.pop();
    EXPECT_TRUE(complexQueue.empty());
}

TEST(PmrQueueTest, ComplexTypeQueueIterator) {
    ListMemoryResource memory_resource;
    PmrQueue<ComplexType> complexQueue(&memory_resource);

    ComplexType item1(1, "Item1", 10.5);
    ComplexType item2(2, "Item2", 20.75);
    ComplexType item3(3, "Item3", 30.0);

    complexQueue.push(item1);
    complexQueue.push(item2);
    complexQueue.push(item3);

    ComplexType expected_items[] = {item1, item2, item3};
    int i = 0;
    for (auto it = complexQueue.begin(); it != complexQueue.end(); ++it) {
        EXPECT_EQ(*it, expected_items[i]);
        i++;
    }
}

TEST(PmrQueueTest, MemoryResourceCleanupOnDestruction) {
    ListMemoryResource memory_resource;
    {
        PmrQueue<int> tempQueue(&memory_resource);
        tempQueue.push(1);
        tempQueue.push(2);
    } // Queue goes out of scope and should free all memory

    // Verify that all allocated memory blocks have been cleared after
    // destruction of the queue
    EXPECT_EQ(memory_resource.allocated_block_count(), 0);
}
