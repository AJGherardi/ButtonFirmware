#include "mesh.h"
#include "composition.h"

static uint8_t dev_uuid[16] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xdd, 0x0d};

static uint16_t primary_addr;
static uint16_t primary_net_idx;

static int output_number(bt_mesh_output_action_t action, uint32_t number)
{
    printk("OOB Number %06u\n", number);
    return 0;
}

static int output_string(const char *str)
{
    printk("OOB String %s\n", str);
    return 0;
}

static void prov_complete(uint16_t net_idx, uint16_t addr)
{
    printk("provisioning complete for net_idx 0x%04x addr 0x%04x\n",
           net_idx, addr);
    primary_addr = addr;
    primary_net_idx = net_idx;
}

static void prov_reset(void)
{
    bt_mesh_prov_enable(BT_MESH_PROV_ADV | BT_MESH_PROV_GATT);
}

static const struct bt_mesh_prov prov = {
    .uuid = dev_uuid,
    .output_size = 6,
    .output_actions = (BT_MESH_DISPLAY_NUMBER | BT_MESH_DISPLAY_STRING),
    .output_number = output_number,
    .output_string = output_string,
    .complete = prov_complete,
    .reset = prov_reset,
};

void bt_ready(int err)
{
    // For out of band provisioning
    struct bt_le_oob oob;
    // Sets up mesh support dose not advertise
    bt_mesh_init(&prov, &comp);
    // Load bt settings from flash
    settings_load();
    // Use Nordic FICR as UUID
    if (!bt_le_oob_get_local(BT_ID_DEFAULT, &oob))
    {
        memcpy(dev_uuid, oob.addr.a.val, 6);
    }
    // Prov if not done already
    bt_mesh_prov_enable(BT_MESH_PROV_GATT | BT_MESH_PROV_ADV);
}
