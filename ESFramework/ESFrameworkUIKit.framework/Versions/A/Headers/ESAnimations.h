//
//  ESAnimations.h
//  ESFramework
//
//  Created by Elf Sundae on 14-4-7.
//  Copyright (c) 2014 www.0x123.com. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <QuartzCore/QuartzCore.h>

/**
 * Animations.
 *
 * Example:
 *
 * @code
 * [someView.layer addAnimation:[ESAnimations popup] forKey:nil];
 * [someView setNeedsDisplay];
 * @endcode
 *
 */
@interface ESAnimations : NSObject

+ (CAKeyframeAnimation *)popup:(double)duration;
+ (CATransition *)fade:(double)duration;

+ (CATransition *)pushFromTop:(double)duration;
+ (CATransition *)pushFromLeft:(double)duration;
+ (CATransition *)pushFromBottom:(double)duration;
+ (CATransition *)pushFromRight:(double)duration;

@end
