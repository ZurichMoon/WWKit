//
//  ESStoreProductViewControllerManager.h
//  ESFramework
//
//  Created by Elf Sundae on 14-4-10.
//  Copyright (c) 2014 www.0x123.com. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <ESFrameworkCore/ESFrameworkCore.h>

/**
 * Singleton that presenting `SKStoreProductViewController` if it's exists.
 *
 * On iOS 6.0 or later, it will present `SKStoreProductViewController` if the
 * iTunes Store is reachable, or else it will uses [ESApp openURL:] to open App Store.
 *
 */
@interface ESStoreProductViewControllerManager : NSObject

ES_SINGLETON_DEC(sharedManager);

- (BOOL)isSKStoreProductViewControllerExists;
- (BOOL)hasPresentedProductViewController;

/**
 * The first time to present `SKStoreProductViewController` will be slowly, 
 * you can show a activityView or HUD, and hide it in `willAppear` block.
 */
- (void)openWithItemURL:(NSURL *)iTunesLink willAppear:(ESBasicBlock)willAppear;

///=============================================
/// @name App Special
///=============================================

- (void)openWithAppID:(NSString *)appID willAppear:(ESBasicBlock)willAppear;

@end
