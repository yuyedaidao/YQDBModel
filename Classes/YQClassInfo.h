//
//  YQDBClassInfo.h
//  YQDBModel 因为没办法用YY大神 .m 文件的相关接口，所以可耻地全复制了相关类
//  膜拜：https://github.com/ibireme
//  Created by 王叶庆 on 15/12/12.
//  Copyright © 2015年 王叶庆. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <objc/runtime.h>

/**
 Type encoding's type.
 */
typedef NS_OPTIONS(NSUInteger, YQEncodingType) {
    YQEncodingTypeMask       = 0xFF, ///< mask of type value
    YQEncodingTypeUnknown    = 0, ///< unknown
    YQEncodingTypeVoid       = 1, ///< void
    YQEncodingTypeBool       = 2, ///< bool
    YQEncodingTypeInt8       = 3, ///< char / BOOL
    YQEncodingTypeUInt8      = 4, ///< unsigned char
    YQEncodingTypeInt16      = 5, ///< short
    YQEncodingTypeUInt16     = 6, ///< unsigned short
    YQEncodingTypeInt32      = 7, ///< int
    YQEncodingTypeUInt32     = 8, ///< unsigned int
    YQEncodingTypeInt64      = 9, ///< long long
    YQEncodingTypeUInt64     = 10, ///< unsigned long long
    YQEncodingTypeFloat      = 11, ///< float
    YQEncodingTypeDouble     = 12, ///< double
    YQEncodingTypeLongDouble = 13, ///< long double
    YQEncodingTypeObject     = 14, ///< id
    YQEncodingTypeClass      = 15, ///< Class
    YQEncodingTypeSEL        = 16, ///< SEL
    YQEncodingTypeBlock      = 17, ///< block
    YQEncodingTypePointer    = 18, ///< void*
    YQEncodingTypeStruct     = 19, ///< struct
    YQEncodingTypeUnion      = 20, ///< union
    YQEncodingTypeCString    = 21, ///< char*
    YQEncodingTypeCArray     = 22, ///< char[10] (for example)
    
    YQEncodingTypeQualifierMask   = 0xFF00,   ///< mask of qualifier
    YQEncodingTypeQualifierConst  = 1 << 8,  ///< const
    YQEncodingTypeQualifierIn     = 1 << 9,  ///< in
    YQEncodingTypeQualifierInout  = 1 << 10, ///< inout
    YQEncodingTypeQualifierOut    = 1 << 11, ///< out
    YQEncodingTypeQualifierBycopy = 1 << 12, ///< bycopy
    YQEncodingTypeQualifierByref  = 1 << 13, ///< byref
    YQEncodingTypeQualifierOneway = 1 << 14, ///< oneway
    
    YQEncodingTypePropertyMask         = 0xFF0000, ///< mask of property
    YQEncodingTypePropertyReadonly     = 1 << 16, ///< readonly
    YQEncodingTypePropertyCopy         = 1 << 17, ///< copy
    YQEncodingTypePropertyRetain       = 1 << 18, ///< retain
    YQEncodingTypePropertyNonatomic    = 1 << 19, ///< nonatomic
    YQEncodingTypePropertyWeak         = 1 << 20, ///< weak
    YQEncodingTypePropertyCustomGetter = 1 << 21, ///< getter=
    YQEncodingTypePropertyCustomSetter = 1 << 22, ///< setter=
    YQEncodingTypePropertyDynamic      = 1 << 23, ///< @dynamic
};

/**
 Get the type from a Type-Encoding string.
 
 @discussion See also:
 https://developer.apple.com/library/mac/documentation/Cocoa/Conceptual/ObjCRuntimeGuide/Articles/ocrtTypeEncodings.html
 https://developer.apple.com/library/mac/documentation/Cocoa/Conceptual/ObjCRuntimeGuide/Articles/ocrtPropertyIntrospection.html
 
 @param typeEncoding  A Type-Encoding string.
 @return The encoding type.
 */
YQEncodingType YQEncodingGetType(const char *typeEncoding);


/**
 Instance variable information.
 */
@interface YQClassIvarInfo : NSObject
@property (nonatomic, assign, readonly) Ivar ivar;              ///< ivar opaque struct
@property (nonatomic, strong, readonly) NSString *name;         ///< Ivar's name
@property (nonatomic, assign, readonly) ptrdiff_t offset;       ///< Ivar's offset
@property (nonatomic, strong, readonly) NSString *typeEncoding; ///< Ivar's type encoding
@property (nonatomic, assign, readonly) YQEncodingType type;    ///< Ivar's type

/**
 Creates and returns an ivar info object.
 
 @param ivar ivar opaque struct
 @return A new object, or nil if an error occurs.
 */
- (instancetype)initWithIvar:(Ivar)ivar;
@end


/**
 Method information.
 */
@interface YQClassMethodInfo : NSObject
@property (nonatomic, assign, readonly) Method method;                  ///< method opaque struct
@property (nonatomic, strong, readonly) NSString *name;                 ///< method name
@property (nonatomic, assign, readonly) SEL sel;                        ///< method's selector
@property (nonatomic, assign, readonly) IMP imp;                        ///< method's implementation
@property (nonatomic, strong, readonly) NSString *typeEncoding;         ///< method's parameter and return types
@property (nonatomic, strong, readonly) NSString *returnTypeEncoding;   ///< return value's type
@property (nonatomic, strong, readonly) NSArray *argumentTypeEncodings; ///< array of arguments' type

/**
 Creates and returns a method info object.
 
 @param method method opaque struct
 @return A new object, or nil if an error occurs.
 */
- (instancetype)initWithMethod:(Method)method;
@end


/**
 Property information.
 */
@interface YQClassPropertyInfo : NSObject
@property (nonatomic, assign, readonly) objc_property_t property; ///< property's opaque struct
@property (nonatomic, strong, readonly) NSString *name;           ///< property's name
@property (nonatomic, assign, readonly) YQEncodingType type;      ///< property's type
@property (nonatomic, strong, readonly) NSString *typeEncoding;   ///< property's encoding value
@property (nonatomic, strong, readonly) NSString *ivarName;       ///< property's ivar name
@property (nonatomic, assign, readonly) Class cls;                ///< may be nil
@property (nonatomic, strong, readonly) NSString *getter;         ///< getter (nonnull)
@property (nonatomic, strong, readonly) NSString *setter;         ///< setter (nonnull)

/**
 Creates and returns a property info object.
 
 @param property property opaque struct
 @return A new object, or nil if an error occurs.
 */
- (instancetype)initWithProperty:(objc_property_t)property;
@end


/**
 Class information for a class.
 */
@interface YQClassInfo : NSObject
@property (nonatomic, assign, readonly) Class cls;      ///< class object
@property (nonatomic, assign, readonly) Class superCls; ///< super class object
@property (nonatomic, assign, readonly) Class metaCls;  ///< class's meta class object
@property (nonatomic, assign, readonly) BOOL isMeta;    ///< whether this class is meta class
@property (nonatomic, strong, readonly) NSString *name; ///< class name
@property (nonatomic, strong, readonly) YQClassInfo *superClassInfo; ///< super class's class info
@property (nonatomic, strong, readonly) NSDictionary *ivarInfos;     ///< key:NSString(ivar),     value:YQClassIvarInfo
@property (nonatomic, strong, readonly) NSDictionary *methodInfos;   ///< key:NSString(selector), value:YQClassMethodInfo
@property (nonatomic, strong, readonly) NSDictionary *propertyInfos; ///< key:NSString(property), value:YQClassPropertyInfo

/**
 If the class is changed (for example: you add a method to this class with
 'class_addMethod()'), you should call this method to refresh the class info cache.
 
 After called this method, you may call 'classInfoWithClass' or
 'classInfoWithClassName' to get the updated class info.
 */
- (void)setNeedUpdate;

/**
 Get the class info of a specified Class.
 
 @discussion This method will cache the class info and super-class info
 at the first access to the Class. This method is thread-safe.
 
 @param cls A class.
 @return A class info, or nil if an error occurs.
 */
+ (instancetype)classInfoWithClass:(Class)cls;

/**
 Get the class info of a specified Class.
 
 @discussion This method will cache the class info and super-class info
 at the first access to the Class. This method is thread-safe.
 
 @param className A class name.
 @return A class info, or nil if an error occurs.
 */
+ (instancetype)classInfoWithClassName:(NSString *)className;

@end
