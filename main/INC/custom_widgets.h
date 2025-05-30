#pragma once
#include <lvgl.h>
// screen_common.h
lv_obj_t* create_round_screen(void);  // 圆形参考区域 直接返回lv_obj_t*
lv_obj_t* create_my_button(lv_obj_t* base, lv_event_cb_t event_cb,
                           void* user_data);
