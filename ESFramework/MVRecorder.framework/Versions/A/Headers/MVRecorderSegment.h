//
//  MVRecorderSegment.h
//  MVRecorder
//
//  Created by Elf Sundae on 14-11-26.
//  Copyright (c) 2014年 www.0x123.com. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <AVFoundation/AVFoundation.h>
#import "MVMediaWriter.h"
#import "MVConfig.h"

/**
 * Video Segments associated filesystem.
 */
@interface MVRecorderSegment : NSObject

- (instancetype)initWithFileURL:(NSURL *)fileURL;
+ (instancetype)segmentWithFileURL:(NSURL *)fileURL;

/**
 * 写入数据前对Video和Audio分别调一次setup.
 * 可以通过 -[segment.mediaWriter isReadyForMediaType:] 检查是否已经setup过.
 *
 * 详见 -[MVMediaWriter setupWithSettings:forMediaType:];
 */
- (BOOL)setupMediaWriterForMediaType:(NSString *)mediaType sampleBuffer:(CMSampleBufferRef)sampleBuffer config:(MVConfig *)config error:(NSError **)outError;
- (BOOL)isMediaWriterReadyForMediaType:(NSString *)mediaType;
/**
 * Ready for writing, both of AVMediaTypeVideo and AVMediaTypeAudio.
 */
- (BOOL)isMediaWriterReadyForWriting;
/**
 * Generate thumbnail, save it to current directory and named it to
 * <segment_name>.jpg, e.g. "segment_20141028.mp4.jpg"
 *
 * Note: call this method only after writing sampleBuffers.
 */
- (NSString *)generateThumbnail;
/**
 * 取消本片段的录制, 删除文件(如有)
 */
- (void)cancel;

@property (nonatomic, copy, readonly) NSURL *fileURL;
@property (nonatomic, strong, readonly) MVMediaWriter *mediaWriter;
/**
 * 标记该段segment是前置还是后置摄像头录制的, 用于翻转视频画面.
 * 默认为AVCaptureDevicePositionUnspecified.
 * FIXME: 不知道能不能从assetTrack中获取该信息.
 */
@property (nonatomic) AVCaptureDevicePosition cameraPosition;

/**
 * Lazily loaded, `[AVAsset assetWithURL:self.fileURL];`
 */
@property (nonatomic, strong) AVURLAsset *asset;
/**
 * Lazily loaded.
 */
@property (nonatomic, strong) AVPlayerItem *playerItem;
@property (nonatomic, readonly) CMTime duration;

- (BOOL)deleteFile;

@end
