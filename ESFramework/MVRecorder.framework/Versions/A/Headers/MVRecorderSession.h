//
//  MVRecorderSession.h
//  MVRecorder
//
//  Created by Elf Sundae on 14-11-26.
//  Copyright (c) 2014年 www.0x123.com. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <ESFrameworkCore/ESFrameworkCore.h>
#import <AVFoundation/AVFoundation.h>
#import "MVRecorderSegment.h"
#import "MVConfig.h"
#import "MVRecorderSessionConfiguration.h"
@class MVRecorderSession;

ES_EXTERN NSString *const MVRecorderSessionIdentifierPrefix;
ES_EXTERN NSString *const MVRecorderSessionSegmentFilenamePrefix;
ES_EXTERN NSString *const MVRecorderSessionInfoRepresentationFilename;

typedef NS_ENUM(NSInteger, MVRecorderSessionStatus) {
        MVRecorderSessionStatusIdle = 0,
        MVRecorderSessionStatusRecording,
        MVRecorderSessionStatusEditing,
        MVRecorderSessionStatusUploading,
        /* Uploaded */
        // 上传完成后移动文件,并删除session文件夹
        // MVRecorderSessionStatusCompletion
};

typedef void (^MVRecorderSessionBlock)(MVRecorderSession *recorderSession);

/**
 * 视频录制会话: MVRecorder的数据中心. 
 * 写入、存储录制的各片段, 生成、配置AVAsset等数据.
 *
 * 如无特别说明, 该类提供的方法**不是**线程安全的. 
 * 例如提供给MVRecorder使用的Recorder类别下的方法, 可能需要在MVRecorder的
 * captureSession线程或类似的serial线程中执行, 以确保文件操作的连续性.
 *
 */
@interface MVRecorderSession : NSObject

+ (instancetype)newSessionWithConfig:(MVConfig *)config;
- (instancetype)initWithConfig:(MVConfig *)config;

+ (void)newSessionWithConfig:(MVConfig *)config selectVideoFromPhotosLibrary:(void (^)(MVRecorderSession *session))completion;

/**
 * Config for recording or choosing from PhotoLibrary.
 */
@property (nonatomic, strong, readonly) MVConfig *config;
/**
 * Configuration for editing and export.
 */
@property (nonatomic, strong, readonly) MVRecorderSessionConfiguration *sessionConfiguration;

/**
 * The unique identifier, sessionID.
 * "session_[recorderStyle]_timestamp"
 */
@property (nonatomic, copy, readonly) NSString *identifier;

@property (nonatomic) MVRecorderSessionStatus status;

/**
 * The date when this session was created.
 */
@property (nonatomic, strong, readonly) NSDate *date;

/**
 * The root directory which recorded and encoded files stored.
 * Directory name is the same as `identifier`.
 */
@property (nonatomic, copy, readonly) NSString *directory;

/**
 * The final output file URL. `<directory>/identifier.mp4`
 */
@property (nonatomic, copy, readonly) NSURL *fileURL;

/**
 * Stores all recorded segments.
 */
@property (nonatomic, strong, readonly) NSMutableArray *segments;

/**
 * The duration of the current recording segment.
 */
@property (nonatomic, readonly) CMTime currentRecordingDuration;

- (NSTimeInterval)currentRecordingDurationGetSeconds;

/**
 * The duration of all recorded segments.
 */
@property (nonatomic, readonly) CMTime segmentsDuration;

- (NSTimeInterval)segmentsDurationGetSeconds;

/**
 * Integer(四舍五入)表示duration, 不会超过self.config中预设的maxDuration和minDuration.
 * 用于上传或展示给用户的, 可能不是真实的duration, 比如config里限制了4-8秒, 真正的
 * duration是2.3秒, 那么这个方法返回的将是4, 同样的, 如果duration是20秒, 将返回8.
 */
- (int)segmentsDurationGetSecondsRepresentation;

/**
 * Returns the total duration recorded so far, including the duration of
 * the current recording segment, if any.
 *
 * `segmentsDuration + currentRecordingDuration`
 */
- (CMTime)recordedDuration;

- (NSTimeInterval)recordedDurationGetSeconds;

/**
 * Thumbnail file path.
 */
//@property (nonatomic, copy) NSString *thumbnailFile;

@end

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma mark - Helper

@interface MVRecorderSession (Helper)

/**
 * The root direcotry which all sessions stored.
 * `Library/MVRecorder`
 */
+ (NSString *)rootDirectory;
+ (void)setRootDirectory:(NSString *)directory;

/**
 * Timestamp为微妙(timeIntervalSince1970*1000000), 避免出现重复的sessionID
 */
+ (unsigned long long)timestampWithDate:(NSDate *)date;
+ (NSDate *)dateWithTimestamp:(unsigned long long)timestamp;

/**
 * Generate new sessionID.
 */
+ (NSString *)createSessionIdentifierWithRecorderStyle:(int)style date:(NSDate *)date;

+ (NSString *)createSessionIdentifierWithRecorderStyle:(int)style timestamp:(unsigned long long)timestamp;

/**
 * Generate new segment filename.
 */
+ (NSString *)createSegmentFilename;

/**
 * Filename for the the final video file.
 */
+ (NSString *)filenameWithIdentifier:(NSString *)sessionID;

/**
 * Thumbnail file name for the final video file.
 */
+ (NSString *)thumbnailFilenameWithIdentifier:(NSString *)sessionID;

/**
 * Parse sessionID, get recorderStyle and timestamp.
 * identifier可以是单独的sessionID,也可以是包含sessionID的字符串(例如filePath)
 */
+ (BOOL)parseSessionIdentifier:(NSString *)identifier recorderStyle:(int *)outRecorderStyle timestamp:(unsigned long long *)outTimestamp;

@end

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma mark - Representation

ES_EXTERN NSString *const MVRecorderSessionInfoIdentifierKey;
ES_EXTERN NSString *const MVRecorderSessionInfoStatusKey;
ES_EXTERN NSString *const MVRecorderSessionInfoDateKey;
ES_EXTERN NSString *const MVRecorderSessionInfoSegmentsKey;
ES_EXTERN NSString *const MVRecorderSessionInfoSegmentsURLKey;
ES_EXTERN NSString *const MVRecorderSessionInfoSegmentsCameraPositionKey;
/// 不保存duration: 每次加载草稿时重新计算
//ES_EXTERN NSString *const MVRecorderSessionInfoSegmentsDurationKey;
ES_EXTERN NSString *const MVRecorderSessionInfoSessionConfigurationKey;

@interface MVRecorderSession (Representation)

/**
 * 从infoRepresentation创建session可能会比较慢, 建议放到非UI线程.
 */
- (instancetype)initWithConfig:(MVConfig *)config infoRepresentationFile:(NSString *)filePath;
- (instancetype)initWithConfig:(MVConfig *)config sessionDirectoryPath:(NSString *)path;
- (instancetype)initWithConfig:(MVConfig *)config infoRepresentation:(NSDictionary *)representation;

- (NSString *)infoRepresentationFilePath;
- (NSDictionary *)createInfoRepresentation;

/**
 * 在当前线程同步保存
 */
- (BOOL)saveInfoRepresentation;
/**
 * 在global_high_queue中保存, 在主线程回调block
 */
- (void)saveInfoRepresentation:(void (^)(BOOL result))block;

@end

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma mark - Draft
@interface MVRecorderSession (Draft)

/**
 * 清理rootDirectory, 每个recorderStyle只保留最新的RecorderSession, 其他都予以删除.
 */
+ (void)cleanup;

/**
 * 删除所有recorderSession: 删除+[self rootDirectory]文件夹.
 */
+ (void)deleteAllSessions;

/**
 * 删除某一recorderStyle的所有session
 */
+ (void)deleteSessionsWithRecorderStyle:(int)recorderStyle;

/**
 * 检查是否有`recorderStyle`对应的草稿.
 * 只是检查是否有recorderStyle对应的session目录, 草稿可能不可用.
 */
+ (BOOL)hasDraftForRecorderStyle:(int)style;

/**
 * 获取该recorderStyle的所有草稿的路径, 没有则返回nil
 */
+ (NSArray *)getDraftSessionsPathsWithRecorderStyle:(int)style;

/**
 * 获取对应配置的草稿, 如果没有草稿或者草稿不可用则返回nil.
 *
 * NOTE: App启动期间第一次执行这个方法时会自动执行+cleanup, 以确保使用最新的草稿.
 */
+ (instancetype)draftSessionWithConfig:(MVConfig *)config;

@end

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma mark - Recorder

/**
 * 提供给Recorder使用的操作session的方法.
 *
 * Note: 如非特别说明, 所有方法都不是线程安全的.
 */
@interface MVRecorderSession (Recorder)

/**
 * 开始录制新的片段. 该方法返回nil的话说明初始化失败, 本次片段无法录制(写入数据)
 */
- (MVRecorderSegment *)startRecordingNewSegment;
/**
 * 当前正在录制的片段.
 */
- (MVRecorderSegment *)currentRecordingSegment;
/**
 * 当前是否正在录制片段.
 */
- (BOOL)isRecordingSegment;

/**
 * 是否支持录制缓存. 如果支持, 当在writerInput is not readyForMoreMediaData时把要写入的
 * sampleBuffer暂时写入缓存
 */
- (BOOL)isSupportRecordingCache;

/**
 * 为写入数据做准备: 配置assetWriter等.
 * Video和Audio在写入数据之前都要分别调用一次(仅一次)这个方法.
 */
- (BOOL)prepareWritingSegmentForMediaType:(NSString *)mediaType sampleBuffer:(CMSampleBufferRef)sampleBuffer error:(NSError **)outError;
/**
 * 检查对应的mediaType是否已经准备好了写数据.
 */
//- (BOOL)isPreparedWritingSegmentForMediaType:(NSString *)mediaType;

/**
 * 往当前正在录制的片段(append)video或audio数据. 默认带cache.
 * 返回NO时, 可以检查self.currentRecordingSegment.mediaWriter.status, 如果不是unkown或writing状态, 本次录制应该被Pause.
 *
 * Returns YES if writing successfully, otherwise skip sampleBuffer and returns NO.
 */
- (BOOL)writeSampleBuffer:(CMSampleBufferRef)sampleBuffer forMediaType:(NSString *)mediaType;
/**
 * 在mediaWriter.assetWriterInput.isReadyForMoreData后调用这个方法, 处理缓存数据.
 */
- (void)assetWriterInputReadyForMoreMediaDataHandler;

/**
 * Stop current recording segment.
 * `segmentIndex` will be NSNotFound if any `error` occurred.
 */
- (void)stopRecordingSegment:(void (^)(NSUInteger segmentIndex, NSError *error))completion;

/**
 * Cancel the current recording segment.
 */
- (void)cancelRecordingSegment;

/**
 * Cancel session, delete session files.
 */
- (void)cancelRecording;

/**
 * 预准备mediaWriter.
 * 在开始写数据前, videoWriter和audioWriter都必须被setup, 同时时间戳是以视频为准的, 这样会导致在
 * videoWriter和audioWriter都prepared之前, 有部分音频数据被丢失了.
 * 这里的预准备mediaWriter就是先用sampleBuffer创建writer, 只是预先创建writer而不会真正写入数据.
 */
- (void)preprepareMediaWriterForMediaType:(NSString *)mediaType sampleBuffer:(CMSampleBufferRef)sampleBuffer devicePosition:(AVCaptureDevicePosition)devicePosition;
/**
 * 在captureInputDevice发生更改时重置预创建的mediaWriter.
 */
- (void)resetPrepreparedMediaWriter;

@end

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma mark - Segment
/**
 * Segments Management.
 * 插入或删除segment会自动调用saveInfoRepresentation, <del>录制过程中无法插入或删除segment.</del>
 */
@interface MVRecorderSession (Segment)

- (MVRecorderSegment *)newSegment;
- (NSUInteger)segmentsCount;
- (BOOL)hasSegments;
- (MVRecorderSegment *)segmentAtIndex:(NSUInteger)index;
- (MVRecorderSegment *)lastSegment;

- (BOOL)insertSegment:(MVRecorderSegment *)segment atIndex:(NSUInteger)index;
- (BOOL)addSegment:(MVRecorderSegment *)segment;

- (BOOL)removeSegmentAtIndex:(NSUInteger)segmentIndex; // will delete file
- (BOOL)removeSegmentAtIndex:(NSUInteger)segmentIndex deleteFile:(BOOL)deleteFile;
- (void)removeLastSegment;
- (void)removeAllSegments:(BOOL)deleteFile;
- (void)removeAllSegments; // will delete file

@end

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma mark - Composition
@interface MVRecorderSession (Composition)
/**
 * AVComposition representation for all segments, used to edit, play and export.
 * The returned composition has already applied `sessionConfiguration`.
 */
- (BOOL)generateComposition;
- (void)cleanComposition;

/**
 * Call `-generateComposition` to generate composition, videoCompostion, and audioMix
 * to edit, export or play.
 */
- (AVMutableComposition *)composition;
- (AVMutableVideoComposition *)videoComposition;
- (AVMutableAudioMix *)audioMix;

/**
 * Call `-generateComposition` first, and you will get a playerItem with videoComposition and audioMix.
 */
- (AVPlayerItem *)playerItem;

@end

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma mark - Editor

@interface MVRecorderSession (Editor)
/**
 * 根据sessionConfiguration中的thumbnailDuration生成缩略图, 设置sessionConfiguration的
 * thumbnailFileURL和blurredThumbnailFileURL.
 * 调用此方法前必须保证self.composition是最新的.
 */
- (BOOL)generateThumbnail;

@end


//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma mark - Export

@interface MVRecorderSession (Export)

/**
 * 根据上次保存到手机相册的sessionConfiguration和当前的sessionConfiguration检测是否需要重新保存.
 */
- (BOOL)shouldResaveToPhotoLibrary;

/**
 * Merge all segments and export to file. 
 * Blocks will callbacked on the main thread.
 */
- (AVAssetExportSession *)exportSessionWithProgressChangedBlock:(void (^)(float progress))progressChangedBlock
                                                     completion:(void (^)(AVAssetExportSessionStatus status, NSURL *fileURL, NSError *error))completion;

- (AVAssetExportSession *)exportSessionWithPresetName:(NSString *)presetName
                                 progressChangedBlock:(void (^)(float progress))progressChangedBlock
                                           completion:(void (^)(AVAssetExportSessionStatus status, NSURL *fileURL, NSError *error))completion;

/**
 * completion中的completed不为YES时, 表示不要执行后面的操作 (例如用户跳转到系统设置去了)
 * saved 表示是否写入了系统相册
 */
- (void)saveToPhotoLibraryWithCompletion:(void (^)(BOOL completed, BOOL saved))completion;


@end