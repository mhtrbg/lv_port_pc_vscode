#include "hmi_main_page.h"
#include <lvgl.h>
#include "hmi_test_page.h"
#include "stdio.h"

DECLARE_PAGE(hmi_test_page);

HMI_REGISTER_PAGE(hmi_main_page, HMI_MAIN_PAGE)

/**************************************************/
// 页面独有的方法
/**************************************************/

/* 冲泡按钮事件回调 */
static void main_page_btn_brew_event_cb(lv_event_t *e) {
  lv_label_set_text(hmi_main_page.label_status, "Brewing...");
}
static void main_page_btn_to_test_event_cb(lv_event_t *e) {
  page_manager_go_to(INSTANCE_PAGE(hmi_test_page), NULL);
}
/* 温度滑块事件回调 */
static void main_page_temp_slider_event_cb(lv_event_t *e) {
  hmi_main_page_t *page = (hmi_main_page_t *)lv_event_get_user_data(e);
  int temp = lv_slider_get_value(page->temp_slider);
}

/* 更新状态显示 */
void main_page_update_status(const char *status) {
  lv_label_set_text(hmi_main_page.label_status, status);
}

/* 更新温度显示 */
void main_page_update_temp(int temp) {
  lv_slider_set_value(hmi_main_page.temp_slider, temp, LV_ANIM_ON);
  lv_label_set_text_fmt(hmi_main_page.temp_label, "%d°C", temp);
}

/**************************************************/
// 下面是通用方法的实现
/**************************************************/
/* 页面初始化 通用*/
static void page_init() {
  snprintf(hmi_main_page.page_data.status,
           sizeof(hmi_main_page.page_data.status), "Ready");
  hmi_main_page.page_data.target_temp = 85;

  hmi_main_page_t *page = &hmi_main_page;
  // 创建屏幕
  page->base.screen = create_round_screen();
  // 添加圆形遮罩
  lv_obj_t *mask = lv_obj_create(page->base.screen);
  lv_obj_set_size(mask, 466, 466);
  lv_obj_set_style_radius(mask, LV_RADIUS_CIRCLE, 0);
  lv_obj_set_style_bg_color(mask, lv_color_black(), 0);
  lv_obj_set_style_bg_opa(mask, LV_OPA_COVER, 0);
  lv_obj_set_style_border_width(mask, 0, 0);
  // 创建冲泡按钮
  page->btn_brew = lv_btn_create(page->base.screen);
  lv_obj_set_pos(page->btn_brew, 100, 100);
  lv_obj_set_size(page->btn_brew, 120, 50);
  lv_obj_add_event_cb(page->btn_brew, main_page_btn_brew_event_cb,
                      LV_EVENT_CLICKED, page);

  lv_obj_t *label = lv_label_create(page->btn_brew);
  lv_label_set_text(label, "start brew");
  lv_obj_center(label);

  // 创建导航按钮
  page->btn_to_test = lv_btn_create(page->base.screen);
  lv_obj_set_pos(page->btn_to_test, 250, 100);
  lv_obj_set_size(page->btn_to_test, 120, 50);
  lv_obj_add_event_cb(page->btn_to_test, main_page_btn_to_test_event_cb,
                      LV_EVENT_CLICKED, page);

  lv_obj_t *label2 = lv_label_create(page->btn_to_test);
  lv_label_set_text(label2, "to test");
  lv_obj_center(label2);

  // 创建状态标签
  page->label_status = lv_label_create(page->base.screen);
  lv_obj_set_pos(page->label_status, 100, 200);
  lv_label_set_text(page->label_status, "Ready");
  lv_obj_set_style_text_color(page->label_status, lv_color_white(), 0);

  // 创建温度控制
  page->temp_slider = lv_slider_create(page->base.screen);
  lv_obj_set_pos(page->temp_slider, 100, 250);
  lv_obj_set_size(page->temp_slider, 200, 20);
  lv_slider_set_range(page->temp_slider, 70, 100);
  lv_slider_set_value(page->temp_slider, 85, LV_ANIM_OFF);
  lv_obj_add_event_cb(page->temp_slider, main_page_temp_slider_event_cb,
                      LV_EVENT_RELEASED, page);

  page->temp_label = lv_label_create(page->base.screen);
  lv_obj_set_pos(page->temp_label, 320, 250);
  lv_label_set_text_fmt(page->temp_label, "%d°C", 85);

  // set_color(page->temp_label);
  lv_obj_set_style_text_color(page->temp_label, lv_color_white(), 0);
}
// static int color_type = 0;
// void set_color(lv_obj_t *obj) {
//   if (color_type == 0) {
//     lv_obj_set_style_text_color(obj, lv_color_white(), 0);
//   } else if (color_type == 1) {
//     lv_obj_set_style_text_color(obj, lv_color_black(), 0);
//   }
// }

/* 页面进入 通用*/
static void page_enter(void *args) {}

/* 页面退出 通用*/
static void page_exit() {
  // 可以在这里保存页面状态
}

/* 页面销毁 通用*/
static void page_destroy(void) {
  // 清理资源
}

/* 主页面update实现 */
static void page_update(void *data) {
  // hmi_main_page_t *page = &hmi_main_page;
  // hmi_main_page_data_t *update = (hmi_main_page_data_t *)data;

  // if (update->status) {
  //   lv_label_set_text(page->label_status, update->status);
  // }

  // if (update->target_temp > 0) {
  //   lv_slider_set_value(page->temp_slider, update->target_temp, LV_ANIM_ON);
  //   lv_label_set_text_fmt(page->temp_label, "%d°C", update->target_temp);
  // }
}
