/*
 * Driver for keys on GPIO lines capable of generating interrupts.
 *
 * Copyright 2005 Phil Blundell
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#include <linux/module.h>
#include <linux/version.h>

#include <linux/init.h>
#include <linux/fs.h>
#include <linux/interrupt.h>
#include <linux/irq.h>
#include <linux/sched.h>
#include <linux/pm.h>
#include <linux/sysctl.h>
#include <linux/proc_fs.h>
#include <linux/delay.h>
#include <linux/platform_device.h>
#include <linux/input.h>
#include <linux/irq.h>
#include <linux/gpiodev.h>
#include <linux/gpiodev_keys.h>

//#include <asm/gpio.h>

static irqreturn_t gpiodev_keys_isr(int irq, void *dev_id)
{
	int i;
	struct platform_device *pdev = dev_id;
	struct gpiodev_keys_platform_data *pdata = pdev->dev.platform_data;
	struct input_dev *input = platform_get_drvdata(pdev);

	for (i = 0; i < pdata->nbuttons; i++) {
		struct gpio *gpio = &pdata->buttons[i].gpio;
		if (irq == gpiodev_to_irq(gpio)) {
			int state = (gpiodev_get_value(gpio) ? 1 : 0) ^ (pdata->buttons[i].active_low);

			if (pdata->buttons[i].type == EV_SW)
				input_report_switch(input, pdata->buttons[i].keycode, state);
			else
				input_report_key(input, pdata->buttons[i].keycode, state);
			input_sync(input);
		}
	}

	return IRQ_HANDLED;
}

static int __devinit gpiodev_keys_probe(struct platform_device *pdev)
{
	struct gpiodev_keys_platform_data *pdata = pdev->dev.platform_data;
	struct input_dev *input;
	int i, error;

	input = input_allocate_device();
	if (!input)
		return -ENOMEM;

	platform_set_drvdata(pdev, input);

	input->evbit[0] = BIT(EV_KEY);

	input->name = pdev->name;
	input->phys = "gpiodev-keys/input0";
	input->cdev.dev = &pdev->dev;
	input->private = pdata;

	input->id.bustype = BUS_HOST;
	input->id.vendor = 0x0001;
	input->id.product = 0x0001;
	input->id.version = 0x0100;

	for (i = 0; i < pdata->nbuttons; i++) {
		int code = pdata->buttons[i].keycode;
		int irq = gpiodev_to_irq(&(pdata->buttons[i].gpio));

		set_irq_type(irq, IRQ_TYPE_EDGE_BOTH);
		error = request_irq(irq, gpiodev_keys_isr, IRQF_SAMPLE_RANDOM | IRQF_SHARED,
				     pdata->buttons[i].desc ? pdata->buttons[i].desc : "gpiodev_keys",
				     pdev);
		if (error) {
			printk(KERN_ERR "gpiodev-keys: unable to claim irq %d; error %d\n",
				irq, error);
			goto fail;
		}
		if (pdata->buttons[i].type == EV_SW) {
			input->evbit[0] |= BIT(EV_SW);
			set_bit(code, input->swbit);
		} else {
			input->evbit[0] |= BIT(EV_KEY);
			set_bit(code, input->keybit);
		}
	}

	error = input_register_device(input);
	if (error) {
		printk(KERN_ERR "Unable to register gpiodev-keys input device\n");
		goto fail;
	}

	return 0;

 fail:
	for (i = i - 1; i >= 0; i--)
		free_irq(gpiodev_to_irq(&pdata->buttons[i].gpio), pdev);

	input_free_device(input);

	return error;
}

static int __devexit gpiodev_keys_remove(struct platform_device *pdev)
{
	struct gpiodev_keys_platform_data *pdata = pdev->dev.platform_data;
	struct input_dev *input = platform_get_drvdata(pdev);
	int i;

	for (i = 0; i < pdata->nbuttons; i++) {
		int irq = gpiodev_to_irq(&pdata->buttons[i].gpio);
		free_irq(irq, pdev);
	}

	input_unregister_device(input);

	return 0;
}

struct platform_driver gpiodev_keys_device_driver = {
	.probe		= gpiodev_keys_probe,
	.remove		= __devexit_p(gpiodev_keys_remove),
	.driver		= {
		.name	= "gpiodev-keys",
	}
};

static int __init gpiodev_keys_init(void)
{
	return platform_driver_register(&gpiodev_keys_device_driver);
}

static void __exit gpiodev_keys_exit(void)
{
	platform_driver_unregister(&gpiodev_keys_device_driver);
}

module_init(gpiodev_keys_init);
module_exit(gpiodev_keys_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Milan Plzik <milan.plzik@gmail.com>");
MODULE_DESCRIPTION("Keyboard driver for GPIO devices");
