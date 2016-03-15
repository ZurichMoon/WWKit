//
//  ESTableViewDataSource.h
//  ESFramework
//
//  Created by Elf Sundae on 5/20/14.
//  Copyright (c) 2014 www.0x123.com. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "UITableViewCell+ESTableViewAdditions.h"

@protocol ESTableViewDataSource <UITableViewDataSource>
@required
/**
 * Returns the object for cell.
 */
- (id)tableView:(UITableView *)tableView dataObjectForRowAtIndexPath:(NSIndexPath *)indexPath;

@optional

/**
 * Returns `UITableViewCell` subclass, tableView will use `UITableViewCell` class if this method is not
 * implemented or returned `nil`.
 */
- (Class)tableView:(UITableView *)tableView cellClassForRowAtIndexPath:(NSIndexPath *)indexPath dataObject:(id)dataObject;
/**
 * Alloc the cell instance with `cellClass` and `reuseIdentifier`.
 * Default implementation:
 * @code
 * return [[cellClass alloc] initWithStyle:UITableViewCellStyleDefault reuseIdentifier:reuseIdentifier];
 * @endcode
 */
- (UITableViewCell *)tableView:(UITableView *)tableView cellNewInstanceForClass:(Class)cellClass reuseIdentifier:(NSString *)reuseIdentifier indexPath:(NSIndexPath *)indexPath;
/**
 * Invoked within `-tableView:cellForRowAtIndexPath:`
 */
- (void)tableView:(UITableView *)tableView willAppearCell:(UITableViewCell *)cell forRowAtIndexPath:(NSIndexPath *)indexPath dataObject:(id)dataObject;

@end