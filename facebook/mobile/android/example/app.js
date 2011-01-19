/*global Ti, Titanium, alert, JSON, require, setTimeout, setInterval */
Titanium.UI.setBackgroundColor('#000');
var win = Titanium.UI.createWindow({  
    title:'Exercise Titanium Facebook Module',
    backgroundColor:'#000',
	exitOnClose: true
});

var APPID = "134793934930";

var FB = require("ti.facebook");
FB.appid = APPID;
FB.permissions = ['publish_stream', 'create_event'];

function showRequestResult(e) {
	var s = '';
	if (e.success) {
		s = "SUCCESS";
		if (e.result) {
			s += "; " + e.result;
		}
		if (e.data) {
			s += "; " + e.data;
		}
	} else {
		s = "FAIL";
		if (e.error) {
			s += "; " + e.error;
		}
	}
	alert(s);
}

var actionsView = Ti.UI.createView({
	top: 105, left: 0, right: 0, visible: FB.loggedIn, height: 'auto'
});

var login = FB.createLoginButton({
	top: 10, style:'wide'
});
win.add(login);

FB.addEventListener('login', function(e) {
	showRequestResult(e);
	if (e.success) {
		actionsView.show();
	}
});

FB.addEventListener('logout', function(e){
	Ti.API.info('logout event');
	actionsView.hide();
});

var checkprops = Ti.UI.createButton( {
	title: 'Check props',
	top: 60,left: 10, right: 10, height: 40
});
checkprops.addEventListener('click', function() {
	var s = '';
	s = 'uid: ' + FB.uid + '; ';
	s += 'loggedIn: ' + FB.loggedIn + '; ';
	s += 'appid: ' + FB.appid + '; ';
	s += 'permissions: ' + JSON.stringify(FB.permissions) + '; ';
	s += 'accessToken: ' + FB.accessToken + '; ';
	s += 'expirationDate: ' + FB.expirationDate + '; ';
	alert(s);
});
win.add(checkprops);

var statusText = Ti.UI.createTextField({
	top: 0, left: 10, right: 10, height: 40,
	hintText: 'Enter your FB status'
});
actionsView.add(statusText);
var statusBtn = Ti.UI.createButton({
	title: 'Publish status with GRAPH API',
	top: 45, left: 10, right: 10, height: 40
});
statusBtn.addEventListener('click', function() {
	FB.requestWithGraphPath('me/feed', {message: statusText.value}, "POST", showRequestResult);
});
actionsView.add(statusBtn);


var queryme = Ti.UI.createButton({
	title: 'Query "me" with GRAPH API',
	top: 90, left: 10, right: 10, height: 40
});

queryme.addEventListener('click', function() {
	FB.requestWithGraphPath('me', {}, 'GET', showRequestResult);
});
actionsView.add(queryme);

var event = Ti.UI.createButton({
	title: 'Create event with GRAPH API',
	top: 135, left: 10, right: 10, height: 40
});

actionsView.add(event);
event.addEventListener('click', function() {
	var starttime = new Date(2011, 4, 31, 17, 0);
	var endtime = new Date(2011, 4, 31, 19, 0);
	var title = "Barry's Birthday Celebration";
	var description = "Barry will have a great party";
	var data = {
		start_time: JSON.stringify(starttime),
		end_time: JSON.stringify(endtime),
		description: description,
		name: title
	};
	FB.requestWithGraphPath('me/events', data, 'POST', showRequestResult);
});

var photo = Ti.UI.createButton({
	title: 'Upload photo with REST API',
	top: 180, left: 10, right: 10, height: 40
});
photo.addEventListener('click', function() {
	var f = Ti.Filesystem.getFile('flower.jpg');
	var blob = f.read();
	var data = {
		caption: 'behold, a flower',
		picture: blob
	};
	FB.request('photos.upload', data, showRequestResult);
});
actionsView.add(photo);

var photo2 = Ti.UI.createButton({
	title: 'Upload photo with GRAPH API',
	top: 225, left: 10, right: 10, height: 40
});
photo2.addEventListener('click', function() {
	var f = Ti.Filesystem.getFile('watermelon.jpg');
	var blob = f.read();
	var data = {
		message: 'behold, a watermelon',
		picture: blob
	};
	FB.requestWithGraphPath('me/photos', data, 'POST', showRequestResult);
});
actionsView.add(photo2);

var wall = Ti.UI.createButton({
	title: 'Publish wall post with GRAPH API',
	top: 270, left: 10, right: 10, height: 40
});
wall.addEventListener('click', function() {
	var data = {
		link: 'http://www.thepostgame.com/features/201101/tom-bradys-guru',
		name: "Tom Brady and his Guru",
		message: "Tom Brady has a guru, and his name ain't Swami",
		caption: "Tom Brady's Guru",
		picture: "http://upload.wikimedia.org/wikipedia/commons/2/25/TomBrady.jpg",
		description: "Tom Brady and Gisele Bundchen walked into an Ann Arbor steakhouse four years ago for a party celebrating the 10th anniversary..."
	};
	FB.requestWithGraphPath('me/feed', data, 'POST', showRequestResult);
});
actionsView.add(wall);

var wallDialog = Ti.UI.createButton({
	title: 'Publish wall post with DIALOG',
	top: 315, left: 10, right: 10, height: 40
});
wallDialog.addEventListener('click', function() {
	var data = {
		link: "http://www.appcelerator.com",
		name: "Appcelerator Titanium",
		message: "Awesome SDKs for building desktop and mobile apps",
		caption: "Appcelerator Titanium",
		picture: "http://developer.appcelerator.com/assets/img/DEV_titmobile_image.png",
		description: "You've got the ideas, now you've got the power. Titanium translates your hard won web skills..."
	};
	FB.dialog("feed", data, showRequestResult);
});
actionsView.add(wallDialog);

win.add(actionsView);
win.open();

