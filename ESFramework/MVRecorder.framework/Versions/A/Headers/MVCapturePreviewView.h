//
//  MVRecorderPreviewView.h
//  MVRecorder
//
//  Created by Elf Sundae on 14-11-26.
//  Copyright (c) 2014年 www.0x123.com. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <AVFoundation/AVFoundation.h>
#import "MVFocusView.h"

@interface MVCapturePreviewView : UIView

- (instancetype)initWithCaptureSession:(AVCaptureSession *)session;

@property (nonatomic) AVCaptureSession *captureSession;
@property (nonatomic, strong, readonly) AVCaptureVideoPreviewLayer *layer;
/// Default is AVLayerVideoGravityResizeAspectFill
@property (nonatomic, copy) NSString *videoGravity;
/**
 * Enable / Disable previewing.
 */
@property (nonatomic) BOOL enabled;

@property (nonatomic, strong) MVFocusView *focusView;

- (void)showFocusAt:(CGPoint)point;
- (void)hideFocus;

/*!
 @method captureDevicePointOfInterestForPoint:
 @abstract
 Converts a point in layer coordinates to a point of interest in the coordinate space of the capture device providing
 input to the layer.
 
 @param pointInLayer
 A CGPoint in layer coordinates.
 
 @result
 A CGPoint in the coordinate space of the capture device providing input to the layer.
 
 @discussion
 AVCaptureDevice pointOfInterest is expressed as a CGPoint where {0,0} represents the top left of the picture area,
 and {1,1} represents the bottom right on an unrotated picture.  This convenience method converts a point in
 the coordinate space of the receiver to a point of interest in the coordinate space of the AVCaptureDevice providing
 input to the receiver.  The conversion takes frameSize and videoGravity into consideration.
 */
- (CGPoint)captureDevicePointOfInterestForPoint:(CGPoint)pointInLayer;

@end
