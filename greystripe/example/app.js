// This is a test harness for your module
// You should do something interesting in this harness 
// to test out the module and to provide instructions 
// to users on how to use it by example.


// open a single window
var window = Ti.UI.createWindow({
  backgroundColor:'white'
});
window.open();

Titanium.Greystripe = require('ti.greystripe');

Titanium.Greystripe.setup({
	applicationId:'<<<YOUR APP ID HERE>>>',
	adSlots:[{size:Titanium.Greystripe.BANNER, name:'ad1'}]
});
var view = Titanium.Greystripe.createView({
	name:'ad1',
	height:48,
	top:10,
	left:10,
	right:10
});
window.add(view);