//
//  Book.m
//  YQDBModel
//
//  Created by 王叶庆 on 15/12/12.
//  Copyright © 2015年 王叶庆. All rights reserved.
//

#import "Book.h"

@implementation Book

+ (NSString *)primaryKey{
    return @"number";
}

+ (YQPKType)primaryKeyType{
    return YQPKTypeNumber;
}

@end
