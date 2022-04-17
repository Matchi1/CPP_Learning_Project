#pragma once

#include <algorithm>
#include <cassert>
#include <iostream>

template <size_t Size, typename ElementType>
class Point
{
public:

    std::array<ElementType, Size> values;

    Point() = default;

    template <typename... elements>
    Point(ElementType first, elements&&... rest)
        : values { first, rest... } {
            constexpr size_t size = sizeof...(rest);
            static_assert(Size == size + 1);
        }

    ElementType& x() { return values[0]; }
    ElementType x() const { return values[0]; }

    ElementType& y()
    {
        static_assert(Size >= 2);
        return values[1];
    }

    ElementType y() const
    {
        static_assert(Size >= 2);
        return values[1];
    }

    ElementType& z()
    {
        static_assert(Size >= 3);
        return values[2];
    }

    ElementType z() const
    {
        static_assert(Size >= 3);
        return values[2];
    }

    Point& operator+=(const Point& other)
    {
        std::transform(values.begin(), values.end(), other.values.begin(), values.begin(),
                       std::plus<float>());
        return *this;
    }

    Point& operator-=(const Point& other)
    {
        std::transform(values.begin(), values.end(), other.values.begin(), values.begin(),
                       std::minus<float>());
        return *this;
    }

    Point& operator*=(const float scalar)
    {
        std::transform(values.begin(), values.end(), values.begin(),
                       [scalar](float value) -> float { return value * scalar; });
        return *this;
    }

    Point& operator*=(const Point& other)
    {
        std::transform(values.begin(), values.end(), other.values.begin(), values.begin(),
                std::multiplies<ElementType>());
        return *this;
    }

    Point operator+(const Point& other) const
    {
        Point result = *this;
        result += other;
        return result;
    }

    Point operator-(const Point& other) const
    {
        Point result = *this;
        result -= other;
        return result;
    }

    Point operator-() const { return Point { -x(), -y(), -z() }; }

    Point operator*(const float scalar) const
    {
        Point result = *this;
        result *= scalar;
        return result;
    }

    Point operator*(const Point& other) const
    {
        Point result = *this;
        result *= other;
        return result;
    }

    float length() const
    {
        return std::sqrt(std::inner_product(values.begin(), values.end(), values.begin(), 0.));
    }

    float distance_to(const Point& other) const { return (*this - other).length(); }

    Point& normalize(const float target_len = 1.0f)
    {
        const float current_len = length();
        if (current_len == 0)
        {
            throw std::logic_error("cannot normalize vector of length 0");
        }

        *this *= (target_len / current_len);
        return *this;
    }

    Point& cap_length(const float max_len)
    {
        assert(max_len > 0);

        const float current_len = length();
        if (current_len > max_len)
        {
            *this *= (max_len / current_len);
        }

        return *this;
    }
};
