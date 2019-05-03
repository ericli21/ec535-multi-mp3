# EC535 Project: Multi-MP3
## Caroline Ekchian, Eric Li, Kaitlin Walsh

This is the guide to follow to set up MultiMP3, a final project for EC 535 Intro to Embedded Systems.  Once set up, MultiMP3 acts as a multi-user MP3 player that connects to a bluetooth speaker.  Users can log in using the LCD touchscreen and the UART fingerprint scanner.

## Project Setup

### External Hardware
The external hardware required for this project setup is the LCD touchscreen, the Bluetooth antenna and speaker, the Gumstix Verdex board and the Parallax UART fingerprint scanner, and a serial to USB cable. 

The serial to USB cable is required for initial setup and debugging. To connect this cable to the Gumstix board, connect the serial cable to either J2, J3, or J4 on the gumstix board, then connect the USB side of this cable to the computer. Next, the LCD touchscreen needs to be connected to the to the gumstix board. This is done by connecting the LCD panel ribbon cable to the LCD panel port (console-vx) on the gumstix. 

The fingerprint scanner is connected to the Gumstix board via the STUART (Standard UART) connector. The pin connections are outlined in the table below.


|Fingerprint Scanner Pin Name|Gumstix Pin Name|Fingerprint Scanner Pin Number|Gumstix Connector, Pin Number|
|---|---|---|---|
|VCC|VCC|1|AC97, 7 
|GND|GND|2|STUART, 1|
|RXD|ST_TXD|3|STUART,  2|
|TXD|ST_RXD|4|STUART, 4|



### External Libraries

All external libraries were downloaded from the Gumstix website at the following links: 
* [Page 1](https://downloads.gumstix.com/feeds/archive/318M/glibc/ipk/armv5te/)
* [Page 2](https://downloads.gumstix.com/feeds/archive/318M/glibc/ipk/gumstix-custom-verdex/)

The following packages needed to be installed to use madplay and aplay:
* alsa-utils-aplay_1.0.14-r1_armv5te.ipk
* madplay_0.15.2b-r0_armv5te.ipk

The following packages also needed to be installed because they were dependencies for madplay, aplay, and the bluetooth communication interface:
* bluez-utils-alsa_3.24-r2_gumstix-custom-verdex.ipk
* bluez-utils_3.24-r4_gumstix-custom-verdex.ipk
* gettext_0.14.1-r7_armv5te.ipk
* libaudiofile0_0.2.6-r6_armv5te.ipk
* libesd0_0.2.36-r2_armv5te.ipk
* libgettextlib_0.14.1-r7_armv5te.ipk
* libgettextsrc_0.14.1-r7_armv5te.ipk
* libiconv_1.11-r4_armv5te.ipk
* libid3tag0_0.15.1b-r0_armv5te.ipk
* libmad0_0.15.1b-r0_armv5te.ipk
* libstdc++6_4.1.2-r10_armv5te.ipk

The libraries were installed onto the SD card on the Gumstix through the serial connection with the host computer.

> root@gumstix-custom-verdex:~$ cd /media/card
> root@gumstix-custom-verdex:~$ mkdir packages
> root@gumstix-custom-verdex:~$ cd packages
> root@gumstix-custom-verdex:~$ rz -bZ
> root@gumstix-custom-verdex:~$ (Ctrl + A + Z), (S + Enter)
> root@gumstix-custom-verdex:~$ (navigate to package location on host)
> root@gumstix-custom-verdex:~$ (select one or many libraries with spacebar + Enter)

Once installed, each library was installed using the ipkg install command. Install the dependencies before installing madplay and aplay.

> root@gumstix-custom-verdex:~$ cd /media/card/packages
> root@gumstix-custom-verdex:~$ ipkg install [package file name]


### QT

Similar to Lab 5, the QT application is created using dependencies from the EC535 source folder. Please include all code modules relating to the Qt user interface in the same directory (named “Ui”) so that they all are added to the qmake project automatically. 

> qmake -project
> qmake

We will need to replace the Makefile’s INCPATH with the following (in Lab 5 tutorial):

(image here)

To make a fresh Ui binary executable:
> make clean
> make

### Songs

Transfering songs to the SD card was done using the serial connection between the Gumstix and the host computer. The average song takes about 8 minutes to download.

> root@gumstix-custom-verdex:~$ cd /media/card
> root@gumstix-custom-verdex:~$ mkdir songs
> root@gumstix-custom-verdex:~$ cd songs
> root@gumstix-custom-verdex:~$ rz -bZ
> root@gumstix-custom-verdex:~$ (Ctrl + A + Z), (S + Enter)
> root@gumstix-custom-verdex:~$ (navigate to song location on host)
> root@gumstix-custom-verdex:~$ (select one or many songs with spacebar + Enter)

Due to the way we process songs within this project, the song file names had to be edited to remove non-standard ASCII characters and spaces.  These characters and spaces are fine within the ID3 tags, and do not need to be edited there.

> "10 d E A T h b R E a s T ⚄ ⚄.mp3" -> “10.mp3” 

### Initialization

Within the minicom terminal, run the following commands to set up the variables that will be needed to run our QT variables:

> export QWS_MOUSE_PROTO='tslib:/dev/input/touchscreen0'
> export TSLIB_CONFFILE=/etc/ts.conf
> export TSLIB_PLUGINDIR=/usr/lib
> export TSLIB_TSDEVICE=/dev/input/event0
> export TSLIB_FBDEVICE=/dev/fb0
> export TSLIB_CONSOLEDEVICE=/dev/tty
> export QT_QWS_FONTDIR=/media/card/lib/fonts
> export TSLIB_PLUGINDIR=/usr/lib/ts
    
Run “ts_calibrate” after this, noting that sometimes the calibration screen does not show.  Just hit Ctrl+C and run calibrate again.

Initially, we needed to configure the Gumstix board so that it could recognize and communicate with bluetooth speaker. To do this, we followed the instructions at the following link: [Bluetooth Guide](https://wiki.gumstix.com/index.php/Category:How_to_-_bluetooth)

After installing all of the packages that were needed to use madplay, aplay, and the bluetooth communication interface, we were able to enable the communication between our gumstix board and our bluetooth speaker. In order to enable this communication, we first needed to update the /etc/bluetooth/audio.service file to enable autostart for the bluetooth service. We did this by editing this file so that ‘Autostart=true’. After changing this value, we restarted the gumstix board. Once the board restarted, we ran the following command: 

> root@gumstix-custom-verdex:~$ passkey-agent --default 0000 &

We then turned on our bluetooth speaker so that we could determine the MAC address of the speaker. We did this by running the following command:

> root@gumstix-custom-verdex:~$ hcitool scan

The output of running this command is the devices that were detected while running the scan and their MAC addresses. We found the MAC address associated with our bluetooth speaker and edited the /etc/asound.conf so that it contained the following: 

(input here)

After taking these steps, we verified that we were able to play song by running the following command on the command line:

> root@gumstix-custom-verdex:~$ madplay 10.mp3 -r 44100 --output=wave:- | aplay -D D80_Speaker

## Project Use
