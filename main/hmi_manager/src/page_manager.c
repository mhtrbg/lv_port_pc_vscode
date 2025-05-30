#include "page_manager.h"
#include "string.h"
/* 全局页面管理器实例 */
static page_manager_t page_manager_instance;
page_manager_t *global_page_manager = &page_manager_instance;

/* 初始化页面管理器 */
void page_manager_init(void) {
  memset(&page_manager_instance, 0, sizeof(page_manager_instance));
  page_manager_instance.top = -1;  // 空栈
}

/* 导航到新页面(压栈) */
void page_manager_go_to(page_base_t *page, void *args) {
  if (page == NULL) return;

  // 栈满检查
  if (page_manager_instance.top >= PAGE_STACK_DEPTH - 1) {
    return;
  }

  // 退出当前页面(如果有)
  if (page_manager_instance.top >= 0) {
    if (page_manager_instance.stack[page_manager_instance.top]->exit) {
      page_manager_instance.stack[page_manager_instance.top]->exit();
    }
  }

  // 初始化新页面
  if (page->init) {
    page->init();
  }
  // 进入新页面(带可选参数)
  lv_scr_load(page->screen);
  if (page->enter) {
    page->enter(args);  // args可以为NULL
  }
  // 压栈新页面
  page_manager_instance.top++;
  page_manager_instance.stack[page_manager_instance.top] = page;
  page->state = PAGE_STATE_ACTIVE;
}

/* 返回上一页(线程安全版) */
void page_manager_go_back(void *args) {
  // 栈空检查(至少保留一个页面)
  if (page_manager_instance.top <= 0) {
    return;
  }

  page_base_t *current = page_manager_instance.stack[page_manager_instance.top];
  page_base_t *prev =
      page_manager_instance.stack[page_manager_instance.top - 1];

  // 标记当前页面为销毁中
  current->state = PAGE_STATE_DESTROYING;

  // 退出当前页面
  if (current->exit) {
    current->exit();
  }

  // 销毁当前页
  if (current->destroy) {
    current->destroy();
  }

  lv_obj_del_async(current->screen);
  // 出栈当前页面
  page_manager_instance.top--;
  lv_scr_load(prev->screen);
  // 进入前一页面
  if (prev->enter) {
    prev->enter(NULL);
  }
  prev->state = PAGE_STATE_ACTIVE;
}

/* 返回首页并清空栈(线程安全版) */
void page_manager_go_off_all(page_base_t *next_page) {
  if (next_page == NULL) return;

  // 销毁栈中所有页面(从栈顶开始)
  while (page_manager_instance.top >= 0) {
    page_base_t *page = page_manager_instance.stack[page_manager_instance.top];

    // 标记页面为销毁中
    page->state = PAGE_STATE_DESTROYING;

    if (page->exit) {
      page->exit();
    }

    if (page->destroy) {
      page->destroy();
    }
    lv_obj_del_async(page->screen);
    page_manager_instance.top--;
  }

  // 初始化新页面
  if (next_page->init) {
    next_page->init();
  }

  // 设置页面状态为活跃
  next_page->state = PAGE_STATE_ACTIVE;
  lv_scr_load(next_page->screen);

  // 进入首页
  if (next_page->enter) {
    next_page->enter(NULL);
  }

  // 重置栈
  page_manager_instance.top = 0;
  page_manager_instance.stack[0] = next_page;

  // rt_mutex_release(&page_manager_instance.lock);
}

/* 获取当前页面 */
page_base_t *page_manager_get_current(void) {
  if (page_manager_instance.top < 0) {
    return NULL;
  }
  return page_manager_instance.stack[page_manager_instance.top];
}
