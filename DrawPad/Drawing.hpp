#ifndef Drawing_hpp
#define Drawing_hpp

//#include <algorithm>
//#include <cassert>
//#include <cmath>
//#include <cstdio>
//#include <cstdlib>
//#include <ctime>
#include "vec2.hpp"


#pragma mark - 変数・定数の定義

// 実行全体に関する変数
extern bool     gIsBatchDrawing;    //!< バッチ処理がONになっているかどうか
extern float    gFrameRate;         //!< 現時点でのフレームレート
extern bool     gIsPausing;         //!< 実行が一時停止中かどうか

// グラフィックス関係の変数
extern unsigned char    *gpBuffer;  //!< 画面のバッファ(ABGR,ABGR,...)

// キーボード関係の変数
extern unsigned gKeyData;           //!< キーボードの入力データ

// マウス関係の変数
extern bool     gIsMouseDown;       //!< 左マウスボタンが押されているかどうか
extern int      gMouseX;            //!< マウスの現在のX座標
extern int      gMouseY;            //!< マウスの現在のY座標

// 色の定数
extern const int    kColorBlack;    //!< 黒の色を表す定数
extern const int    kColorGray;     //!< グレーの色を表す定数
extern const int    kColorWhite;    //!< 白の色を表す定数
extern const int    kColorRed;      //!< 赤の色を表す定数
extern const int    kColorGreen;    //!< 緑の色を表す定数
extern const int    kColorBlue;     //!< 青の色を表す定数
extern const int    kColorYellow;   //!< 黄色を表す定数
extern const int    kColorDarkBlue; //!< 暗い青の色を表す定数

// キーボードの定数
extern const unsigned   kKeyA;          //!< キーAに対応したビットフラグ定数
extern const unsigned   kKeyS;          //!< キーSに対応したビットフラグ定数
extern const unsigned   kKeyD;          //!< キーDに対応したビットフラグ定数
extern const unsigned   kKeyW;          //!< キーWに対応したビットフラグ定数
extern const unsigned   kKeyUpArrow;    //!< 上矢印キーに対応したビットフラグ定数
extern const unsigned   kKeyDownArrow;  //!< 下矢印キーに対応したビットフラグ定数
extern const unsigned   kKeyLeftArrow;  //!< 左矢印キーに対応したビットフラグ定数
extern const unsigned   kKeyRightArrow; //!< 右矢印キーに対応したビットフラグ定数
extern const unsigned   kKeyReturn;     //!< returnキーに対応したビットフラグ定数
extern const unsigned   kKeySpace;      //!< spaceキーに対応したビットフラグ定数



#pragma mark - 全般的な操作

/**
    秒数で指定した時間だけ処理を中断します。
    @param seconds  処理を中断する秒単位の時間
 */
void    Sleep(float seconds);

/**
    バッチ処理を開始します。バッチ処理を行っている間、画面上に描画結果は反映されません。
 */
void    StartBatch();

/**
    バッチ処理を終了します。バッチ処理を行っている間に実行されたすべての描画結果が、画面上に反映されます。
 */
void    EndBatch();



#pragma mark - グラフィックス操作

/**
    指定した色で画面をクリアします。
    @param  color   画面をクリアする色（0xRRGGBB形式の数値か、kColorRedなどの定数）
 */
void    Clear(int color);

/**
    指定した座標の色を取得します。
    @param  x   X座標
    @param  y   Y座標
    @return 0xRRGGBB形式の数値
 */
int     GetColor(int x, int y);

/**
    指定した座標に点を描画します。
    @param  x   X座標
    @param  y   Y座標
    @param  color   描画色（0xRRGGBB形式の数値か、kColorRedなどの定数）
 */
void    DrawPoint(int x, int y, int color);

/**
    指定した2点の座標を結ぶ直線を描画します。
    @param  x1  始点のX座標
    @param  y1  始点のY座標
    @param  x2  終点のX座標
    @param  y2  終点のY座標
    @param  color   描画色（0xRRGGBB形式の数値か、kColorRedなどの定数）
 */
void    DrawLine(int x1, int y1, int x2, int y2, int color);

/**
    指定した3点の座標を結ぶ三角形を描画します。
    @param  x1  点1のX座標。画面中央を0として、右方向がプラス方向。
    @param  y1  点1のY座標。画面中央を0として、上方向がプラス方向。
    @param  x2  点2のX座標。画面中央を0として、右方向がプラス方向。
    @param  y2  点2のY座標。画面中央を0として、上方向がプラス方向。
    @param  x3  点3のX座標。画面中央を0として、右方向がプラス方向。
    @param  y3  点3のY座標。画面中央を0として、上方向がプラス方向。
    @param  color   描画色（0xRRGGBB形式の数値か、kColorRedなどの定数）
 */
void    DrawTriangle(int x1, int y1, int x2, int y2, int x3, int y3, int color);

/**
    指定した3点の座標を結ぶ三角形を塗りつぶします。
    @param  x1  点1のX座標。画面中央を0として、右方向がプラス方向。
    @param  y1  点1のY座標。画面中央を0として、上方向がプラス方向。
    @param  x2  点2のX座標。画面中央を0として、右方向がプラス方向。
    @param  y2  点2のY座標。画面中央を0として、上方向がプラス方向。
    @param  x3  点3のX座標。画面中央を0として、右方向がプラス方向。
    @param  y3  点3のY座標。画面中央を0として、上方向がプラス方向。
    @param  color   描画色（0xRRGGBB形式の数値か、kColorRedなどの定数）
 */
void    FillTriangle(int x1, int y1, int x2, int y2, int x3, int y3, int color);

/**
    指定した座標から指定した大きさの四角形を描画します。
    @param  x   始点のX座標。画面中央を0として、右方向がプラス方向。
    @param  y   始点のY座標。画面中央を0として、上方向がプラス方向。
    @param  width   四角形の横方向の大きさ。プラス値を指定すると始点から右に、マイナス値を指定すると始点から左に向かって描画します。
    @param  height  四角形の縦方向の大きさ。プラス値を指定すると始点から上に、マイナス値を指定すると始点から下に向かって描画します。
 */
void    DrawRect(int x, int y, int width, int height, int color);

/**
    指定した座標から指定した大きさの四角形を塗りつぶします。
    @param  x   始点のX座標。画面中央を0として、右方向がプラス方向。
    @param  y   始点のY座標。画面中央を0として、上方向がプラス方向。
    @param  width   四角形の横方向の大きさ。プラス値を指定すると始点から右に、マイナス値を指定すると始点から左に向かって描画します。
    @param  height  四角形の縦方向の大きさ。プラス値を指定すると始点から上に、マイナス値を指定すると始点から下に向かって描画します。
 */
void    FillRect(int x, int y, int width, int height, int color);


/**
    指定した中心点と半径で円を描画します。
    @param  cx  中心点のX座標。画面中央を0として、右方向がプラス方向。
    @param  cy  中心点のY座標。画面中央を0として、上方向がプラス方向。
    @param  radius  半径
    @param  color   描画色（0xRRGGBB形式の数値か、kColorRedなどの定数）
 */
void    DrawCircle(int cx, int cy, int radius, int color);

// TODO: 正円の縦横比を変えて楕円を描画するための引数をDrawCircle()関数に追加する。

/**
    指定した中心点と半径、開始角度と終了角度をラジアン単位で指定して、円弧を描画します。
    角度は-πから+πの範囲に修正された上で比較されます。
    0〜5/2πが指定された場合、これは0〜1/2πが指定されたことになりますので、第1象限の90度の円弧が描画されます。
    @param  cx  中心点のX座標。画面中央を0として、右方向がプラス方向。
    @param  cy  中心点のY座標。画面中央を0として、上方向がプラス方向。
    @param  radius  半径
    @param  color   描画色（0xRRGGBB形式の数値か、kColorRedなどの定数）
    @param  startAngleRad   円弧の描画の開始角度（ラジアン単位）
    @param  endAngleRad     円弧の描画の終了角度（ラジアン単位）
 */
void    DrawCircle(int cx, int cy, int radius, int color, float startAngleRad, float endAngleRad);

/**
    指定した中心点と半径で円を塗りつぶします。
    @param  cx  中心点のX座標。画面中央を0として、右方向がプラス方向。
    @param  cy  中心点のY座標。画面中央を0として、上方向がプラス方向。
    @param  radius  半径
    @param  color   描画色（0xRRGGBB形式の数値か、kColorRedなどの定数）
 */
void    FillCircle(int cx, int cy, int radius, int color);

// TODO: 正円の縦横比を変えて楕円を描画するための引数をFillCircle()関数に追加する。

/**
    指定した中心点と半径、開始角度と終了角度をラジアン単位で指定して、扇形の図形を塗りつぶし描画します。
    角度は-πから+πの範囲に修正された上で比較されます。
    0〜5/2πが指定された場合、これは0〜1/2πが指定されたことになりますので、第1象限の90度の扇形が描画されます。
    @param  cx  中心点のX座標。画面中央を0として、右方向がプラス方向。
    @param  cy  中心点のY座標。画面中央を0として、上方向がプラス方向。
    @param  radius  半径
    @param  color   描画色（0xRRGGBB形式の数値か、kColorRedなどの定数）
    @param  startAngleRad   円弧の描画の開始角度（ラジアン単位）
    @param  endAngleRad     円弧の描画の終了角度（ラジアン単位）
 */
void    FillCircle(int cx, int cy, int radius, int color, float startAngleRad, float endAngleRad);

/**
    指定した座標からスキャンを開始して、borderColorの色で囲まれた領域をpaintColorの色で塗りつぶします。
    画面(-320, -240)-(319, 239)より外の領域の座標が指定された場合、塗りつぶしは行われません。
    @param  x   X座標。画面中央を0として、右方向がプラス方向。
    @param  y   Y座標。画面中央を0として、上方向がプラス方向。
    @param  paintColor  塗りつぶしの色（0xRRGGBB形式の数値か、kColorRedなどの定数）
    @param  borderColor 境界線の色（0xRRGGBB形式の数値か、kColorRedなどの定数）
 */
void    Paint(int x, int y, int paintColor, int borderColor);

/**
    指定された座標にグラフィック・パターンを描画します。
    グラフィック・パターンはunsigned int型の配列で、先頭2つの要素がX方向の大きさとY方向の大きさ、
    その後はARGB,ARGB,ARGB,...となります。ARGBの各要素は、0x00〜0xffの8ビットで表されます。
    A（アルファ値）のデータは、0だと不透明、それ以外だと透明なピクセルとして扱われます。
    @param  buffer  グラフィック・パターンをunsigned int型でx*y個分格納したバッファ
    @param  x   X座標。画面中央を0として、右方向がプラス方向。
    @param  y   Y座標。画面中央を0として、上方向がプラス方向。
 */
void    DrawPattern(unsigned int *buffer, int x, int y);

/**
    指定された座標に文字を描画します。12x20ピクセルのサイズで、0x20〜0x7eのASCII文字コードの半角英数字のみ描画可能です。
    @param  c   描画対象の文字
    @param  x   X座標。画面中央を0として、右方向がプラス方向。
    @param  y   Y座標。画面中央を0として、上方向がプラス方向。
    @param  color   描画色（0xRRGGBB形式の数値か、kColorRedなどの定数）
 */
void    DrawCharacter(char c, int x, int y, int color);

/**
    指定された座標に文字列を描画します。12x20ピクセルのサイズで、0x20〜0x7eのASCII文字コードの半角英数字のみ描画可能です。
    @param  str 描画対象のC言語文字列
    @param  x   X座標。画面中央を0として、右方向がプラス方向。
    @param  y   Y座標。画面中央を0として、上方向がプラス方向。
    @param  color   描画色（0xRRGGBB形式の数値か、kColorRedなどの定数）
 */
void    DrawText(const char *str, int x, int y, int color);

/**
    画面をスクロールします。
    @param  x   X方向のスクロール量。右方向がプラス方向。
    @param  y   Y方向のスクロール量。上方向がプラス方向。
 */
void    Scroll(int x, int y);



#pragma mark - キーボード関係の操作

/**
    指定したキーが押されているかどうかを判定します。
    @param  key キーボードに対応したビットフィールド定数
    @return keyに対応したキーが押されていればtrue、そうでなければfalse
 */
bool    CheckKey(unsigned int key);



#pragma mark - マウス関係の操作

/**
    マウスカーソルの画面上の座標をvec2構造体に取得します。
    @return マウスカーソルの座標。画面中央を(0, 0)として、右方向・上方向がプラス方向。
 */
vec2     GetMousePos();

/**
    マウスカーソルの画面上のX座標を取得します。
    @return マウスカーソルのX座標。画面中央を0として、右方向がプラス方向。
 */
int     GetMouseX();

/**
    マウスカーソルの画面上のY座標を取得します。
    @return マウスカーソルのY座標。画面中央を0として、上方向がプラス方向。
 */
int     GetMouseY();

/**
    マウスの左ボタンが押されているかどうかを取得します。
    @return マウスの左ボタンが押されていればtrue、そうでなければfalse
 */
bool    CheckMouse();


#endif /* Drawing_hpp */

