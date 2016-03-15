//
//  MVSampleBuffer.h
//  MVRecorder
//
//  Created by Elf Sundae on 14-12-8.
//  Copyright (c) 2014年 www.0x123.com. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <AVFoundation/AVFoundation.h>

/**
 * MVSampleBuffer is designed as a holder to retain CMSampleBufferRef.
 */
@interface MVSampleBuffer : NSObject

@property (nonatomic) CMSampleBufferRef sampleBuffer;
@property (nonatomic, copy) NSString *mediaType;

- (instancetype)initWithSampleBuffer:(CMSampleBufferRef)sampleBuffer mediaType:(NSString *)mediaType;

@end
