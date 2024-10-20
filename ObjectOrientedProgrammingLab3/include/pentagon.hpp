#pragma once

#include "polygonal.hpp"

class Pentagon : public Polygonal {
  public:
    Pentagon();
    Pentagon(const std::initializer_list<flat_vector> &list);
    Pentagon(const std::vector<flat_vector> &vect);
    Pentagon(const Pentagon &other);
    Pentagon(Pentagon &&other) noexcept;
    Pentagon &operator=(const Pentagon &other);
    Pentagon &operator=(Pentagon &&other) noexcept;

  private:
    void validatePointsCount(size_t count) const;
};