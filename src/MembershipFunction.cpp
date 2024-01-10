//
// Created by robos on 10/01/2024.
//

#include <stdexcept>
#include "MembershipFunction.h"
#include "cmath"
#include <cstring>

namespace Fuzzy {


    TriMF::TriMF(const char *name, float a, float b, float c, float peak) {
        // assert that a < b < c
        if (!(a < b && b < c)) {
            throw std::invalid_argument("Invalid arguments: should be a < b < c");
        }


        this->name = name;
        this->a = a;
        this->b = b;
        this->c = c;
        this->middle = b;
        this->width = fabsf(a - c); // fabsf is the floating point version of abs

        this->peak = peak;
    }

    TriMF::TriMF(const char *name, float middle, float width, float peak) {
        this->name = name;
        this->middle = middle;
        this->width = width;
        this->a = middle - width/2;
        this->b = middle;
        this->c = middle + width/2;

        this->peak = peak;
    }

    // Copy constructor
    TriMF::TriMF(const TriMF &other) {
        this->name = other.name;
        this->middle = other.middle;
        this->width = other.width;
        this->a = other.a;
        this->b = other.b;
        this->c = other.c;

        this->peak = other.peak;
    }

    // Assignment operator
    TriMF &TriMF::operator=(const TriMF &other) {
        this->name = other.name;
        this->middle = other.middle;
        this->width = other.width;
        this->a = other.a;
        this->b = other.b;
        this->c = other.c;

        this->peak = other.peak;
        return *this;
    }

    float TriMF::mu(float x) {
        if (x <= a || x >= c) { // Outside the triangle
            return 0;
        } else if (x <= b) {
            return peak * (x - a) / (b - a); // Rising edge
        } else {
            return peak * (c - x) / (c - b); // Falling edge
        }
    }

    const char *TriMF::toString() {
        return name;
    }
} // Fuzzy