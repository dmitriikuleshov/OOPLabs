#pragma once

#include "figure.hpp"
#include "flat_vector.hpp"
#include <cmath>
#include <list>
#include <vector>

const int COLLINEAR = 0;
const int CLOCKWISE = 1;
const int COUNTER_CLOCKWISE = 2;

int orientation(flat_vector p, flat_vector q, flat_vector r);

class Polygonal : public Figure {
  public:
    std::vector<flat_vector> points;

    // Constructors

    Polygonal();

    Polygonal(const std::initializer_list<flat_vector> &list);

    Polygonal(const std::vector<flat_vector> &vect);

    Polygonal(const Polygonal &other);

    Polygonal(Polygonal &&other) noexcept;

    // Copy Assignment Operator

    Polygonal &operator=(const Polygonal &other);

    // Move Assignment Operator

    Polygonal &operator=(Polygonal &&other) noexcept;

    // Comparison

    bool operator==(const Polygonal &other) const noexcept;

    // Calculation functions

    virtual flat_vector centroid() const override;

    virtual double area() const noexcept override;

    virtual operator double() const noexcept override;

    virtual ~Polygonal() = default;

  private:
    void jarvisMatch();

    void removeDuplicatePoints();

    bool allPointsAreOnTheSameLine();

  protected:
    // Stream operators

    virtual std::istream &read_from_stream(std::istream &);

    virtual std::ostream &print_in_stream(std::ostream &) const;
};
