//
//  MVPlayer.h
//  MVRecorder
//
//  Created by Elf Sundae on 15-1-5.
//  Copyright (c) 2015年 www.0x123.com. All rights reserved.
//


#import <AVFoundation/AVFoundation.h>
@class MVPlayer;
#import "MVRenderer.h"

//@protocol MVPlayerDelegate;

typedef void (^MVPlayerDidPlayToEndTimeBlock)(MVPlayer *player, AVPlayerItem *currentOriginalItem, NSError *error);

/**
 * 因为self.renderer使用了AVPlayerItemVideoOutput, 所以MVPlayer只支持iOS6+.
 */
@interface MVPlayer : AVPlayer

/**
 * Returns a player instance with no playerItem, 
 * playerItem can be set using `-replaceCurrentItem...`
 */

+ (instancetype)player;

+ (instancetype)playerWithDidPlayToEndTimeBlock:(MVPlayerDidPlayToEndTimeBlock)block;

//@property (nonatomic, weak) __weak id<MVPlayerDelegate> delegate;
@property (nonatomic, copy) MVPlayerDidPlayToEndTimeBlock didPlayToEndTimeBlock;


/**
 * 为了达到平滑的循环播放, currentItem在播放前被设置成了多个asset的合体(AVComposition).
 * `currentOriginalItem`返回原始的单个item.
 */
@property (nonatomic, strong, readonly) AVPlayerItem *currentOriginalItem;

@property (nonatomic, strong) id<MVRenderer> renderer;

/**
 * The number of times that the sound will return to the beginning upon reaching the end.
 * A value of zero means to play just once.
 * A value of one will result in playing twice, and so on..
 * Any negative number will loop indefinitely until stopped.
 */
//@property (nonatomic) NSInteger numberOfLoops;

/**
 * Indicates the current item should be loopped playing.
 * If it is set before -replaceCurrentItem... , the loop playing will be smoothly.
 *
 * Default value if NO.
 */
@property (nonatomic, getter=isLoopEnabled) BOOL loopEnabled;

/**
 * Stop playing and reset playingItem to nil.
 */
- (void)reset;

- (BOOL)isPlaying;
- (BOOL)canPlay;
- (CMTime)playableDuration;

- (void)replaceCurrentItemWithURL:(NSURL *)url;
- (void)replaceCurrentItemWithAsset:(AVAsset *)asset;

@end


//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma mark - MVPlayerDelegate

//@protocol MVPlayerDelegate <NSObject>
//@optional
//- (void)player:(MVPlayer *)player didPlayToEndTime:(AVPlayerItem *)playerItem;
//@end