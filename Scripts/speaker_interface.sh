#!/bin/bash

# ash speaker_interface.sh $[action] $2[/path/song.mp3] &

# Play button pressed
if [ $1 = "play" ]
then

	# Check if we are coming back from a pause
	pausevar=$(cat temp.txt)

	# Used in the case of conflicting PID in info and play
	pid_song_temp=$(cat temp_pid.txt)

	if [ $pausevar = 1 ]
	then
		# Continue playing song and reset pause file
		kill -CONT $pid_song_temp
		echo "0" > temp.txt
	else
		# Play new song
		madplay -v --display-time=remaining $2 44100 --output=wave:- 2>song_info.txt | aplay -D D80_speaker &
		pid_song=$(pidof madplay)

		# Store the PID of the currently playing song
		echo $pid_song > temp_pid.txt
		echo "0" > temp.txt
	fi

# Pause button pressed
elif [ $1 = "pause" ]
then	
	# Set Pause Variable
	echo "1" > temp.txt
	
	# Pause currently playing song
	pid_song_temp=$(cat temp_pid.txt)
	kill -STOP $pid_song_temp

# Next/Previous song pressed
elif [ $1 = "next" ]
then	
	# Reset pause
	echo "0" > temp.txt

	# Kill current song
	killall -9 aplay
	killall -9 madplay
	echo "killedall"
	sleep 1

	# Send output of stderr (where madplay prints) to song_info.txt
	echo "hello"
	madplay -v --display-time=remaining $2 44100 --output=wave:- 2>song_info.txt | aplay -D D80_speaker  &

	# Store the PID of the currently playing song
	pid_song=$!
	echo $pid_song > temp_pid.txt

# Stop button pressed
elif [ $1 = "stop" ]
then	
	# Reset pause file
	echo "0" > temp.txt

	# Kill everything
	killall -9 madplay 
	killall -9 aplay

# Get information for ID3 tag parsing
elif [ $1 = "info" ]
then	
	# Reset information temp files
	rm song_info.txt
	touch song_info.txt
	rm output.txt
	touch output.txt

	# Run madplay on info song, redirect wave output to null
	madplay -v --display-time=remaining $2 44100 --output=null:- 2>song_info.txt &

	# Kill this song		
	pid_song=$!
	sleep 2	
	#usleep 30000
	kill -9 $pid_song

	# Fix the carriage return >:(
	tr '\r' '\n' < song_info.txt > output.txt
	
fi

