//
//  MVCaptureManager.h
//  MVRecorder
//
//  Created by Elf Sundae on 14-11-28.
//  Copyright (c) 2014年 www.0x123.com. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <ESFrameworkCore/ESFrameworkCore.h>
#import <AVFoundation/AVFoundation.h>
#import "MVCapturePreviewView.h"
#import "MVError.h"
#import "MVHelper.h"
#import "MVConfig.h"

/**
 * `MVCaptureManager` manage the capture from a device such as a camera or microphone.
 * It manages device inputs and outputs.
 *
 * @warning You should always access captureSession's properties or methods
 * on the sessionQueue using `-dispatchOnSessionQueue`
 */
@interface MVCaptureManager : NSObject

@property (nonatomic, readonly) AVCaptureSession *session;
@property (nonatomic, readonly) AVCaptureDeviceInput *videoDeviceInput;
@property (nonatomic, readonly) AVCaptureDeviceInput *audioDeviceInput;
@property (nonatomic, readonly) MVCapturePreviewView *previewView;
@property (nonatomic, readonly) MVConfig *config;

- (instancetype)initWithConfig:(MVConfig *)config;

/**
 * `block` will blocked on the main thread.
 */
- (void)setupSession:(void (^)(NSError *error))block;

- (void)destorySession:(void (^)(void))block;
- (void)destorySession;

/**
 * When the view that owned `previewView` disappearred, you should call -stopPreview.
 * When the app enters background or return foreground, `MVCaptureManager` has automatically
 * start or stop previewing.
 *
 * 如果captureSession在running时, 另外一个app(例如"相机")调用captureSession时会导致当前这个app被结束掉进程.
 */
//- (void)startPreview:(void (^)(BOOL result))block;
//- (void)stopPreview:(dispatch_block_t)block;
//- (BOOL)isPreviewRunning;

- (BOOL)startSessionRunning;
- (void)startSessionRunning:(dispatch_block_t)block;
- (BOOL)stopSessionRunning;
- (void)stopSessionRunning:(dispatch_block_t)block;

- (AVCaptureDevice *)currentVideoDevice;
/**
 * CaptureSession的有序队列, 凡是对CaptureSession进行的访问和修改都必须放到这个队列里, 以保证不紊乱.
 * 外部也可以用此队列执行有序的操作,例如MVRecorder的开始/停止录制、写媒体文件等.
 *
 * 这个方法会先检查当前是不是在sessionQueue中, 如果是的话直接调用block, 如果不是则dispatch_async到sessionQueue中
 */
- (void)dispatchOnSessionQueue:(dispatch_block_t)block;
/**
 * dispatch_async到sessionQueue中执行.
 */
- (void)dispatchAsyncOnSessionQueue:(dispatch_block_t)block;
/**
 * 检查当前执行的代码是否处于CaptureSessionQueue中.
 */
- (BOOL)isInSessionQueue;

@end

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma mark - Device

@interface MVCaptureManager (Device)
/**
 * Indicates whether the camera has a flash, and the flash is currently available for use.
 */
- (BOOL)isFlashAvailable;

- (BOOL)isFlashActive;

/**
 * Indicates current mode of the camera flash, if it has one.
 *
 * Default is AVCaptureFlashModeAuto, which means that
 * before recording, if the flash is currently active (see -isFlashActive),
 * this property will be AVCaptureFlashModeOn and the flash/torch will be open, else if the
 * flash is not active currently, this property will be AVCaptureFlashModeOff and the flash/torch
 * will be closed.
 *
 * To disable this automatically behavior, you can set `preferredCameraFlashMode` in `MVConfig`.
 */
@property (nonatomic) AVCaptureFlashMode flashMode;

- (BOOL)toggleFlashMode;

/**
 * Indicates whether the camera currently can be focused.
 */
- (BOOL)isFocusAvailable;
/**
 * Default is AVCaptureFocusModeContinuousAutoFocus.
 */
@property (nonatomic) AVCaptureFocusMode focusMode;

- (BOOL)isExposureAvailable;
/// 曝光模式
@property (nonatomic) AVCaptureExposureMode exposureMode;

/**
 * Set FocusMode and ExposureMode for the current video device.
 * If the current device has no focus funcation, only set the exposureMode.
 */
- (void)setFocusMode:(AVCaptureFocusMode)focusMode withPointOfInterest:(CGPoint)point;

- (AVCaptureDevicePosition)devicePosition;
- (void)toggleDevicePosition:(void (^)(BOOL changed, AVCaptureDevice *newDevice))block;

@end
