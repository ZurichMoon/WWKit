//
//  MVPixelBufferView.h
//  MVRecorder
//
//  Created by Elf Sundae on 1/12/15.
//  Copyright (c) 2015 www.0x123.com. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <GLKit/GLKit.h>
#import <CoreImage/CoreImage.h>
#import "MVFilterGroup.h"
#import "MVRenderer.h"

/**
 * OpenGL渲染视图, 可带滤镜. 
 * 用于视频录制和编辑播放时的实时预览.
 *
 * 参考https://github.com/ElfSundae/AVDemo/blob/master/RosyWriter/Classes/Utilities/OpenGLPixelBufferView.h
 * https://github.com/rFlex/SCRecorder/blob/master/Library/Sources/SCImageView.h
 */
@interface MVPixelBufferView : GLKView

- (void)displayPixelBuffer:(CVPixelBufferRef)pixelBuffer;

@end
