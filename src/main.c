#include <zephyr.h>
#include <sys/printk.h>
#include <settings/settings.h>
#include <sys/byteorder.h>
#include <device.h>
#include <drivers/gpio.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/conn.h>
#include <bluetooth/l2cap.h>
#include <bluetooth/hci.h>
#include <bluetooth/mesh.h>
#include <stdio.h>

#include "mesh.h"
#include "composition.h"
#include "settings.h"

// Device Tree Data
#define LED0_NODE DT_ALIAS(led0)
#define LED0 DT_GPIO_LABEL(LED0_NODE, gpios)

// void init_relay(uint8_t dev_number, const char *device, uint32_t pin)
// {
// 	onoff_state[dev_number].relay_device = device_get_binding(device);
// 	gpio_pin_configure(onoff_state[dev_number].relay_device, pin, GPIO_OUTPUT_ACTIVE | GPIO_PULL_UP);
// 	gpio_pin_set(onoff_state[dev_number].relay_device, pin, 1);
// }

void main(void)
{
	// Get saved settings
	ps_settings_init();
	// // Bind to and init hardware
	// init_relay(0, LED0, 17);
	// init_relay(1, LED0, 18);
	// Enable bt hardware and add bt_ready callback
	bt_enable(bt_ready);
}
