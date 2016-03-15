//
//  ESSpeexRecorderSettings.h
//  ESFramework
//
//  Created by Elf Sundae on 7/29/14.
//  Copyright (c) 2014 www.0x123.com. All rights reserved.
//

@import Foundation;

typedef NS_ENUM(NSInteger, ESSpeexModeID) {
        ESSpeexModeIDNarrowband         = 0,
        ESSpeexModeIDWideband           = 1,
        ESSpeexModeIDUltraWideband      = 2,
};

/**
 * Speex is mainly designed for three different sampling
 * rates: 8 kHz, 16 kHz, and 32 kHz. These are respectively
 * refered to as narrowband, wideband and ultra-wideband.
 */
extern int ESSpeexRecorderSampleRateForModeID(ESSpeexModeID modeID);

/**
 * Settings for audio recorder and Speex encoder.
 *
 * Recommended settings for voice recording:
 *      encoderQuality: 2
 *      enableVAD: YES
 *      enableDenoise: YES
 *
 */
@interface ESSpeexRecorderSettings : NSObject

///=============================================
/// @name Recorder
///=============================================

/// Default is 0.0, which means there is no maximum duration limit
/// until disk space is not enough.
@property (nonatomic) NSTimeInterval maxDuration;
/// Minimum duration required, recorder will fail when duration is
/// less than `minDuration`. Defaults is 0.0, means no limit
@property (nonatomic) NSTimeInterval minDuration;
/// Default is NO
@property (nonatomic) BOOL enableAudioLevelMetering;
/// Sampling rate (Hz) for recording, 6000~48000,
/// default is 8000 `ESSpeexRecorderSampleRateForModeID(ESSpeexModeIDNarrowband);`
@property (nonatomic) int recorderSampleRate;
/// Enable stereo (2 channels), default is mono (1 channels)
@property (nonatomic) BOOL enableStereo;

///=============================================
/// @name Encoder
///=============================================

/**
 * Refer: http://www.speex.org/docs/manual/speex-manual/node4.html#SECTION00410000000000000000
 */

/// Auto selected speex modeID from `recorderSampleRate`
@property (nonatomic, readonly) ESSpeexModeID speexModeID;
/// Encoding quality (0-10), default is 2
@property (nonatomic) int encoderQuality;
/// Encoding bit-rate (use bit-rate n or lower)
@property (nonatomic) int encoderBitRate;
/// Enable VBR (Variable Bit-Rate), disabled by default
@property (nonatomic) BOOL enableVBR;
/// Set max VBR bit-rate allowed
@property (nonatomic) int VBRMaxBitrate;
/// Enable average bit-rate (ABR) at rate bps
@property (nonatomic) int ABR;
/// Enable voice activity detection (VAD), enabled by default
@property (nonatomic) BOOL enableVAD;
/// Enable file-based discontinuous transmission (DTX)
@property (nonatomic) BOOL enableDTX;
/// Denoise the input before encoding, enabled by default
@property (nonatomic) BOOL enableDenoise;
/// Set encoding complexity (0-10), default 3
@property (nonatomic) int encoderComplexity;

/// Pack n frames in each Ogg packet (this saves space at low bit-rates)
/// Number of frames per Ogg packet (1-10), default 1
@property (nonatomic) int framesPerPacket;

/// Title for this track.
@property (nonatomic, copy) NSString *title;
/// Author of this track.
@property (nonatomic, copy) NSString *author;
/// NSString => NSString
@property (nonatomic, strong) NSDictionary *comments;

@end
