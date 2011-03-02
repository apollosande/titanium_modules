/**
 * Appcelerator Barcode Module
 *
 * Appcelerator Titanium is Copyright (c) 2009-2010 by Appcelerator, Inc.
 * and licensed under the Apache Public License (version 2)
 */
#import "TiGreystripeModule.h"
#import "TiBase.h"
#import "TiHost.h"
#import "TiUtils.h"
#import "TiApp.h"

@implementation TiGreystripeModule

// this is generated for your module, please do not change it
-(id)moduleGUID
{
	return @"03dc7887-2abe-4bb5-bd9a-00910721a1f4";
}

// this is generated for your module, please do not change it
-(NSString*)moduleId
{
	return @"ti.greystripe";
}


#pragma mark Lifecycle


-(void)_destroy
{
	[super _destroy];
}

-(void)startup
{
	// this method is called when the module is first loaded
	// you *must* call the superclass
	[super startup];
	
	NSLog(@"[INFO] Greystripe module loaded",self);
}

-(void)shutdown:(id)sender
{
	// this method is called when the module is being unloaded
	// typically this is during shutdown. make sure you don't do too
	// much processing here or the app will be quit forceably
	
	// you *must* call the superclass
	[super shutdown:sender];
}

#pragma mark Cleanup 

-(void)dealloc
{
	// release any resources that have been retained by the module
	[super dealloc];
}

#pragma mark Internal Memory Management

-(void)didReceiveMemoryWarning:(NSNotification*)notification
{
	// optionally release any resources that can be dynamically
	// reloaded once memory is available - such as caches
	[super didReceiveMemoryWarning:notification];
}

#pragma Public APIs

MAKE_SYSTEM_PROP(BANNER,kGSAdSizeBanner);
MAKE_SYSTEM_PROP(IPHONE_FULLSCREEN,kGSAdSizeIPhoneFullScreen);
MAKE_SYSTEM_PROP(IPAD_MEDIUM_RECTANGLE,kGSAdSizeIPadMediumRectangle);
MAKE_SYSTEM_PROP(IPAD_LEADERBOARD,kGSAdSizeIPadLeaderboard);
MAKE_SYSTEM_PROP(IPAD_WIDE_SKYSCRAPER,kGSAdSizeIPadWideSkyscraper);

-(void)setup:(id)args
{
	ENSURE_DICT(args);
	ENSURE_UI_THREAD(setup,args);
	
	NSString *applicationID = [args objectForKey:@"applicationId"];
	id slots = [args objectForKey:@"adSlots"];
	ENSURE_ARRAY(slots);
	
	NSMutableArray *slotpairs = [NSMutableArray array];
	
	for (id slot in slots)
	{
		ENSURE_DICT(slot);
		GSAdSize size = [TiUtils intValue:@"size" properties:slot def:kGSAdSizeBanner];
		NSString *name = [TiUtils stringValue:@"name" properties:slot];
		[slotpairs addObject:[GSAdSlotDescription descriptionWithSize:size name:name]];
	}
	[GSAdEngine startupWithAppID:applicationID adSlotDescriptions:slotpairs];
	NSLog(@"[INFO] GSAdEngine is loaded with version %@",GSAdEngine.version);
}

@end
