//
//  MVMediaWriter.h
//  MVRecorder
//
//  Created by Elf Sundae on 14-12-8.
//  Copyright (c) 2014年 www.0x123.com. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <AVFoundation/AVFoundation.h>
@class MVMediaWriter;

typedef void (^MVMediaWriterAssetWriterInputBlock)(MVMediaWriter *mediaWriter, AVAssetWriterInput *assetWriterInput, NSString *mediaType);

@interface MVMediaWriter : NSObject

/**
 * Returns nil if initialization filure.
 */
- (instancetype)initWithURL:(NSURL *)outputURL error:(NSError **)outError;

@property (nonatomic, readonly) AVAssetWriter *assetWriter;

@property (nonatomic, readonly) AVAssetWriterInput *videoAssetWriterInput;
@property (nonatomic, readonly) AVAssetWriterInput *audioAssetWriterInput;

- (AVAssetWriterInput *)assetWriterInputForMediaType:(NSString *)mediaType;
- (NSString *)mediaTypeForAssetWriterInput:(AVAssetWriterInput *)writerInput;

@property (nonatomic,strong) NSArray *metadata;
- (NSError *)error;
- (NSURL *)outputURL;
- (AVAssetWriterStatus)status;

@property (nonatomic, readonly, getter=isVideoReady) BOOL videoReady;
@property (nonatomic, readonly, getter=isAudioReady) BOOL audioReady;
- (BOOL)isReadyForMediaType:(NSString *)mediaType;

/**
 * 在写数据之前要先调用这个方法setup, video和audio各调用一次.
 * setup成功后, videoReady或audioReady就为YES了, 表示可以正常写入数据.
 */
- (BOOL)setupWithSettings:(NSDictionary *)settings forMediaType:(NSString *)mediaType;

/**
 * 在实时音视频处理(例如写入文件)中, AVAssetWriterInput的ReadyForMoreMediaData可能因为来不及处理而为NO.
 * 这个方式是设置在writerInput的ReadyForMoreMediaData属性为YES时的回调.
 *
 * 使用情景:在appendSampleBuffer时如果 ReadyForMoreMediaData 为NO, 可以先保存sampleBuffer, 等到这个方法回调
 * 时再写入. 这样就不用丢弃掉这些sampleBuffer.
 *
 * 注意: 此回调非线程安全, 外部应该dispatch到dataWriting线程执行后续操作.
 *
 * @see 官方文档 -[AVAssetWriterInput readyForMoreMediaData]
 */
@property (nonatomic, copy) MVMediaWriterAssetWriterInputBlock assetWriterInputReadyForMoreMediaDataHandler;

@end
