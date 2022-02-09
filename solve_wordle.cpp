#include <iostream>
#include <solver/A2DD.h>

int main(int argc, char **argv) {
  std::cout << "hi23" << std::endl;
  const auto a = A2DD(0, 1);
  std::cout << a.getSum() << std::endl;
}