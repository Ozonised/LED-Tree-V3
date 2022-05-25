# LED-Tree-V3
LED-Tree-V3 is the successor to my [Arduino UNO based LED-Tree](https://youtu.be/-E3FYhSJXbc). It is built around the ATmega8A microcontroller by Microchip. 

# Inspiration
The original inspiration for this project came from GreatScott's [3D LED Christmas tree](https://www.youtube.com/watch?v=Ya9RpvQyww4&t=0s). I really liked his idea and wanted to improve upon his project. The first verison I made was completely analog and based on the infamous ne555 and Cd4017 based knight rider circuit. You can watch it's build video [here](https://www.youtube.com/watch?v=1S3l5N7w0WI). One of the drawbacks with this verison was that it only had 1 effect. So to alleviate this issue, I made V2 using an Arduino UNO.

# Why did I create this V3?
Well the Arduino UNO based LED-Tree had several shortcomings:
1. No way to toggle through the effects manually
2. No brightness control 
3. Insufficient number of shift regsiter
4. Coarse animation
5. Very few effects
6. In my opinion, the Arduino was an overkill for this project


# Features:
To mitigate the mentioned above issues, I created V3. It's features are listed below:
1. Added a switch to toggle through the effects
2. Potentiometer to control the brightness
3. 4 shift register as compared to 2 in the previous version
4. As a result of the increased number of shift register and LEDs, the animations wihtout a doubt are a lot smoother
5. Currently it has 11 effects but not limited to 11
6. Switched the ATmega328p of the Arduino UNO with an ATmega8A

# Drawbacks:
So far the only drawback I can think of is that it only has 11 effects. This is an improvement over the previous version but definitely not it's limit. My creativity skill is equivalent to that of an infant but not yours(hopefully). I can use some of your imaginations to come up with some effects. Let me know if you are interested.
