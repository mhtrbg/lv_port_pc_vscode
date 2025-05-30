#include "hmi_coffee_page.h"
#include "stdio.h"

HMI_REGISTER_PAGE(hmi_coffee_page, NO_UPDATE)

/**************************************************/
// 页面独有的方法
/**************************************************/

/**************************************************/
// 下面是通用方法的实现
/**************************************************/
/* 页面初始化 通用*/
static void page_init() {
  hmi_coffee_page_t *page = &hmi_coffee_page;
  // 创建屏幕
  page->base.screen = create_round_screen();
  // // 创建按钮
  lv_obj_t *btn_back = lv_btn_create(page->base.screen);
  lv_obj_set_pos(btn_back, 150, 150);
  lv_obj_set_size(btn_back, 120, 50);
  lv_obj_t *label2 = lv_label_create(btn_back);
  lv_label_set_text(label2, "coffee");
  lv_obj_center(label2);
  lv_obj_set_style_text_color(label2, lv_color_white(), 0);
}

/* 页面进入 通用*/
static void page_enter(void *args) {}

/* 页面退出 通用*/
static void page_exit() {}

/* 页面销毁 通用*/
static void page_destroy(void) {}

/* 主页面update实现 */
static void page_update(void *data) {}
