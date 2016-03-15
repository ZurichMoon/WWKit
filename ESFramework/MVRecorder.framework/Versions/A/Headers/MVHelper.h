//
//  MVHelper.h
//  MVRecorder
//
//  Created by Elf Sundae on 14-11-26.
//  Copyright (c) 2014年 www.0x123.com. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <AVFoundation/AVFoundation.h>

typedef NS_ENUM(NSInteger, MVAuthorizationStatus) {
        /* The user has not yet made a choice regarding whether the client can access the hardware */
        // -Elf, iOS7以上才有针对相机和麦克风的隐私设置
        //MVAuthorizationStatusNotDetermined = 0,
        
        /* The client is authorized to access the hardware */
        MVAuthorizationStatusAuthorized = 0,
        /* The user explicitly denied access to the hardware */
        MVAuthorizationStatusDenied,
};

@interface MVHelper : NSObject

///=============================================
/// @name Capture Utilities
///=============================================

/**
 * Returns available cameras.
 */
+ (NSArray *)availableVideoCaptureDevices;
/**
 * Returns all available audio devices.
 */
+ (NSArray *)availableAudioCaptureDevices;
/**
 * availableVideoCaptureDevices.count > 1
 */
+ (BOOL)hasMultipleVideoCaptureDevices;

+ (BOOL)isVideoCaptureDevicePositionAvailable:(AVCaptureDevicePosition)position;
/**
 * Returns nil if no any video devices.
 */
+ (AVCaptureDevice *)videoCaptureDeviceWithPreferredPosition:(AVCaptureDevicePosition)position;
/**
 * Returns nil if no any audio devices.
 */
+ (AVCaptureDevice *)audioCaptureDevice;

+ (AVCaptureConnection *)connectionWithMediaType:(NSString *)mediaType fromConnections:(NSArray *)connections;

/**
 * Set video orientation for connection.
 */
+ (BOOL)setOrientation:(AVCaptureVideoOrientation)orientation forCaptureConnection:(AVCaptureConnection *)connection;

/**
 * Set `activeVideoMaxFrameDuration` and `activeVideoMinFrameDuration` to frameRate on iOS7+
 */
+ (BOOL)setFrameRate:(int)frameRate forCaptureDevice:(AVCaptureDevice *)device;

/**
 * Set frameRate for AVCaptureConnection of videoDataOutput.
 * Note: You may only use this method when `+[MVHelper setFrameRate:forCaptureDevice:]` failed.
 *
 * Should called within captureSession.beginConfiguration and commitConfiguration
 */
+ (BOOL)setFrameRate:(int)frameRate forCaptureVideoDataOutput:(AVCaptureVideoDataOutput *)videoDataOutput;

/**
 * Indicates whether the camera has a flash, and the flash is currently available for use.
 */
+ (BOOL)isFlashAvailable:(AVCaptureDevice *)device;

/**
 * Indicates whether the camera has a flash, and the flash is currently active.
 */
+ (BOOL)isFlashActive:(AVCaptureDevice *)device;

/**
 * Set flash mode and torch mode. AT/AF.
 */
+ (BOOL)setFlashModeAndTorchMode:(AVCaptureFlashMode)flashMode forCaptureDevice:(AVCaptureDevice *)device;

/**
 * Indicates whether the camera currently can be focused.
 */
+ (BOOL)isFocusAvailable:(AVCaptureDevice *)device;

/**
 * Indicates whether the camera supports exposure points of interest.
 */
+ (BOOL)isExposureAvailable:(AVCaptureDevice *)device;

+ (BOOL)setFocusMode:(AVCaptureFocusMode)focusMode forCaptureDevice:(AVCaptureDevice *)device;
+ (BOOL)setExposureMode:(AVCaptureExposureMode)exposureMode forCaptureDevice:(AVCaptureDevice *)device;

/**
 * 设置聚焦和曝光. `focusMode`为AVCaptureFocusModeAutoFocus时会设置subjectAreaChangeMonitoringEnabled为YES,
 * 否则设置subjectAreaChangeMonitoringEnabled为NO.
 *
 * Note: 前置摄像头没有聚焦功能, 只会设置曝光. 
 * 如果设备不支持传入的focusMode,就不会设置.
 */
+ (BOOL)setFocusModeAndExposureMode:(AVCaptureFocusMode)focusMode forCaptureDevice:(AVCaptureDevice *)device;
+ (BOOL)setFocusModeAndExposureMode:(AVCaptureFocusMode)focusMode forCaptureDevice:(AVCaptureDevice *)device atPointOfInterest:(CGPoint)point;

///=============================================
/// @name Authorization
///=============================================

/**
 * Request Camera or microphone privacy accessing authorization, `block` will called on the main thread.
 */
+ (void)requestCaptureAuthorizationForMediaType:(NSString *)mediaType block:(void (^)(MVAuthorizationStatus status))block;

/**
 * For AVMediaTypeVideo and AVMediaTypeAudio.
 * MVErrorCodeCameraIsNotAuthorized or MVErrorCodeMicrophoneIsNotAuthorized if denied.
 */
+ (void)requestCaptureAuthorization:(void (^)(NSError *error))block;

/**
 * Request authorization for Photo Library.
 */
+ (void)requestPhotoLibraryAuthorization:(void (^)(MVAuthorizationStatus status))block;

/**
 * Save video from `videoURL` to Photo Library.
 *
 * Note: You may request authorization using +[MVHelper requestPhotoLibraryAuthorization] before saving.
 */
+ (void)saveVideoAtURL:(NSURL *)videoURL toPhotosAlbum:(NSString *)albumName completion:(void (^)(NSError *error))completion;

///=============================================
/// @name Compression
///=============================================

/**
 * 根据视频尺寸计算bitrate, 适用于直播流.
 */
+ (UInt64)recommendedVideoBitRateForSize:(CMVideoDimensions)videoSize;


///=============================================
/// @name Composition
///=============================================

/**
 * Returns time after appending.
 */
+ (CMTime)appendAssetTrack:(AVAssetTrack *)track toCompositionTrack:(AVMutableCompositionTrack *)compositionTrack atTime:(CMTime)atTime withBounds:(CMTime)bounds;
/**
 * Returns orientation for the video asset track.
 */
+ (AVCaptureVideoOrientation)orientationForVideoAssetTrack:(AVAssetTrack *)assetTrack isPortrait:(BOOL *)isPortrait;

/**
 * 检查time是否在bounds范围内.
 * 如果bounds为Invalid则返回kCMTimeInvalid, 
 * 如果time为Invalid则返回kCMTimeZero, 
 * 如果time大于bounds则返回bounds.
 */
+ (CMTime)checkTime:(CMTime)time withBounds:(CMTime)bounds;

///=============================================
/// @name Renderer
///=============================================

//+ (CGRect)
@end
