#ifndef vec2_hpp
#define vec2_hpp

struct vec2
{
    int x;
    int y;

    vec2();
    vec2(int x, int y);
    vec2(const vec2& v);

    void    Add(const vec2& v);
    vec2    Center() const;

    const vec2  operator+(const vec2& v) const;
    const vec2  operator-(const vec2& v) const;
    const vec2  operator*(int value) const;
    const vec2  operator/(int value) const;

    vec2&       operator+=(const vec2& v);
    vec2&       operator-=(const vec2& v);
    vec2&       operator*=(int value);
    vec2&       operator/=(int value);

    bool    operator==(const vec2& v) const;
    bool    operator!=(const vec2& v) const;

    friend const vec2 operator*(float value, const vec2& v);

};

#endif /* vec2_hpp */

