//
//  YQFMDBManager.h
//  YQDBModel
//
//  Created by 王叶庆 on 15/12/12.
//  Copyright © 2015年 王叶庆. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <FMDB.h>

@interface YQFMDBManager : NSObject

+ (instancetype)sharedManager;
@property (nonatomic, copy) NSString *dbName;
/**
 *  根据配置的dbName返回一个FMDatabase(需手动close)
 */
@property (nonatomic, readonly) FMDatabase *currentDB;
/**
 *  根据配置的dbName返回一个FMDatabaseQueue(需手动close)
 */
@property (nonatomic, readonly) FMDatabaseQueue *currentDBQueue;
@end
