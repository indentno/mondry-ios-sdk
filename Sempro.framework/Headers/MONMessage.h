//
//  MONMessage.h
//  Sempro
//

#import <UIKit/UIKit.h>
#import "MONCoordinates.h"
#import "MONDisplaySettings.h"

/**
 *  @abstract Notification that is fired when a message fails to upload.
 */
extern NSString* _Nonnull const MONMessageUploadFailedNotification;

/**
 *  @abstract Notification that is fired when a message uploads successfully.
 */
extern NSString* _Nonnull const MONMessageUploadCompletedNotification;

/**
 *  @abstract A type of message that contains an image, text, and/or action buttons
 */
extern NSString* _Nonnull const MONMessageTypeImage;

/**
 *  @abstract A type of message that contains text and/or action buttons
 */
extern NSString* _Nonnull const MONMessageTypeText;

/**
 *  @abstract A type of message that contains a location
 */
extern NSString* _Nonnull const MONMessageTypeLocation;

/**
 *  @abstract A type of message that contains a file and/or text
 */
extern NSString* _Nonnull const MONMessageTypeFile;

/**
 *  @abstract A type of message that contains a horizontally scrollable set of items
 */
extern NSString* _Nonnull const MONMessageTypeCarousel;

/**
 *  @abstract A type of message that contains a vertically scrollable set of items
 */
extern NSString* _Nonnull const MONMessageTypeList;

/**
 *  @discussion Upload status of an MONMessage.
 *
 *  @see MONMessage
 */
typedef NS_ENUM(NSInteger, MONMessageUploadStatus) {
    /**
     *  A user message that has not yet finished uploading.
     */
    MONMessageUploadStatusUnsent,
    /**
     *  A user message that failed to upload.
     */
    MONMessageUploadStatusFailed,
    /**
     *  A user message that was successfully uploaded.
     */
    MONMessageUploadStatusSent,
    /**
     *  A message that did not originate from the current user.
     */
    MONMessageUploadStatusNotUserMessage
};

@interface MONMessage : NSObject

/**
 *  @abstract Create a message with the given text. The message will be owned by the current user.
 */
-(nonnull instancetype)initWithText:(nonnull NSString*)text;

/**
 *  @abstract Create a message with the given text, payload, and metadata. The message will be owned by the current user
 */
-(nonnull instancetype)initWithText:(nonnull NSString *)text payload:(nullable NSString *)payload metadata:(nullable NSDictionary *)metadata;

/**
 *  @abstract Create a message with the given coordinates, payload, and metadata. The message will be owned by the current user
 */
-(nonnull instancetype)initWithCoordinates:(nonnull MONCoordinates *)coordinates payload:(nullable NSString *)payload metadata:(nullable NSDictionary *)metadata;

/**
 *  @abstract The unique identifier of the message. May be nil if a unique identifier has not been generated for this message
 */
@property(readonly, nullable) NSString* messageId;

/**
 *  @abstract The text content of the message. May be nil if mediaUrl or actions are provided
 */
@property(nullable) NSString* text;

/**
 *  @abstract The text fallback to display for message types not supported by the SDK. May be nil
 */
@property(nullable) NSString* textFallback;

/**
 *  @abstract The name of the author. This property may be nil if no name could be determined.
 */
@property(nullable) NSString* name;

/**
 *  @abstract The url for the author's avatar image. May be nil
 */
@property(nullable) NSString* avatarUrl;

/**
 *  @abstract The date and time the message was sent
 */
@property(nullable) NSDate *date;

/**
 *  @abstract Returns YES if the message originated from the user, or NO if the message comes from the app team.
 */
@property(readonly) BOOL isFromCurrentUser;

/**
 *  @abstract The upload status of the message.
 *
 *  @see MONMessageStatus
 */
@property(readonly) MONMessageUploadStatus uploadStatus;

/**
 *  @abstract An array of MONMessageAction objects representing the actions associated with this message (if any)
 *
 *  @discussion This array may be nil or empty, so check the length of the array to know if a message has actions or not.
 *
 *  @see MONMessageAction
 */
@property(readonly, nullable) NSArray* actions;

/**
 *  @abstract An array of MONMessageItem objects representing the items associated with this message
 *
 *  @discussion Only messages of type `MONMessageTypeCarousel` and `MONMessageTypeList` contain items.
 *
 *  @see MONMessageItem
 */
@property(readonly, nullable) NSArray* items;

/**
 *  @abstract The url to the media asset, if applicable. Returns nil if the message is not an image or file message.
 */
@property(nullable) NSString* mediaUrl;

/**
 *  @abstract The size of the media asset in bytes. May be nil.
 */
@property(nullable) NSNumber* mediaSize;

/**
 *  @abstract The type the message.
 *
 *  @discussion Valid types include MONMessageTypeText, MONMessageTypeImage, and MONMessageTypeLocation
 */
@property(nullable) NSString* type;

/**
 *  @abstract Coordinates for a location for a message of type MONMessageTypeLocation
 */
@property(readonly, nullable) MONCoordinates *coordinates;

/**
 *  @abstract Settings to adjust the layout of a message of type MONMessageTypeCarousel
 *
 *  @see MONDisplaySettings
 */
@property(readonly, nullable) MONDisplaySettings *displaySettings;

/**
 *  @abstract The role of the message.
 *
 *  @discussion Valid roles include `appUser`, `appMaker`, and `whisper`. Messages created with -initWithText: have role of `appUser`.
 */
@property(readonly, nullable) NSString* role;

/**
 *  @abstract Metadata associated with the message.
 *
 *  @discussion A flat dictionary of metadata set through the REST API. May be nil.
 */
@property(nullable) NSDictionary* metadata;

/**
 *  @abstract The payload of an action with type MONMessageActionTypeReply
 *
 *  @discussion The payload of a MONMessageActionTypeReply, if applicable. May be nil
 */
@property(nullable) NSString* payload;

@end
