//
//  ESTextView.h
//  ESFramework
//
//  Created by Elf Sundae on 5/20/14.
//  Copyright (c) 2014 www.0x123.com. All rights reserved.
//

#import <UIKit/UIKit.h>

typedef NS_ENUM(NSInteger, ESTextViewBorderStyle) {
        ESTextViewBorderStyleNone = 0,
        ESTextViewBorderStyleLine,
        ESTextViewBorderStyleRoundedRect,
};

/**
 * `ESTextView` is a subclass of `UITextView` that supports some interface style,
 * and can be set a placeholder.
 *
 * TODO: implemente in next version.
 *
 */
@interface ESTextView : UITextView
@property (nonatomic, copy) NSString *placeholder;
@property (nonatomic, strong) UIColor *placeholderColor;
@property (nonatomic) ESTextViewBorderStyle borderStyle;
@end
