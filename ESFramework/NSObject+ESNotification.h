//
//  NSObject+ESNotification.h
//  QXLoveCity
//
//  Created by Elf Sundae on 3/10/15.
//  Copyright (c) 2015 www.0x123.com. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_INLINE CGRect ESRectExpandWithEdgeInsets(CGRect rect, UIEdgeInsets insets) {
        return UIEdgeInsetsInsetRect(rect, insets);
}

NS_INLINE CGRect ESRectExpandWithEdgeInsetsFrom(CGRect rect, CGFloat top, CGFloat left, CGFloat bottom, CGFloat right) {
        return ESRectExpandWithEdgeInsets(rect, UIEdgeInsetsMake(top, left, bottom, right));
}

/**
 * `return floorf((containerSize.width - size.width) / 2.f);`
 */
ES_INLINE CGFloat ESSizeCenterX(CGSize containerSize, CGSize size) {
        return floorf((containerSize.width - size.width) / 2.f);
}

/**
 * `return floorf((containerSize.height - size.height) / 2.f);`
 */
ES_INLINE CGFloat ESSizeCenterY(CGSize containerSize, CGSize size) {
        return floorf((containerSize.height - size.height) / 2.f);
}

///=============================================
/// @name Notification with block
///=============================================
#pragma mark - Notification with block

typedef void (^ESNotificationHandler)(NSNotification *notification, NSDictionary *userInfo);
@interface NSObject (ESObserver)
/**
 * Add `self` to `NSNotificationCenter` as an observer.
 */
- (void)addNotification:(NSString *)name handler:(ESNotificationHandler)handler;
/**
 * Remove notification which added using `-addNotification:handler:`.
 * When the `name` is nil, it will remove all noticications added using `-addNotification:handler:`.
 */
- (void)removeNotification:(NSString *)name;

@end