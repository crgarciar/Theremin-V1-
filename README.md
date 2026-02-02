#### Ultrasonic Theremin Project

An Arduino-based musical instrument that uses ultrasound to detect hand distance and convert it into real-time sound frequencies. This project features two distinct "octave" modes toggled by a physical button.



##### Features Continuous Pitch 

Uses mathematical mapping for a smooth "slide" whistle effect.

Dual Range Mode: Toggle between Low (200Hz–1000Hz) and High (1001Hz–1800Hz) frequency banks using a button.

Distance Filtering: Constrained to a 2cm–60cm playable zone to prevent erratic noise.



##### Hardware Required

1x Arduino Uno (or compatible board)

1x HC-SR04 Ultrasonic Sensor

1x Passive Buzzer (Piezo)

1x Momentary Push Button Jumper Wires and 

1x Breadboard

##### Wiring Diagram Component Arduino:

#### [ThinkerCad Schematichs ](https://www.tinkercad.com/things/0nNt2go7DoY-brave-maimu-luulia/editel?returnTo=https%3A%2F%2Fwww.tinkercad.com%2Fdashboard&sharecode=kQzRtuOT2MUKDMhv9b0fQ1MflmI6hRCIHU3POau6ue4)

*Important*: The button is wired to Ground. When pressed, the signal is LOW.



###### Software Setup 

Ensure you have the Arduino IDE installed.

Install the SR04.h library (available via the Library Manager or as a header file).

Upload the provided .ino sketch to your Arduino.

Open the Serial Monitor (9600 baud) to see the live distance and frequency data.



###### How to Play Pitch Control: 

Move your hand toward or away from the ultrasonic sensor.

Closer (2cm): Higher Pitch Further (60cm): Lower Pitch Toggle Range: \* Released: Play in the standard range ($200Hzt-1000Hz).

Pressed: Shift into the high-frequency "solo" range (1001Hz-1800Hz).

Silence: Move your hand more than 60cm away to stop the sound.



###### Troubleshooting

Constant Beeping: Check if the Echo/Trig pins are swapped.

No Sound: Ensure you are using a Passive buzzer (one that can play different tones) rather than an Active buzzer (which only plays one fixed beep).

Jittery Sound: Keep the sensor away from soft surfaces (like curtains or carpet) which can absorb the ultrasonic pulse.



###### Final Notes



I've created a note for you that explains the extra code blocks at the bottom of your file. It covers:



Tuned Notes: How to switch from sliding frequencies to specific musical notes.



Silent Calibration: Using the second block of code to test your distance settings without the buzzer making noise.





