//
//  UITableViewCell+ESTableViewAdditions.h
//  ESFramework
//
//  Created by Elf Sundae on 5/21/14.
//  Copyright (c) 2014 www.0x123.com. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <ESFrameworkCore/ESFrameworkCore.h>

@interface UITableViewCell (ESTableViewAdditions)

@property (nonatomic, strong) id dataObject;
+ (CGFloat)tableView:(UITableView *)tableView rowHeightForObject:(id)dataObject;

@end
