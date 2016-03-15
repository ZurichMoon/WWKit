//
//  ESMoviePlayerViewController.h
//  ESFramework
//
//  Created by Elf Sundae on 5/17/14.
//  Copyright (c) 2014 www.0x123.com. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <MediaPlayer/MediaPlayer.h>
#import <ESFrameworkCore/ESFrameworkCore.h>

/**
 * `ESMoviePlayerViewController` will automatically listen `UIApplicationDidEnterBackgroundNotification` to stop playing,
 * and listen `UIApplicationWillEnterForegroundNotification` to resume playing.
 */
@interface ESMoviePlayerViewController : MPMoviePlayerViewController

@property (nonatomic) BOOL dismissWhenPlaybackEnded;
@property (nonatomic) BOOL autoPlayWhenEnterForeground;
@property (nonatomic, copy) ESBasicBlock willAppearBlock;
@property (nonatomic, copy) ESBasicBlock dismissedBlock;
/** Only works on iOS6.0+ */
@property (nonatomic) UIInterfaceOrientation initialInterfaceOrientation;

- (void)present;

@end
