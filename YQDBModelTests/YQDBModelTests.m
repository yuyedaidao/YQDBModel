//
//  YQDBModelTests.m
//  YQDBModelTests
//
//  Created by 王叶庆 on 15/12/12.
//  Copyright © 2015年 王叶庆. All rights reserved.
//

#import <XCTest/XCTest.h>
#import "YQFMDBManager.h"
#import "User.h"

@interface YQDBModelTests : XCTestCase

@end

@implementation YQDBModelTests

- (void)setUp {
    [super setUp];
    // Put setup code here. This method is called before the invocation of each test method in the class.
    YQFMDBManager *m = [YQFMDBManager sharedManager];
    m.dbName = @"wang";
    [User createTable];
    [Book createTable];
}

- (void)tearDown {
    // Put teardown code here. This method is called after the invocation of each test method in the class.
    [super tearDown];
}

- (void)testExample {
    // This is an example of a functional test case.
    // Use XCTAssert and related functions to verify your tests produce the correct results.
}

- (void)testPerformanceExample {
    // This is an example of a performance test case.
    [self measureBlock:^{
        // Put the code you want to measure the time of here.
    }];
}

- (void)testUser{
//    User *user = [User new];
    NSLog(@"create user :%d",[User createTable]);
}

- (void)testYYModel{
    User *user = [User new];
    user.name = @"大头";
    user.age = 13;

    Book *book = [Book new];
    book.name = @"清明上河图";
    book.number = 123;
    user.favBook = book;
    
    User *a = [User new];
    a.name = @"二小";
    
    User *b = [User new];
    b.name = @"三孬";
    
    user.friends = @[a,b];
    
    User *user1 = [User new];
    user1.name = @"大头";

    NSLog(@"save user : %u",[user save]);
    NSLog(@"save user1 : %u",[user1 save]);
}

- (void)testUpdate{
    User *user = [User new];
    user.name = @"大头";
    user.age = 13;
    
    Book *book = [Book new];
    book.name = @"清明上河图";
    book.number = 123;
    user.favBook = book;
    
    User *a = [User new];
    a.name = @"二小";
    
    User *b = [User new];
    b.name = @"三孬";
    
    user.friends = @[a,b];
    
//    NSLog(@"update user %u",[user update]);
    NSLog(@"saveOrUpdate %u",[user saveOrUpdate]);
}
- (void)testFMDBManager{
    YQFMDBManager *m = [YQFMDBManager sharedManager];
    m.dbName = @"wang";
    NSLog(@"db path :%@",[m valueForKey:@"dbFullPath"]);
    
}
@end
