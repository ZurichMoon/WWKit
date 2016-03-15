//
//  MVFocusView.h
//  MVRecorder
//
//  Created by Elf Sundae on 14-11-27.
//  Copyright (c) 2014年 www.0x123.com. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface MVFocusView : UIView

/**
 * Default frame is  80x80
 */
+ (instancetype)newInstance;

/**
 * Optional set the focus' image.
 */
@property (nonatomic) UIImage *image;
@property (nonatomic, strong, readonly) UIImageView *imageView;

/**
 * Set center to `point` and apply animation.
 */
- (void)showAtPoint:(CGPoint)point;
- (void)hide;

@end
