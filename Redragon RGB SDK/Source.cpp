#include <stdio.h>
#include <iostream>
#include "libusb.h"
#include<cmath> 

#pragma comment(lib, "libusb.lib")

using namespace std;

static struct usb_device *find_device(uint16_t vendor, uint16_t product);

static char Apply[] = { 0x02, 0xF1, 0x02, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
static struct usb_device *dev;
static struct usb_dev_handle *handle;
int LEDProfileOffs = 0x49;
int BrightnessProfileOffs = 0x4F;


extern "C"
{
	__declspec(dllexport) bool InitializeDevice(int M_Profile) 
	{
		int status = 0;
		dev = find_device(0x04D9, 0xFC30);
		if (dev == NULL)
		{
			return false;
		}
		handle = usb_open(dev);
		if (handle == NULL)
		{
			return false;
		}
		status = usb_claim_interface(handle, 2);
		if (M_Profile == 1) {
			LEDProfileOffs = 0x49;
			BrightnessProfileOffs = 0x4F;
		}
		else if (M_Profile == 2) {
			LEDProfileOffs = 0x51;
			BrightnessProfileOffs = 0x57;
		}
		else if (M_Profile == 3) {
			LEDProfileOffs = 0x59;
			BrightnessProfileOffs = 0x5F;
		}
		else if (M_Profile == 4) {
			LEDProfileOffs = 0x61;
			BrightnessProfileOffs = 0x67;
		}
		else if (M_Profile == 5) {
			LEDProfileOffs = 0x69;
			BrightnessProfileOffs = 0x6F;
		}
		else {
			LEDProfileOffs = 0x49;
			BrightnessProfileOffs = 0x4F;
		}

		return true;
	}

	__declspec(dllexport) bool RedragonSetColor(int R, int G, int B, int Level)
	{
		
		int bytes_written = 0;

		char Apply_Color[] = { 0x02, 0xF3, LEDProfileOffs, 0x04, 0x06, 0x00, 0x00, 0x00, R, G, B /* Color */, 0x01, 0x00, 0x02, 0x00, 0x00 };

		bytes_written = usb_control_msg(handle, 0x22, 0x09, 0x0302, 0x0002, Apply_Color, sizeof(Apply_Color), 500); // Set Color

		if (Level > -1) {
			static char Brightness[] = { 0x02,0xF3, BrightnessProfileOffs,0x04,0x01,0x00,0x00,0x00,Level /* Level */,0x00,0x00,0x00,0x00,0x00,0x00,0x00 };
			bytes_written = usb_control_msg(handle, 0x22, 0x09, 0x0302, 0x0002, Brightness, sizeof(Brightness), 500); // Set Brightness Level
		}

		bytes_written = usb_control_msg(handle, 0x22, 0x09, 0x0302, 0x0002, Apply, sizeof(Apply), 500); // Apply Settings
		
		return true;
	}
}
static struct usb_device *find_device(uint16_t vendor, uint16_t product)
{
	struct usb_bus *bus;
	struct usb_device *dev;
	struct usb_bus *busses;

	usb_init();
	usb_find_busses();
	usb_find_devices();

	busses = usb_get_busses();

	for (bus = busses; bus; bus = bus->next)
	{
		for (dev = bus->devices; dev; dev = dev->next)
		{
			if ((dev->descriptor.idVendor == vendor) && (dev->descriptor.idProduct == product))
			{
				return dev;
			}
		}
	}

	return NULL;
}
