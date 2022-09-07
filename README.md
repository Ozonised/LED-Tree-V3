# LED-Tree-V3
![LED Tree](/Images/Led-tree.jpg)
[LED-Tree-V3](https://youtu.be/tDnKHj7r4Kc) is the successor to my [Arduino UNO based LED-Tree](https://youtu.be/-E3FYhSJXbc). It is built around the ATmega8A microcontroller by Microchip. 

# Inspiration
The original inspiration for this project came from GreatScott's [3D LED Christmas tree](https://www.youtube.com/watch?v=Ya9RpvQyww4&t=0s). I really liked his idea and wanted to improve upon his project. The first verison I made was completely analog and based on the infamous ne555 and Cd4017 based knight rider circuit. You can watch it's build video [here](https://www.youtube.com/watch?v=1S3l5N7w0WI). One of the drawbacks with this verison was that it only had 1 effect. So to alleviate this issue, I made V2 using an Arduino UNO.

# Why did I create V3?
Well the Arduino UNO based LED-Tree had several shortcomings:
1. No way to toggle through the effects manually
2. No brightness control 
3. Insufficient number of shift regsiter
4. Coarse animation
5. Very few effects
6. In my opinion, the Arduino UNO was an overkill for this project


# Features:
To mitigate the mentioned above issues, I created V3. It's features are listed below:
1. Added a switch to toggle through the effects
2. Potentiometer to control the brightness
3. 4 shift register as compared to 2 in the previous version
4. As a result of the increased number of shift register and LEDs, the animations without a doubt are a lot smoother
5. Currently it has 11 effects but not limited to 11
6. Switched the ATmega328p of the Arduino UNO with an ATmega8A

![PCB](/Images/PCB.jpg)


# Drawbacks:
Version 3 is a major improvement over version 2 but that doesn't mean it's perfect. There are 2 drawbacks that I would like to mention.
1. It only has 11 effects. This is an improvement over the previous version but definitely not it's limit. My creativity skills are equivalent to that of an infant but not yours(hopefully). I can definitely use some of your imaginations to come up with newer and mesmerising effects. Let me know if you are interested.
2. It always needs to be powered either by a wall adapter or a powerbank.

# LED-TREE-V4
The latter is the one that bothered me the most. So to overcome this, I came up Version 4. This version does not bring any software changes but resolves the issue with it being always connected to a powerbank or a wall adapter. I did so by using one of those 3.7 volt to 5 volt power bank modules, based around [HT4928S](https://www.google.com/url?sa=t&rct=j&q=&esrc=s&source=web&cd=&ved=2ahUKEwji78mUqNj5AhXU6jgGHemCBBEQFnoECAYQAw&url=https%3A%2F%2Fwww.mikrocontroller.net%2Fattachment%2F480367%2FHT4928S-HOTCHIP_EN.pdf&usg=AOvVaw0lIInGk0nGiufScK4jM46i) mobile power supply management chip, with a lithium ion cell to power the project.

# Part Lists:
## Part list for V3:
|   | Component | Quantity |
| - | --------- | :------: |
| 1.| Atmega8A  | 1 |
| 2.| 28 pin IC socket | 1 |
| 3.| 74HC595 | 4 |
| 4.| 16 pin IC socket | 4 |
| 5.| 7 * 9cm Perf Board | 1 |
| 6.| 3mm Copper Wire | 30cm |
| 7.| 1mm Copper Wire | 250 - 300 cm |
| 8.| 5mm LED | 32 |
| 9.| 330 ohm resistor | 32 |
| 10.| 4 * 1 female header | 8 |
| 11.| 4 * 1 male header | 10 |
| 12.| 1k resistor | 1 |
| 13.| 10k resistor | 2 |
| 14.| 100K resistor | 1 |
| 15.| 100nF capacitor | 1 |
| 16.| 1uF capacitor | 1 |
| 17.| 100uF capacitor | 1 |
| 18.| 470uF capacitor | 1 |
| 19.| SPST switch | 2 |
| 20.| Micro USB female port | 1 |
| 21.| 28 awg wire | 9 - 10 m |
## Part list for V4
|    |           |       |
| -- | --------- | :---: |
| 22.| 3.7 to 5 volt power bank module | 1 |
| 23.| SPST switch | 1 |
| 24.| lithium ion cell | 1 |

# Setting Up ATmega 8
I did not burn a bootloader into the microncontroller so it cannot be programmed through the serial port. So it must be programmed through the ICSP headers via the Serial Peripheral Interface(SPI). To do so, you need an AVR ISP programmer like USBASP or ATmel ICE but a cheaper solution would be to use an Arduino UNO or a Nano as an ISP programmer(this is what I used). 
By default the ATmega 8 uses its internal 8 MHz RC oscillator with a prescaler of 8 which equates to a sytem clock frequency of 1 MHz which is rather slow. However for this project, we will be running it at 8 MHz. So follow the steps listed below to configure the microcontroller: 

1. Download and install AVRDude. AVRDude is the program used by Arduino IDE and PlatformIO to upload your code to an AVR microcontroller.
2. Open up the Arduino IDE, select ```ArduinoISP``` under File/Examples/ and hit upload.
3. Wire up the Arduino and ATmega8 as shown in the [schematic](/Schematic/ATmega8-programmer.pdf): ![ATmega8 programmer](/Images/ATmega8-programmer.png)
4. By default, the low fuse of the ATmega8 is set to 0xE1. This must be set to 0xE4 to configure the microcontroller to run at 8MHz. Type ``` avrdude -c stk500v1  -P COM5 -p atmega8 -b 19200 -U lfuse:w:0xe4:m -U hfuse:w:0xd9:m ```. Alternatively, you can use an online [AVR fuse bit calculator](https://www.engbedded.com/fusecalc/) for your selected microcontroller. ![Changing lfuse](/Images/Changing-fuse-bits.png)
### Note: 
The ```-P <port>```argument specifies the connection port. In my case, the arduino is connected to ```COM5``` and hence the argument ```-P COM5```. For ```-p <partno>``` either ```-p m8``` or ```-p atmega8``` can be used. Refer this [guide](https://www.ladyada.net/learn/avr/avrdude.html) for more information.
