/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2010 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#import "TiGreystripeView.h"
#import "TiUtils.h"

@implementation TiGreystripeView

-(void)dealloc
{
	RELEASE_TO_NIL(adview);
	[super dealloc];
}

#pragma mark Public APIs

-(void)setName_:(id)name
{
	ENSURE_STRING(name);
	if (adview!=nil)
	{
		[adview removeFromSuperview];
		RELEASE_TO_NIL(adview);
	}
	adview = [[GSAdView adViewForSlotNamed:name delegate:self] retain];
}

#pragma mark Delegates

- (void)greystripeAdReadyForSlotNamed:(NSString *)name
{
	NSLog(@"[DEBUG] Greystripe ad ready named: %@",name);
	// we only map this to one name so we can ignore name parameter
	[super addSubview:adview];
}

/**
 * Sent by the Greystripe SDK whenever a full-screen Greystripe display is 
 * about to open. This may result from a click on an expandable ad or the 
 * presentation of a full-screen ad. Upon receiving this message, your 
 * application should pause animation, music, or other processor-intensive 
 * activities in order to ensure that ads perform properly.
 */
- (void)greystripeFullScreenDisplayWillOpen
{
}

/**
 * Sent by the Greystripe SDK whenever the full-screen Greystripe display is
 * about to close.  Upon receiving this message, the application should resume
 * any animation, music, or other processor-intensive activities that were
 * halted in response to greystripeFullScreenDisplayWillOpen.
 */
- (void)greystripeFullScreenDisplayWillClose
{
}

@end
