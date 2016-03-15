//
//  MVConfig.h
//  MVRecorder
//
//  Created by Elf Sundae on 14-11-26.
//  Copyright (c) 2014年 www.0x123.com. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <AVFoundation/AVFoundation.h>
#import <ESFrameworkCore/ESFrameworkCore.h>

typedef NS_ENUM(NSInteger, MVVideoSource) {
        /* 拍摄 */
        MVVideoSourceCapture            = 0,
        /* 从系统相册选取 */
        MVVideoSourcePhotosLibrary      = 1,
};

typedef NS_ENUM(NSInteger, MVCaptureQualityType) {
        MVCaptureQualityTypeAuto        = 0,
        MVCaptureQualityTypeLow         = 1,
        MVCaptureQualityTypeMedium      = 2,
        MVCaptureQualityTypeHigh        = 3,
        // 设置成photo时是高清模式, 视野更广, 摄像头不用拉很远也能拍比较大的范围
        // http://stackoverflow.com/a/4926999/521946
        MVCaptureQualityTypePhoto       = 4,
};

typedef NS_ENUM(NSInteger, MVExportQualityType) {
        MVExportQualityTypeAuto         = 0,
        MVExportQualityTypeLow          = 1,
        MVExportQualityTypeMedium       = 2,
        MVExportQualityTypeHigh         = 3,
};

typedef NS_ENUM(NSInteger, MVCaptureFocusMode) {
        /* 初始化摄像头时自动对焦, 用户可手动调节 */
        MVCaptureFocusModeManual = 0,
        /* 自动对焦且用户不可手动调节 */
        MVCaptureFocusModeAuto = 1,
};

/**
 * Configuration for the Recorder, the Encoder, and the Exporter.
 *
 */
@interface MVConfig : NSObject

+ (instancetype)defaultConfig;

/**
 * 从服务端配置生成MVConfig.
 *
 * style:               int, 录制类型(对不同配置的分类). 一种配置对应一个style,用于标记草稿,不同style的草稿不能混用. 默认为0
 *                      服务端可以根据不同的配置定义不同的style, 例如可分段, 不可分段, 从系统相册选取,
 *                      4-6秒, 3-11秒, 不可分段3-8秒视频尺寸640, 等均可成为一种style
 * source:              int, 0(默认):拍摄 1:从系统相册选取
 * max_count:           int, 最大片段的个数, 0为不限制, 1为不可分段. 默认为0
 * min_duration:        int, 最小录制时间, 小于这个时间的不能完成录制. 默认为0. 0为不限制.
 * max_duration:        int, 最大录制时间, 录制时间大于这个长度的自动完成录制. 默认为0. 0为不限制.
 * video_size:          uint, 视频尺寸, 例如480, 所有视频均为正方形. 默认为480
 * video_framerate:     uint, 视频帧频(FPS), 默认为30. 在iPhone4/iTouch4等单核设备上始终为15
 * video_bitrate:       uint, 视频压缩比率, 默认自动,根据video_size计算: 480*480*4.05=933120
 * audio_bitrate:       uint, 音频压缩比率, 默认128000
 * record_quality:      uint, 录制质量,用于配置摄像头的采集质量. 默认为4.经测试系统默认为高
 *                      0:自动 1:低 2:中等 3:高 4:原始
 * export_quality:      uint, 最终生成视频的质量, 0:自动 1:低 2:中等 3:高, 默认中等
 * max_buffer_count:    uint, 录制时为了不丢弃音视频数据而设置的buffer. 0-10, 默认为6
 * camera_position:     uint, 初始的摄像头位置, 0(默认):后置 1:前置.
 * focus_mode:          uint, 对焦和曝光模式, 0(默认):可手动调节 1:自动且不可手动调节
 * logo_duration:       int, Logo水印的时长(从视频最后面的logo_duration时间开始添加Logo水印)
 * logo_text:           string, Logo水印的文字
 * quality:             float, 缩略图的JPEG压缩质量, 默认0.5
 * bgmusic:             string, 背景音乐的包名
 *
 *
 * 所有配置字段在客户端都有默认值, 如果某字段解析失败(比如服务端没有传这个参数,或者这个参数的值不符合要求)就用默认值.
 *
 */
+ (instancetype)configWithDictionary:(NSDictionary *)dictionary;

/**
 * 视频录制配置可能有不止一种的类型, 例如可以分段、不可分段、从系统相册选取, 4-6秒, 3-8秒都各是一种类型.
 * 根据不同的type, MVRecorderSession在保存和检查草稿时能区分开来.
 * 默认为0, 对应的maxSegmentsCount为0
 */
@property (nonatomic) int recorderStyle;

@property (nonatomic) MVVideoSource videoSource;

/**
 * The max count of segments, 0 or negative number for no limit.
 */
@property (nonatomic) int maxSegmentsCount;

/**
 * The minimum recorded duration required to finish this whole recording.
 *
 * Default is 0, means no limit.
 */
@property (nonatomic) int minRecordedDuration;
/**
 * If the `minRecordedDuration` is 0, the `minimumRecordedDuration will be kCMTimeInvalid.
 */
@property (nonatomic, readonly) CMTime minimumRecordedDuration;

/**
 * Specifies the maximum capture duration for the whole recording, the Recorder will be 
 * finished automatically if this limit is reached.
 *
 * Default is 0, means no limit.
 */
@property (nonatomic) int maxRecordedDuration;
/**
 * If the `maxRecordedDuration` is 0, the `maximumRecordedDuration will be kCMTimeInvalid.
 */
@property (nonatomic, readonly) CMTime maximumRecordedDuration;

/**
 * Specifies the width and height for output video.
 * The video is square, means the video size will be videoSize*videoSize.
 *
 * Default is 480.
 */
@property (nonatomic) int videoSize;
/**
 * {videoSize, videoSize}
 */
@property (nonatomic, readonly) CMVideoDimensions videoDimensions;

/**
 * Camera recording frame rate (FPS), default is 30.
 * 
 * Note: For single core systems like iPhone 4 and iPod Touch 4th Generation we always use 15.
 */
@property (nonatomic) int videoFrameRate;

/**
 * Video Average Bitrate for the Encoder, default is 1000000.
 */
@property (nonatomic) UInt64 videoBitRate;
/**
 * Audio Bitrate for the Encoder, default is 128000.
 */
@property (nonatomic) UInt64 audioBitRate;

/**
 * 默认是MVCaptureQualityTypeAuto
 */
@property (nonatomic) MVCaptureQualityType captureQualityType;
/**
 * 根据captureQualityType返回AVCaptureSession的captureSessionPreset配置.
 * 返回nil时不用设置AVCaptureSession的sessionPreset.
 */
- (NSString *)captureSessionPreset;

/**
 * Default is MVExportQualityTypeAuto.
 */
@property (nonatomic) MVExportQualityType exportQualityType;
/**
 * Preset name for AVAssetExportSession.
 */
- (NSString *)assetExportPreset;

/**
 * 录制时缓存的最大数量, 0-10, 0表示不缓存, mediaWriter实时写不了(is not readyForMoreMediaData)时
 * 就丢弃掉CMSampleBuffer. 默认为6
 *
 * @see https://github.com/rFlex/SCRecorder/issues/100
 */
@property (nonatomic) int maxRecordingBuffersCount;

/**
 * Specifies preferred device position which the video capture device used in initialization.
 *
 * Default is AVCaptureDevicePositionBack.
 */
@property (nonatomic) AVCaptureDevicePosition preferredCameraPosition;

/**
 * See -[MVCaptureManager flashMode], Default is AVCaptureFlashModeOff.
 *
 * 注: 此方法已作废, flashMode默认总是是Off. 因为在flashModeOn时从captureSession移除摄像头时,
 * 下次获取这个摄像头的isFlashActive属性则总是true, 需要在removeInput时还原此摄像头成flashModeAuto,
 * 这样会导致destoryCaptureSession时延时.  另外, 自动打开摄像头对用户也可能不友好(例如偷拍,刺眼等情况)
 */
@property (nonatomic) AVCaptureFlashMode preferredCameraFlashMode __attribute__((deprecated("不再支持自动flash")));

/**
 * 预设的对焦和曝光模式, 默认是MVCaptureFocusModeManual.
 */
@property (nonatomic) MVCaptureFocusMode preferredFocusMode;

/**
 * 视频的transform, 例如用于放大缩小视频. 默认CGAffineTransformIdentity
 */
@property (nonatomic) CGAffineTransform videoTransform;

/**
 * Specifies whether the receiver should always discard any video frame that is not processed 
 * before the next frame is captured.
 *
 * The default value is NO.
 */
@property(nonatomic) BOOL alwaysDiscardsLateVideoFrames;

#if 0 // 丢弃掉setup mediaWriter之前的数据(主要是音频)
/**
 * 开始录制后会先根据sampleBuffer初始化AVAssetWriter, audio和video都必须至少有一次sampleBuffer才能初始化
 * AVAssetWriter成功, 该属性标记在writer成功初始化之前的video数据是否应该被丢弃.
 *
 * 另外, 如果不丢弃, 从0时间创建的缩略图可能会抖动(因为手按下播放时手机抖动导致摄像头会抖动).
 *
 * The default value is NO.
 */
@property (nonatomic) BOOL discardsEarlierVideoFrames;
#endif

/**
 * Logo水印的时长, 为0时表示不添加Logo水印, 默认为0
 */
@property (nonatomic) int logoWatermarkDuration;

/**
 * Logo水印文字, (美丽约的用户昵称)
 */
@property (nonatomic, copy) NSString *logoWatermarkText;

/**
 * 缩略图压缩成JPEG的质量, 0.0-1.0
 */
@property (nonatomic) float thumbnailQuality;
/**
 * Defaults is 10.0
 */
@property (nonatomic) float thumbnailBlurredRadius;

@property (nonatomic, copy) NSString *musicPackageIdentifier;


/**
 * 校验录制总时间. 
 * 返回0表示正常范围(大于最小时间限制并且小于最大限制)
 * 返回1表示大于最大时间限制.
 * 返回-1表示小于最小时间限制.
 *
 * @param duration 一般为 recorder.session.recordedDurationGetSeconds
 */
- (int)checkRecordedDuration:(NSTimeInterval)duration;

@end


@interface MVConfig (AssetWriter)
- (NSDictionary *)videoAssetWriterSettingsWithSampleBuffer:(CMSampleBufferRef)sampleBuffer;
- (NSDictionary *)audioAssetWriterSettingsWithSampleBuffer:(CMSampleBufferRef)sampleBuffer;
- (NSDictionary *)assetWriterSettingsForMediaType:(NSString *)mediaType withSampleBuffer:(CMSampleBufferRef)sampleBuffer;
//- (NSArray *)assetWriterMetadata;
@end
