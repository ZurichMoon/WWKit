//
//  MVPreviewView.h
//  MVRecorder
//
//  Created by Elf Sundae on 1/9/15.
//  Copyright (c) 2015 www.0x123.com. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <GLKit/GLKit.h>
#import <CoreVideo/CoreVideo.h>

/**
 * Video Preview View that rendered with OpenGL ES.
 */
@interface MVPreviewView : GLKView

- (void)displayPixelBuffer:(CVPixelBufferRef)pixelBuffer;

@end
