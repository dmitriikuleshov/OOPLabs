#pragma once

#include "polygonal.hpp"

template <Number T> 
class Hexagon : public Polygonal<T> {
  public:
    Hexagon();
    Hexagon(const std::initializer_list<flat_vector<T>> &list);
    Hexagon(const std::vector<flat_vector<T>> &vect);
    Hexagon(const Hexagon &other);
    Hexagon(Hexagon &&other) noexcept;
    Hexagon &operator=(const Hexagon &other);
    Hexagon &operator=(Hexagon &&other) noexcept;

  private:
    void validatePointsCount(size_t count) const;
};

template <Number T> 
Hexagon<T>::Hexagon() : Polygonal<T>() {}

template <Number T>
Hexagon<T>::Hexagon(const std::initializer_list<flat_vector<T>> &list)
    : Polygonal<T>(list) {
    validatePointsCount(this->points.size());
}

template <Number T>
Hexagon<T>::Hexagon(const std::vector<flat_vector<T>> &vect)
    : Polygonal<T>(vect) {
    validatePointsCount(this->points.size());
}

template <Number T>
Hexagon<T>::Hexagon(const Hexagon &other) : Polygonal<T>(other) {}

template <Number T>
Hexagon<T>::Hexagon(Hexagon &&other) noexcept
    : Polygonal<T>(std::move(other)) {}

template <Number T> 
Hexagon<T> &Hexagon<T>::operator=(const Hexagon &other) {
    if (this != &other) {
        Polygonal<T>::operator=(other);
    }
    return *this;
}

template <Number T>
Hexagon<T> &Hexagon<T>::operator=(Hexagon &&other) noexcept {
    if (this != &other) {
        Polygonal<T>::operator=(std::move(other));
    }
    return *this;
}

template <Number T> 
void Hexagon<T>::validatePointsCount(size_t count) const {
    if (count != 6) {
        throw std::logic_error("Error: A Hexagon must have exactly 6 points.");
    }
}