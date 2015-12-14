//
//  User.m
//  YQDBModel
//
//  Created by 王叶庆 on 15/12/12.
//  Copyright © 2015年 王叶庆. All rights reserved.
//

#import "User.h"

@implementation User

+ (NSDictionary *)modelContainerPropertyGenericClass{
    return @{
             @"friends":[User class],
             @"favBook":[Book class]
             };
}

+ (NSString *)primaryKey{
    return @"name";
}

+ (YQPKType)primaryKeyType{
    return YQPKTypeString;
}

- (NSString *)friendsDBMapperValue{
    NSMutableArray *value = [NSMutableArray array];
    [self.friends enumerateObjectsUsingBlock:^(User  *_Nonnull obj, NSUInteger idx, BOOL * _Nonnull stop) {
        [value addObject:obj.name];
    }];
    return [value componentsJoinedByString:@","];
}
@end
