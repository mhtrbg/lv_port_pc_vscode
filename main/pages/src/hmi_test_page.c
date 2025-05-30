#include "hmi_test_page.h"
#include <lvgl.h>

/**************************************************/
// 不同页面此部分需要重命名
/**************************************************/
/* 注册页面实例 */

HMI_REGISTER_PAGE(hmi_test_page, HMI_TEST_PAGE)
/**************************************************/
// 页面独有的方法和字段
/**************************************************/
lv_timer_t *test_timer;
/*页面独有的方法*/
static void test_page_btn_event_cb(lv_event_t *e) {
  page_manager_go_back(NULL);
}

static void timer_cb(lv_timer_t *timer) {
  static int counter = 0;

  // 更新 UI（正常部分）
  lv_label_set_text_fmt(hmi_test_page.label_status, "Count: %d", counter);
  counter++;
  if (counter > 100) {
    counter = 0;
  }

  // 模拟阻塞（测试 UI 卡顿）
  if (counter % 5 == 0) {  // 每 5 次触发一次阻塞
                           // lv_label_set_text(hmi_test_page.label_status,
                           // "Blocking..."); blocking_task(); // 故意阻塞 500ms
  }
}

/**************************************************/
// 下面是通用方法的实现
/**************************************************/

/* 页面初始化 页面入栈时调用 绘制页面组件*/
static void page_init() {
  hmi_test_page_t *page = &hmi_test_page;
  // 创建屏幕
  page->base.screen = lv_obj_create(NULL);

  // // 创建按钮
  page->btn_back = lv_btn_create(page->base.screen);
  lv_obj_set_pos(page->btn_back, 150, 150);
  lv_obj_set_size(page->btn_back, 120, 50);
  lv_obj_add_event_cb(page->btn_back, test_page_btn_event_cb, LV_EVENT_CLICKED,
                      page);
  lv_obj_t *label2 = lv_label_create(page->btn_back);
  lv_label_set_text(label2, "back");
  lv_obj_center(label2);

  // 创建状态标签
  page->label_status = lv_label_create(page->base.screen);
  lv_obj_set_pos(page->label_status, 200, 300);
  lv_label_set_text(page->label_status, 0);

  // 创建温度控制
  page->number_slider = lv_slider_create(page->base.screen);
  lv_obj_set_pos(page->number_slider, 100, 250);
  lv_obj_set_size(page->number_slider, 200, 20);
  lv_slider_set_range(page->number_slider, 0, 100);
  lv_slider_set_value(page->number_slider, 0, LV_ANIM_ON);
  lv_obj_add_flag(page->number_slider, LV_OBJ_FLAG_USER_1);
  lv_obj_add_flag(page->number_slider, LV_OBJ_FLAG_CLICKABLE);

  // 创建状态标签
  page->temp_label = lv_label_create(page->base.screen);
  lv_obj_set_pos(page->temp_label, 320, 250);
  lv_label_set_text_fmt(page->temp_label, "%d°C", 85);
  // 创建定时器（100ms 触发一次）
  test_timer = lv_timer_create(timer_cb, 100, NULL);
}

/* 页面进入 页面入栈时调用 如有参数输入 可在此处理*/
static void page_enter(void *args) {}

/* 页面退出 退出时需要处理的逻辑
只要当前页面切换哪怕在栈内都会触发这个方法
*/
static void page_exit() {}

/* 页面销毁 销毁时需要处理的逻辑
当前页面出栈时调用
*/
static void page_destroy(void) { lv_timer_del(test_timer); }

/* 主页面update实现 模拟器中暂时不实现*/
static void page_update(void *data) {
  hmi_test_page_data_t *update = (hmi_test_page_data_t *)data;

  if (update->target_number > 0) {
    lv_slider_set_value(hmi_test_page.number_slider, update->target_number,
                        LV_ANIM_ON);
    lv_label_set_text_fmt(hmi_test_page.temp_label, "%d°C",
                          update->target_number);
  }
}
