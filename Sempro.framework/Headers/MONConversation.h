//
//  MONConversation.h
//  Sempro
//

#import <Foundation/Foundation.h>
#import "MONMessage.h"
#import "MONMessageAction.h"
#import "MONMessageItem.h"
#import "MONConversationActivity.h"

NS_ASSUME_NONNULL_BEGIN
@protocol MONConversationDelegate;

typedef void (^MONImageUploadProgressBlock)(double progress);
typedef void (^MONImageUploadCompletionBlock)(NSError* _Nullable error, MONMessage* _Nullable message);
typedef void (^MONFileUploadProgressBlock)(double progress);
typedef void (^MONFileUploadCompletionBlock)(NSError* _Nullable error, MONMessage* _Nullable message);

/**
 *  @discussion Represents various actions the user takes when interacting with Sempro UI components.
 */
typedef NS_ENUM(NSInteger, MONAction) {
    /**
     *  The user has tapped on a Sempro in-app notification.
     */
    MONActionInAppNotificationTapped,
    /**
     *  The user has tapped on a Sempro push notification.
     */
    MONActionPushNotificationTapped
};

/**
 *  @abstract Posted when the count of unread messages changes. The notification object will be an instance of MONConversation, of which you can then inspect the messageCount property.
 *
 *  @see MONConversation
 */
extern NSString* const MONConversationUnreadCountDidChangeNotification;

/**
 *  @abstract Posted when an image upload begins.
 *
 *  @discussion The userInfo dictionary contains the UIImage to upload. Use MONConversationImageKey to access this value.
 *
 *  This notification is guaranteed to fire on the main thread.
 *
 *  @see MONConversationImageKey
 */
extern NSString* const MONConversationImageUploadDidStartNotification;

/**
 *  @abstract Posted when an image upload receives a progress update.
 *
 *  @discussion The userInfo dictionary contains the UIImage being uploaded, as well as an NSNumber reflecting the current progress. Use MONConversationImageKey and MONConversationProgressKey to access these values.
 *
 *  This notification is guaranteed to fire on the main thread.
 *
 *  @see MONConversationImageKey
 *  @see MONConversationProgressKey
 */
extern NSString* const MONConversationImageUploadProgressDidChangeNotification;

/**
 *  @abstract Posted when an image upload completes, either in success or failure.
 *
 *  @discussion The userInfo dictionary contains the UIImage that was uploaded. Use MONConversationImageKey to access this value.
 *
 *  If the upload succeeded, the userInfo dictionary will also include the MONMessage instance of the new message. Use MONConversationMessageKey to access this value.
 *  If the upload failed, the userInfo dictionary will include the NSError that occurred. Use MONConversationErrorKey to access this value.
 *
 *  This notification is guaranteed to fire on the main thread.
 *
 *  @see MONMessage
 *  @see MONConversationImageKey
 *  @see MONConversationMessageKey
 *  @see MONConversationErrorKey
 */
extern NSString* const MONConversationImageUploadCompletedNotification;

/**
 *  @abstract Posted when a file upload begins.
 *
 *  @discussion The userInfo dictionary contains the url of the file to upload. Use MONConversationFileKey to access this value.
 *
 *  This notification is guaranteed to fire on the main thread.
 *
 *  @see MONConversationFileKey
 */
extern NSString* const MONConversationFileUploadDidStartNotification;

/**
 *  @abstract Posted when a file upload receives a progress update.
 *
 *  @discussion The userInfo dictionary contains the url of the file being uploaded, as well as an NSNumber reflecting the current progress. Use MONConversationFileKey and MONConversationProgressKey to access these values.
 *
 *  This notification is guaranteed to fire on the main thread.
 *
 *  @see MONConversationFileKey
 *  @see MONConversationProgressKey
 */
extern NSString* const MONConversationFileUploadProgressDidChangeNotification;

/**
 *  @abstract Posted when a file upload completes, either in success or failure.
 *
 *  @discussion The userInfo dictionary contains the url of the file that was uploaded. Use MONConversationFileKey to access this value.
 *
 *  If the upload succeeded, the userInfo dictionary will also include the MONMessage instance of the new message. Use MONConversationMessageKey to access this value.
 *  If the upload failed, the userInfo dictionary will include the NSError that occurred. Use MONConversationErrorKey to access this value.
 *
 *  This notification is guaranteed to fire on the main thread.
 *
 *  @see MONMessage
 *  @see MONConversationFileKey
 *  @see MONConversationMessageKey
 *  @see MONConversationErrorKey
 */
extern NSString* const MONConversationFileUploadCompletedNotification;

/**
 *  @abstract Posted when new messages are received from the server.
 *
 *  @discussion The userInfo dictionary contains an NSArray of MONMessage objects. Use MONConversationNewMessagesKey to access this value.
 *
 *  @see MONMessage
 *  @see MONConversationNewMessagesKey
 */
extern NSString* const MONConversationDidReceiveMessagesNotification;

/**
 *  @abstract Posted when an operation to load previous messages in a conversation has been completed
 *
 *  @discussion This notification is posted as the result of [MONConversation loadPreviousMessages]
 *
 *  If the operation succeeded, the object returned by this notification will include the updated array of messages
 *  If the operation failed, the userInfo dictionary will contain an "error" object with the response error
 *
 *  @see MONMessage
 *  @see MONConversationPreviousMessagesKey
 */
extern NSString* const MONConversationDidReceivePreviousMessagesNotification;

/**
 *  @abstract Posted when a conversation activity has been created, such as typing start/stop
 *
 *  @see MONConversationActivity
 *  @see MONConversationActivityKey
 */
extern NSString* const MONConversationDidReceiveActivityNotification;

/**
 *  @abstract A key whose value is an NSArray of MONMessage objects.
 *
 *  @discussion This key is used with MONConversationDidReceiveMessagesNotification notification.
 *
 *  @see MONConversationDidReceiveMessagesNotification
 */
extern NSString* const MONConversationNewMessagesKey;

/**
 *  @abstract A key whose value is an NSArray of MONMessage objects
 *
 *  @discussion This key is used with MONConversationDidReceivePreviousMessagesNotification notification
 *
 *  @see MONConversationDidReceivePreviousMessagesNotification
 */
extern NSString* const MONConversationPreviousMessagesKey;

/**
 *  @abstract A key whose value is a UIImage which represents an image being uploaded.
 *
 *  @discussion This key is used with MONConversationImageUploadDidStartNotification, MONConversationImageUploadProgressDidChangeNotification, and MONConversationImageUploadCompletedNotification notifications.
 *
 *  @see MONConversationImageUploadDidStartNotification
 *  @see MONConversationImageUploadProgressDidChangeNotification
 *  @see MONConversationImageUploadCompletedNotification
 */
extern NSString* const MONConversationImageKey;

/**
 *  @abstract A key whose value is an NSURL which represents a file being uploaded.
 *
 *  @discussion This key is used with MONConversationFileUploadDidStartNotification, MONConversationFileUploadProgressDidChangeNotification, and MONConversationFileUploadCompletedNotification notifications.
 *
 *  @see MONConversationFileUploadDidStartNotification
 *  @see MONConversationFileUploadProgressDidChangeNotification
 *  @see MONConversationFileUploadCompletedNotification
 */
extern NSString* const MONConversationFileKey;

/**
 *  @abstract A key whose value is an NSError.
 *
 *  @discussion This key is used with MONConversationImageUploadCompletedNotification notification.
 *
 *  @see MONConversationImageUploadCompletedNotification
 */
extern NSString* const MONConversationErrorKey;

/**
 *  @abstract A key whose value is an MONMessage object representing the newly created message.
 *
 *  @discussion This key is used with MONConversationImageUploadCompletedNotification notification.
 *
 *  @see MONConversationImageUploadCompletedNotification
 */
extern NSString* const MONConversationMessageKey;

/**
 *  @abstract A key whose value is an NSNumber reflecting the current progress of an image upload.
 *
 *  @discussion This key is used with MONConversationImageUploadProgressDidChangeNotification notification.
 *
 *  @see MONConversationImageUploadProgressDidChangeNotification
 */
extern NSString* const MONConversationProgressKey;

/**
 *  @abstract A key whose value is a MONConversationActivity object representing the newly created activity
 *
 *  @discussion This key is used with MONConversationDidReceiveActivityNotification notification.
 *
 *  @see MONConversationDidReceiveActivityNotification
 */
extern NSString* const MONConversationActivityKey;

/**
 *  @discussion The MONConversation class provides an interface to interact with the current user's conversation.
 *
 *  To obtain an instance, use `[Sempro conversation]`. +initWithSettings:completionHandler: must have been called prior to retrieving the shared conversation object.
 *
 *  To send a message, use -sendMessage: with an MONMessage object
 *
 *  Example:
 *
 *  `[[Sempro conversation] sendMessage:[[MONMessage alloc] initWithText:@"Hello World!"]];`
 *
 *  A notification will be fired indicating the success or failure of the message. To subscribe to these notifications, use NSNotificationCenter.
 *
 *  Example:
 *
 *  `[[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(messageUploaded:) name:MONMessageUploadCompletedNotification object:nil];`
 *
 *  `[[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(messageFailed:) name:MONMessageUploadFailedNotification object:nil];`
 *
 *  @see MONMessage
 *  @see Sempro
 */
@interface MONConversation : NSObject

/**
 *  @abstract The unique identifier of the conversation. May be nil if a conversation doesn't exist for the current user
 */
@property(readonly, nullable) NSString* conversationId;

/**
 *  @abstract The array of MONMessage objects representing the conversation.
 *
 *  @see MONMessage
 */
@property(readonly, nullable) NSArray* messages;

/**
 *  @abstract The total number of messages in the conversation, including user-generated messages.
 */
@property(readonly) NSUInteger messageCount;

/**
 *  @abstract Count of unread messages in the conversation.
 *
 *  @discussion The primary use of this property is to be able to display an indicator / badge when the conversation has unread messages.
 */
@property(readonly) NSUInteger unreadCount;

/**
 *  @abstract Date when the business last read the user messages
 */
@property(readonly) NSDate *appMakerLastRead;

/**
 *  @abstract Metadata associated with the conversation.
 *
 *  @discussion A flat dictionary of metadata set through the REST API. May be nil.
 */
@property(readonly, nullable) NSDictionary* metadata;

/**
 *  @abstract A delegate object for receiving notifications related to the conversation.
 *
 *  @see MONConversationDelegate
 */
@property(weak, nullable) id<MONConversationDelegate> delegate;


/**
 *  @abstract Boolean representing whether there are previous messages in the conversation that can be fetched or not
 *
 *  @discussion Returns YES if there are previous messages in the conversation, NO otherwise. For fetching previous messages, use [MONConversation loadPreviousMessages]
 */
@property(readonly) BOOL hasPreviousMessages;

/**
 *  @abstract Marks all unread messages as read.
 *
 *  @discussion Marks all unread messages as read, and notifies that the unread count changed.
 *
 *  @see MONMessage
 */
-(void)markAllAsRead;

/**
 *  @abstract Loads previous messages for this conversation, if any
 *
 *  @discussion Will get previous messages for this conversation based on the timestamp of the current oldest message and will notify the delegate of new incoming messages through [MONConversationDelegate conversation:didReceivePreviousMessages:]
 */
-(void)loadPreviousMessages;

/**
 *  @abstract Adds a new message to the conversation.
 *
 *  @discussion For each message added using `sendMessage`, a notification will be fired indicating the success or failure status of the upload.
 *
 *  @see MONMessageUploadFailedNotification
 *  @see MONMessageUploadCompletedNotification
 */
-(void)sendMessage:(MONMessage*)message;

/**
 *  @abstract Adds an image message to the conversation.
 *
 *  @discussion Use the progress block to track the progress of the upload. Progress is reported as a number between 0 and 1.
 *
 *  The completion block is called when the operation completes, either in success or failure. Both blocks are guaranteed to be called on the main thread.
 *
 *  In case of success, the error parameter will be nil, and the message parameter will contain the newly created message. The message will already be part of the messages array when this block is called.
 *
 *  In case of failure, the message parameter will be nil, and the error parameter will contain the error that occurred.
 *
 *  @param image The image to upload. Must not be nil.
 *  @param progressBlock Called to report progress updates. May be nil.
 *  @param completionBlock Called when the upload completes or fails. May be nil.
 */
-(void)sendImage:(UIImage *)image withProgress:(nullable MONImageUploadProgressBlock)progressBlock completion:(nullable MONImageUploadCompletionBlock)completionBlock;

-(void)sendFile:(NSURL *)fileLocation withProgress:(nullable MONFileUploadProgressBlock)progressBlock completion:(nullable MONFileUploadCompletionBlock)completionBlock;

/**
 *  @abstract Sends a postback to the server.
 *
 *  @discussion The completion block is called when the operation completes, either in success or failure.
 *
 *  In case of success, the error parameter will be nil.
 *
 *  In case of failure, the error parameter will contain the error that occurred.
 *
 *  @param messageAction The messageAction for which to send the postback. Must not be nil.
 *  @param completionBlock Called when the postback completes or fails. May be nil.
 */
-(void)postback:(MONMessageAction*)messageAction completion:(nullable void (^)(NSError* _Nullable error))completionBlock;

/**
 *  @abstract Retries a message that failed to send.
 *
 *  @discussion The failed message will be removed from the messages array, and a new message will be constructed with the same text as the failed message. A notification will be fired indicating the success or failure status of the upload.
 *
 *  @see MONMessageUploadFailedNotification
 *  @see MONMessageUploadCompletedNotification
 */
-(void)retryMessage:(MONMessage*)failedMessage;

/**
 *  @abstract Notify the server that the user is typing.
 *
 *  @discussion This method is called automatically when using the default conversation view controller. Only call this method if your application implements its own conversation view.
 *
 *  Typing updates are automatically throttled, so you may call this method as often as necessary. The typing stop event will automatically fire 10 seconds after the most recent call to this method.
 */
-(void)startTyping;

/**
 *  @abstract Notify the server that the user has finished typing.
 *
 *  @discussion This method is called automatically when using the default conversation view controller. Only call this method if your application implements its own conversation view.
 *
 *  If the user was not flagged as typing recently, this method will result in a no-op.
 */
-(void)stopTyping;

@end

/**
 *  @discussion Delegate protocol for events related to the conversation.
 *
 *  Creating a delegate is optional, and may be used to receive callbacks when important changes happen in the conversation.
 *
 *  Delegate methods are guaranteed to be called from the main thread.
 */
@protocol MONConversationDelegate <NSObject>

@optional
/**
 *  @abstract Notifies the delegate of a change in unread message count.
 *
 *  @discussion Called when conversation data is fetched from the server, or when the user enters the conversation screen.
 *
 *  @param conversation The conversation object that initiated the change.
 *  @param unreadCount The new number of unread messages.
 */
-(void)conversation:(MONConversation*)conversation unreadCountDidChange:(NSUInteger)unreadCount;

/**
 *  @abstract Asks the delegate if an in-app notification should be shown for a message.
 *
 *  @discussion Called when a new message is received, right before the in-app notification is to be shown for that message. To show your own in-app notification, return NO from this method, and use the MONMessage object to construct your view.
 *
 *  @param conversation The conversation object that initiated the change.
 *  @param message The message that will be displayed in the notification.
 *
 *  @return YES to allow Sempro to present the notification. NO to suppress the notification, and perform custom handling.
 *
 *  @see MONMessage
 */
-(BOOL)conversation:(MONConversation*)conversation shouldShowInAppNotificationForMessage:(MONMessage*)message;

/**
 *  @abstract Asks the delegate if the conversation should show for the given action.
 *
 *  @discussion Called when the user performs an action that causes the conversation screen to show. Return NO to cancel the display of the conversation screen and perform your own handling of the action.
 *
 *  @param conversation The conversation object.
 *  @param action The action the user has taken.
 *  @param info An instance of NSDictionary with a `message` object with the latest MONMessage represented as an NSDictionary
 *
 *  @return YES to allow default handling. NO to suppress the conversation screen, and perform custom handling.
 *
 *  @see MONAction
 */
-(BOOL)conversation:(MONConversation*)conversation shouldShowForAction:(MONAction)action withInfo:(nullable NSDictionary *) info;

/**
 *  @abstract Gives the delegate the option to modify a message before it is sent
 *
 *  @discussion Called when a message is about to be sent to give the delegate the option of modify or decorate its content (i.e. add metadata) before sending to Sempro. When the message type is `file` or `image`, only the message `metadata` may be updated. Other message properties such as `type` or `text` won't be considered.
 *
 *  @return the message to be sent
 */
-(MONMessage *)conversation:(MONConversation*)conversation willSendMessage:(MONMessage *)message;

/**
 *  @abstract Gives the delegate the option to modify a message before it is displayed. If nil is returned the message will be hidden
 *
 *  @discussion Called when a message is about to be displayed to the user to give the delegate the option of modifying its content before display or hide it
 *
 *  @return the message to be displayed. If nil, the message won't get displayed
 */
-(nullable MONMessage *)conversation:(MONConversation*)conversation willDisplayMessage:(MONMessage *)message;

/**
 *  @abstract Notifies the delegate of new incoming messages.
 *
 *  @discussion Called when new messages are received from the server.
 *
 *  @param conversation The conversation object.
 *  @param messages An array of MONMessage objects representing the new messages.
 *
 *  @see MONMessage
 */
-(void)conversation:(MONConversation*)conversation didReceiveMessages:(NSArray*)messages;

/**
 *  @abstract Notifies the delegate when older messages in the conversation history have been received
 *
 *  @discussion Called when older messages in the conversation history are received from the server
 *
 *  @param conversation The conversation object
 *  @param messages The messages that have been fetched
 */
-(void)conversation:(MONConversation*)conversation didReceivePreviousMessages:(NSArray*)messages;

/**
 *  @abstract Notifies the delegate of new conversation activity
 *
 *  @discussion Called when a new activity is received from the server
 *
 *  @param conversation The conversation object
 *  @param activity The activity that was received
 */
-(void)conversation:(MONConversation *)conversation didReceiveActivity:(MONConversationActivity *)activity;

/**
 *  @abstract Asks the delegate if default handling should be performed for a message action.
 *
 *  @discussion Called when the user taps a message action.
 *
 *  @return YES to allow default handling. NO to perform custom handling.
 */
-(BOOL)conversation:(MONConversation *)conversation shouldHandleMessageAction:(MONMessageAction*)action;

/**
 *  @abstract Notifies the delegate when the conversation is about to be presented.
 *
 *  @discussion Called in the viewWillAppear: method of the conversation view controller.
 */
-(void)conversation:(MONConversation *)conversation willShowViewController:(UIViewController*)viewController;

/**
 *  @abstract Notifies the delegate when presentation of the conversation completes.
 *
 *  @discussion Called in the viewDidAppear: method of the conversation view controller.
 */
-(void)conversation:(MONConversation *)conversation didShowViewController:(UIViewController*)viewController;

/**
 *  @abstract Notifies the delegate when the conversation is about to be dismissed.
 *
 *  @discussion Called in the viewWillDisappear: method of the conversation view controller.
 */
-(void)conversation:(MONConversation *)conversation willDismissViewController:(UIViewController*)viewController;

/**
 *  @abstract Notifies the delegate when dismissal of the conversation completes.
 *
 *  @discussion Called in the viewDidDisappear: method of the conversation view controller.
 */
-(void)conversation:(MONConversation *)conversation didDismissViewController:(UIViewController*)viewController;

@end
NS_ASSUME_NONNULL_END
