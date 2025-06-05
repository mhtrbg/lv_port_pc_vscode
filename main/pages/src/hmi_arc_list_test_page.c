#include "hmi_arc_list_test_page.h"
#include "stdio.h"

HMI_REGISTER_PAGE(hmi_arc_list_test_page, NO_UPDATE)

/**************************************************/
// 页面独有的方法
/**************************************************/
#define ARC_SIZE 460
#define ARC_WIDTH 4

#define START_ANGLE 240
#define TOTAL_ANGLE 60

#define LIST_WIDTH 250
#define LIST_HEIGHT 300
#define LIST_NUM 10
#define LIST_ITEM_HEIGHT 100

// 滚动事件回调函数

/**************************************************/
// 下面是通用方法的实现
/**************************************************/

/* 页面初始化 通用*/

static void update_arc_scroller(lv_obj_t *list, lv_obj_t *arc) {
  // 计算总内容高度和最大滚动距离
  lv_coord_t total_height = LIST_ITEM_HEIGHT * LIST_NUM;
  lv_coord_t max_scroll = total_height - LIST_HEIGHT;

  // 获取当前滚动位置（lv_obj_get_scroll_y 返回负值，取绝对值）
  lv_coord_t scroll_y = lv_obj_get_scroll_y(list);

  // 计算滚动比例（0~1）
  float scroll_ratio = (max_scroll > 0) ? (float)scroll_y / max_scroll : 0;
  scroll_ratio = LV_CLAMP(0.0f, scroll_ratio, 1.0f);

  // 计算弧形指示器长度（可视区域占比）
  float visible_ratio = (float)LIST_HEIGHT / total_height;
  visible_ratio = LV_CLAMP(0.1f, visible_ratio, 1.0f);

  // 计算弧形角度
  int indicator_angle = TOTAL_ANGLE * visible_ratio;
  int scroll_angle =
      START_ANGLE + scroll_ratio * (TOTAL_ANGLE - indicator_angle);

  // 确保角度不超出范围
  scroll_angle = LV_CLAMP(START_ANGLE, scroll_angle,
                          START_ANGLE + TOTAL_ANGLE - indicator_angle);

  // 更新弧形
  lv_arc_set_angles(arc, scroll_angle, scroll_angle + indicator_angle);
}

static void list_event_cb(lv_event_t *e) {
  lv_obj_t *list = lv_event_get_target(e);
  lv_obj_t *arc = lv_event_get_user_data(e);
  update_arc_scroller(list, arc);
}
// 自定义列表项创建函数
static lv_obj_t *create_list_item(lv_obj_t *list, const char *text) {
  // 创建容器作为列表项
  lv_obj_t *item = lv_list_add_btn(list, NULL, text);

  // 设置固定高度40px
  lv_obj_set_height(item, LIST_ITEM_HEIGHT);

  // 获取文本标签并调整样式
  lv_obj_t *label = lv_obj_get_child(item, 0);
  if (label) {
    // 文本垂直居中
    lv_obj_set_style_text_align(label, LV_TEXT_ALIGN_CENTER, 0);
    lv_obj_set_style_pad_top(label, 10, 0);  // 通过padding调整文本位置
    lv_obj_set_style_pad_bottom(label, 10, 0);
  }

  return item;
}

static void page_init() {
  hmi_arc_list_test_page_t *page = &hmi_arc_list_test_page;

  // 1. 创建圆形屏幕
  page->base.screen = create_round_screen();

  // 创建列表 - 设置更大的高度
  lv_obj_t *list = lv_list_create(page->base.screen);
  lv_obj_set_size(list, LIST_WIDTH, LIST_HEIGHT);
  lv_obj_remove_style(list, NULL, LV_PART_SCROLLBAR);  // 移除滚动条样式
  // 禁用弹性滚动
  lv_obj_clear_flag(list, LV_OBJ_FLAG_SCROLL_ELASTIC);

  static lv_style_t list_style;
  lv_style_init(&list_style);
  lv_style_set_pad_row(&list_style, 0);
  lv_obj_add_style(list, &list_style, 0);
  .

      lv_obj_center(list);
  // 添加一些列表项作为示例
  for (int i = 0; i < LIST_NUM; i++) {
    char buf[32];
    lv_snprintf(buf, sizeof(buf), "Item %d", i + 1);
    create_list_item(list, buf);
  }
  /********************************************************** */
  // 创建弧形滚动条
  lv_obj_t *arc = lv_arc_create(page->base.screen);
  lv_obj_set_size(arc, ARC_SIZE, ARC_SIZE);
  lv_arc_set_rotation(arc, 90);
  lv_arc_set_bg_angles(arc, START_ANGLE, START_ANGLE + TOTAL_ANGLE);
  lv_obj_set_style_arc_width(arc, ARC_WIDTH, LV_PART_MAIN);       // 背景宽度
  lv_obj_set_style_arc_width(arc, ARC_WIDTH, LV_PART_INDICATOR);  // 前景宽度
  // 初始设置
  lv_obj_remove_style(arc, NULL, LV_PART_KNOB);
  lv_obj_remove_flag(arc, LV_OBJ_FLAG_CLICKABLE);
  lv_obj_set_style_arc_color(arc, lv_color_hex(0x444444), LV_PART_MAIN);
  lv_obj_set_style_arc_color(arc, lv_color_hex(0xC8A46C), LV_PART_INDICATOR);
  lv_obj_center(arc);

  // 初始更新滚动条
  update_arc_scroller(list, arc);

  // 添加滚动事件回调
  lv_obj_add_event_cb(list, list_event_cb, LV_EVENT_SCROLL, arc);
}

/* 页面进入 通用*/
static void page_enter(void *args) {}

/* 页面退出 通用*/
static void page_exit() {}

/* 页面销毁 通用*/
static void page_destroy(void) {}

/* 主页面update实现 */
static void page_update(void *data) {}
