//
//  MONAuthenticationDelegate.h
//  Sempro
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

typedef void (^MONAuthenticationCompletionBlock)(NSString *jwt);

/**
 *  @discussion Delegate protocol for events related to authentication.
 *
 *  Creating a delegate is optional, and may be used to receive callbacks for important authentication events.
 */
@protocol MONAuthenticationDelegate <NSObject>

@optional

/**
 *  @abstract Notifies the delegate that the current jwt used to authenticate requests is invalid.
 *
 *  @discussion Called when a request fails due to an invalid jwt. Use `completionHandler` to update the token and automatically retry the failed request. If the updated jwt is also invalid, this method is called again, with a maximum of 5 retry attempts per request.
 *
 *  @param error Error object for the request
 *  @param completionHandler Block to call with the updated jwt
 */
- (void)onInvalidToken:(NSError *) error handler:(MONAuthenticationCompletionBlock)completionHandler;

NS_ASSUME_NONNULL_END

@end
