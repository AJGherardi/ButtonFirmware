#include "composition.h"
#include "settings.h"

void save_event0(void)
{
    settings_save_one("ps/event0", &event_state[0].bound_scene, sizeof(&event_state[0].bound_scene));
}

void save_event1(void)
{
    settings_save_one("ps/event1", &event_state[1].bound_scene, sizeof(&event_state[1].bound_scene));
}

static int ps_set(const char *key, size_t len_rd,
                  settings_read_cb read_cb, void *cb_arg)
{
    ssize_t len = 0;
    int key_len;
    const char *next;

    key_len = settings_name_next(key, &next);

    if (!next)
    {
        if (!strncmp(key, "event0", key_len))
        {
            len = read_cb(cb_arg, &event_state[0].bound_scene,
                          sizeof(event_state[0].bound_scene));
        }

        if (!strncmp(key, "event1", key_len))
        {
            len = read_cb(cb_arg, &event_state[1].bound_scene,
                          sizeof(event_state[1].bound_scene));
        }

        return (len < 0) ? len : 0;
    }

    return -ENOENT;
}

static struct settings_handler ps_settings = {
    .name = "ps",
    .h_set = ps_set,
};

int ps_settings_init(void)
{
    int err;

    err = settings_subsys_init();
    if (err)
    {
        printk("settings_subsys_init failed (err %d)", err);
        return err;
    }

    err = settings_register(&ps_settings);
    if (err)
    {
        printk("ps_settings_register failed (err %d)", err);
        return err;
    }

    return 0;
}
