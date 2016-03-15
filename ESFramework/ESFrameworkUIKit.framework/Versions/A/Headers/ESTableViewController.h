//
//  ESTableViewController.h
//  ESFramework
//
//  Created by Elf Sundae on 4/29/14.
//  Copyright (c) 2014 www.0x123.com. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <ESFrameworkCore/ESFrameworkCore.h>
#import "ESTableViewDataSource.h"
#import "ESRefreshControl.h"
#import "UIViewController+ESStatusOverlayView.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma mark - ESTableViewController

/**
 * `UIViewController` coontains a `UITableView`
 */
@interface ESTableViewController : UIViewController <UITableViewDelegate>
{
        UITableView *_tableView;
}

@property (nonatomic, strong) UITableView *tableView;
@property (nonatomic, readonly) UITableViewStyle tableViewStyle;

/// defaults to YES. If YES, any selection is cleared in viewWillAppear:
@property (nonatomic) BOOL clearsSelectionOnViewWillAppear;

- (instancetype)initWithStyle:(UITableViewStyle)style;

@end

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma mark - DataSource
@interface ESTableViewController (DataSource) <ESTableViewDataSource>
@end
