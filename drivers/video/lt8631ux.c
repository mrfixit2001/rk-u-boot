// SPDX-License-Identifier: GPL-2.0+
/*
 * (C) Copyright 2018 Liviu Dudau <liviu@dudau.co.uk>
 *
 * Based on the Linux driver, (C) 2012 Texas Instruments
 */

#include <common.h>
#include <dm.h>
#include <display.h>
#include <i2c.h>

static int i2c_write(struct udevice *dev, uint addr, uint value)
{
	int ret = 0;

	do {
		ret = dm_i2c_reg_write(dev, addr, value);
	} while (ret);

	return ret;
}

static int lt8631ux_init(struct udevice *dev)
{
	i2c_write(dev, 0x0a, 0x7a);
	i2c_write(dev, 0x0b, 0x11);
	i2c_write(dev, 0x0c, 0x2c);
	i2c_write(dev, 0x0d, 0xaf);
	i2c_write(dev, 0x0e, 0x00);
	i2c_write(dev, 0x0f, 0x01);
	i2c_write(dev, 0x10, 0xaf);
	i2c_write(dev, 0x11, 0xaf);
	i2c_write(dev, 0x12, 0xaf);

	i2c_write(dev, 0x14, 0x52);

	i2c_write(dev, 0x16, 0xff);
	i2c_write(dev, 0x17, 0x3c);
	i2c_write(dev, 0x18, 0x70);
	i2c_write(dev, 0x19, 0xb4);
	i2c_write(dev, 0x1a, 0x80);
	i2c_write(dev, 0x1b, 0x80);
	i2c_write(dev, 0x1c, 0x00);
	i2c_write(dev, 0x1d, 0x80);
	i2c_write(dev, 0x1e, 0x00);
	i2c_write(dev, 0x1f, 0x80);

	i2c_write(dev, 0x23, 0x3f);
	i2c_write(dev, 0x24, 0x3f);
	i2c_write(dev, 0x25, 0xa8);
	i2c_write(dev, 0x26, 0xa8);
	i2c_write(dev, 0x27, 0xa8);
	i2c_write(dev, 0x28, 0xaa);
	i2c_write(dev, 0x29, 0xa0);
	i2c_write(dev, 0x2a, 0x08);
	i2c_write(dev, 0x2b, 0x0a);
	i2c_write(dev, 0x2c, 0xb4);
	i2c_write(dev, 0x2d, 0x00);
	i2c_write(dev, 0x2e, 0x07);
	i2c_write(dev, 0x2f, 0x90);

	i2c_write(dev, 0x33, 0x01);
	i2c_write(dev, 0x34, 0x01);
	i2c_write(dev, 0x35, 0x0b);
	i2c_write(dev, 0x36, 0x01);
	i2c_write(dev, 0x37, 0x0b);
	i2c_write(dev, 0x38, 0x01);
	i2c_write(dev, 0x39, 0x0b);

	// Enable main LED
	i2c_write(dev, 0x3c, 0x3a);

	return 0;
}

static int lt8631ux_enable(struct udevice *dev, int panel_bpp,
			   const struct display_timing *timing)
{
	return lt8631ux_init(dev);
}

static int lt8631ux_probe(struct udevice *dev)
{
    printf("\nProbing lt8631ux....\n");
	return lt8631ux_init(dev);
}

struct dm_display_ops lt8631ux_ops = {
	.enable = lt8631ux_enable,
};

static const struct udevice_id lt8631ux_ids[] = {
	{ .compatible = "lontium,lt8631ux" },
	{ }
};

U_BOOT_DRIVER(tda19988) = {
	.name = "lt8631ux",
	.id = UCLASS_DISPLAY,
	.of_match = lt8631ux_ids,
	.ops = &lt8631ux_ops,
	.probe = lt8631ux_probe
};
