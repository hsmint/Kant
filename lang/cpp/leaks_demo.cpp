#ifndef USE_SMART_POINTER
#define USE_SMART_POINTER 0
#endif

#include <iostream>
#include <memory>

class Motor {
  private:
    int id_;
    double speed_ = 0.0;

  public:
    explicit Motor(int id) : id_(id) {}
    void setSpeed(double v) { speed_ = v; }

};

int
main() {
#if USE_SMART_POINTER
  std::cout << "[모드] make_unique\n";
  for (int i = 0; i < 1000; ++i) {
    auto m = std::make_unique<Motor>(i);
    m->setSpeed(i);
  }
#else
  std::cout << "[모드] raw\n";
  for (int i = 0; i < 1000; ++i) {
    Motor* m = new Motor(i);
    m->setSpeed(i);
  }
#endif
  std::cout << "프로그램 종료.\n";
  return 0;
}

