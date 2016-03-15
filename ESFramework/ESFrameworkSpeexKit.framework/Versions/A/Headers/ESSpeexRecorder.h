//
//  ESSpeexRecorder.h
//  ESFramework
//
//  Created by Elf Sundae on 7/20/14.
//  Copyright (c) 2014 www.0x123.com. All rights reserved.
//

@import Foundation;
@class ESSpeexRecorder;
#import "ESSpeexRecorderSettings.h"

typedef NS_ENUM(NSInteger, ESSpeexRecorderResult) {
        /* Finished by calling -stopRecording; */
        ESSpeexRecorderFinishedNormal                   = 0,
        /* Finished because the maxDuraiton reached */
        ESSpeexRecorderFinishedWithMaxDurationReached   = 1,
        /* Finished because the audio session has beeen interrupted */
        ESSpeexRecorderFinishedWithInterruption         = 2,
        
        /* Recorder setup failure */
        ESSpeexRecorderSetupFailure                     = -100,
        /* Audio input is not available */
        ESSpeexRecorderAudioInputIsNotAvailable         = -101,
        /* Recorder permission denied */
        ESSpeexRecorderPermissionDenied                 = -102,
        /* Encoding error occurred */
        ESSpeexRecorderEncodingErrorOccurred            = -201,
        /* Unknwon error occurred */
        ESSpeexRecorderUnknownErrorOccurred             = -300,
        /* The minDuration is not reached */
        ESSpeexRecorderMinDurationNotReached            = -400,
        /* There's no audio data, for example, stop recording too soon */
        ESSpeexRecorderNoAudioData                      = -500,
};

typedef void (^ESSpeexRecorderBlock)(ESSpeexRecorder *recorder,
                                     ESSpeexRecorderResult result,
                                     NSString *file,
                                     NSTimeInterval duration);

/**
 * An audio recorder that encoded with Speex codec.
 */
@interface ESSpeexRecorder : NSObject

/**
 * Returns the default output directory of speex files.
 */
+ (NSString *)directoryOfAudioFiles;

/**
 * `file` and `settings` both can be nil.
 */
- (instancetype)initWithFile:(NSString *)file settings:(ESSpeexRecorderSettings *)settings;
- (instancetype)initWithSettings:(ESSpeexRecorderSettings *)settings;
- (instancetype)init;

/**
 * Start recording.
 */
- (void)startWithCompletion:(ESSpeexRecorderBlock)completion;
@property (nonatomic, copy) ESSpeexRecorderBlock completion;

/**
 * Stop recording, the recoder and encoder will may not be stopped immediately
 * if there are any reset PCM data to be encoded.
 *
 * When the encoder finished, the `completion` block will be invoked.
 */
- (void)stopRecording;

/**
 * Stop recording, and the recoder and encoder will stop immediately,
 * Asynchronous stops occur after all queued
 buffers have been played or recorded.
 * the `completion` block will be invoked.
 */
- (void)stop;

/**
 * Detect if it is recording or not.
 */
- (BOOL)isRecording;

/**
 * Delete the recorded file. 
 * The recorder must be stopped. 
 * Returns NO on failure.
 */
- (BOOL)deleteRecordedFile;

/**
 * Call to refresh meter values.
 */
- (void)updateMeters;

/**
 * Returns peak power in range 0-1 for a given channel.
 */
- (float)peakPowerForChannel:(NSUInteger)channelNumber;

/**
 * Returns average power in range 0-1 for a given channel.
 */
- (float)averagePowerForChannel:(NSUInteger)channelNumber;

/**
 * Settings for the Audio Recorder and the Speex Encoder,
 * it can be set by -initWithSettings: method.
 */
- (ESSpeexRecorderSettings *)settings;

/**
 * Get the current duration of the recording - only valid while recording.
 */
- (NSTimeInterval)currentDuration;

@end
