#include "flat_vector.hpp"
#include "hexagon.hpp"
#include "polygonal.hpp"
#include <gtest/gtest.h>
#include <iostream>

// Constructor Tests
TEST(InitializationTest, DefaultConstructor) {
    Polygonal poly;
    EXPECT_TRUE(poly.points.empty());
}

TEST(InitializationTest, InitializerListConstructor_Valid) {
    Polygonal poly{{0, 0}, {1, 1}, {0, 2}};
    EXPECT_EQ(poly.points.size(), 3);
}

TEST(InitializationTest, InitializerListConstructor_Invalid) {
    EXPECT_THROW(Polygonal({flat_vector(0, 0), flat_vector(1, 1)}),
                 std::invalid_argument);
}

TEST(InitializationTest, VectorConstructor_Valid) {
    std::vector<flat_vector> vect = {{0, 0}, {1, 1}, {0, 2}};
    Polygonal poly(vect);
    EXPECT_EQ(poly.points.size(), 3);
}

TEST(InitializationTest, VectorConstructor_Invalid) {
    std::vector<flat_vector> vect = {{0, 0}, {1, 1}};
    EXPECT_THROW(Polygonal poly(vect), std::invalid_argument);
}

TEST(InitializationTest, CopyConstructor) {
    Polygonal poly{{0, 0}, {1, 1}, {0, 2}};
    Polygonal poly_copy(poly);
    EXPECT_EQ(poly_copy.points, poly.points);
}

TEST(InitializationTest, MoveConstructor) {
    Polygonal poly{{0, 0}, {1, 1}, {0, 2}};
    Polygonal poly_move(std::move(poly));
    EXPECT_EQ(poly_move.points.size(), 3);
    EXPECT_TRUE(poly.points.empty());
}

TEST(InitializationTest, CopyAssignment) {
    Polygonal poly1{{0, 0}, {1, 1}, {0, 2}};
    Polygonal poly2 = poly1;
    EXPECT_EQ(poly2.points, poly1.points);
}

TEST(InitializationTest, MoveAssignment) {
    Polygonal poly1{{0, 0}, {1, 1}, {0, 2}};
    Polygonal poly2;
    poly2 = std::move(poly1);
    EXPECT_EQ(poly2.points.size(), 3);
    EXPECT_TRUE(poly1.points.empty());
}

TEST(InitializationTest, JarvisMatchValid) {
    Polygonal poly({flat_vector(0, 0), flat_vector(4, 4), flat_vector(4, 0),
                    flat_vector(2, 2)});
    std::vector<flat_vector> expected_points = {
        flat_vector(0, 0), flat_vector(4, 0), flat_vector(4, 4)};
    EXPECT_EQ(poly.points, expected_points);
}

TEST(InitializationTest, JarvisMatchDotsOnTheSameLine) {
    EXPECT_THROW(Polygonal poly({flat_vector(0, 0), flat_vector(4, 4),
                                 flat_vector(1, 1), flat_vector(-1, -1)}),
                 std::logic_error);
}

// Calculation Tests
void runCalculationTest(std::vector<flat_vector> &points, double expected_area,
                        flat_vector expected_centroid) {
    Polygonal p(points);
    ASSERT_NEAR(p.area(), expected_area, 1e-2);
    ASSERT_NEAR(p.centroid().x, expected_centroid.x, 1e-2);
    ASSERT_NEAR(p.centroid().y, expected_centroid.y, 1e-2);
}

TEST(CalculationTest, CalculationTest1) {
    std::vector<flat_vector> p{{1, 1}, {4, 1}, {2, 5}};
    runCalculationTest(p, 6.0, flat_vector(2.33, 2.33));
}

TEST(CalculationTest, CalculationTest2) {
    std::vector<flat_vector> p{{0, 0}, {4, 0}, {4, 3}, {0, 3}};
    runCalculationTest(p, 12.0, flat_vector(2.0, 1.5));
}

TEST(CalculationTest, CalculationTest3) {
    std::vector<flat_vector> p{{1, 1}, {3, 1}, {4, 3}, {2, 5}, {0, 3}};
    runCalculationTest(p, 10, flat_vector(2.0, 2.6));
}

TEST(CalculationTest, CalculationTest4) {
    std::vector<flat_vector> p{{0, 0}, {4, 0}, {6, 2}, {5, 5}, {3, 6}, {1, 4}};
    runCalculationTest(p, 24.5, flat_vector(3.17, 2.83));
}

TEST(CalculationTest, CalculationTest5) {
    std::vector<flat_vector> p{{1, 1}, {5, 1}, {7, 3}, {6, 6},
                               {4, 7}, {2, 6}, {0, 4}};
    runCalculationTest(p, 30, flat_vector(3.57, 4.0));
}

TEST(CalculationTest, CalculationTest6) {
    std::vector<flat_vector> p{{2, 0}, {5, 0}, {7, 2}, {6, 5},
                               {4, 7}, {2, 6}, {0, 4}, {1, 2}};
    runCalculationTest(p, 32.5, flat_vector(3.71, 3.43));
}

// (0, 2), (1, 1) are not in hull
TEST(CalculationTest, CalculationTest7) {
    std::vector<flat_vector> p{{1, 0}, {4, 0},  {6, 2}, {5, 5}, {3, 6},
                               {1, 5}, {-1, 3}, {0, 2}, {1, 1}};
    runCalculationTest(p, 28.5, flat_vector(2.71, 3.0));
}

TEST(CalculationTest, CalculationTest8) {
    std::vector<flat_vector> p{{0, 0}, {3, 0}, {5, 1}, {6, 3},  {5, 5},
                               {4, 6}, {2, 7}, {0, 6}, {-1, 4}, {-1, 2}};
    runCalculationTest(p, 36.5, flat_vector(2.3, 3.4));
}

// (2, 2), (3, 2) are not in hull
TEST(CalculationTest, CalculationTest9) {
    std::vector<flat_vector> p{{0, 0}, {5, 0}, {5, 4}, {0, 4}, {2, 2}, {3, 2}};
    runCalculationTest(p, 20.0, flat_vector(2.5, 2.0));
}

TEST(CalculationTest, CalculationTest10) {
    std::vector<flat_vector> p{{1, 1}, {5, 1}, {6, 3}, {4, 5}, {2, 4}};
    runCalculationTest(p, 13.5, flat_vector(3.6, 2.8));
}

// Hexagon Tests
TEST(HexagonTest, Empty) {
    Hexagon h;
    EXPECT_TRUE(h.points.empty());
}

TEST(HexagonTest, TooFewPoints_Invalid) {
    EXPECT_THROW(
        Hexagon h({flat_vector{1, 1}, flat_vector{5, 1}, flat_vector{6, 3},
                   flat_vector{4, 5}, flat_vector{2, 4}}),
        std::logic_error);
}

TEST(HexagonTest, Initialization_Valid) {
    EXPECT_NO_THROW(
        Hexagon h({flat_vector{1, 1}, flat_vector{5, 1}, flat_vector{6, 3},
                   flat_vector{4, 5}, flat_vector{2, 4}, flat_vector{3, 0}}));
}

TEST(HexagonTest, PointInsideHull_Invalid) {
    EXPECT_THROW(
        Hexagon h({flat_vector{1, 1}, flat_vector{5, 1}, flat_vector{6, 3},
                   flat_vector{4, 5}, flat_vector{2, 4}, flat_vector{3, 2}}),
        std::logic_error);
}

TEST(HexagonTest, CopyConstructor) {
    Hexagon h1{{1, 1}, {5, 1}, {6, 3}, {4, 5}, {2, 4}, {3, 0}};
    Hexagon h2(h1);
    EXPECT_EQ(h1.points, h2.points);
}

TEST(HexagonTest, MoveConstructor) {
    Hexagon h{{1, 1}, {5, 1}, {6, 3}, {4, 5}, {2, 4}, {3, 0}};
    Hexagon h_move(std::move(h));
    EXPECT_EQ(h_move.points.size(), 6);
    EXPECT_TRUE(h.points.empty());
}

TEST(HexagonTest, CopyAssignment) {
    Hexagon h1{{1, 1}, {5, 1}, {6, 3}, {4, 5}, {2, 4}, {3, 0}};
    Hexagon h2{{1, 1}, {5, 1}, {6, 3}, {4, 5}, {2, 4}, {3, -1}};
    h1 = h2;
    EXPECT_EQ(h1.points, h2.points);
}

TEST(HexagonTest, MoveAssignment) {
    Hexagon h1{{1, 1}, {5, 1}, {6, 3}, {4, 5}, {2, 4}, {3, 0}};
    Hexagon h2;
    h2 = std::move(h1);
    EXPECT_EQ(h2.points.size(), 6);
    EXPECT_TRUE(h1.points.empty());
}

TEST(HexagonTest, CalculationTest) {
    Hexagon h{{1, 1}, {5, 1}, {6, 3}, {4, 5}, {2, 4}, {3, 0}};
    ASSERT_NEAR(h.area(), 15.5, 1e-2);
}

int main(int argc, char **argv) {

    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}