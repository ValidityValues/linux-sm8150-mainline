/* SPDX-License-Identifier: GPL-2.0 */
#ifndef __LINUX_OF_GPIO_H
#define __LINUX_OF_GPIO_H

#include <linux/of.h>

enum of_gpio_flags {
	OF_GPIO_ACTIVE_LOW = 0x1,
	OF_GPIO_SINGLE_ENDED = 0x2,
	OF_GPIO_OPEN_DRAIN = 0x4,
	OF_GPIO_TRANSITORY = 0x8,
	OF_GPIO_PULL_UP = 0x10,
	OF_GPIO_PULL_DOWN = 0x20,
	OF_GPIO_PULL_DISABLE = 0x40,
};

extern int of_get_named_gpio(struct device_node *np, const char *propname,
			     int index);
extern int of_get_named_gpio_flags(struct device_node *np, const char *propname,
				   int index, enum of_gpio_flags *flags);

static inline int of_get_gpio(struct device_node *np, int nr)
{
	return of_get_named_gpio(np, "gpios", nr);
}

static inline int of_get_gpio_flags(struct device_node *np, int nr,
				   enum of_gpio_flags *flags)
{
	return of_get_named_gpio_flags(np, "gpios", nr, flags);
}

#endif /* __LINUX_OF_GPIO_H */
