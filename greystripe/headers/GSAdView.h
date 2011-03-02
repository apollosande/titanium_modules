//
//  GSAdView.h
//  GreystripeSDK
//
//  Copyright 2010 Greystripe, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "GreystripeDelegate.h"

@class GSAdSlotDescription;
@class GSAdViewInternal;

/**
 * Minimum refresh interval between ad displays in a single GSAdView. Use this
 * interval if you'd like to have an auto-refreshing GSAdView that refreshes
 * as often as possible. This value is currently 30 seconds.
 */
extern const NSTimeInterval kGSMinimumRefreshInterval;

/**
 * Core view class encapsulating a single ad view.
 *
 * GSAdViews are lazily instantiated and managed within the GSAdEngine.
 */
@interface GSAdView : UIView {
	GSAdViewInternal * m_adViewInternal;
}

/**
 * Return the GSAdView corresponding to the already-registered slot of the 
 * given name. If a GSAdView instance for the given slot name has not yet been
 * created, one will be created at this time and cached within the GSAdEngine
 * so that all future calls to this method will return the same GSAdView 
 * instance. If no slot with the given name has yet been registered with the
 * GSAdManager, an exception will be thrown. Note that the returned ad view
 * will not automatically refresh its display to show the next ad that has been
 * downloaded for the associated slot unless the user has clicked through on
 * the most recently displayed ad. In all other cases you must explicitly 
 * call refresh to refresh the display. 
 *
 * Note that you may change the delegate associated with the receiver by 
 * simply calling this method with a different delegate.
 *
 * @param a_name		the name of the ad slot
 * @param a_delegate	the delegate object which will be informed of ad-related
 *						events
 */
+ (id)adViewForSlotNamed:(NSString *)a_name delegate:(id<GreystripeDelegate>)a_delegate;

/**
 * Return the GSAdView corresponding to the already-registered slot of the 
 * given name. If a GSAdView instance for the given slot name has not yet been
 * created, one will be created at this time and cached within the GSAdEngine
 * so that all future calls to this method will return the same GSAdView 
 * instance. If no slot with the given name has yet been registered with the
 * GSAdManager, an exception will be thrown. 
 * 
 * The refresh interval will be used refresh the view and display the next ad
 * that is ready at the given interval. You may still manually attempt to 
 * refresh the returned GSAdView instance, but calls will only be honored so 
 * long as kGSMinimumRefreshInterval has passed since the last ad displayed in 
 * the GSAdView. NOTE: refresh intervals less than kGSMinimumRefreshInterval
 * are not allowed. An exception will be thrown if you provide a refresh 
 * interval less than kGSMinimumRefreshInterval.
 *
 * Note that you may change the delegate and refresh interval associated with
 * the receiver by simply calling this method with different delegate and/or
 * refresh interval values.
 *
 * @param a_name		the name of the ad slot
 * @param a_delegate	the delegate object which will be informed of ad-related
 *						events
 * @param a_interval	the interval, in seconds, at which the display will be
 *						refreshed
 */
+ (id)adViewForSlotNamed:(NSString *)a_name delegate:(id<GreystripeDelegate>)a_delegate refreshInterval:(NSTimeInterval)a_interval;

/**
 * Refresh the receiver's view to display the next ad that has been downloaded
 * for the receiver's associated ad slot. If the next ad for the given slot is
 * not yet ready, the call will be a no-op. This call will be honored so long 
 * as kGSMinimumRefreshInterval seconds have passed since the previous ad 
 * display in the receiver.
 */
- (void)refresh;

@end
