#ifndef RENDR_DRV_HOOKS
#define RENDR_DRV_HOOKS

#include <iostream>
#include <dlfcn.h>
#include <cstdint>

#define uint unsigned int

uint32_t (*drv_rendr_init)();
void     (*drv_rendr_quit)();
void     (*drv_rendr_wait)                    (uint);
uint32_t (*drv_rendr_window_open)             (uint,uint,const char*);
void     (*drv_rendr_window_change_attribute) (uint32_t,const char*,const void*);
void     (*drv_rendr_window_close)            (uint32_t);

void* drv_handle;

void drv_load_driver(const char* driver){
  drv_handle=dlopen(driver,RTLD_NOW);

  drv_rendr_init                   =(uint32_t(*)())                                 dlsym(drv_handle,"drv_rendr_init");
  drv_rendr_quit                   =(void    (*)())                                 dlsym(drv_handle,"drv_rendr_quit");
  drv_rendr_wait                   =(void    (*)(uint))                             dlsym(drv_handle,"drv_rendr_wait");
  drv_rendr_window_open            =(uint32_t(*)(uint,uint,const char*))            dlsym(drv_handle,"drv_rendr_window_open");
  drv_rendr_window_change_attribute=(void    (*)(uint32_t ,const char*,const void*))dlsym(drv_handle,"drv_rendr_window_change_attribute");
  drv_rendr_window_close           =(void    (*)(uint32_t))                         dlsym(drv_handle,"drv_rendr_window_close");
}

void drv_close_driver(){
  dlclose(drv_handle); }

#undef uint

#endif
