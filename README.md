# FreeRtos
Playing around with some FreeRTOS and Fastled to get started with multithreading and RTOS 

Two threads looping around an ledstrip with different speeds.
Task1 makes the strip goes blue with a set 300ms delay

Task2 is using an IRsensor to measure distance from my hand. 
If it gets close it sets the delay of the thread to between 200 and 30ms.
This makes the led strip goes orange-redish while holding the hand. 
If hand is away it sets at 1500ms


![Twocounterlights](https://user-images.githubusercontent.com/92029450/169715869-e7533d0b-5472-4f35-8235-c137e3007178.png)
