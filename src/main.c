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
#define SW0_NODE DT_ALIAS(sw0)
#define SW0_GPIO_LABEL DT_GPIO_LABEL(SW0_NODE, gpios)
#define SW0_GPIO_PIN DT_GPIO_PIN(SW0_NODE, gpios)
#define SW0_GPIO_FLAGS (GPIO_INPUT | DT_GPIO_FLAGS(SW0_NODE, gpios))
// Button callback
static struct gpio_callback button_cb_data;
void button_pressed(const struct device *dev, struct gpio_callback *cb,
					uint32_t pins)
{
	// Make msg buffer
	NET_BUF_SIMPLE_DEFINE(msg, 2 + 6);
	// Define msg context
	struct bt_mesh_msg_ctx ctx = {
		.net_idx = BT_MESH_NET_PRIMARY,
		.app_idx = root_models[4].keys[0],
		.addr = 0x0001,
		.send_ttl = BT_MESH_TTL_DEFAULT,
	};
	// Add paylode to buffer
	bt_mesh_model_msg_init(&msg, BT_MESH_MODEL_OP_EVENT_STATUS);
	bt_mesh_model_send(&root_models[4], &ctx, &msg, NULL, NULL);
}

void main(void)
{
	// Get saved settings
	ps_settings_init();
	// Bind to and init hardware
	const struct device *button;
	button = device_get_binding(SW0_GPIO_LABEL);
	gpio_pin_configure(button, SW0_GPIO_PIN, SW0_GPIO_FLAGS);
	gpio_pin_interrupt_configure(button,
								 SW0_GPIO_PIN,
								 GPIO_INT_EDGE_TO_ACTIVE);
	gpio_init_callback(&button_cb_data, button_pressed, BIT(SW0_GPIO_PIN));
	gpio_add_callback(button, &button_cb_data);
	// Enable bt hardware and add bt_ready callback
	bt_enable(bt_ready);
}
