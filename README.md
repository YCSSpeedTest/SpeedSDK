# SpeedTestSDK
# 1. 安装要求
>云测速SDK是用Swift 4.0 编写,最低兼容IOS10.0 
>官网：http://www.speedtest.cn


# 示例
## a.先注册appID和密钥
```obj
[SpeedTestApi registerAppWithAppid:@"" appSecret:@""];
```
## b.初始化SpeedTestApi
```obj
self.apiValue = [[SpeedTestApi alloc]initWithDelegate:self];
```
## c.开始事件
```obj
[self.apiValue beginDownTest];
```
## d.具体反馈协议

```obj
- (void)speedTestDisConnectedWithError:(NSString *)error {
NSLog(@"异常问题:  %@", error);
}
- (void)speedTestShowWithState:(enum SpeedState)state isAverage:(BOOL)isAverage speedValue:(CGFloat)speedValue {
NSString *value2;
if (isAverage) {
value2 = @"平均网速: ";
} else {
value2 = @"瞬时网速: ";
}
}
```
