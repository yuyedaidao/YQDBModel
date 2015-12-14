//
//  YQSQLCache.h
//  YQDBModel
//
//  Created by 王叶庆 on 15/12/13.
//  Copyright © 2015年 王叶庆. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface YQSQLCache : NSObject

@property (nonatomic, copy) NSString *saveSql;
@property (nonatomic, copy) NSString *updateSql;
@property (nonatomic, copy) NSString *countSql;

@end
