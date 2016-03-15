//
//  MVSkinWhiten.h
//  MVRecorder
//
//  Created by Elf Sundae on 1/14/15.
//  Copyright (c) 2015 www.0x123.com. All rights reserved.
//

#import <CoreImage/CoreImage.h>

@interface MVSkinWhiten : CIFilter
@property (nonatomic, strong) CIImage *inputImage;
@property (nonatomic, strong) NSArray *inputFacesMetadata;
@property (nonatomic, strong) NSNumber *inputDegree;
@end
