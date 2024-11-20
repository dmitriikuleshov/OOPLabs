#pragma once

#include "polygonal.hpp"

template <Number T> 
class Octagon : public Polygonal<T> {
  public:
    Octagon();
    Octagon(const std::initializer_list<flat_vector<T>> &list);
    Octagon(const std::vector<flat_vector<T>> &vect);
    Octagon(const Octagon &other);
    Octagon(Octagon &&other) noexcept;
    Octagon &operator=(const Octagon &other);
    Octagon &operator=(Octagon &&other) noexcept;

  private:
    void validatePointsCount(size_t count) const;
};

template <Number T> 
Octagon<T>::Octagon() : Polygonal<T>() {}

template <Number T>
Octagon<T>::Octagon(const std::initializer_list<flat_vector<T>> &list)
    : Polygonal<T>(list) {
    validatePointsCount(this->points.size());
}

template <Number T>
Octagon<T>::Octagon(const std::vector<flat_vector<T>> &vect)
    : Polygonal<T>(vect) {
    validatePointsCount(this->points.size());
}

template <Number T>
Octagon<T>::Octagon(const Octagon &other) : Polygonal<T>(other) {}

template <Number T>
Octagon<T>::Octagon(Octagon &&other) noexcept
    : Polygonal<T>(std::move(other)) {}

template <Number T> 
Octagon<T> &Octagon<T>::operator=(const Octagon &other) {
    if (this != &other) {
        Polygonal<T>::operator=(other);
    }
    return *this;
}

template <Number T>
Octagon<T> &Octagon<T>::operator=(Octagon &&other) noexcept {
    if (this != &other) {
        Polygonal<T>::operator=(std::move(other));
    }
    return *this;
}

template <Number T> 
void Octagon<T>::validatePointsCount(size_t count) const {
    if (count != 8) {
        throw std::logic_error("Error: A Octagon must have exactly 6 points.");
    }
}