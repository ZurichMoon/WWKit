//
//  MVError.h
//  MVRecorder
//
//  Created by Elf Sundae on 14-11-26.
//  Copyright (c) 2014年 www.0x123.com. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <ESFrameworkCore/ESFrameworkCore.h>

ES_EXTERN NSString *const MVErrorDomain;

typedef NS_ENUM(NSInteger, MVErrorCode) {
        MVErrorCodeUnknown                      = -1,
        MVErrorCodeInternal                     = 10,
        MVErrorCodeCameraIsNotAuthorized        = 100,
        MVErrorCodeMicrophoneIsNotAuthorized    = 101,
        MVErrorCodePhotosAlbumIsNotAuthorized   = 102,
        MVErrorCodeCaptureSessionFailed         = 200,
        MVErrorCodeCanNotStartSegment           = 300,
        MVErrorCodeMediaWriterFailed            = 301,
        MVErrorCodeMediaWriterCancelled         = 302,
        MVErrorCodeSegmentCancelled             = 303,
        MVErrorCodeSegmentIsInvalid             = 304,
        MVErrorCodeExportError                  = 400,
        
        MVErrorCodeSavePhotosAlbumError         = 1000,
};

@interface NSError (MVError)
+ (instancetype)mvError:(MVErrorCode)code description:(NSString *)description;
@end
