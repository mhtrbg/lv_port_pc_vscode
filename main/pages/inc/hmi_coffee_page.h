#pragma once
#include "page_manager.h"
/* 主页面消息数据类型 */
typedef struct {
  int tem_data;
} hmi_coffee_page_data_t;
/* 主页面数据结构 */
typedef struct {
  page_base_t base;  // 继承页面基类

} hmi_coffee_page_t;
