### Hard to wake up every morning ? Always late, even if you planned to wake up earlier ? Or just want to ease and make your wake up moment more comfortable ? Here is the solution !

	# Wake up Theory

I think that a typical alarm clock isn't enough to wake you up. My theory is that a bright with a sound ease your wake up, and it is more efficient if there is a link between the sound and the bright, like in a video. Moreover, it's still better if the video content is interesting, new, and orchestrated in an order that will retain your intention at the right moment.

	# The solution

I've created a two-parts solution to be able to drive your TV and your Playstation 4 to wake you up at the right time. An "Arduino" device is activated by yourself (by a single button) when you go sleeping, then it sends a single request to the Web Service Driver to retrieve all the commands that the Arduino will execute. The commands are a totally custom creation of myself, a new protocol, to tell the Arduino what to do exactly. The WS is already developped to drive the Arduino and provide these features in order:
	1. Close the TV and PS4 after a timer period (usefull to shutdown your TV and PS4 when you fall asleep, without caring about shuting down the devices).
	2. Start all the devices needed and go to open video content according to the formula you chose.
	3. Close all the devices after all the medias content have been displayed (or just after a maximum activation time).


	# Web Service Driver

The Web Service Driver is the brain of the project. All the execution logic is writen here, and sent to the Arduino as command sequences. It eases a lot the development or the improvement in the project because for every new features that are added in the future, most of the time it will require a change only in the Web Service, so we don't have to touch at the Arduino program at all for most of the cases.

For the moment, the project only manages a TV with a PS4, but it can be adapted for any other set of devices. If you are interesting in widening the set of possibilities, you are invited to contribute ;)

For more informations about the Web Service part, please have a look at the related repository : (https://github.com/RayanoxPersonalProjects/VideoAlarmClock-WS)
