#ifndef __DEPENDENCIES_H__
#define __DEPENDENCIES_H__

#include "SW_SPI.h"

static void gpio_low(PIN_t *pin);
static void gpio_high(PIN_t *pin);
static void is_gpio_high(PIN_t *pin);
static void uDelay(uint32 delay_us);
static void IRQ_disable();
static void IRQ_enable();


#endif /* __DEPENDENCIES_H__ */
