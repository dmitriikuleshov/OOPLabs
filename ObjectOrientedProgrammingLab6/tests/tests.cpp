#include <gtest/gtest.h>

#include "dragon.h"
#include "frog.h"
#include "knight.h"
#include "npc.h"
#include "visitor.h"

TEST(NPCTest, IsCloseTest) {
    auto knight = std::make_shared<Knight>("Knight1", 0, 14);
    auto frog = std::make_shared<Frog>("Frog1", 40, 11);
    auto dragon = std::make_shared<Dragon>("Dragon1", 88, 15);

    ASSERT_TRUE(knight->is_close(frog, 50));
    ASSERT_TRUE(frog->is_close(dragon, 100));
    ASSERT_FALSE(dragon->is_close(knight, 25));
}

TEST(NPCTest, AcceptTest) {
    auto knight = std::make_shared<Knight>("Knight1", 0, 14);
    auto frog = std::make_shared<Frog>("Frog1", 40, 11);
    auto dragon = std::make_shared<Dragon>("Dragon1", 88, 15);

    ASSERT_TRUE(dragon->accept(knight));
    ASSERT_FALSE(knight->accept(knight));
    ASSERT_FALSE(frog->accept(knight));

    ASSERT_TRUE(knight->accept(dragon));
    ASSERT_FALSE(dragon->accept(dragon));
    ASSERT_FALSE(frog->accept(dragon));

    ASSERT_TRUE(knight->accept(frog));
    ASSERT_TRUE(dragon->accept(frog));
    ASSERT_TRUE(frog->accept(frog));
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}