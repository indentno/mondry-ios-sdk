//
//  MONConversationActivity.h
//  Sempro
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/**
 *  @abstract An activity type indicating that the appMaker started typing a response
 */
extern NSString const *MONConversationActivityTypeTypingStart;

/**
 *  @abstract An activity type indicating that the appMaker stopped typing a response
 */
extern NSString const *MONConversationActivityTypeTypingStop;

/**
 *  @abstract An activity type indicating that the appMaker recently read the user message
 */
extern NSString const *MONConversationActivityTypeConversationRead;

/**
 *  @abstract A key whose value is an NSString representing the appMaker name.
 *
 *  @discussion This key is used in the MONConversationActivity data object.
 */
extern NSString const *MONConversationActivityDataNameKey;

/**
 *  @abstract A key whose value is an NSString representing the URL of the appMaker avatar.
 *
 *  @discussion This key is used in the MONConversationActivity data object.
 */
extern NSString const *MONConversationActivityDataAvatarUrlKey;

@interface MONConversationActivity : NSObject

/**
 *  @abstract the role of who is performing the typing activity
 */
@property(readonly) NSString *role;

/**
 *  @abstract the type of activity that is being triggered. Could be either MONConversationActivityTypeTypingStart, MONConversationActivityTypeTypingStop or MONConversationActivityTypeConversationRead
 */
@property(readonly) NSString *type;

/**
 *  @abstract additional data for this activity. Posible values are the appMaker's 'name' and/or 'avatarUrl'
 */
@property(readonly, nullable) NSDictionary *data;

/**
 *  @abstract date when the appMaker last read user messages for activities of type MONConversationActivityTypeConversationRead
 */
@property(readonly, nullable) NSDate *appMakerLastRead;

@end
NS_ASSUME_NONNULL_END
