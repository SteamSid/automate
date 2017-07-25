#include <iostream>
#include <cstdint>
#include <cstdlib>
#include <cstring>

#include "rendr_main.hpp"
#include "drivers/rendr_drv_hooks.hpp"

int is_error=0;

void _ld_drv(){
  const char* drv;

  if(const char* enval=std::getenv("AUTOMATE_DRIVER_GRAPHICS")) drv=enval;
  else { std::cout<<"ERROR! Failed to load graphics driver, nothing specified!\n"; return; }

  drv_load_driver(drv); }

unsigned int rnr::init(){
  _ld_drv(); }

void rnr::quit(){
  drv_close_driver(); }

void rnr::wait(int t){
  drv_rendr_wait(t); }

rnr::window::window(int w,int h,const char* name) {
  _wid=drv_rendr_window_open(w,h,name); }

void rnr::window::close() {
  _wid=0;
  if(_wid!=0) drv_rendr_window_close(_wid); }

void rnr::window::resize(int w,int h) {
  int* nmem=(int*)malloc(sizeof(int)*2);
  memcpy(nmem  ,&w,sizeof(int));
  memcpy(nmem+1,&h,sizeof(int));
  drv_rendr_window_change_attribute(_wid,"size",(const void*)nmem);
  free(nmem); }

void rnr::window::rename(const char* name) {
  drv_rendr_window_change_attribute(_wid,"name",(const void*)name); }

rnr::window::~window() {
  close(); }

