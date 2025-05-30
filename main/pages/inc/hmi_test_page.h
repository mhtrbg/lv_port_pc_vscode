#ifndef __HMI_TEST_PAGE_H__
#define __HMI_TEST_PAGE_H__

#include "page_manager.h"
#include <lvgl.h>
/* 主页面消息数据类型 */
typedef struct {
  int target_number;
} hmi_test_page_data_t;
/* 主页面数据结构 */
typedef struct {
  page_base_t base;                // 继承页面基类
  lv_obj_t *btn_back;              // 返回按钮
  lv_obj_t *label_status;          // 状态标签
  lv_obj_t *number_slider;         // 温度滑块
  lv_obj_t *temp_label;            // 状态标签
  hmi_test_page_data_t page_data;  // 页面数据
} hmi_test_page_t;

#endif /* __TEST_PAGE_H__ */
