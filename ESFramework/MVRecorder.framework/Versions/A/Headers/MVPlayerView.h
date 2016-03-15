//
//  MVPlayerView.h
//  MVRecorder
//
//  Created by Elf Sundae on 1/16/15.
//  Copyright (c) 2015 www.0x123.com. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "MVPlayer.h"

@interface MVPlayerView : UIView

- (instancetype)initWithFrame:(CGRect)frame player:(MVPlayer *)player;

@property (nonatomic, strong) MVPlayer *player;
@property (nonatomic, strong, readonly) AVPlayerLayer *layer;
/**
 * AVLayerVideoGravityResizeAspectFill is default.
 */
@property (nonatomic, copy) NSString *videoGravity;


/**
 * When the `tapActionHandler` is not nil, `MVPlayerView` will pause/resume the player
 * when is is tapped. Otherwise, the tap-to-pause feature will be disabled.
 * You can check `playerView.player.isPlaying` to detect if the player playing or pausing.
 */
@property (nonatomic, copy) void (^tapActionHandler)(MVPlayerView *playerView, BOOL isPlaying);
- (BOOL)tapActionEnabled;
/**
 * The image shows when the player was paused, normally it is a "Tap To Play" Icon.
 */
@property (nonatomic, strong) UIImage *imageForPausedState;
@property (nonatomic, strong, readonly) UIImageView *imageViewForPausedState;

@end
