## Overview

Paxtogeddon reader is a weaponised reader aimed at targetting Paxton Net2 system.

Features:

* CLK/DATA decoding straight off the back of the reader
* Paxton auth token decoding
  * Also determines if its was a Net2 or Switch2 token, and even the colour of the fob!
* Persistent log saving on SPIFFS
* Wifi AP ect for in the field use

### Changes in V2

So Dan has been at it again and rewrote the entire thing from V1, and also added some really nice functionality.

#### Function cards

You can now use a selection of function cards to do some nice stuff like:

* Display "TEST CARD" for use in the field as initial test to ensure everything is working before you head out
  * Card number - 99999999
* Revert to defaults if you forget your password for the wifi, but it wont clear the log!
  * Card number - 99999998
* Connects to configured AP instead of acting as AP
  * Card number - 99999997
* Display AP info on connected OLED screen incase you forget it
  * Card number - 99999996

#### Settings menu

With this version you can also configure it from the web gui without the need to reflash it every time you want to change the SSID, change the IP, or change the refresh timer.
It also has a captive portal for when you connect to the SSID on a phone it loads automatically for quickly accessing the web gui.

![V2 Settings Page](https://github.com/00Waz/Paxtogeddon-Reader/blob/main/Images/V2_Settings.png?raw=true)

#### Send card number

Unlike V1, the transmission pins are the same as the capture pins for retransmission of data if connected inline with a reader.
You can also send a specific number direct from the web gui if you just want to type one in. This will calculate the CLK/Data and send over the transmssion pins.

![Send Card Number](https://github.com/00Waz/Paxtogeddon-Reader/blob/main/Images/Card_Number.png?raw=true)

#### Companion App

There's a companion app to run on a windows host to make cloning cards easier, as it will send the commands directly from the web gui straight to your proxmark via the proxspace container app set up on Windows ([Proxspace Github](https://github.com/Gator96100/ProxSpace))

#### Smart Watch Notifications

Nice little hook into a smart watch, so you get live notifications when a read is gained, so you know when you can do a happy root dance (while being hidden).

Another ESP32 board is needed, as it wont all fit onto to the one now, its getting a bit big and the supermini only has one core.

![Kit layout](https://github.com/00Waz/Paxtogeddon-Reader/blob/main/Images/PR2.jpg?raw=true)

![Smart Watch](https://github.com/00Waz/Paxtogeddon-Reader/blob/main/Images/PR4.jpg?raw=true)

It now hooks into a FitPro M4/M5/M6, super cheap on Amazon :)

### Other

**"Sounds like Dan did a lot of work here, why is it on your GitHub Waz?" I hear you say...**

Well...

Quote from the codes main developer - Daniel "Dr0pR00t" Raines

```
"Anyone can share it mate, do whatever you want with it. 
Stick it on your own GitHub, I don’t mind at all. 👍"
```

Note I was not the main writer of this code, but Dan couldn't be bothered to put it on GitHub because he's "not a hacker".

This guy is a legend in this space, and you should show him some love over at [Dans LinkedIn](https://www.linkedin.com/in/danielraines/)

**"I remember seeing an Iceman video on En4rab's code for the doorsim that did this" I also hear you say...**

Quote from En4rab

```
“I would have used my own code but it was shit and Daniel's is much better”
```

So En4rab wrote some micropython code that started this whole process, but this ended swiftly when we realised that micropython was a bit bad...

However he has made a <ins>REALLY</ins> nice printed circuit board design with an OLED attachment for this project, which can be found at [En4rab's board](https://github.com/en4rab/Paxtogeddon-OLED-PCB)

## Hardware

### Bill of materials

* ESP32C3 Supermini board
* 0.22uF ceramic capacitor
* 1uF ceramic capacitor
* 100nF ceramic capacitor
* 2x 1kOhm resistors
* 7805 Voltage Regulator
* 2x 1A Diodes
* desire to get root

### Janky Circuit Design

This is the basic design of this board, excuse the rubbish drawing, but if you know what you're looking at, you'll be fine.

![Janky Circuit Drawing](https://github.com/00Waz/Paxtogeddon-Reader/blob/main/Images/circuit.png?raw=true)

### Field use

#### Board

A little board setup of the above circuit to make in the field use a little neater.

![](https://github.com/00Waz/Paxtogeddon-Reader/blob/main/Images/Components.png?raw=true)
![](https://github.com/00Waz/Paxtogeddon-Reader/blob/main/Images/Jumpers_and_wiring.png?raw=true)
![](https://github.com/00Waz/Paxtogeddon-Reader/blob/main/Images/Board.png?raw=true)

Adjust the sourcecode to refelct the new GPIO pin outs for this board:

```
const byte HEARTBEAT_LED_PIN = 8;  //Adjust as required (built-in LED to show main loop "extremely fast" heartbeat!)
const byte CLOCK_PIN = 3;         //Adjust as required
const byte DATA_PIN = 4;          //Adjust as required
const byte REPLAY_CLOCK_PIN = 5;   //Adjust as required - Something that exists on the board, but not used
const byte REPLAY_DATA_PIN = 6;   //Adjust as required - Something that exists on the board, but not used
const byte WIFI_MODE_PIN = 7;     //Adjust as required - Something that exists on the board, but not used
const byte GREEN_LED_PIN = 0;     //Adjust as required
const byte RED_LED_PIN = 2;       //Adjust as required
const byte YELLOW_LED_PIN = 1;    //Adjust as required
```

#### Case

So I made a case for use in the field to house a battery pack, and make sure stuff doesn't get broken

To get this working nice as i have it below, you just need some threaded insert and bolt for the reader, of and the reader ofcourse. FYI, the P200 works really well for this and has a read range or arounf 20cm.

Battery I used for this build can be found here, [Battery pack on Amazon](https://www.amazon.co.uk/dp/B00EUG26SO?ref_=ppx_hzsearch_conn_dt_b_fed_asin_title_4). I like these basically because theyre small, solid 12v to power all my weaponised readers, and dont break if I drop them.

![](https://github.com/00Waz/Paxtogeddon-Reader/blob/main/Images/1.jpg?raw=true)
![](https://github.com/00Waz/Paxtogeddon-Reader/blob/main/Images/3.jpg?raw=true)
![](https://github.com/00Waz/Paxtogeddon-Reader/blob/main/Images/5.jpg?raw=true)
