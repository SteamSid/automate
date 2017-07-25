#ifndef __RENDR_MAIN_HPP
#define __RENDR_MAIN_HPP

namespace rnr {
  unsigned int init();
  void quit();
  void wait(int);

  class window {
    private:
      uint32_t _wid;
    public:
      window(int,int,const char*);
      void close();
      void resize(int,int);
      void rename(const char*);
      ~window(); };
}

#endif
