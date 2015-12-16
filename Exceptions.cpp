#include "Gaming.h"
#include "Exceptions.h"
#include <iostream>

Gaming::DimensionEx::DimensionEx(unsigned expWidth, unsigned expHeight, unsigned width, unsigned height): __exp_width(expWidth), __exp_height(expHeight), __width(width), __height(height) {

}

void Gaming::InsufficientDimensionsEx::__print_args(std::ostream &os) const {
    os << "minimum dimensions: " << getExpHeight() << ", " << getExpWidth() << ";" << "tried dimensions: " << getHeight() << ", " << getWidth();
}

Gaming::InsufficientDimensionsEx::InsufficientDimensionsEx(unsigned minWidth, unsigned minHeight, unsigned width, unsigned height): DimensionEx(minWidth, minHeight, width, height) {
    setName("InsufficientDimensionsEx");
}

void Gaming::OutOfBoundsEx::__print_args(std::ostream &os) const {
    os << "maximum dimensions: " << getExpHeight() << ", " << getExpWidth() << ";" << "tried dimensions: " << getHeight() << ", " << getWidth();
}

Gaming::OutOfBoundsEx::OutOfBoundsEx(unsigned maxWidth, unsigned maxHeight, unsigned width, unsigned height): DimensionEx(maxWidth, maxHeight, width, height) {
    setName("OutOfBoundsEx");
}
