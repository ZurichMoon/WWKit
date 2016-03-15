//
//  MVFilterGroup.h
//  MVRecorder
//
//  Created by Elf Sundae on 15-1-6.
//  Copyright (c) 2015年 www.0x123.com. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <CoreImage/CoreImage.h>
#import <CoreVideo/CoreVideo.h>

@interface MVFilterGroup : NSObject

@property (nonatomic, strong, readonly) NSMutableArray *filters;

- (instancetype)initWithFilters:(NSArray *)filters;
- (instancetype)initWithFilter:(CIFilter *)filter;
- (void)addFilter:(CIFilter *)filter;
- (void)removeFilter:(CIFilter *)filter;
- (CIImage *)processImage:(CIImage *)image;

@end
