#include <solver/WordleGuesser.h>
WordleGuesser::WordleGuesser(int x, int y) {
  gx = x;
  gy = y;
}

int WordleGuesser::getSum() const { return gx + gy; }
