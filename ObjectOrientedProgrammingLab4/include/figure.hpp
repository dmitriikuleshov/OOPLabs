#pragma once

#include <iostream>
#include <utility>
#include <vector>

#include "flat_vector.hpp"

// --------------- HEADER ---------------

template <Number T> class Figure {
  public:
    virtual flat_vector<T> centroid() const = 0;

    virtual T area() const noexcept = 0;

    virtual operator double() const noexcept = 0;

    virtual ~Figure() = 0;

    friend std::istream &operator>>(std::istream &is, Figure<T> &figure) {
        figure.read_from_stream(is);
        return is;
    }

    friend std::ostream &operator<<(std::ostream &os, const Figure<T> &figure) {
        figure.print_in_stream(os);
        return os;
    }

  protected:
    virtual std::istream &read_from_stream(std::istream &in) = 0;

    virtual std::ostream &print_in_stream(std::ostream &out) const = 0;
};

// --------------- IMPLEMENTATION ---------------

template <Number T> Figure<T>::~Figure() {}