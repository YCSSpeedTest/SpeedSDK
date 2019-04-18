//Copyright © 2019 Max. All rights reserved.

#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>
#import "SpeedTestSimplePing.h"

typedef NS_ENUM(NSInteger, SpeedTestPingStatus) {
    SpeedTestPingStatusDidStart,
    SpeedTestPingStatusDidFailToSendPacket,
    SpeedTestPingStatusDidReceivePacket,
    SpeedTestPingStatusDidReceiveUnexpectedPacket,
    SpeedTestPingStatusDidTimeout,
    SpeedTestPingStatusError,
    SpeedTestPingStatusFinished,
};

@interface SpeedTestPingItem : NSObject

@property(nonatomic) NSString *originalAddress;
@property(nonatomic, copy) NSString *IPAddress;

@property(nonatomic) NSUInteger dateBytesLength;
@property(nonatomic) double     timeMilliseconds;
@property(nonatomic) NSInteger  timeToLive;
@property(nonatomic) NSInteger  ICMPSequence;

@property(nonatomic) SpeedTestPingStatus status;

+ (NSString *)statisticsWithPingItems:(NSArray *)pingItems;
+ (NSString *)showLoss:(NSArray *)pingItems;
@end

@interface SpeedTestPingServices : NSObject

/// 超时时间, default 500ms
@property(nonatomic) double timeoutMilliseconds;

+ (SpeedTestPingServices *)startPingAddress:(NSString *)address
                      callbackHandler:(void(^)(SpeedTestPingItem *pingItem, NSArray *pingItems))handler;

@property(nonatomic) NSInteger  maximumPingTimes;
- (void)cancel;

@end

