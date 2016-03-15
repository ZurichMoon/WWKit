//
//  ESSpeexPlayer.h
//  ESFramework
//
//  Created by Elf Sundae on 7/17/14.
//  Copyright (c) 2014 www.0x123.com. All rights reserved.
//

@import Foundation;
@class ESSpeexPlayer;

extern NSString *const ESSpeexPlayerErrorDomain;

typedef NS_ENUM(NSInteger, ESSpeexPlayerErrorCode) {
        /* Audio file is not a correct speex file */
        ESSpeexPlayerErrorCodeBadFile           = 100,
        /* Decoder error, or iOS audio components error */
        ESSpeexPlayerErrorCodePlayingError      = 101,
};

typedef void (^ESSpeexPlayerBlock)(NSString *file, NSError *error);

/**
 * An audio player that can play Speex (Ogg contained) files.
 */
@interface ESSpeexPlayer : NSObject

+ (instancetype)sharedPlayer;

- (void)playFile:(NSString *)file didFinishPlaying:(ESSpeexPlayerBlock)didFinishPlaying;
- (void)stop;
- (BOOL)isPlaying;

@property (nonatomic) float volume;
@property (nonatomic, copy) ESSpeexPlayerBlock didFinishPlayingBlock;

@end
