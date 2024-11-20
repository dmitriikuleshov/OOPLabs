#pragma once

#include "polygonal.hpp"

template <Number T> 
class Pentagon : public Polygonal<T> {
  public:
    Pentagon();
    Pentagon(const std::initializer_list<flat_vector<T>> &list);
    Pentagon(const std::vector<flat_vector<T>> &vect);
    Pentagon(const Pentagon &other);
    Pentagon(Pentagon &&other) noexcept;
    Pentagon &operator=(const Pentagon &other);
    Pentagon &operator=(Pentagon &&other) noexcept;

  private:
    void validatePointsCount(size_t count) const;
};

template <Number T> 
Pentagon<T>::Pentagon() : Polygonal<T>() {}

template <Number T>
Pentagon<T>::Pentagon(const std::initializer_list<flat_vector<T>> &list)
    : Polygonal<T>(list) {
    validatePointsCount(this->points.size());
}

template <Number T>
Pentagon<T>::Pentagon(const std::vector<flat_vector<T>> &vect)
    : Polygonal<T>(vect) {
    validatePointsCount(this->points.size());
}

template <Number T>
Pentagon<T>::Pentagon(const Pentagon &other) : Polygonal<T>(other) {}

template <Number T>
Pentagon<T>::Pentagon(Pentagon &&other) noexcept
    : Polygonal<T>(std::move(other)) {}

template <Number T> 
Pentagon<T> &Pentagon<T>::operator=(const Pentagon &other) {
    if (this != &other) {
        Polygonal<T>::operator=(other);
    }
    return *this;
}

template <Number T>
Pentagon<T> &Pentagon<T>::operator=(Pentagon &&other) noexcept {
    if (this != &other) {
        Polygonal<T>::operator=(std::move(other));
    }
    return *this;
}

template <Number T> 
void Pentagon<T>::validatePointsCount(size_t count) const {
    if (count != 5) {
        throw std::logic_error("Error: A Pentagon must have exactly 6 points.");
    }
}