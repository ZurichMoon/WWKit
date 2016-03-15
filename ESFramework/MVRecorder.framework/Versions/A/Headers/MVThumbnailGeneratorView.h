//
//  MVThumbnailGeneratorView.h
//  MVRecorder
//
//  Created by Elf Sundae on 2/11/15.
//  Copyright (c) 2015 www.0x123.com. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <AVFoundation/AVFoundation.h>

@interface MVThumbnailGeneratorView : UIView

- (instancetype)initWithFrame:(CGRect)frame asset:(AVAsset *)asset;

/**
 * Set `asset` will change `generator`, you can reset configuration for generator after
 * `asset` change.
 */
@property (nonatomic, strong) AVAsset *asset;
@property (nonatomic, strong, readonly) AVAssetImageGenerator *generator;

/**
 * Default is 0, means no background
 */
@property (nonatomic) NSUInteger segmentsCount;

@property (nonatomic) CMTime thumbnailRequestedTime;
/// KVO 
@property (nonatomic, readonly) CMTime thumbnailActualTime;

/// Contains all segmenets
@property (nonatomic, strong, readonly) UIView *segmentsBackgroundView;
/// Slider thumb.
@property (nonatomic, strong, readonly) UIImageView *thumbImageView;

@property (nonatomic, strong, readonly) UILabel *tipsLabel;

/// Size for every segment, default is CGSizeZero that it will be automatically calculated
/// according `self.frame.width` and `segmentsCount`.
@property (nonatomic) CGSize segmentsSize;
/// thumbImageView的尺寸是segmentsSize加上thumbInsets, 默认是UIEdgeInsetsZero
@property (nonatomic) UIEdgeInsets thumbInsets;

@end
