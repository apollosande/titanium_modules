# Titanium Facebook Module

## Description

Access the Facebook Graph and REST APIs from Titanium Mobile 1.5.1 and higher using this module.

## Accessing the Titanium Facebook Module

To access this module from JavaScript, you would do the following:

	var FB = require("ti.facebook"); // variable name can be anything you want, of course

The `FB` variable is then a reference to the module.

## Reference

### Functions

#### ti.facebook.authorize()

Shows the official Facebook authorize dialog to login the user (if not already logged in) and authorize your app's requested permissions.  Be sure to set `appid` and `permissions` properties before calling this.  Listen for the module's `login` event to determine if this succeeds.

#### ti.facebook.createLoginButton({...})

Create a Facebook-themed login button which you can be put on to a window/view just like any of the `Titanium.UI` views. The sole argument is a dictionary object of properties just like you would use to set options for `Titanium.UI` objects (`top`, `left`, etc.)  Additionally it recognizes one special property:

- style[string] : If you set this to "wide", you get a wider version of the button that says "Connect with Facebook" instead of just "Connect".

Note that you probably don't want to set width/height of this button because it's themed for you using images.

This button automatically recognizes the state of the Facebook session.  For example, if the session is currently logged-in (i.e., checking `.loggedIn` would return `true`), then the button shows "Logout".  And you don't need to create a click event handler for it: it "just works".

#### ti.facebook.dialog(name, parameters, callback)

Open a supported Facebook [dialog](http://developers.facebook.com/docs/reference/dialogs/).  "feed" is just about the only useful one.

Arguments:

- name[string] : which dialog to show, such as "feed".  See [Facebook's reference](http://developers.facebook.com/docs/reference/dialogs/).
- parameters[object] : A dictionary object containing properties to pre-fill dialog fields.  See the example in this document.
- callback[function] : Will be called when dialog completes.  Make sure your callback function accepts one argument.  The argument will be filled with a dictionary object that can contain one or more of the following:
  - success[boolean] true if dialog successful.
  - cancelled[boolean] true if dialog cancelled.
  - error[string] an error message if any.
  - result[string] data passed back by Facebook after the dialog was posted, if any.

#### ti.facebook.logout()

Logout the session and forget the OAuth `accessToken`.  Listen for the module's `logout` event to determine if this succeeds.

#### ti.facebook.request(method, parameters, callback)

Make a call to the deprecated Facebook REST API.

Arguments:

- method[string] : The REST method to call.
- parameters[object] : A dictionary object for setting parameters required by the call, if any.  See usage examples.
- callback[function] : A callback for when call is completed.  The callback should accept a single argument which will be filled with a dictionary object concerning call results.  Items in the dictionary can be:
  - success[boolean] true if successful.
  - error[string] error message, if any.
  - method[string] the REST method call you specified
  - result[string] the data returned by Facebook.

#### ti.facebook.requestWithGraphPath(path, parameters, httpMethod, callback)

Make a [Facebook Graph API](http://developers.facebook.com/docs/reference/api/) request.  If the request requires user authorization, be sure user is already logged-in and your app is authorized.  (You can check `loggedIn` for that.)

Arguments:

- path[string] : The graph API path to request.  For example, "me" requests [information about the logged-in user](http://developers.facebook.com/docs/reference/api/user/).
- parameters[object] : A dictionary object for setting parameters required by the call, if any.  See usage examples.
- httpMethod[string] : The http method (GET/POST/DELETE) to use for the call.
- callback[function] : A callback for when call is completed.  The callback should accept a single argument which will be filled with a dictionary object concerning call results. Items in the dictionary can be:
  - success[boolean] : true if successful.
  - error[string] : error message, if any.
  - path[string] the graph call path you specified
  - result[string] the JSON returned by Facebook.

### Properties

#### ti.faceboook.accessToken (string)

The OAuth access token resulting from a successful `authorize()`.  You really shouldn't need to use this, since this toke is applied automatically for you whenever you make a call.

#### ti.facebook.appid (string)

Your Facebook application appid, given to you by Facebook. 

#### ti.facebook.expirationDate (date)

When your `accessToken` expires.  Note that you don't really have to manage this manually.  Just check `.loggedIn` and if it returns `true` then your user is logged-in and has an unexpired access token.

#### ti.facebook.loggedIn (boolean)

Returns true if your user is logged-in to facebook and an unexpired OAuth access token exists.  You should check this before making `request` and `requestWithGraphPath` calls, and redirect to `authorize` if it returns `false`.

#### ti.facebook.permissions (array)

Array of strings, each of which is a permission you want your app to have.  Be sure to set this and `appid` before calling `authorize`.

#### ti.facebook.uid (string)

The Facebook user id for the logged-in user.  Some API calls might require this.

### Events

#### login

Fires when the Facebook session finishes attempting a login, such as via a call to `authorize` or via use of the special login button created via `createLoginButton`.

The event object can contain these properties:

- success[boolean] : true if login was successful.
- error[string] : error message if any.
- cancelled[boolean] : true if user cancelled login.
- uid[string] : Facebook user id if user logged in successfully.
- data[string] : Data returned by Facebook from the call that the module makes to the "me" graph path after authentication and authorization completes.  Contains info such as the user's name, gender, locale, etc.

#### logout

Fires when the Facebook session successfully logs out.  No event arguments.

## Usage

In the usage examples below, the variable name `FB` denotes the instance of the module acquired via ...

	var FB = require("ti.facebook");

You can, of course, use any variable name you wish in your code.

### Declare the module

To use the module, you need to add it to the "modules" section of your application's tiapp.xml file, like this:

	<modules>
		<module version="0.1">ti.facebook</module>
	</modules>	

### Authorize

Shows official Facebook dialog for logging in the user and prompting the user to approve your requested permissions.  Listen for the module's "login" event to determine success/failure.

	var FB = require("ti.facebook");
	FB.appid = '[YOUR APPID]';
	FB.permissions = ['publish_stream']; // Permissions your app needs
	FB.addEventListener('login', function(e) {
		if (e.success) {
			alert('Logged In');
		} else if (e.error) {
			alert(e.error);
		} else if (e.cancelled) {
			alert("Cancelled");
		}
	});
	FB.authorize();

### Logout

Logout the user and forget the authorization token.  Listen for the module's "logout" event to determine when logout is finished.

	FB.addEventListener('logout', function(e) {
		alert('Logged out');
	});
	FB.logout();

### Authorize/Logout via the special LoginButton

We've provided the Facebook-themed LoginButton which updates its state automatically depending on whether the user is logged-in or not.  I.e., when the user is logged-in, then the button will show "Logout", and vice-versa.

Note that you don't need to set a click listener or anything else on the button.  It "just works".  To listen for the actual login and logout events (which are part of the Titanium Facebook module and not specific to the login button), add listeners at the module level as in the example below.

	// Don't forget to set your appid and requested permissions, else the login button
	// won't be effective.
	FB.appid = '[your appid]';
	FB.permissions = ['publish_stream'];
	FB.addEventListener('login', function(e) {
		if (e.success) {
			alert('Logged in');
		}
	});
	FB.addEventListener('logout', function(e) {
		alert('Logged out');
	});

	// add the button.  Note that it doesn't need a click event or anything.
	Titanium.UI.currentWindow.add(FB.createLoginButton({ top: 50, style: 'wide' }));

The `style:'wide'` shows a wide version of the button that displays "Connect with Facebook" instead of just "Connect".

### Simple Graph API call

This example makes a call to the "me" graph path and displays the results, which will be JSON from Facebook.  It assumes the user is already logged-in (you can check this with `FB.loggedIn`.)

	FB.requestWithGraphPath('me', {}, 'GET', function(e) {
		if (e.success) {
			alert(e.result);
		} else if (e.error) {
			alert(e.error);
		} else {
			alert('Unknown response');
		}
	});

### Create an Event with Graph API

This example uses the Graph API to [create an event](http://developers.facebook.com/docs/reference/api/event/) in the logged-on user's Facebook account.  This requires the "create_event" permission.

	// First make sure this permission exists
	FB.permissions = ['create_event'];
	FB.authorize();

	// ...
	// ...

	// Now create the event after you've confirmed authorize() was successful.
	var starttime = new Date(2011, 4, 31, 17, 0);
	var endtime = new Date(2011, 4, 31, 19, 0);
	var title = "Barry's Birthday Celebration";
	var description = "Barry will have a great party";
	var data = {
		start_time: JSON.stringify(starttime), // API expects a JSON stringified date
		end_time: JSON.stringify(endtime),
		description: description,
		name: title
	};
	FB.requestWithGraphPath('me/events', data, 'POST', function(e) {
		if (e.success) {
			alert("Success! Returned from FB: " + e.result);
		} else {
			if (e.error) {
				alert(e.error);
			} else {
				alert("Unknown result");
			}
		}
	});

### Set user's Facebook status with Graph API

Use the Graph API to set the [user's Facebook status](http://developers.facebook.com/docs/reference/api/status/).  Requires the "publish_stream" permissions.

	// First make sure this permission exists
	FB.permissions = ['publish_stream'];
	FB.authorize();

	// ...
	// ...

	// Now create the status message after you've confirmed that authorize() succeeded
	FB.requestWithGraphPath('me/feed', {message: "Trying out FB Graph API and it's fun!"}, "POST", function(e) {
		if (e.success) {
			alert("Success!  From FB: " + e.result);
		} else {
			if (e.error) {
				alert(e.error);
			} else {
				alert("Unkown result");
			}
		}
	});

### Post a photo using the Graph API

This example [posts a photo to the user's account](http://developers.facebook.com/docs/reference/api/photo/) using the Graph API.  Another example below shows how to do this with the REST API, if desired.  This requires the "publish_stream" permission.

	// First make sure this permission exists
	FB.permissions = ['publish_stream'];
	FB.authorize();

	// ...
	// ...

	// Now post the photo after you've confirmed that authorize() succeeded
	var f = Ti.Filesystem.getFile('pumpkin.jpg');
	var blob = f.read();
	var data = {
		message: 'This is a pumpkin',
		picture: blob
	};
	FB.requestWithGraphPath('me/photos', data, 'POST', function(e){
		if (e.success) {
			alert("Success!  From FB: " + e.result);
		} else {
			if (e.error) {
				alert(e.error);
			} else {
				alert("Unkown result");
			}
		}
	});

### Post a photo using the REST API

This example [posts a photo to the user's account](http://developers.facebook.com/docs/reference/rest/photos.upload/) using the REST API.  Another example above shows how to do this with the Graph API.  This requires the "publish_stream" permission.

	// First make sure this permission exists
	FB.permissions = ['publish_stream'];
	FB.authorize();

	// ...
	// ...

	// Now post the photo after you've confirmed that authorize() succeeded
	var f = Ti.Filesystem.getFile('pumpkin.jpg');
	var blob = f.read();
	var data = {
		caption: 'This is a pumpkin',
		picture: blob
	};
	FB.request('photos.upload', data, function(e){
		if (e.success) {
			alert("Success!  From FB: " + e.result);
		} else {
			if (e.error) {
				alert(e.error);
			} else {
				alert("Unkown result");
			}
		}
	});

### Show the Facebook Feed Dialog

This example shows how to display the [official Facebook dialog](http://developers.facebook.com/docs/reference/dialogs/feed/) for making a post to the user's feed.  In this example, we'll prefill some of the feed fields by passing a data dictionary to the dialog() method; this is not required.

	var data = {
		link: "http://www.appcelerator.com",
		name: "Appcelerator Titanium Mobile",
		message: "Checkout this cool open source project for creating mobile apps",
		caption: "Appcelerator Titanium Mobile",
		picture: "http://developer.appcelerator.com/assets/img/DEV_titmobile_image.png",
		description: "You've got the ideas, now you've got the power. Titanium translates your hard won web skills into native applications..."
	};
	FB.dialog("feed", data, function(e) {
		if (e.success) {
			alert("Success!  From FB: " + e.result);
		} else {
			if (e.error) {
				alert(e.error);
			} else if (e.cancelled) {
				alert('Cancelled');
			} else {
				alert("Unkown result");
			}
		}
	});


## Author

Appcelerator, Inc.
http://www.appcelerator.com

## License

Copyright (c) 2011 by Appcelerator, Inc. All Rights Reserved.
Licensed under the terms of the Apache Public License
Please see the LICENSE included with this distribution for details.

