#include "DrawingVector.hpp"


// 指定した座標の色情報を取得する
int GetColor(const vec2& pos)
{
    return GetColor(pos.x, pos.y);
}

// 点の描画
void DrawPoint(const vec2& pos, int color)
{
    DrawPoint(pos.x, pos.y, color);
}

// 直線の描画
void DrawLine(const vec2& p1, const vec2& p2, int color)
{
    DrawLine(p1.x, p1.y, p2.x, p2.y, color);
}

// 三角形の描画
void DrawTriangle(const vec2& p1, const vec2& p2, const vec2& p3, int color)
{
    DrawTriangle(p1.x, p1.y, p2.x, p2.y, p3.x, p3.y, color);
}

// 三角形の塗りつぶし
void FillTriangle(const vec2& p1, const vec2& p2, const vec2& p3, int color)
{
    FillTriangle(p1.x, p1.y, p2.x, p2.y, p3.x, p3.y, color);
}

// 円の描画
void DrawCircle(const vec2& center, int radius, int color)
{
    DrawCircle(center.x, center.y, radius, color);
}

// 円の描画（開始角度、終了角度を指定）
void DrawCircle(const vec2& center, int radius, int color, float startAngleRad, float endAngleRad)
{
    DrawCircle(center.x, center.y, radius, color, startAngleRad, endAngleRad);
}

// 円の塗りつぶし
void FillCircle(const vec2& center, int radius, int color)
{
    FillCircle(center.x, center.y, radius, color);
}

// 円の塗りつぶし
void FillCircle(const vec2& center, int radius, int color, float startAngleRad, float endAngleRad)
{
    FillCircle(center.x, center.y, radius, color, startAngleRad, endAngleRad);
}

// 矩形の描画
void DrawRect(const vec2& origin, const vec2& size, int color)
{
    DrawRect(origin.x, origin.y, size.x, size.y, color);
}

// 矩形の塗りつぶし
void FillRect(const vec2& origin, const vec2& size, int color)
{
    FillRect(origin.x, origin.y, size.x, size.y, color);
}

// 境界色を指定して塗りつぶし
void Paint(const vec2& pos, int paintColor, int borderColor)
{
    Paint(pos.x, pos.y, paintColor, borderColor);
}

// パターンの描画
void DrawPattern(unsigned int *buffer, const vec2& pos)
{
    DrawPattern(buffer, pos.x, pos.y);
}

// 文字の描画
void DrawCharacter(char c, const vec2& pos, int color)
{
    DrawCharacter(c, pos.x, pos.y, color);
}

// 文字列の描画
void DrawText(const char *str, const vec2& pos, int color)
{
    DrawText(str, pos.x, pos.y, color);
}

// スクロール処理
void Scroll(const vec2& size)
{
    Scroll(size.x, size.y);
}

// マウスカーソルのY座標を取得する
vec2 GetMouse()
{
    return vec2(GetMouseX(), GetMouseY());
}


