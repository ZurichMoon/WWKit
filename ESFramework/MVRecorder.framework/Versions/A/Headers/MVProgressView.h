//
//  MVProgressView.h
//  MVRecorder
//
//  Created by Elf Sundae on 1/29/15.
//  Copyright (c) 2015 www.0x123.com. All rights reserved.
//

#import <UIKit/UIKit.h>
@class MVConfig;
@class MVRecorderSession;

/**
 * 显示视频节点(segment)的进度条.
 * 实际使用中, 只有当录制时长有最大限制时显示MVProgressView才有意义. 因为没有最大录制时间就无法计算progress.
 */
@interface MVProgressView : UIView

- (instancetype)initWithFrame:(CGRect)frame config:(MVConfig *)config;

/// 进度
@property (nonatomic) float progress;
/// 要显示节点的位置(contains NSNumber with float, [0, 1])
@property (nonatomic, strong) NSArray *segments;
/// 节点的颜色, 默认为nil, 即和progressTintColor一致,这样会使节点看起来是透明的
@property (nonatomic, strong) UIColor *segmentsTintColor;

@property (nonatomic, strong) UIColor *progressTintColor;
@property (nonatomic, strong) UIColor *trackTintColor;
/// 锚点(录制最小限制)位置的颜色
@property (nonatomic, strong) UIColor *anchorTintColor;
@property (nonatomic) CGFloat anchorPosition;
/// 最右边的进度指示器
@property (nonatomic, strong) UIImage *progressIndicatorImage;
/// 默认为0, 指示器没动画时默认显示在当前progressWidth
@property (nonatomic) CGFloat progressIndicatorOffset;
/// 默认为0, 指示器动画时默认显示在progressWidth的右边
@property (nonatomic) CGFloat progressIndicatorOffsetWhenAnimating;
/// 片段高亮(待删除)时的颜色
@property (nonatomic, strong) UIColor *segmentHighlightedTintColor;

@property (nonatomic, getter=isHighlighted) BOOL highlighted;

/**
 * 读取recorderSesion的segments和config的minRecordedDuration和maxRecordedDuration, 
 * 自动设置MVProgressView的segments和progress.
 */
- (void)setProgressWithRecorderSession:(MVRecorderSession *)session;

/**
 * App resign active时会自动停止动画, 请调用者自行在appBecomeActive再开启动画(检查progressView是否正在显示).
 * setProgress时也自动停止动画.
 */
- (void)startProgressIndicatorAnimation;
- (void)stopProgressIndicatorAnimation;
- (BOOL)isProgressIndicatorAnimating;

@end
