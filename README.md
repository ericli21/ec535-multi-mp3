# EC535 Project: Multi-MP3
## Caroline Ekchian, Eric Li, Kaitlin Walsh

This is the guide to follow to set up MultiMP3, a final project for EC 535 Intro to Embedded Systems.  Once set up, MultiMP3 acts as a multi-user MP3 player that connects to a bluetooth speaker.  Users can log in using the LCD touchscreen and the UART fingerprint scanner.

## Project Setup

### External Hardware
The external hardware required for this project setup is the LCD touchscreen, the Bluetooth antenna, and the Parralax UART fingerprint scanner.
Connect the LCD touchscreen to the Gumstix board by connecting the ribbon cable (to the port)?????

Similarly, connect the fingerprint scanner to the UART fingerprint reader board by connecting the ribbon cable to the port.

Connect fingerprint scanner wires to the gumstix pins (diagram here)

### External Libraries

All external libraries were downloaded from the Gumstix website at the following link: [link here].
The following libraries were the main libraries used by this project:
* alsa-utils-aplay_1.0.14-r1_armv5te.ipk
* madplay_0.15.2b-r0_armv5te.ipk

The following libraries were dependencies from our main libraries:
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

How to install/make QT (instructions from lab)
What we had to modify within the makefile for our additional code

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

Within the gumstix/minicom terminal, run the following commands to set up QT variables:

> export QWS_MOUSE_PROTO='tslib:/dev/input/touchscreen0'
> export TSLIB_CONFFILE=/etc/ts.conf
> export TSLIB_PLUGINDIR=/usr/lib
> export TSLIB_TSDEVICE=/dev/input/event0
> export TSLIB_FBDEVICE=/dev/fb0
> export TSLIB_CONSOLEDEVICE=/dev/tty
> export QT_QWS_FONTDIR=/media/card/lib/fonts
> export TSLIB_PLUGINDIR=/usr/lib/ts
    
Run “ts_calibrate” after this, noting that sometimes the calibration screen does not show.  Just hit Ctrl+C and run calibrate again.

Bluetooth: changing the .conf file, finding the MAC address of the speaker, passkey-agent command

## Project Use
