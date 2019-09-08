#ifndef DrawingVector_hpp
#define DrawingVector_hpp

#include "Drawing.hpp"
#include "vec2.hpp"

/**
    指定した座標の色を取得します。
    @param  pos 色を取得する座標
    @return 0xRRGGBB形式の数値
 */
int     GetColor(const vec2& pos);

/**
    指定した座標に点を描画します。
    @param  pos 点を描画する座標
    @param  color   描画色（0xRRGGBB形式の数値か、kColorRedなどの定数）
 */
void    DrawPoint(const vec2& pos, int color);

/**
    指定した2点の座標を結ぶ直線を描画します。
    @param  p1  始点の座標
    @param  p2  終点の座標
    @param  color   描画色（0xRRGGBB形式の数値か、kColorRedなどの定数）
 */
void    DrawLine(const vec2& p1, const vec2& p2, int color);

/**
    指定した3点の座標を結ぶ三角形を描画します。
    @param  p1  点1の座標
    @param  p2  点2の座標
    @param  p3  点3の座標
    @param  color   描画色（0xRRGGBB形式の数値か、kColorRedなどの定数）
 */
void    DrawTriangle(const vec2& p1, const vec2& p2, const vec2& p3, int color);

/**
    指定した3点の座標を結ぶ三角形を塗りつぶします。
    @param  p1  点1の座標
    @param  p2  点2の座標
    @param  p3  点3の座標
    @param  color   描画色（0xRRGGBB形式の数値か、kColorRedなどの定数）
 */
void    FillTriangle(const vec2& p1, const vec2& p2, const vec2& p3, int color);

/**
    指定した座標から指定した大きさの四角形を描画します。
    @param  origin  始点の座標
    @param  size    四角形の大きさ
 */
void    DrawRect(const vec2& origin, const vec2& size, int color);

/**
    指定した座標から指定した大きさの四角形を塗りつぶします。
    @param  origin  始点の座標
    @param  size    四角形の大きさ
 */
void    FillRect(const vec2& origin, const vec2& size, int color);


/**
    指定した中心点と半径で円を描画します。
    @param  center  中心点の座標
    @param  radius  半径
    @param  color   描画色（0xRRGGBB形式の数値か、kColorRedなどの定数）
 */
void    DrawCircle(const vec2& center, int radius, int color);

// TODO: 正円の縦横比を変えて楕円を描画するための引数をDrawCircle()関数に追加する。

/**
    指定した中心点と半径、開始角度と終了角度をラジアン単位で指定して、円弧を描画します。
    角度は-πから+πの範囲に修正された上で比較されます。
    0〜5/2πが指定された場合、これは0〜1/2πが指定されたことになりますので、第1象限の90度の円弧が描画されます。
    @param  center  中心点の座標
    @param  radius  半径
    @param  color   描画色（0xRRGGBB形式の数値か、kColorRedなどの定数）
    @param  startAngleRad   円弧の描画の開始角度（ラジアン単位）
    @param  endAngleRad     円弧の描画の終了角度（ラジアン単位）
 */
void    DrawCircle(const vec2& center, int radius, int color, float startAngleRad, float endAngleRad);

/**
    指定した中心点と半径で円を塗りつぶします。
    @param  center  中心点の座標
    @param  radius  半径
    @param  color   描画色（0xRRGGBB形式の数値か、kColorRedなどの定数）
 */
void    FillCircle(const vec2& center, int radius, int color);

// TODO: 正円の縦横比を変えて楕円を描画するための引数をFillCircle()関数に追加する。

/**
    指定した中心点と半径、開始角度と終了角度をラジアン単位で指定して、扇形の図形を塗りつぶし描画します。
    角度は-πから+πの範囲に修正された上で比較されます。
    0〜5/2πが指定された場合、これは0〜1/2πが指定されたことになりますので、第1象限の90度の扇形が描画されます。
    @param  center  中心点の座標
    @param  radius  半径
    @param  color   描画色（0xRRGGBB形式の数値か、kColorRedなどの定数）
    @param  startAngleRad   円弧の描画の開始角度（ラジアン単位）
    @param  endAngleRad     円弧の描画の終了角度（ラジアン単位）
 */
void    FillCircle(const vec2& center, int radius, int color, float startAngleRad, float endAngleRad);

/**
    指定した座標からスキャンを開始して、borderColorの色で囲まれた領域をpaintColorの色で塗りつぶします。
    画面(-320, -240)-(319, 239)より外の領域の座標が指定された場合、塗りつぶしは行われません。
    @param  pos スキャンを開始する座標
    @param  paintColor  塗りつぶしの色（0xRRGGBB形式の数値か、kColorRedなどの定数）
    @param  borderColor 境界線の色（0xRRGGBB形式の数値か、kColorRedなどの定数）
 */
void    Paint(const vec2& pos, int paintColor, int borderColor);

/**
    指定された座標にグラフィック・パターンを描画します。
    グラフィック・パターンはunsigned int型の配列で、先頭2つの要素がX方向の大きさとY方向の大きさ、
    その後はARGB,ARGB,ARGB,...となります。ARGBの各要素は、0x00〜0xffの8ビットで表されます。
    A（アルファ値）のデータは、0だと不透明、それ以外だと透明なピクセルとして扱われます。
    @param  buffer  グラフィック・パターンをunsigned int型でx*y個分格納したバッファ
    @param  pos 描画の開始座標
 */
void    DrawPattern(unsigned int *buffer, const vec2& pos);

/**
    指定された座標に文字を描画します。12x20ピクセルのサイズで、0x20〜0x7eのASCII文字コードの半角英数字のみ描画可能です。
    @param  c   描画対象の文字
    @param  pos 描画の開始座標
    @param  color   描画色（0xRRGGBB形式の数値か、kColorRedなどの定数）
 */
void    DrawCharacter(char c, const vec2& pos, int color);

/**
    指定された座標に文字列を描画します。12x20ピクセルのサイズで、0x20〜0x7eのASCII文字コードの半角英数字のみ描画可能です。
    @param  str 描画対象のC言語文字列
    @param  pos 描画の開始座標
    @param  color   描画色（0xRRGGBB形式の数値か、kColorRedなどの定数）
 */
void    DrawText(const char *str, const vec2& pos, int color);

/**
    画面をスクロールします。
    @param  size    スクロール量
 */
void    Scroll(const vec2& size);

/**
    マウスカーソルの画面上の座標を取得します。
    @return マウスカーソルの座標
 */
vec2     GetMouse();

#endif /* DrawingVector_hpp */

