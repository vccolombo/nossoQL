#include <cstdio>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <string>

int main(int argc, char const *argv[]) {
  char comando[200];
  while (fgets(comando, 200, stdin) != NULL) {
    std::cout << comando << '\n';
  }

  return 0;
}
