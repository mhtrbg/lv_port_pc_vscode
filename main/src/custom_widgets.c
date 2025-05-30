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
