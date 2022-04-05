#!/bin/bash
cd /home/nema/Documents/PlatformIO/Projects/220303-225705-lptm4c123gh6pm
if [[ $1 = "build" ]]
then
	/home/nema/.platformio/penv/bin/pio run --environment lptm4c123gh6pm
elif [[ $1 = "compile" ]] 
then
	/home/nema/.platformio/penv/bin/pio run --target upload --environment lptm4c123gh6pm
elif [[ $1 = "both" ]]
then
	/home/nema/.platformio/penv/bin/pio run --environment lptm4c123gh6pm
	/home/nema/.platformio/penv/bin/pio run --target upload --environment lptm4c123gh6pm
else
	echo "Invalid directive, please use either 'build', 'compile', or 'both'."
fi
