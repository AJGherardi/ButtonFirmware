#ifndef _MESH_H
#define _MESH_H

#include <settings/settings.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/conn.h>
#include <bluetooth/l2cap.h>
#include <bluetooth/hci.h>
#include <bluetooth/mesh.h>

// Model IDs
#define BT_MESH_MODEL_ID_EVENT_SETUP_SRV 0x1312
#define BT_MESH_MODEL_ID_EVENT_CLI 0x1313
// Op codes
#define BT_MESH_MODEL_OP_EVENT_BIND BT_MESH_MODEL_OP_2(0x82, 0x9E)
#define BT_MESH_MODEL_OP_EVENT_STATUS BT_MESH_MODEL_OP_2(0x82, 0x9F)
#define BT_MESH_MODEL_OP_SCENE_RECALL BT_MESH_MODEL_OP_2(0x82, 0x42)
#define BT_MESH_MODEL_OP_SCENE_RECALL_UNACK BT_MESH_MODEL_OP_2(0x82, 0x43)

void bt_ready(int err);

#endif
