#include "vec2.hpp"

#include <stdexcept>


vec2::vec2()
    : x(0), y(0)
{}

vec2::vec2(int _x, int _y)
    : x(_x), y(_y)
{}

vec2::vec2(const vec2& v)
    : x(v.x), y(v.y)
{}

void vec2::Add(const vec2& v)
{
    x += v.x;
    y += v.y;
}

vec2 vec2::Center() const
{
    return vec2(x / 2, y / 2);
}

const vec2 vec2::operator+(const vec2& v) const
{
    return vec2(x + v.x, y + v.y);
}

const vec2 vec2::operator-(const vec2& v) const
{
    return vec2(x - v.x, y - v.y);
}

const vec2 vec2::operator*(int value) const
{
    return vec2(x * value, y * value);
}

const vec2 vec2::operator/(int value) const
{
    if (value == 0) {
        throw std::runtime_error("Zero division");
    }
    return vec2(x / value, y / value);
}

vec2& vec2::operator+=(const vec2& v)
{
    x += v.x;
    y += v.y;
    return *this;
}

vec2& vec2::operator-=(const vec2& v)
{
    x -= v.x;
    y -= v.y;
    return *this;
}

vec2& vec2::operator*=(int value)
{
    x *= value;
    y *= value;
    return *this;
}

vec2& vec2::operator/=(int value)
{
    if (value == 0) {
        throw std::runtime_error("Zero division");
    }
    x /= value;
    y /= value;
    return *this;
}

bool vec2::operator==(const vec2& v) const
{
    return (x == v.x && y == v.y);
}

bool vec2::operator!=(const vec2& v) const
{
    return (x != v.x || y != v.y);
}

const vec2 operator*(float value, const vec2& v)
{
    return vec2(v.x * value, v.y * value);
}

