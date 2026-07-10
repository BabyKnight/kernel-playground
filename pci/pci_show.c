#include <linux/init.h>
#include <linux/module.h>
#include <linux/pci.h>
#include <linux/kernel.h>

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Read PCI vendor device class example");
MODULE_AUTHOR("Vincent Hu");

static int __init pci_show_init(void)
{
	struct pci_dev *pdev = NULL;

	while((pdev = pci_get_device(PCI_ANY_ID, PCI_ANY_ID, pdev)) != NULL) {

		printk(KERN_INFO "BDF = %s, vendor:0x%04X, Device:0x%04X, Class:0x%06X\n",
				pci_name(pdev),
				pdev->vendor,
				pdev->device,
				pdev->class);
	}
	printk(KERN_INFO "PCI bus scan finished\n");

	return 0;
}

static void __exit pci_show_exit(void)
{
	pr_info("pci module exit\n");
}

module_init(pci_show_init);
module_exit(pci_show_exit);
