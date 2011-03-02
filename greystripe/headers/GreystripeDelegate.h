/// @file GreystripeDelegate.h
//  Copyright 2010 Greystripe, Inc. All rights reserved.

@protocol GreystripeDelegate <NSObject>

@optional
/**
 * Sent by the Greystripe SDK whenever an ad has become ready to be displayed
 * for the slot of the given name. This message is most useful for non-full-
 * screen ad slots, as you'll likely want to respond to the message by 
 * wiring up the GSAdView for the slot of the given name to your view 
 * hierarchy so that you may display the ad.
 */
- (void)greystripeAdReadyForSlotNamed:(NSString *)a_name;

/**
 * Sent by the Greystripe SDK whenever a full-screen Greystripe display is 
 * about to open. This may result from a click on an expandable ad or the 
 * presentation of a full-screen ad. Upon receiving this message, your 
 * application should pause animation, music, or other processor-intensive 
 * activities in order to ensure that ads perform properly.
 */
- (void)greystripeFullScreenDisplayWillOpen;

/**
 * Sent by the Greystripe SDK whenever the full-screen Greystripe display is
 * about to close.  Upon receiving this message, the application should resume
 * any animation, music, or other processor-intensive activities that were
 * halted in response to greystripeFullScreenDisplayWillOpen.
 */
- (void)greystripeFullScreenDisplayWillClose;

/**
 * Sent by the Greystripe SDK when it receives didReceiveMemoryWarning from the
 * device.  This is sent as a courtesy to applications that may not use
 * UIViewControllers to control their primary view, and as such will not receive
 * the notification on their own.  In the event that an application receives
 * this message, the app should free up as much of its own memory as possible,
 * such as dumping caches that aren't absolutely necessary.
 */
- (void)greystripeDidReceiveMemoryWarning;

@end
