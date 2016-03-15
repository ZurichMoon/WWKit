//
//  MVPlayerPreviewView.h
//  MVRecorder
//
//  Created by Elf Sundae on 1/16/15.
//  Copyright (c) 2015 www.0x123.com. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "MVPlayer.h"

@interface MVPlayerPreviewView : UIView

@property (nonatomic, strong, readonly) AVPlayerLayer *layer;
@property (nonatomic, strong) MVPlayer *player;
/**
 * AVLayerVideoGravityResizeAspectFill is default.
 */
@property (nonatomic, copy) NSString *videoGravity;

- (instancetype)initWithFrame:(CGRect)frame player:(MVPlayer *)player;

@end
