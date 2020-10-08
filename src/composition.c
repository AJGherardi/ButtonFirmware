#include <drivers/gpio.h>

#include "composition.h"
#include "mesh.h"
#include "settings.h"

// Publications
BT_MESH_HEALTH_PUB_DEFINE(health_pub, 0);
// Message handlers declaration
static void event_bind(struct bt_mesh_model *model,
                       struct bt_mesh_msg_ctx *ctx,
                       struct net_buf_simple *buf);
// Server cfg
static struct bt_mesh_cfg_srv cfg_srv = {
    .relay = BT_MESH_RELAY_ENABLED,
    .beacon = BT_MESH_BEACON_ENABLED,
    .frnd = BT_MESH_FRIEND_NOT_SUPPORTED,
    .gatt_proxy = BT_MESH_GATT_PROXY_DISABLED,
    .default_ttl = 7,
    .net_transmit = BT_MESH_TRANSMIT(2, 20),
    .relay_retransmit = BT_MESH_TRANSMIT(2, 20),
};
// Client cfg
static struct bt_mesh_cfg_cli cfg_cli = {};
// Health server cfg
static struct bt_mesh_health_srv health_srv = {};

// Event setup server dispatch table
static const struct bt_mesh_model_op event_setup_srv_op[] = {
    {BT_MESH_MODEL_OP_EVENT_BIND, 0, event_bind},
    BT_MESH_MODEL_OP_END,
};
// Event states
struct event_state event_state[] = {
    {.bound_scene = 0},
    {.bound_scene = 0},
    {.bound_scene = 0},
    {.bound_scene = 0},
};
// Models
struct bt_mesh_model root_models[] = {
    BT_MESH_MODEL_CFG_SRV(&cfg_srv),
    BT_MESH_MODEL_CFG_CLI(&cfg_cli),
    BT_MESH_MODEL_HEALTH_SRV(&health_srv, &health_pub),
    BT_MESH_MODEL(BT_MESH_MODEL_ID_EVENT_SETUP_SRV, event_setup_srv_op,
                  NULL, &event_state[0]),
    BT_MESH_MODEL(BT_MESH_MODEL_ID_EVENT_CLI, NULL,
                  NULL, NULL),
    BT_MESH_MODEL(BT_MESH_MODEL_ID_SCENE_SRV, NULL,
                  NULL, NULL),
};

struct bt_mesh_model s0_models[] = {
    BT_MESH_MODEL(BT_MESH_MODEL_ID_EVENT_SETUP_SRV, event_setup_srv_op,
                  NULL, &event_state[1]),
    BT_MESH_MODEL(BT_MESH_MODEL_ID_EVENT_CLI, NULL,
                  NULL, NULL),

};

struct bt_mesh_model s1_models[] = {
    BT_MESH_MODEL(BT_MESH_MODEL_ID_EVENT_SETUP_SRV, event_setup_srv_op,
                  NULL, &event_state[2]),
    BT_MESH_MODEL(BT_MESH_MODEL_ID_EVENT_CLI, NULL,
                  NULL, NULL),
};

struct bt_mesh_model s2_models[] = {
    BT_MESH_MODEL(BT_MESH_MODEL_ID_EVENT_SETUP_SRV, event_setup_srv_op,
                  NULL, &event_state[3]),
    BT_MESH_MODEL(BT_MESH_MODEL_ID_EVENT_CLI, NULL,
                  NULL, NULL),
};

// Elements
static struct bt_mesh_elem elements[] = {
    BT_MESH_ELEM(0, root_models, BT_MESH_MODEL_NONE),
    BT_MESH_ELEM(0, s0_models, BT_MESH_MODEL_NONE),
    BT_MESH_ELEM(0, s1_models, BT_MESH_MODEL_NONE),
    BT_MESH_ELEM(0, s2_models, BT_MESH_MODEL_NONE),
};
// Comp
const struct bt_mesh_comp comp = {
    .cid = BT_COMP_ID_LF,
    .elem = elements,
    .elem_count = ARRAY_SIZE(elements),
};
// Event message handlers
static void event_bind(struct bt_mesh_model *model,
                       struct bt_mesh_msg_ctx *ctx,
                       struct net_buf_simple *buf)
{
    // Get data from msg
    struct event_state *event_state = model->user_data;
    uint16_t scene_number;
    scene_number = net_buf_simple_pull_le16(buf);
    // Set scene number
    event_state->bound_scene = scene_number;
    if (model->elem_idx == 0)
    {
        save_event0();
    }
    else if (model->elem_idx == 1)
    {
        save_event1();
    }
}