//
//  NSObject+ESNotification.m
//  QXLoveCity
//
//  Created by Elf Sundae on 3/10/15.
//  Copyright (c) 2015 www.0x123.com. All rights reserved.
//

#import "NSObject+ESNotification.h"

#pragma mark - Notification with block
@interface NSObject (_ESObserverInternal)
/**
 * 保存所有notication的handlers: notification_name => handlers array
 */
@property (nonatomic, strong) NSMutableDictionary *__es_notificationHandlers;
@end

static const void *__es_notificationHandlersKey = &__es_notificationHandlersKey;

@implementation NSObject (ESObserver)
- (void)set__es_notificationHandlers:(NSMutableDictionary *)handlers
{
        [self setAssociatedObject_nonatomic_retain:handlers key:__es_notificationHandlersKey];
}
- (NSMutableDictionary *)__es_notificationHandlers
{
        NSMutableDictionary *dict = [self getAssociatedObject:__es_notificationHandlersKey];
        if (!dict) {
                dict = [NSMutableDictionary dictionary];
                [self set__es_notificationHandlers:dict];
        }
        return dict;
}
- (void)__es_appendNotificationHandler:(ESNotificationHandler)handler toName:(NSString *)name
{
        [[self __es_notificationHandlersWithName:name] addObject:[handler copy]];
}
- (NSMutableArray *)__es_notificationHandlersWithName:(NSString *)name
{
        NSMutableArray *array = self.__es_notificationHandlers[name];
        if (!array) {
                array = [NSMutableArray array];
                (self.__es_notificationHandlers)[name] = array;
        }
        return array;
}

/// Notification Handler
- (void)__es_notificationSelector:(NSNotification *)notification
{
        NSMutableArray *array = [self __es_notificationHandlersWithName:notification.name];
        for (ESNotificationHandler handler in array) {
                handler(notification, notification.userInfo);
        }
}

- (void)addNotification:(NSString *)name handler:(ESNotificationHandler)handler
{
        if (ESIsStringWithAnyText(name) && handler) {
                [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(__es_notificationSelector:) name:name object:nil];
                [self __es_appendNotificationHandler:handler toName:name];
        }
}

- (void)removeNotification:(NSString *)name
{
        if (ESIsStringWithAnyText(name)) {
                [[NSNotificationCenter defaultCenter] removeObserver:self name:name object:nil];
                [self.__es_notificationHandlers removeObjectForKey:name];
        } else {
                NSMutableDictionary *dict = [self getAssociatedObject:__es_notificationHandlersKey];
                [dict enumerateKeysAndObjectsWithOptions:NSEnumerationConcurrent usingBlock:^(id key, id obj, BOOL *stop) {
                        [[NSNotificationCenter defaultCenter] removeObserver:self name:(NSString *)key object:nil];
                }];
                [dict removeAllObjects];
        }
}

@end
