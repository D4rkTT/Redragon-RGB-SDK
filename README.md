<p align="center"><img align="center" src="redragonSDK.png"></p>

# Redragon RGB SDK
First SDK for redragon products, it's unofficial and support few products due it's depending on reverse engineering every product to support it.

## Supported Devices
- Redragon M711 Cobra

## Usage (C#)
1- Import dll to your project 
```C#
[DllImport("Redragon RGB SDK.dll")]
public static extern bool InitializeDevice(int M_Profile);
[DllImport("Redragon RGB SDK.dll")]
public static extern bool RedragonSetColor(int R, int G, int B, int Level);
```

2- Use this function to check if device connected and initilaize it with current mouse profile
```C#
InitializeDevice(int M_Profile);
```
- M_Profile -> Current Mouse Profile
- It will return true if device connected and successfully initialized

3- Use this function to set color
```C#
RedragonSetColor(int R, int G, int B, int Level);
```

- R 0-255
- G 0-255
- B 0-255
- Level 1-3
- Enter Level -1 if u dont want to change Brightness Level
- It will return true if succssfully set

## Current Mode
- Fully Lighted Single Color

## Credits
- CalcProgrammer1 for his code to send USB Commands [Corsair K70 EGB](https://www.reddit.com/r/MechanicalKeyboards/comments/2ij2um/corsair_k70_rgb_usb_protocol_reverse_engineering/)
- Libusb

#### I'm Sorry that supported devices list is few but like i said ``support few products due it's depending on reverse engineering every product to support it.``

## Donate
As you see all my applications is open source

if you wanna to buy me a coffie or buy me a product to support it ☕❤
- Bitcoin: ``1sgPvUDBT8ZpXwvJAjSsqWPiebjxTdjX9``
- Ether:   ``0xdAcA9df277711Af20FA18b849471d50047D94B4b``
- USDD:    ``0xdAcA9df277711Af20FA18b849471d50047D94B4b``
## License
The code is licensed under the ISC license. You're free to use, modify, redistribute and even use it in any commercial projects so long as you keep the copyright notice. Be aware that this means I provide no warranty whatsoever should your product malfunction.
