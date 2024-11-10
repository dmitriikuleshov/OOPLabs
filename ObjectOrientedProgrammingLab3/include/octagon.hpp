#pragma once

#include "polygonal.hpp"

class Octagon : public Polygonal {
  public:
    Octagon();
    Octagon(const std::initializer_list<flat_vector> &list);
    Octagon(const std::vector<flat_vector> &vect);
    Octagon(const Octagon &other);
    Octagon(Octagon &&other) noexcept;
    Octagon &operator=(const Octagon &other);
    Octagon &operator=(Octagon &&other) noexcept;

  private:
    void validatePointsCount(size_t count) const;
};