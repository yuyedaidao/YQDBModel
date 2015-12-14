//
//  User.h
//  YQDBModel
//
//  Created by 王叶庆 on 15/12/12.
//  Copyright © 2015年 王叶庆. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "NSObject+YQDBModel.h"
#import "Book.h"

@interface User : NSObject<YQModel>
@property (nonatomic, copy) NSString *name;
@property (nonatomic, assign) NSInteger age;
@property (nonatomic, strong) Book *favBook;
@property (nonatomic, strong) NSArray *friends;
@end
