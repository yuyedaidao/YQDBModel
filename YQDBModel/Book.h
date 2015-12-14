//
//  Book.h
//  YQDBModel
//
//  Created by 王叶庆 on 15/12/12.
//  Copyright © 2015年 王叶庆. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "NSObject+YQDBModel.h"
@interface Book : NSObject<YQModel>
@property (nonatomic, copy) NSString *name;
/**
 *  图书馆序号
 */
@property (nonatomic, assign) NSInteger number;
@end
