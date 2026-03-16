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
auto Mnoj = [&](int size, int min, int max) {
        auto mt1 = MatrixRandom(size, min, max);
        auto mt2 = MatrixRandom(size, min, max);
        int sizelocal = mt1.size();

        std::vector<std::vector<int>> result(sizelocal, std::vector<int>(sizelocal, 0));
        for (int i = 0; i < sizelocal; i++) {
            for (int j = 0; j < sizelocal; j++) {
                for (int k = 0; k < sizelocal; k++) {
                    result[i][j] += mt1[i][k] * mt2[k][j];
                }
            }
        }
        return result;
};
#pragma omp parallel num_threads(2)
{
    auto Result = Mnoj(size, min, max);
    #pragma omp critical
{
    std::cout << "\nПотік " << omp_get_thread_num() << " результат:\n";
    for (int i = 0; i < Result.size(); i++) {
        for (int j = 0; j < Result[i].size(); j++) {
            // Виводимо число і просто додаємо табуляцію для відступу
            std::cout << Result[i][j] << "\t";
        }
        std::cout << "\n"; // Перехід на новий рядок
    }
}
}
}
