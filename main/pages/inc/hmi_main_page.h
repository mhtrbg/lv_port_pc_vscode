#ifndef __HMI_MAIN_PAGE_H__
#define __HMI_MAIN_PAGE_H__

#include "page_manager.h"

/* 主页面消息数据类型 */
typedef struct {
  int target_temp;
  char status[32];
} hmi_main_page_data_t;
/* 主页面数据结构 */
typedef struct {
  page_base_t base;  // 继承页面基类

  lv_obj_t *btn_brew;      // 冲泡按钮
  lv_obj_t *btn_to_test;   // 导航按钮
  lv_obj_t *label_status;  // 状态标签
  lv_obj_t *temp_slider;   // 温度滑块
  lv_obj_t *temp_label;    // 温度显示
  hmi_main_page_data_t page_data;
} hmi_main_page_t;

#endif /* __MAIN_PAGE_H__ */
