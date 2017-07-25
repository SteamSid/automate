#include <iostream>
#include "renderer/rendr_main.hpp"

int main(int argc,char *argv[]) {
  rnr::init();
  rnr::window win(1280,720,"New Window");
  rnr::wait(1000);
  win.close();
  rnr::quit();
  return 0; }
