#include <iostream>
#include <omp.h>
#include <vector>
#include <cstdlib>
#include <ctime>



int main() {
  srand(time(0));

  int size;
  int min;
  int max;

do {
  std::cout << "Параметри матриці (size, min, max)" << std::endl;
  std::cin >> size >> min >> max;
} while(min > max);


auto MatrixRandom = [](int size, int min, int max) {
        std::vector<std::vector<int>> mt(size, std::vector<int>(size));
        for(int i = 0; i < size; i++) {
            for(int j = 0; j < size; j++) {
                mt[i][j] = rand() % (max - min + 1) + min;
            }
        }
        return mt;
    };

auto mt1 = MatrixRandom(size, min, max);
auto mt2 = MatrixRandom(size, min, max);




}
