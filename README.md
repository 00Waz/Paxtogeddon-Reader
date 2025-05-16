### Overview

The Paxtogeddon reader is source code to create a weaponised reader to target Paxton Net2 and Switch2 tokens.

Features:

* CLK/DATA decoding straight off the back of the reader
* Paxton auth token decoding
  * Also determines if its was a Net2 or Switch2 token, and even the colour of the fob!
* Persistent log saving on SPIFFS
* Wifi AP ect for in the field shinanigans

### Quote from the codes main developer

```
"Anyone can share it mate, do whatever you want with it. 
Stick it on your own GitHub, I don’t mind at all. 👍"
```

Note I was not the main writer of this code, but Dan couldn't be bothered to put it on GitHub because he's "not a hacker".

### Quote from En4rab

```
“I would have used my own code but it was shit and Daniel's is much better”
```

### Bill of materials

* ESP32 dev board
* 0.22uF Electrolytic capacitor
* 1uF Electrolytic capacitor
* 100nF Ceramic capacitor
* 2x 1kOhm resistors
* 7805 Voltage Regulator
* 2x 1A Diodes
* desire to get root

### Janky Circuit Design

If anyone wants to draw this a bit nicer be my guest

![Janky Circuit Drawing](https://github.com/00Waz/Paxtogeddon-Reader/blob/main/images/circuit.png?raw=true)

### Notes on flashing

I have noticed that i have had to format SPIFFS before i flash the firmware, otherwise issues are had.
So if you want to/need to do this, theres some simple SPIFFS formatting code that you should flash first in this repo.

### Field use

#### Board

A little board setup of the above circuit to make in the field use a little neater.

(https://github.com/00Waz/Paxtogeddon-Reader/blob/main/images/Components.png?raw=true)
(https://github.com/00Waz/Paxtogeddon-Reader/blob/main/images/Jumpers_and_wiring.png?raw=true)
(https://github.com/00Waz/Paxtogeddon-Reader/blob/main/images/Board.png?raw=true)

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
I used an ESP32C3 Supermini board, as they're awesome and set the pins as below

(https://github.com/00Waz/Paxtogeddon-Reader/blob/main/images/1.png?raw=true)
(https://github.com/00Waz/Paxtogeddon-Reader/blob/main/images/2.png?raw=true)
(https://github.com/00Waz/Paxtogeddon-Reader/blob/main/images/3.png?raw=true)
(https://github.com/00Waz/Paxtogeddon-Reader/blob/main/images/4.png?raw=true)
(https://github.com/00Waz/Paxtogeddon-Reader/blob/main/images/5.png?raw=true)
