#ifndef _COMPOSITION_H
#define _COMPOSITION_H

#include <zephyr.h>
#include <bluetooth/mesh.h>

// States
struct event_state
{
    uint16_t bound_scene;
};

extern struct bt_mesh_model root_models[];
extern struct event_state event_state[];
extern const struct bt_mesh_comp comp;

#endif