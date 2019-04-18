//Copyright © 2019 Max. All rights reserved.

@import Foundation;

#include <AssertMacros.h>

NS_ASSUME_NONNULL_BEGIN

@protocol SpeedTestSimplePingDelegate;



typedef NS_ENUM(NSInteger, SpeedTestSimplePingAddressStyle) {
    SpeedTestSimplePingAddressStyleAny,          ///< Use the first IPv4 or IPv6 address found; the default.
    SpeedTestSimplePingAddressStyleICMPv4,       ///< Use the first IPv4 address found.
    SpeedTestSimplePingAddressStyleICMPv6        ///< Use the first IPv6 address found.
};



@interface SpeedTestSimplePing : NSObject

- (instancetype)init NS_UNAVAILABLE;


- (instancetype)initWithHostName:(NSString *)hostName NS_DESIGNATED_INITIALIZER;


@property (nonatomic, copy, readonly) NSString * hostName;



@property (nonatomic, weak, readwrite, nullable) id<SpeedTestSimplePingDelegate> delegate;


@property (nonatomic, assign, readwrite) SpeedTestSimplePingAddressStyle addressStyle;



@property (nonatomic, copy, readonly, nullable) NSData * hostAddress;
@property (nonatomic, copy, readonly, nullable) NSString *IPAddress;
@property (nonatomic, assign, readonly) NSInteger packetLength;



@property (nonatomic, assign, readonly) sa_family_t hostAddressFamily;



@property (nonatomic, assign, readonly) uint16_t identifier;



@property (nonatomic, assign, readonly) uint16_t nextSequenceNumber;

- (void)start;

- (nonnull NSData *)packetWithPingData:(nullable  NSData *)data;



- (void)sendPacket:(nonnull NSData *)data;



- (void)stop;

@end


@protocol SpeedTestSimplePingDelegate <NSObject>

@optional


- (void)spt_simplePing:(SpeedTestSimplePing *)pinger didStartWithAddress:(NSData *)address;



- (void)spt_simplePing:(SpeedTestSimplePing *)pinger didFailWithError:(NSError *)error;



- (void)spt_simplePing:(SpeedTestSimplePing *)pinger didSendPacket:(NSData *)packet sequenceNumber:(uint16_t)sequenceNumber;



- (void)spt_simplePing:(SpeedTestSimplePing *)pinger didFailToSendPacket:(NSData *)packet sequenceNumber:(uint16_t)sequenceNumber error:(NSError *)error;



- (void)spt_simplePing:(SpeedTestSimplePing *)pinger didReceivePingResponsePacket:(NSData *)packet timeToLive:(NSInteger)timeToLive sequenceNumber:(uint16_t)sequenceNumber timeElapsed:(NSTimeInterval)timeElapsed;


- (void)spt_simplePing:(SpeedTestSimplePing *)pinger didReceiveUnexpectedPacket:(NSData *)packet;

@end

#pragma mark * ICMP On-The-Wire Format


struct STICMPHeader {
    uint8_t     type;
    uint8_t     code;
    uint16_t    checksum;
    uint16_t    identifier;
    uint16_t    sequenceNumber;
    // data...
};
typedef struct STICMPHeader STICMPHeader;

__Check_Compile_Time(sizeof(STICMPHeader) == 8);
__Check_Compile_Time(offsetof(STICMPHeader, type) == 0);
__Check_Compile_Time(offsetof(STICMPHeader, code) == 1);
__Check_Compile_Time(offsetof(STICMPHeader, checksum) == 2);
__Check_Compile_Time(offsetof(STICMPHeader, identifier) == 4);
__Check_Compile_Time(offsetof(STICMPHeader, sequenceNumber) == 6);

enum {
    STICMPv4TypeEchoRequest = 8,          ///< The ICMP `type` for a ping request; in this case `code` is always 0.
    STICMPv4TypeEchoReply   = 0           ///< The ICMP `type` for a ping response; in this case `code` is always 0.
};

enum {
    STICMPv6TypeEchoRequest = 128,        ///< The ICMP `type` for a ping request; in this case `code` is always 0.
    STICMPv6TypeEchoReply   = 129         ///< The ICMP `type` for a ping response; in this case `code` is always 0.
};

NS_ASSUME_NONNULL_END

