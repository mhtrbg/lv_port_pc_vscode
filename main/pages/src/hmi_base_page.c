#include "hmi_base_page.h"
#include "stdio.h"

HMI_REGISTER_PAGE(hmi_base_page, NO_UPDATE)

/**************************************************/
// 页面独有的方法
/**************************************************/

/**************************************************/
// 下面是通用方法的实现
/**************************************************/
/* 页面初始化 通用*/
static void page_init() {}

/* 页面进入 通用*/
static void page_enter(void *args) {}

/* 页面退出 通用*/
static void page_exit() {}

/* 页面销毁 通用*/
static void page_destroy(void) {}

/* 主页面update实现 */
static void page_update(void *data) {}
