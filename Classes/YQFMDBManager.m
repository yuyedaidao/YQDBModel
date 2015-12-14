//
//  YQFMDBManager.m
//  YQDBModel
//
//  Created by 王叶庆 on 15/12/12.
//  Copyright © 2015年 王叶庆. All rights reserved.
//

#import "YQFMDBManager.h"

#define DBDEBUG

@interface YQFMDBManager ()
@property (nonatomic, copy) NSString *dbPath;
@property (nonatomic, strong) FMDatabase *database;
@property (nonatomic, strong) FMDatabaseQueue *dbQueue;
/**
 *  = dbPath/dbName
 */
@property (nonatomic, copy) NSString *dbFullPath;
@end

@implementation YQFMDBManager

+ (instancetype)sharedManager{
    static dispatch_once_t onceToken;
    static YQFMDBManager *_manager;
    dispatch_once(&onceToken, ^{
        _manager = [YQFMDBManager new];
        _manager.dbPath = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES).firstObject;
    });
    return _manager;
}

- (FMDatabase *)currentDB{
    if(!self.database){
        NSAssert(self.dbName, @"请先指定dbName");
        self.database = [FMDatabase databaseWithPath:_dbFullPath];
        if([self.database open]) return self.database;
        return nil;
    }
    return self.database;
}

- (FMDatabaseQueue *)dbQueue{
    if(!self.dbQueue){
        NSAssert(self.dbName, @"请先指定dbName");
        self.dbQueue = [FMDatabaseQueue databaseQueueWithPath:_dbFullPath];
        NSAssert(self.dbQueue, @"dbQueue创建失败");
    }
    return self.dbQueue;
}

#pragma mark set & get
- (void)setDbName:(NSString *)dbName{
    if(![dbName isEqualToString:_dbName]){
        _dbName = dbName;
        _dbFullPath = [NSString stringWithFormat:@"%@/%@.%@",_dbPath,_dbName,@"sqlite"];
    }
}

@end
