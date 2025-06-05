#include "ui_app.h"
#include "ui_style.h"
#include "hmi_main_page.h"
#include "hmi_coffee_page.h"
#include "hmi_arc_list_test_page.h"
DECLARE_PAGE(hmi_main_page);
DECLARE_PAGE(hmi_coffee_page);
DECLARE_PAGE(hmi_arc_list_test_page);

// UI从这里开始
void ui_app_init(void) {
  ui_style_init();
  // 初始化页面管理器
  page_manager_init();
  // 切换到主页面
  // page_manager_go_to(INSTANCE_PAGE(hmi_main_page), NULL);
  page_manager_go_to(INSTANCE_PAGE(hmi_arc_list_test_page), NULL);
}
