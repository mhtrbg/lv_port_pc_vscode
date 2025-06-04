#include "hmi_coffee_page.h"
#include "stdio.h"

HMI_REGISTER_PAGE(hmi_coffee_page, NO_UPDATE)

/**************************************************/
// 页面独有的方法
/**************************************************/
static void scroll_event_cb(lv_event_t *e) {
  lv_obj_t *cont = lv_event_get_target_obj(e);
  lv_area_t cont_a;
  lv_obj_get_coords(cont, &cont_a);
  int32_t cont_x_center = cont_a.x1 + lv_area_get_width(&cont_a) / 2;

  int32_t r = lv_obj_get_width(cont) / 3;  // 减小半径，避免过度缩放
  int32_t child_cnt = (int32_t)lv_obj_get_child_count(cont);

  for (int32_t i = 0; i < child_cnt; i++) {
    lv_obj_t *child = lv_obj_get_child(cont, i);
    lv_area_t child_a;
    lv_obj_get_coords(child, &child_a);

    int32_t child_x_center = child_a.x1 + lv_area_get_width(&child_a) / 2;
    int32_t diff_x = LV_ABS(child_x_center - cont_x_center);

    // 1. 计算 scale（确保不会过小）
    float scale;
    if (diff_x >= r) {
      scale = 0.7f;  // 最小缩放 0.7
    } else {
      uint32_t y_sqr = r * r - diff_x * diff_x;
      lv_sqrt_res_t res;
      lv_sqrt(y_sqr, &res, 0x8000);
      scale = 0.7f + 0.3f * ((float)res.i / r);  // scale ∈ [0.7, 1.0]
    }

    // 2. 设置变换原点为中心点
    lv_obj_set_style_transform_pivot_x(child, lv_obj_get_width(child) / 2, 0);
    lv_obj_set_style_transform_pivot_y(child, lv_obj_get_height(child) / 2, 0);

    // 3. 应用缩放和位移
    int32_t scale_percent = (int32_t)(scale * 100);
    lv_obj_set_style_transform_scale_x(child, scale_percent, 0);
    lv_obj_set_style_transform_scale_y(child, scale_percent, 0);
    lv_obj_set_style_translate_y(child, (r - diff_x) / 4, 0);  // 轻微下沉

    LV_LOG_USER("child %d: scale=%.2f", i, scale);  // 调试输出
  }
}
/**************************************************/
// 下面是通用方法的实现
/**************************************************/
/* 页面初始化 通用*/
static void page_init() {
  hmi_coffee_page_t *page = &hmi_coffee_page;

  // 1. 创建圆形屏幕
  page->base.screen = create_round_screen();

  // 2. 创建水平滚动容器
  lv_obj_t *cont = lv_obj_create(page->base.screen);
  lv_obj_set_size(cont, 300, 150);  // 足够容纳3个按钮
  lv_obj_center(cont);
  lv_obj_set_flex_flow(cont, LV_FLEX_FLOW_ROW);
  lv_obj_add_event_cb(cont, scroll_event_cb, LV_EVENT_SCROLL, NULL);
  lv_obj_set_style_clip_corner(cont, true, 0);
  lv_obj_set_scroll_dir(cont, LV_DIR_HOR);
  lv_obj_set_scroll_snap_x(cont, LV_SCROLL_SNAP_CENTER);
  lv_obj_set_scrollbar_mode(cont, LV_SCROLLBAR_MODE_OFF);

  // 3. 创建带样式的按钮
  for (uint32_t i = 0; i < 3; i++) {
    lv_obj_t *btn = lv_button_create(cont);
    lv_obj_set_size(btn, 80, 100);  // 增大按钮尺寸
    lv_obj_set_flex_grow(btn, 0);

    // 设置按钮背景色
    lv_obj_set_style_bg_color(btn, lv_palette_main(LV_PALETTE_BLUE), 0);
    lv_obj_set_style_bg_opa(btn, LV_OPA_COVER, 0);

    // 添加标签
    lv_obj_t *label = lv_label_create(btn);
    lv_label_set_text_fmt(label, "Btn %d", i);
    lv_obj_center(label);
  }

  // 4. 初始化滚动位置并激活屏幕
  // lv_obj_send_event(cont, LV_EVENT_SCROLL, NULL);
  lv_obj_scroll_to_view(lv_obj_get_child(cont, 0), LV_ANIM_OFF);
}

/* 页面进入 通用*/
static void page_enter(void *args) {}

/* 页面退出 通用*/
static void page_exit() {}

/* 页面销毁 通用*/
static void page_destroy(void) {}

/* 主页面update实现 */
static void page_update(void *data) {}
