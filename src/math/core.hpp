#pragma once

namespace math {
    template <typename T>
    T divEuclid(T const& a, T const& b) {
        T q = a / b;
        if (a % b < 0) {
            if (b > 0) {
                --q;
            } else {
                ++q;
            }
        }
        return q;
    }

    template <typename T>
    T remEuclid(T const& a, T const& b) {
        int r = a % b;
        if (r < 0) {
            r += std::abs(b);
        }
        return r;
    }
} // math