//
//  MVPixelBuffer.h
//  MVRecorder
//
//  Created by Elf Sundae on 1/12/15.
//  Copyright (c) 2015 www.0x123.com. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreVideo/CoreVideo.h>

/**
 * CVPixelBufferRef holder.
 */
@interface MVPixelBuffer : NSObject

//@property(nonatomic, retain) __attribute__((NSObject)) CVPixelBufferRef pixelBuffer;
@property (nonatomic) CVPixelBufferRef pixelBuffer;

- (instancetype)initWithPixelBuffer:(CVPixelBufferRef)buffer;

@end
