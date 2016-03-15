//
//  ESButton.h
//  ESFramework
//
//  Created by Elf Sundae on 4/20/14.
//  Copyright (c) 2014 www.0x123.com. All rights reserved.
//

#import <UIKit/UIKit.h>

typedef NS_ENUM(NSUInteger, ESButtonStyle) {
        ESButtonStyleRoundedRect = 100,
        /** Half circle */
        ESButtonStyleSemi,
        ESButtonStyleCircle,
};

typedef NS_ENUM(NSUInteger, ESButtonColor) {
        ESButtonColorDefault,
        ESButtonColorPrimary,
        ESButtonColorInfo,
        ESButtonColorSuccess,
        ESButtonColorWarning,
        ESButtonColorDanger,
        ESButtonColorInverse,
        ESButtonColorTwitter,
        ESButtonColorFacebook,
        ESButtonColorPurple,
        ESButtonColorGray,
        ESButtonColorRed,
};

/**
 * UIButton with rounded style.
 */
@interface ESButton : UIButton

@property (nonatomic) ESButtonStyle buttonStyle;
@property (nonatomic) ESButtonColor buttonColor;
@property (nonatomic, strong) UIColor *color;
@property (nonatomic) CGFloat cornerRadius;
@property (nonatomic) BOOL isFlatStyle;
@property (nonatomic) BOOL applyFlatStyleAutomatically; // default is YES

+ (instancetype)button;
+ (instancetype)buttonWithTitle:(NSString *)title;
+ (instancetype)buttonWithTitle:(NSString *)title buttonColor:(ESButtonColor)color;
+ (instancetype)buttonWithCircleImage:(UIImage *)image;

+ (UIColor *)buttonColor:(ESButtonColor)color;
@end
