#include <gtest/gtest.h>

#include "attacker_visitors.hpp"
#include "dragon.hpp"
#include "frog.hpp"
#include "knight.hpp"
#include "npc.hpp"
#include <filesystem>

auto config =
    NpcPropertiesConfigHandler::create_config(getenv("NPC_PROPERTIES_CONFIG"));

TEST(NPCTest, IsCloseTest) {

    auto knight = Knight::create("Knight1", 0, 14);
    auto frog = Frog::create("Frog1", 40, 11);
    auto dragon = Dragon::create("Dragon1", 88, 15);

    knight->set_kill_distance(50);
    frog->set_kill_distance(100);
    dragon->set_kill_distance(25);

    ASSERT_TRUE(knight->is_close(frog));
    ASSERT_TRUE(frog->is_close(dragon));
    ASSERT_FALSE(dragon->is_close(knight));
}

TEST(NPCTest, AcceptTestDragon) {
    auto knight = Knight::create("Knight1", 10, 10);
    auto frog = Frog::create("Frog1", 40, 11);
    auto dragon = Dragon::create("Dragon1", 88, 15);

    auto dragon_visitor = DragonAttackerVisitor::create(config);

    knight->accept(dragon_visitor);
    dragon->accept(dragon_visitor);
    frog->accept(dragon_visitor);

    ASSERT_TRUE(frog->is_alive());
    ASSERT_TRUE(dragon->is_alive());
    ASSERT_FALSE(knight->is_alive());
}

TEST(NPCTest, AcceptTestKnight) {
    auto knight = Knight::create("Knight1", 10, 10);
    auto frog = Frog::create("Frog1", 40, 11);
    auto dragon = Dragon::create("Dragon1", 88, 15);

    auto knight_visitor = KnightAttackerVisitor::create(config);

    knight->accept(knight_visitor);
    dragon->accept(knight_visitor);
    frog->accept(knight_visitor);

    ASSERT_TRUE(frog->is_alive());
    ASSERT_FALSE(dragon->is_alive());
    ASSERT_TRUE(knight->is_alive());
}

TEST(NPCTest, AcceptTestFrog) {
    auto knight = Knight::create("Knight1", 10, 10);
    auto frog = Frog::create("Frog1", 40, 11);
    auto dragon = Dragon::create("Dragon1", 88, 15);

    auto frog_visitor = FrogAttackerVisitor::create(config);

    knight->accept(frog_visitor);
    dragon->accept(frog_visitor);
    frog->accept(frog_visitor);

    ASSERT_FALSE(frog->is_alive());
    ASSERT_FALSE(dragon->is_alive());
    ASSERT_FALSE(knight->is_alive());
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}