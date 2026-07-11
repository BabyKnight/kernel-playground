#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/usb.h>

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("A Simple USB Device Scanner using usb_for_each_dev");
MODULE_AUTHOR("Vincent Hu");
MODULE_VERSION("0.1");

static int v_usb_dev_callback(struct usb_device *udev, void *data)
{
	int *count = (int *)data;
	struct usb_device_descriptor *desc = &udev->descriptor;

	(*count)++;

	pr_info("----------------------------------------------------------\n");

	pr_info("Bus %03d Device %03d: Port Path: %s\n",
			udev->bus->busnum, udev->devnum, udev->devpath);

	pr_info("  |-- Vendor ID  : 0x%04x\n", le16_to_cpu(desc->idVendor));
	pr_info("  |-- Product ID : 0x%04x\n", le16_to_cpu(desc->idProduct));

	pr_info("  |-- Dev Class  : 0x%02x (SubClass: 0x%02x, Protocol: 0x%02x)\n",
			desc->bDeviceClass, desc->bDeviceSubClass, desc->bDeviceProtocol);

	pr_info("  |-- Speed      : %s\n",
			(udev->speed == USB_SPEED_SUPER_PLUS) ? "SuperSpeed+" :
			(udev->speed == USB_SPEED_SUPER) ? "SuperSpeed" :
			(udev->speed == USB_SPEED_HIGH) ? "High-Speed" :
			(udev->speed == USB_SPEED_FULL) ? "Full-Speed" : "Low-Speed");

	pr_info("  |-- Configurations: %d (Active Config ID: %d)\n",
			desc->bNumConfigurations, udev->actconfig ? udev->actconfig->desc.bConfigurationValue : 0);

	return 0;
}

static int __init v_usb_show_init(void)
{
	int usb_dev_count = 0;

	pr_info("===============STARTING USB BUS SCAN===================");
	usb_for_each_dev(&usb_dev_count, v_usb_dev_callback);

	pr_info("===============SCAN USB BUS FINISHED (Found %d DevS)===================", usb_dev_count);
	return 0;
}

static void __exit v_usb_show_exit(void)
{
	pr_info("USB scan module unloaded.\n");
}

module_init(v_usb_show_init);
module_exit(v_usb_show_exit);
