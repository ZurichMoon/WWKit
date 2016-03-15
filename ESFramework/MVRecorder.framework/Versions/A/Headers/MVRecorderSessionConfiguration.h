//
//  MVRecorderSessionConfiguration.h
//  MVRecorder
//
//  Created by Elf Sundae on 2/4/15.
//  Copyright (c) 2015 www.0x123.com. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <AVFoundation/AVFoundation.h>

/**
 * 编辑视频的配置
 */
@interface MVRecorderSessionConfiguration : NSObject <NSCopying>

/**
 * 是否开启原音, 默认开启., --KVO
 */
@property (nonatomic) BOOL originalVoiceOn;
/**
 * 背景音乐的音量
 */
@property (nonatomic) float musicVolume;
/**
 * 背景音乐的本地地址, 为nil时表示没有背景音乐. --KVO
 */
@property (nonatomic, copy) NSURL *musicFileURL;
/**
 * 是否添加背景音乐
 */
- (BOOL)isMusicOn;

/**
 * 剪裁视频的bounds. 如果视频是正方形, 则这个值是CGRectZero.
 */
@property (nonatomic) CGRect videoClipsBounds;

/**
 * 从此处截取封面
 */
@property (nonatomic) NSTimeInterval thumbnailTime;

/**
 * 视频封面的文件地址, 如果还没有生成封面则该值为nil.
 */
@property (nonatomic, copy) NSURL *thumbnailFileURL;
/**
 * 模糊过的视频封面的文件地址, 如果还没有生成则该值为nil.
 */
@property (nonatomic, copy) NSURL *blurredThumbnailFileURL;
/**
 * 最终生成的视频是否已经保存到系统相册了
 */
@property (nonatomic) BOOL hasSavedToPhotoLibrary;

+ (instancetype)configurationWithRepresentation:(NSData *)data;
- (NSData *)representation;

/**
 * 将所有配置重置
 */
- (void)resetToDefaults;

/**
 * 检查两个配置是否相同, 用于检测是否需要重新保存视频到手机相册
 */
//- (BOOL)isEqualToConfiguration:(MVRecorderSessionConfiguration *)configuration;

@end
