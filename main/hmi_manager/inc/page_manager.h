#ifndef __PAGE_MANAGER_H__
#define __PAGE_MANAGER_H__

#include <lvgl.h>

#define DECLARE_PAGE(name) extern name##_t name

#define INSTANCE_PAGE(page_name) ((page_base_t *)&(page_name))

// 定义 HMI_REGISTER_PAGE 宏，自动生成所有代码
#define HMI_REGISTER_PAGE(page_name, type_name)                 \
  static void page_init();                                      \
  static void page_enter(void *args);                           \
  static void page_exit();                                      \
  static void page_destroy(void);                               \
  static void page_update(void *data);                          \
                                                                \
  page_name##_t page_name = {.base = {                          \
                                 .update_page_type = type_name, \
                                 .init = page_init,             \
                                 .enter = page_enter,           \
                                 .exit = page_exit,             \
                                 .destroy = page_destroy,       \
                                 .update = page_update,         \
                                 .user_data = NULL,             \
                             }};

/* 页面栈最大深度 */
#define PAGE_STACK_DEPTH 10

/*需要通信的后Update的页面类型*/
typedef enum {
  NO_UPDATE = 0,
  HMI_MAIN_PAGE,
  HMI_TEST_PAGE,
} update_type_t;
/* 页面状态标志 */
typedef enum {
  PAGE_STATE_ACTIVE = 0x01,     // 页面活跃状态
  PAGE_STATE_DESTROYING = 0x02  // 页面正在销毁
} page_state_t;

/* 在page_base_t中添加update方法 */
typedef struct page_base_t {
  lv_obj_t *screen;           // 页面根对象
  void (*init)(void);         // 页面初始化函数
  void (*enter)(void *args);  // 页面进入函数
  void (*exit)(void);         // 页面退出函数
  void (*destroy)(void);      // 页面销毁函数
  void *user_data;            // 用户数据

  volatile uint8_t state;          // 页面状态标志
  void (*update)(void *data);      // 页面更新函数(新增)
  update_type_t update_page_type;  // 页面类型(新增)

} page_base_t;
/* 页面管理器 */
typedef struct {
  page_base_t *stack[PAGE_STACK_DEPTH];  // 页面栈
  int top;                               // 栈顶指针
  // struct rt_mutex lock;                 // 页面操作锁
} page_manager_t;

/* 全局页面管理器指针 */
extern page_manager_t *global_page_manager;

/* 页面管理器API */
void page_manager_init(void);
void page_manager_go_to(page_base_t *page, void *args);
void page_manager_go_back(void *args);
void page_manager_go_off_all(page_base_t *page);
page_base_t *page_manager_get_current(void);

#endif /* __PAGE_MANAGER_H__ */
