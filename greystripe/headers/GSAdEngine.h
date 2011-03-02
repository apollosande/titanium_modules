//
//  GSAdEngine.h
//  GreystripeSDK
//
//  Copyright 2010 Greystripe, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "GreystripeDelegate.h"

/**
 * All available ad sizes.
 *
 * For non full-screen sizes be sure to size your container view to the same
 * dimensions.
 */
typedef enum GSAdSize {
	kGSAdSizeBanner = 1,				// 320x48
	kGSAdSizeIPhoneFullScreen,			// full screen
	kGSAdSizeIPadMediumRectangle,		// 300x250
	kGSAdSizeIPadLeaderboard,			// 728x90
	kGSAdSizeIPadWideSkyscraper			// 160x600
} GSAdSize;

/**
 * Simple class describing a single ad slot in your app.
 *
 * Ad slots are used to uniquely identify, by name, the various ad slots in 
 * your app. Typically you'll want to have just one per unique ad size that you
 * are using unless you want to have multiple ad views of a given size present
 * on screen at the same time.
 */
@interface GSAdSlotDescription : NSObject {
	GSAdSize m_size;
	
	/**
	 * Name of this ad slot description. This will be used to uniquely identify
	 * the ad slot within the Greystripe ad engine. 
	 *
	 * MUST be alphanumeric.
	 */
	NSString * m_name;
}

@property (readonly) GSAdSize size;
@property (readonly) NSString * name;

+ (id)descriptionWithSize:(GSAdSize)a_size name:(NSString *)a_name;

- (id)initWithSize:(GSAdSize)a_size name:(NSString *)a_name;

@end

/**
 * Class providing strictly static methods through which all direct interaction
 * with the Greystripe ad engine takes place.
 *
 * This class has no members and should never be alloc'd directly as all
 * methods are accessible statically.
 */
@interface GSAdEngine : NSObject {

}

/**
 * Greystripe ad engine initializer. Basic server synchronization will be 
 * performed to ensure that you application receives the proper ads. Note that
 * the order of the GSAdSlotDescriptions does matter as this controls the order
 * in which ads will be fetched. As this method is critical to initialization, 
 * it must be called before any other methods in this class.
 *
 * @param	a_appID
 * @param	a_descriptions
 */
+ (void)startupWithAppID:(NSString *)a_appID adSlotDescriptions:(NSArray *)a_descriptions;

/**
 * Display a full screen ad for the slot with the given name.
 *
 * @param	a_name	the name of the full screen slot whose ad you want to 
 *					display
 * @return	YES if the given slot exists and there is an ad ready to be 
 *			displayed, or NO if no ad is ready for this slot or there is no 
 *			network connection
 */
+ (BOOL)displayFullScreenAdForSlotNamed:(NSString *)a_name;

/**
 * Because full screen ads have no interaction with your app's view hierarchy,
 * you never create GSAdViews for full screen ads. Instead the Greystripe ad
 * engine handles creation of all necessary views and presentation of them. In 
 * order to listen to any display-related events for full-screen ads, however, 
 * you'll have to explicitly register a delegate with the Greystripe ad engine
 * using this method for each of your full screen ad slots.
 *
 * @param a_delegate	the object to receive delegate messages
 * @param a_name		the name of the full screen ad slot for which delegate
 *						messages will be sent
 */
+ (void)setFullScreenDelegate:(id<GreystripeDelegate>)a_delegate forSlotNamed:(NSString *)a_name;

/**
 * Return whether an ad is ready to be displayed for the slot of the given
 * name. Note that the semantics of this method differ based on whether the 
 * given slot is full-screen. For full-screen ads the semantics are the same
 * as isNextAdDownloadedForSlotNamed:, but for non-full-screen ads a return
 * value of YES means that ad content is ready to be displayed and your app
 * should therefore wire up the associated GSAdView to your view hierarchy.
 * 
 * @param	a_name	the name of the slot
 * @return	YES if an ad is ready to be displayed for the slot with the given 
 *			name, otherwise NO
 */
+ (BOOL)isAdReadyForSlotNamed:(NSString *)a_name;

/**
 * Return whether the next ad has been downloaded for the slot of the given 
 * name. For non-full-screen ads, your app may want to respond to a return 
 * value of YES by attempting to refresh the associated GSAdView.
 * 
 * @param	a_name	the name of the slot
 * @return	YES if a the next ad to be displayed for the slot of the given name
 *			has been downloaded
 */
+ (BOOL)isNextAdDownloadedForSlotNamed:(NSString *)a_name;

/**
 * Return the version string corresponding to this version and build of the
 * Greystripe SDK.  This is provided for convenience during testing as a
 * way to ensure that you are using the proper version and build of the 
 * Greystripe SDK.
 * 
 * @return	the version string
 */
+ (NSString *)version;

@end
