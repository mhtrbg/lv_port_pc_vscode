#include "custom_widgets.h"

lv_obj_t* create_round_screen(void) {
  // 1. 创建基础屏幕
  lv_obj_t* screen = lv_obj_create(NULL);
  lv_obj_remove_style_all(screen);
  lv_obj_set_size(screen, 466, 466);

  // 2. AMOLED优化设置
  lv_obj_set_style_bg_color(screen, lv_color_black(), 0);
  lv_obj_set_style_bg_opa(screen, LV_OPA_COVER, 0);

  // 3. 设置圆形裁剪区域
  lv_obj_set_style_clip_corner(screen, true, 0);
  lv_obj_set_style_radius(screen, LV_RADIUS_CIRCLE, 0);  // 使用宏定义更清晰

  // 4. 添加可见边框（关键修改部分）
  lv_obj_set_style_border_color(screen, lv_palette_main(LV_PALETTE_GREY), 0);
  lv_obj_set_style_border_width(screen, 4, 0);         // 4像素粗边框
  lv_obj_set_style_border_opa(screen, LV_OPA_100, 0);  // 完全不透明
  lv_obj_set_style_border_post(screen, true, 0);       // 确保边框显示在内容之上

  return screen;
}

lv_obj_t* create_my_button(lv_obj_t* base, lv_event_cb_t event_cb,
                           void* user_data) {
  lv_obj_t* btn_brew = lv_btn_create(base);
  lv_obj_set_pos(btn_brew, 100, 100);
  lv_obj_set_size(btn_brew, 120, 50);
  lv_obj_add_event_cb(btn_brew, event_cb, LV_EVENT_CLICKED, user_data);
  lv_obj_t* label = lv_label_create(btn_brew);
  lv_label_set_text(label, "start brew");
  lv_obj_center(label);
};
