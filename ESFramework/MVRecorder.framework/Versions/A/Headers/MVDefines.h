//
//  MVDefines.h
//  MVRecorder
//
//  Created by Elf Sundae on 14-12-8.
//  Copyright (c) 2014年 www.0x123.com. All rights reserved.
//

#import <ESFrameworkCore/ESFrameworkCore.h>

ES_EXTERN NSString *const MVRecorderVersion;

ES_EXTERN void _MVLog_(NSString *format, ...);

#ifdef DEBUG
#define MVLog(format, ...) _MVLog_((@"%@:%d %s " format), [[NSString stringWithUTF8String:__FILE__] lastPathComponent], __LINE__, __PRETTY_FUNCTION__, ##__VA_ARGS__)
#else
#define MVLog(format, ...)
#endif

#define __DEMO_FILTER   0