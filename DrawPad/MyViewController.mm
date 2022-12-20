#import "MyViewController.h"
#import "MyImageView.h"
#include "Drawing.hpp"
#include <algorithm>
#include <AVFAudio/AVFAudio.h>


void DrawMain();


@interface MyViewController ()
@property (weak) IBOutlet MyImageView *myImageView;
@end


static MyViewController *sInstance = nil;


@implementation MyViewController {
    CGColorSpaceRef     colorSpace;         //!< ビットマップ生成のための色空間
    CGContextRef        bitmapContext;      //!< ビットマップ生成のためのCore Graphicsコンテキスト
    NSTimeInterval      oldTime;            //!< 前のフレームの終了時間
    NSTimeInterval      frameCalcTime;      //!< フレーム計測の開始時間
    int                 frameCount;         //!< 1回の計測におけるフレーム実行の回数
    NSMenuItem          *pauseMenuItem;     //!< Pauseのメニュー項目
    NSMenuItem          *stepOverMenuItem;  //!< Step Overのメニュー項目
    bool                doStepOver;         //!< ステップ実行
    bool                doReset;            //!< リセットの実行
    bool                hasInitFinished;    //!< 初期化処理の完了
    bool                isMainLoopRunning;  //!< メインループの実行中フラグ
}

// ビューが読み込まれた直後の初期化処理
- (void)viewDidLoad
{
    [super viewDidLoad];

    sInstance = self;

    // メニュー項目の取得
    NSMenu *menu = [[NSApplication sharedApplication] mainMenu];
    NSMenu *runMenu = [[menu itemWithTag:10] submenu];
    [runMenu setAutoenablesItems:NO];
    pauseMenuItem = [runMenu itemWithTag:100];
    stepOverMenuItem = [runMenu itemWithTag:101];
    [stepOverMenuItem setEnabled:NO];
    doStepOver = false;
    doReset = false;
    hasInitFinished = true;

    // 画像バッファの生成と、ビットマップ生成のためのコンテキストの生成
    gpBuffer = (unsigned char *)malloc(4 * 640 * 480);
    memset(gpBuffer, 0, 4 * 640 * 480);
    colorSpace = CGColorSpaceCreateDeviceRGB();
    bitmapContext = CGBitmapContextCreate(gpBuffer, 640, 480, 8, 640*4, colorSpace, kCGImageAlphaNoneSkipLast);

    // メインループ実行の開始
    isMainLoopRunning = false;
    [self startRunning];
}

// メインループ実行の開始
- (void)startRunning
{
    // 画面のクリア
    gIsBatchDrawing = true;
    Clear(kColorBlack);
    gIsBatchDrawing = false;

    // メモリバッファ（が設定されたビットマップコンテキスト）をCore Graphics画像に変換し、ビューにセットする。
    CGImageRef cgImage = CGBitmapContextCreateImage(bitmapContext);
    [self.myImageView setImage:cgImage];
    CGImageRelease(cgImage);

    // キーボード・マウス関係の変数の初期化
    gKeyData = 0;
    gIsMouseDown = false;

    // フレームレート計算のための変数の初期化
    frameCalcTime = [NSDate timeIntervalSinceReferenceDate];
    frameCount = 0;
    oldTime = frameCalcTime;

    // メインループ実行のためのスレッド生成
    [NSThread detachNewThreadSelector:@selector(mainLoopProc:) toTarget:self withObject:nil];
    [self.view.window setTitle:@"DrawPad (Running) 0.0fps"];
    hasInitFinished = true;
}

// クリーンアップ
- (void)dealloc
{
    CGContextRelease(bitmapContext);
    free(gpBuffer);
    CGColorSpaceRelease(colorSpace);
}

// メインループのスレッドプロシージャ
- (void)mainLoopProc:(id)dummy
{
    isMainLoopRunning = true;
    @autoreleasepool {
        DrawMain();
        [[NSOperationQueue mainQueue] addOperationWithBlock:^{
            [self.view.window setTitle:[NSString stringWithFormat:@"DrawPad (Finished) %.1ffps", gFrameRate]];
        }];
        [[NSOperationQueue mainQueue] waitUntilAllOperationsAreFinished];
    }
    isMainLoopRunning = false;
}

// キー押下に対応するイベントハンドラ
- (void)keyDown:(NSEvent *)event
{
    // macOS固有のキーコード
    unsigned short keyCode = [event keyCode];

    // Left Arrow
    if (keyCode == 0x7b) {
        gKeyData |= kKeyLeftArrow;
    }
    // Right Arrow
    else if (keyCode == 0x7c) {
        gKeyData |= kKeyRightArrow;
    }
    // Up Arrow
    else if (keyCode == 0x7e) {
        gKeyData |= kKeyUpArrow;
    }
    // Down Arrow
    else if (keyCode == 0x7d) {
        gKeyData |= kKeyDownArrow;
    }
    // A
    else if (keyCode == 0x00) {
        gKeyData |= kKeyA;
    }
    // S
    else if (keyCode == 0x01) {
        gKeyData |= kKeyS;
    }
    // D
    else if (keyCode == 0x02) {
        gKeyData |= kKeyD;
    }
    // W
    else if (keyCode == 0x0d) {
        gKeyData |= kKeyW;
    }
    // Return
    else if (keyCode == 0x24) {
        gKeyData |= kKeyReturn;
    }
    // Space
    else if (keyCode == 0x31) {
        gKeyData |= kKeySpace;
    }
    // その他のキー
    else {
        //printf("keyDown: 0x%02x\n", keyCode);
    }
}

// キーが離されたことに対応するイベントハンドラ
- (void)keyUp:(NSEvent *)event
{
    // macOS固有のキーコード
    unsigned short keyCode = [event keyCode];

    // Left Arrow
    if (keyCode == 0x7b) {
        gKeyData &= ~kKeyLeftArrow;
    }
    // Right Arrow
    else if (keyCode == 0x7c) {
        gKeyData &= ~kKeyRightArrow;
    }
    // Up Arrow
    else if (keyCode == 0x7e) {
        gKeyData &= ~kKeyUpArrow;
    }
    // Down Arrow
    else if (keyCode == 0x7d) {
        gKeyData &= ~kKeyDownArrow;
    }
    // A
    else if (keyCode == 0x00) {
        gKeyData &= ~kKeyA;
    }
    // S
    else if (keyCode == 0x01) {
        gKeyData &= ~kKeyS;
    }
    // D
    else if (keyCode == 0x02) {
        gKeyData &= ~kKeyD;
    }
    // W
    else if (keyCode == 0x0d) {
        gKeyData &= ~kKeyW;
    }
    // Return
    else if (keyCode == 0x24) {
        gKeyData &= ~kKeyReturn;
    }
    // Space
    else if (keyCode == 0x31) {
        gKeyData &= ~kKeySpace;
    }
    // その他のキー
    else {
        //printf("keyUp: 0x%02x\n", keyCode);
    }
}

// マウス押下に対応するイベントハンドラ
- (void)mouseDown:(NSEvent *)event
{
    NSPoint pos = [event locationInWindow];
    pos = [self.view convertPoint:pos fromView:nil];
    gMouseX = (int)pos.x;
    gMouseY = (int)pos.y;
    gIsMouseDown = true;
}

// マウス移動に対応するイベントハンドラ
- (void)mouseMoved:(NSEvent *)event
{
    NSPoint pos = [event locationInWindow];
    pos = [self.view convertPoint:pos fromView:nil];
    gMouseX = (int)pos.x;
    gMouseY = (int)pos.y;
}

// マウスが離されたことに対応するイベントハンドラ
- (void)mouseUp:(NSEvent *)event
{
    NSPoint pos = [event locationInWindow];
    pos = [self.view convertPoint:pos fromView:nil];
    gMouseX = (int)pos.x;
    gMouseY = (int)pos.y;
    gIsMouseDown = false;
}

// マウスドラッグに対応するイベントハンドラ
- (void)mouseDragged:(NSEvent *)event
{
    NSPoint pos = [event locationInWindow];
    pos = [self.view convertPoint:pos fromView:nil];
    gMouseX = (int)pos.x;
    gMouseY = (int)pos.y;
}

// メモリバッファの画像をクリップボードにコピーする
- (void)copy:(id)sender
{
    [[NSOperationQueue mainQueue] addOperationWithBlock:^{
        // メモリバッファ（が設定されたビットマップコンテキスト）をCore Graphics画像に変換し、クリップボードにセットする。
        @autoreleasepool {
            CGImageRef cgImage = CGBitmapContextCreateImage(bitmapContext);
            NSImage *nsImage = [[NSImage alloc] initWithCGImage:cgImage size:NSMakeSize(640, 480)];
            NSPasteboard *pboard = [NSPasteboard generalPasteboard];
            [pboard clearContents];
            [pboard writeObjects:@[ nsImage ]];
            CGImageRelease(cgImage);
        }
    }];
}

// メモリバッファの画像をデスクトップフォルダに書き出す
- (void)takeScreenshot:(id)sender
{
    [[NSOperationQueue mainQueue] addOperationWithBlock:^{
        @autoreleasepool {
            // メモリバッファ（が設定されたビットマップコンテキスト）を画像に変換
            CGImageRef cgImage = CGBitmapContextCreateImage(bitmapContext);
            NSImage *nsImage = [[NSImage alloc] initWithCGImage:cgImage size:NSMakeSize(640, 480)];
            NSBitmapImageRep *imageRep = [[NSBitmapImageRep alloc]
                                       initWithBitmapDataPlanes:NULL
                                                     pixelsWide:640
                                                     pixelsHigh:480
                                                  bitsPerSample:8
                                                samplesPerPixel:4
                                                       hasAlpha:YES
                                                       isPlanar:NO
                                                 colorSpaceName:NSDeviceRGBColorSpace
                                                    bytesPerRow:0
                                                   bitsPerPixel:0];
            imageRep.size = NSMakeSize(640, 480);
            [NSGraphicsContext saveGraphicsState];
            [NSGraphicsContext setCurrentContext:
                     [NSGraphicsContext graphicsContextWithBitmapImageRep:imageRep]];
            [nsImage drawAtPoint:NSMakePoint(0, 0)
                        fromRect:NSZeroRect
                       operation:NSCompositeSourceOver
                        fraction:1.0];
            [NSGraphicsContext restoreGraphicsState];

            // ファイル名を作成
            NSDate *date = [NSDate date];
            NSDateFormatter *dateFormatter = [NSDateFormatter new];
            dateFormatter.dateFormat = @"yyyyMMdd_HHmmss";
            NSString *timeStr = [dateFormatter stringFromDate:date];
            NSString *username = NSUserName();
            NSString *filename = [NSString stringWithFormat:@"%@_%@.png", username, timeStr];

            // ファイルパスを作成
            NSArray *paths = NSSearchPathForDirectoriesInDomains (NSDesktopDirectory, NSUserDomainMask, YES);
            NSString *desktopPath = paths[0];
            NSString *filepath = [desktopPath stringByAppendingPathComponent:filename];
            
            // ファイルを保存
            NSData *data = [imageRep representationUsingType:NSPNGFileType
                                                  properties:@{}];
            [data writeToFile:filepath atomically:YES];
            
            // Finder上で画像ファイルを選択する
            NSWorkspace *workspace = [NSWorkspace sharedWorkspace];
            [workspace selectFile:filepath inFileViewerRootedAtPath:[filepath stringByDeletingLastPathComponent]];
        }
    }];
}

// 実行を一時中断する
- (void)pauseExecution:(id)sender
{
    gIsPausing = !gIsPausing;
}

// ステップ実行
- (void)stepOver:(id)sender
{
    doStepOver = true;
}

// 実行のリセット
- (void)resetExecution:(id)sender
{
    if (isMainLoopRunning) {
        doReset = true;
    } else {
        [self startRunning];
    }
}

// 1フレームあたりの描画を終了し、バッファの内容を画面上に反映させる。
- (void)finishDrawing
{
    [[NSOperationQueue mainQueue] addOperationWithBlock:^{
        // メモリバッファ（が設定されたビットマップコンテキスト）をCore Graphics画像に変換し、ビューにセットする。
        CGImageRef cgImage = CGBitmapContextCreateImage(bitmapContext);
        [self.myImageView setImage:cgImage];
        CGImageRelease(cgImage);

        // フレームレート表示を更新
        if (gIsPausing) {
            [self.view.window setTitle:[NSString stringWithFormat:@"DrawPad (Pausing) %.1ffps", gFrameRate]];
            [pauseMenuItem setTitle:@"Continue"];
            [stepOverMenuItem setEnabled:YES];
        }
    }];
    [[NSOperationQueue mainQueue] waitUntilAllOperationsAreFinished];

    // 一時停止の処理
    bool hasPaused = gIsPausing;
    while (gIsPausing && !doStepOver && !doReset) {
        [NSThread sleepForTimeInterval:0.05];
    }
    if (doReset) {
        doReset = false;
        hasInitFinished = false;
        [[NSOperationQueue mainQueue] addOperationWithBlock:^{
            [self startRunning];
        }];
        [[NSOperationQueue mainQueue] waitUntilAllOperationsAreFinished];
        while (!hasInitFinished) {
            [NSThread sleepForTimeInterval:0.05];
        }
        [NSThread exit];
        return;
    }
    doStepOver = false;
    if (hasPaused && !gIsPausing) {
        [[NSOperationQueue mainQueue] addOperationWithBlock:^{
            [self.view.window setTitle:[NSString stringWithFormat:@"DrawPad (Running) %.1ffps", gFrameRate]];
            [pauseMenuItem setTitle:@"Pause"];
            [stepOverMenuItem setEnabled:NO];
        }];
    }

    // 80fpsを超えないようにスリープさせ、フレームレートを計算する。
    frameCount++;
    NSTimeInterval currentTime = [NSDate timeIntervalSinceReferenceDate];
    NSTimeInterval rest = 1 / 80.0f - (currentTime - oldTime);
    if (rest > 0.0) {
        [NSThread sleepForTimeInterval:rest];
    }
    currentTime = [NSDate timeIntervalSinceReferenceDate];
    oldTime = currentTime;
    NSTimeInterval duration = currentTime - frameCalcTime;
    if (duration >= 1.0) {
        gFrameRate = frameCount / duration;
        frameCalcTime = currentTime;
        frameCount = 0;
        [[NSOperationQueue mainQueue] addOperationWithBlock:^{
            [self.view.window setTitle:[NSString stringWithFormat:@"DrawPad (Running) %.1ffps", gFrameRate]];
        }];
    }
}

@end


// 1フレームあたりの描画を終了させる
void FinishDrawing()
{
    @autoreleasepool {
        [sInstance finishDrawing];
    }
}

// 指定された秒数だけスリープさせる
void Sleep(float seconds)
{
    [NSThread sleepForTimeInterval:(NSTimeInterval)seconds];
}

// AVAudioEngineを生成する
AVAudioEngine *engine = [[AVAudioEngine alloc] init];

void PlaySineWave(float rate, float time, float future)
{
    // プレイヤーノードを生成する
    AVAudioPlayerNode *player = [[AVAudioPlayerNode alloc] init];
    
    // オーディオフォーマットを取得する
    AVAudioFormat *format = [player outputFormatForBus:0];
    // サンプリング周波数を取得する
    float sample_rate = [format sampleRate];
    // フレームの長さを指定する
    float length = time * sample_rate;
    // PCMバッファーを生成する
    AVAudioPCMBuffer *buffer = [[AVAudioPCMBuffer alloc] initWithPCMFormat:format frameCapacity:UInt32(length)];
    // フレームの長さを変更する
    buffer.frameLength = UInt32(length);
    // オーディオのチャンネル数を取得する
    AVAudioChannelCount channels = [format channelCount];

    // 波形を書き込む
    for(int ch = 0; ch < channels; ch++)
    {
        auto samples = [buffer floatChannelData][ch];
        for(int frame = 0; frame < buffer.frameLength; frame++)
        {
            samples[frame] = sinf(Float32(2.0 * M_PI) * rate * Float32(frame) / sample_rate);
        }
    }

    // AVAudioEngineにプレイヤーノードを設定する
    [engine attachNode:player];
    // ミキサーノードを生成する
    AVAudioMixerNode *mixer = [engine mainMixerNode];
    // プレイヤーノードとミキサーノードをAVAudioEngineに接続する
    [engine connect:player to:mixer format:format];

    // 開始時間を設定する
    AVAudioTime *future_time = [AVAudioTime timeWithSampleTime:sample_rate * future atRate:sample_rate];
    
    // 再生の開始を設定する
    [player scheduleBuffer:buffer atTime:future_time options:1UL<<2 completionHandler:nil];

    @try{
        [engine startAndReturnError:nil];
        [player play];
    }
    @catch(NSException *exception){
        NSLog(@"error is %@", exception);
    }
    
}

