//
//  NSObject+YQDBModel.h
//  YQDBModel
//  YQDBModel 因为没办法用YY 大神 .m 文件的相关接口，所以可耻地复制了部分代码
//  膜拜：https://github.com/ibireme
//  Created by 王叶庆 on 15/12/12.
//  Copyright © 2015年 王叶庆. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "YQFMDBManager.h"
#import "YQClassInfo.h"
#import "YQSQLCache.h"

#ifndef YQOREqual
#define YQOREqual(Obj,...) (NSLog(@"该功能稍后实现"),NO) //TODO:稍后实现
#define YQOREqual2(Obj,con1,con2) ((Obj) == (con1) || (Obj) == (con2))
#endif


typedef NS_ENUM(NSUInteger, YQPKType) {
    YQPKTypeNumber,
    YQPKTypeString,
};

@interface NSObject (YQModel)

/**
 Creates and returns a new instance of the receiver from a json.
 This method is thread-safe.
 
 @param json  A json object in `NSDictionary`, `NSString` or `NSData`.
 
 @return A new instance created from the json, or nil if an error occurs.
 */
+ (instancetype)YQ_modelWithJSON:(id)json;

/**
 Creates and returns a new instance of the receiver from a key-value dictionary.
 This method is thread-safe.
 
 @param dictionary  A key-value dictionary mapped to the instance's properties.
 Any invalid key-value pair in dictionary will be ignored.
 
 @return A new instance created from the dictionary, or nil if an error occurs.
 
 @discussion The key in `dictionary` will mapped to the reciever's property name,
 and the value will set to the property. If the value's type does not match the
 property, this method will try to convert the value based on these rules:
 
 `NSString` or `NSNumber` -> c number, such as BOOL, int, long, float, NSUInteger...
 `NSString` -> NSDate, parsed with format "YQYQ-MM-dd'T'HH:mm:ssZ", "YQYQ-MM-dd HH:mm:ss" or "YQYQ-MM-dd".
 `NSString` -> NSURL.
 `NSValue` -> struct or union, such as CGRect, CGSize, ...
 `NSString` -> SEL, Class.
 */
+ (instancetype)YQ_modelWithDictionary:(NSDictionary *)dictionary;

/**
 Set the receiver's properties with a json object.
 
 @discussion Any invalid data in json will be ignored.
 
 @param json  A json object of `NSDictionary`, `NSString` or `NSData`, mapped to the
 receiver's properties.
 
 @return Whether succeed.
 */
- (BOOL)YQ_modelSetWithJSON:(id)json;

/**
 Set the receiver's properties with a key-value dictionary.
 
 @param dic  A key-value dictionary mapped to the receiver's properties.
 Any invalid key-value pair in dictionary will be ignored.
 
 @discussion The key in `dictionary` will mapped to the reciever's property name,
 and the value will set to the property. If the value's type doesn't match the
 property, this method will try to convert the value based on these rules:
 
 `NSString`, `NSNumber` -> c number, such as BOOL, int, long, float, NSUInteger...
 `NSString` -> NSDate, parsed with format "YQYQ-MM-dd'T'HH:mm:ssZ", "YQYQ-MM-dd HH:mm:ss" or "YQYQ-MM-dd".
 `NSString` -> NSURL.
 `NSValue` -> struct or union, such as CGRect, CGSize, ...
 `NSString` -> SEL, Class.
 
 @return Whether succeed.
 */
- (BOOL)YQ_modelSetWithDictionary:(NSDictionary *)dic;

/**
 Generate a json object from the receiver's properties.
 
 @return A json object in `NSDictionary` or `NSArray`, or nil if an error occurs.
 See [NSJSONSerialization isValidJSONObject] for more information.
 
 @discussion Any of the invalid property is ignored.
 If the reciver is `NSArray`, `NSDictionary` or `NSSet`, it just convert
 the inner object to json object.
 */
- (id)YQ_modelToJSONObject;

/**
 Generate a json string's data from the receiver's properties.
 
 @return A json string's data, or nil if an error occurs.
 
 @discussion Any of the invalid property is ignored.
 If the reciver is `NSArray`, `NSDictionary` or `NSSet`, it will also convert the
 inner object to json string.
 */
- (NSData *)YQ_modelToJSONData;

/**
 Generate a json string from the receiver's properties.
 
 @return A json string, or nil if an error occurs.
 
 @discussion Any of the invalid property is ignored.
 If the reciver is `NSArray`, `NSDictionary` or `NSSet`, it will also convert the
 inner object to json string.
 */
- (NSString *)YQ_modelToJSONString;

/**
 Copy a instance with the receiver's properties.
 
 @return A copied instance, or nil if an error occurs.
 */
- (id)YQ_modelCopy;

/**
 Encode the receiver's properties to a coder.
 
 @param aCoder  An archiver object.
 */
- (void)YQ_modelEncodeWithCoder:(NSCoder *)aCoder;

/**
 Decode the receiver's properties from a decoder.
 
 @param aDecoder  An archiver object.
 
 @return self
 */
- (id)YQ_modelInitWithCoder:(NSCoder *)aDecoder;

/**
 Get a hash code with the receiver's properties.
 
 @return Hash code.
 */
- (NSUInteger)YQ_modelHash;

/**
 Compares the receiver with another object for equality, based on properties.
 
 @param model  Another object.
 
 @return `YES` if the reciever is equal to the object, otherwise `NO`.
 */
- (BOOL)YQ_modelIsEqual:(id)model;

@end



/**
 Provide some data-model method for NSArray.
 */
@interface NSArray (YQModel)

/**
 Creates and returns an array from a json-array.
 This method is thread-safe.
 
 @param cls  The instance's class in array.
 @param json  A json array of `NSArray`, `NSString` or `NSData`.
 Example: [{"name","Mary"},{name:"Joe"}]
 
 @return A array, or nil if an error occurs.
 */
+ (NSArray *)YQ_modelArrayWithClass:(Class)cls json:(id)json;

@end



/**
 Provide some data-model method for NSDictionary.
 */
@interface NSDictionary (YQModel)

/**
 Creates and returns a dictionary from a json.
 This method is thread-safe.
 
 @param cls  The value instance's class in dictionary.
 @param json  A json dictionary of `NSDictionary`, `NSString` or `NSData`.
 Example: {"user1":{"name","Mary"}, "user2": {name:"Joe"}}
 
 @return A array, or nil if an error occurs.
 */
+ (NSDictionary *)YQ_modelDictionaryWithClass:(Class)cls json:(id)json;
@end



/**
 If the default model transform does not fit to your model class, implement one or
 more method in this protocol to change the default key-value transform process.
 There's no need to add '<YQModel>' to your class header.
 */
@protocol YQModel <NSObject>
@optional

/**
 Custom property mapper.
 
 @discussion If the key in JSON/Dictionary does not match to the model's property name,
 implements this method and returns the additional mapper.
 
 Example:
 
 json:
 {
 "n":"Harry Pottery",
 "p": 256,
 "ext" : {
 "desc" : "A book written by J.K.Rowing."
 },
 "ID" : 100010
 }
 
 model:
 @interface YQBook : NSObject
 @property NSString *name;
 @property NSInteger page;
 @property NSString *desc;
 @property NSString *bookID;
 @end
 
 @implementation YQBook
 + (NSDictionary *)modelCustomPropertyMapper {
 return @{@"name"  : @"n",
 @"page"  : @"p",
 @"desc"  : @"ext.desc",
 @"bookID": @[@"id", @"ID", @"book_id"]};
 }
 @end
 
 @return A custom mapper for properties.
 */
+ (NSDictionary *)modelCustomPropertyMapper;

/**
 The generic class mapper for container properties.
 
 @discussion If the property is a container object, such as NSArray/NSSet/NSDictionary,
 implements this method and returns a property->class mapper, tells which kind of
 object will be add to the array/set/dictionary.
 
 Example:
 @class YQShadow, YQBorder, YQAttachment;
 
 @interface YQAttributes
 @property NSString *name;
 @property NSArray *shadows;
 @property NSSet *borders;
 @property NSDictionary *attachments;
 @end
 
 @implementation YQAttributes
 + (NSDictionary *)modelContainerPropertyGenericClass {
 return @{@"shadows" : [YQShadow class],
 @"borders" : YQBorder.class,
 @"attachments" : @"YQAttachment" };
 }
 @end
 
 @return A class mapper.
 */
+ (NSDictionary *)modelContainerPropertyGenericClass;

/**
 If you need to create instances of different classes during json->object transform,
 use the method to choose custom class based on dictionary data.
 
 @discussion If the model implements this method, it will be called to determine resulting class
 during `+modelWithJSON:`, `+modelWithDictionary:`, conveting object of properties of parent objects
 (both singular and containers via `+modelContainerPropertyGenericClass`).
 
 Example:
 @class YQCircle, YQRectangle, YQLine;
 
 @implementation YQShape
 
 + (Class)modelCustomClassForDictionary:(NSDictionary*)dictionary {
 if (dictionary[@"radius"] != nil) {
 return [YQCircle class];
 } else if (dictionary[@"width"] != nil) {
 return [YQRectangle class];
 } else if (dictionary[@"y2"] != nil) {
 return [YQLine class];
 } else {
 return [self class];
 }
 }
 
 @end
 
 @param dictionary The json/kv dictionary.
 
 @return Class to create from this dictionary, `nil` to use current class.
 
 */
+ (Class)modelCustomClassForDictionary:(NSDictionary*)dictionary;

/**
 All the properties in blacklist will be ignored in model transform process.
 Returns nil to ignore this feature.
 
 @return An array of property's name (Array<NSString>).
 */
+ (NSArray *)modelPropertyBlacklist;

/**
 If a property is not in the whitelist, it will be ignored in model transform process.
 Returns nil to ignore this feature.
 
 @return An array of property's name (Array<NSString>).
 */
+ (NSArray *)modelPropertyWhitelist;

/**
 If the default json-to-model transform does not fit to your model object, implement
 this method to do additional process. You can also use this method to validate the
 model's properties.
 
 @discussion If the model implements this method, it will be called at the end of
 `+modelWithJSON:`, `+modelWithDictionary:`, `-modelSetWithJSON:` and `-modelSetWithDictionary:`.
 If this method returns NO, the transform process will ignore this model.
 
 @param dic  The json/kv dictionary.
 
 @return Returns YES if the model is valid, or NO to ignore this model.
 */
- (BOOL)modelCustomTransformFromDictionary:(NSDictionary *)dic;

/**
 If the default model-to-json transform does not fit to your model class, implement
 this method to do additional process. You can also use this method to validate the
 json dictionary.
 
 @discussion If the model implements this method, it will be called at the end of
 `-modelToJSONObject` and `-modelToJSONString`.
 If this method returns NO, the transform process will ignore this json dictionary.
 
 @param dic  The json dictionary.
 
 @return Returns YES if the model is valid, or NO to ignore this model.
 */
- (BOOL)modelCustomTransformToDictionary:(NSMutableDictionary *)dic;
/**
 *  建表时使用的主键 实现该方法必须实现primaryKeyType
 *
 *  @return 必须是属性之一
 */
+ (NSString *)primaryKey;
/**
 *  主键类型 实现该方法必须实现primaryKey
 *
 *  @return YQPKType
 */
+ (YQPKType)primaryKeyType;
@end


@interface NSObject (YQModelPropertyBlacklist)
@end

@interface NSObject (YQDBModel)
/**
 *  用于存储update、insert等sql语句
 */
+ (YQSQLCache *)sqlCache;
/**
 *  已当前类名创建数据表
 *
 *  @return 表是否创建成功
 */
+ (BOOL)createTable;
/**
 *  更新或者保存
 *
 *  @return 更新或保存是否成功
 */
- (BOOL)saveOrUpdate;
/**
 *  保存
 *
 *  @return 保存是否成功
 */
- (BOOL)save;
/**
 *  更新
 *
 *  @return 更新是否成功
 */
- (BOOL)update;
/**
 *  根据条件查找
 *
 *  @param condition 条件语句 (like "where name = '王二'")
 *
 *  @return 符合条件的所有对象
 */
+ (NSArray *)selectWithCondition:(NSString *)condition;
@end

