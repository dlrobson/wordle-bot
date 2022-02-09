#include <solver/A2DD.h>
A2DD::A2DD(int x, int y) {
  gx = x;
  gy = y;
}

int A2DD::getSum() const { return gx + gy; }
