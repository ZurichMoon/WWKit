//
//  MVRecorder.h
//  MVRecorder
//
//  Created by Elf Sundae on 14-11-26.
//  Copyright (c) 2014年 www.0x123.com. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <ESFrameworkCore/ESFrameworkCore.h>
#import <AVFoundation/AVFoundation.h>
#import <GLKit/GLKit.h>
#import "MVHelper.h"
#import "MVError.h"
#import "MVConfig.h"
#import "MVRecorderSession.h"
#import "MVCaptureManager.h"
#import "MVRenderer.h"

@protocol MVRecorderDelegate;

typedef NS_ENUM(NSInteger, MVRecorderFinishedReason) {
        /// 正常结束
        MVRecorderFinishedReasonNormal = 0,
        /// 最大录制时间限制
        MVRecorderFinishedReasonMaxRecordedDurationReached,
        /// 最大片段数量限制
        MVRecorderFinishedReasonMaxSegmentsCountReached,
#if 0 // 遇到错误时重新启动captureSession
        /// AVCaptureSession runtime error, 出现这个错误时MVRecorder不可用, 应该被关闭
        MVRecorderFinishedReasonCaptureSessionRuntimeError,
#endif
};

@interface MVRecorder : NSObject

- (instancetype)initWithDelegate:(id<MVRecorderDelegate>)delegate config:(MVConfig *)config;

/**
 * Setup Camera and capture session, should be called at first of all.
 * <del>It will automatically called while startRecording if the Recorder is not prepared.</del>
 *
 * NOTE: 放在viewDidAppear里调用prepare, 因为如果previewLayer没有显示时设置Orientation时无效,
 * 导致录制的视频是翻转的(默认AVCaptureVideoOrientationLandscapeLeft)
 */
- (void)prepare;
/**
 * Indicates whether the Recorder is prepared to record video.
 */
- (BOOL)isPrepared;

/**
 * Start or resume recording a video segment.
 */
- (void)startRecording;
/**
 * Stop current recording video segment.
 */
- (void)pauseRecording;

/**
 * Indicates whether the MVRecorder is recording.
 * 
 * NOTE: It is not KVO, if you want to capture recording state, please implement relative methods
 * define in MVRecorderDelegate.
 */
- (BOOL)isRecording;

/**
 * Unsetup MVRecorder, destory capture session, save/remove current recorder session.
 * After unsetup, the MVRecorder becomes unusable.
 */
- (void)unsetupWithSavingSession:(BOOL)saveSession;
/**
 * Safely & Asynchronously unsetup in captureSessionQueue.
 */
- (void)unsetupWithSavingSession:(BOOL)saveSession completion:(void (^)(void))completion;

- (void)unsetup;

@property (nonatomic, weak) __weak id<MVRecorderDelegate> delegate;
@property (nonatomic, readonly) MVConfig *config;
@property (nonatomic, strong) MVRecorderSession *session;
@property (nonatomic, readonly) MVCaptureManager *captureManager;

#if __DEMO_FILTER
/**
 * Displaying real-time filters.
 */
@property (nonatomic, strong) id<MVRenderer> renderer;
@property (nonatomic, strong) GLKView *renderView;
@property (nonatomic, strong) CIContext *ciContext;
@property (nonatomic, strong) CIFilter *filter;

#endif

/**
 * Determines current videoDevice(Camera) position.
 */
- (AVCaptureDevicePosition)devicePosition;

- (void)toggleDevicePosition;

@end

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma mark - MVRecorderDelegate

@protocol MVRecorderDelegate <NSObject>
@required
/**
 * Recorder is prepared to start recording if `error` is nil, otherwise means
 * the Recorder can not work.
 */
- (void)recorderDidPrepare:(MVRecorder *)recorder error:(NSError *)error;

@optional

///=============================================
/// @name Capture Device State
///=============================================

- (void)recorder:(MVRecorder *)recorder flashAvailableDidChange:(BOOL)isFlashAvailable;
- (void)recorder:(MVRecorder *)recorder flashModeDidChange:(AVCaptureFlashMode)flashMode;
- (void)recorder:(MVRecorder *)recorder devicePositionDidChange:(AVCaptureDevicePosition)devicePosition;

///=============================================
/// @name Capture Session State
///=============================================

- (void)recorder:(MVRecorder *)recorder captureSessionDidStart:(AVCaptureSession *)captureSession;
- (void)recorder:(MVRecorder *)recorder captureSessionDidStop:(AVCaptureSession *)captureSession;
- (void)recorder:(MVRecorder *)recorder captureSessionWasInterrupted:(AVCaptureSession *)captureSession;
- (void)recorder:(MVRecorder *)recorder captureSessionInterruptionEnded:(AVCaptureSession *)captureSession;
- (void)recorder:(MVRecorder *)recorder captureSessionRuntimeError:(AVCaptureSession *)captureSession error:(NSError *)error;

///=============================================
/// @name Recording State
///=============================================

/**
 * Segment recording started.
 */
- (void)recorderDidStartRecording:(MVRecorder *)recorder;
/**
 * MVRecorder did write(append) data(video or audio sampleBuffer) to MVRecorderSegment(recorder.session.currentRecordingSegment).
 *
 * This method will be callbacked multi times while recording, once sampleBuffer from 
 * VideoInput(Camera) or AudioInput(Microphone) was Accepted.
 * You can use this method to update UI, e.g. current recording duration.
 */
- (void)recorderDidWriteData:(MVRecorder *)recorder forMediaType:(NSString *)mediaType;
/**
 * Callbacked when the video/audio data was skipped while recording.
 *
 * This method will be callbacked multi times while recording, once sampleBuffer from
 * VideoInput(Camera) or AudioInput(Microphone) was Skipped.
 * You can use this method to update UI, e.g. current recording duration.
 */
- (void)recorderDidSkipData:(MVRecorder *)recorder forMediaType:(NSString *)mediaType;

/**
 * Segment recording stopped.
 * 如果error不为nil, 这次录制可能没有完整保存文件(录制过程中出错)或者根本没有启动录制(录制初始化失败).
 */
- (void)recorderDidPauseRecording:(MVRecorder *)recorder error:(NSError *)error;

/**
 * MVRecorder has finished because the 'maxRecordedDuration' defined in MVConfig was reached,
 * or the `maxSegmentsCount` defined in MVConfig was reached.
 */
- (void)recorderDidFinish:(MVRecorder *)recorder withReason:(MVRecorderFinishedReason)reason;

@end