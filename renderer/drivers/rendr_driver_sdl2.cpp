#include <SDL2/SDL.h>
#include <cstdint>
#include <cstring>
#include <iostream>
#include <vector>

#define uint unsigned int

std::vector<SDL_Window*> _windows;
const size_t _wsize() { return _windows.size(); }

  extern "C"{

  uint32_t drv_rendr_init(){
    // Initialize SDL and return an error if it fails
    if(SDL_Init(SDL_INIT_VIDEO)!=0){
      printf ("[drv_rendr_sdl2] ERROR: Failed to initialize SDL2: %s\n",SDL_GetError ());
      return 1; }
  return 0; }

  void drv_rendr_quit(){
    for(int i=0;i<_wsize();++i){
      if(_windows[i]) SDL_DestroyWindow(_windows[i]); }
    SDL_Quit(); }

  void drv_rendr_wait(uint t){
    SDL_Delay(t); }

  uint32_t drv_rendr_window_open(uint w,uint h,const char* name){
    // Create SDL2 window and return index for vector

    SDL_Window* window=SDL_CreateWindow(name,SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,w,h,SDL_WINDOW_OPENGL); // Create OpenGL enabled SDL2 window

    if(window==NULL) {
      printf("[drv_rendr_sdl2] WARNING: Failed to create SDL2 window: %s\n",SDL_GetError());
      return 0; }

    int is_set=0;
    int _asize=_wsize();
    for(int i = 0;i<_asize;++i){ // Search the vector for any empty values
      if(_windows[i]==NULL){     // If empty, fill and return index
        is_set=1;
        _windows[i]=window;
        return i; } }

    if(is_set==0) {              // If not empty, push vector back and return index
      _windows.push_back(window);
      return _wsize()-1; } }

  void drv_rendr_window_change_attribute(uint32_t win,const char* attrib,const void* val){
    // Change window attributes
    // Gross if/elseif statement
    // Needed as string switch statements arent a thing and I'm lazy

    // Attributes handled by driver since some graphics libraries don't support certain modifiers

    // Function should never return an error

    if(_windows[win]==NULL) { std::cout<<"[drv_rendr_sdl2] WARNING: Cannot modify attributes of a null window!\n"; return; }

           if(strcmp(attrib,"name")){
      SDL_SetWindowTitle(_windows[win],(const char*)val);
    } else if(strcmp(attrib,"size")){
      SDL_SetWindowSize(_windows[win],*(const int*)val,*((const int*)val)+1);
    } else {
      std::cout<<"[drv_rendr_sdl2] WARNING: Unsupported attribute "<<attrib<<"\n";
    } }

  void drv_rendr_window_close(uint32_t win){
    // Set index to null, DON'T remove it

    if(_windows[win]==NULL) { std::cout<<"[drv_rendr_sdl2] WARNING: Cannot close a null window!\n"; return; }

    SDL_DestroyWindow(_windows[win]);
    _windows[win]=NULL; }

}

#undef uint
