#include <iostream>
#include <omp.h>
#include <vector>
#include <cstdlib>
#include <ctime>



int main() {
  omp_set_nested(1);
  srand(time(0));
  int size = 2000;
  int min = -1000;
  int max = 1000;

//do {
//  std::cout << "Параметри матриці (size, min, max)" << std::endl;
//  std::cin >> size >> min >> max;
//} while(min > max);

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
        #pragma omp parallel for num_threads(2)
        for (int i = 0; i < sizelocal; i++) {
            for (int j = 0; j < sizelocal; j++) {
                for (int k = 0; k < sizelocal; k++) {
                    result[i][j] += mt1[i][k] * mt2[k][j];
                }
            }
        }
        return result;
};
double start = omp_get_wtime();
#pragma omp parallel num_threads(2)
{
    auto Result = Mnoj(size, min, max);
//    #pragma omp critical
//{
//    std::cout << "\nПотік " << omp_get_thread_num() << " результат:\n";
//    for (int i = 0; i < Result.size(); i++) {
//        for (int j = 0; j < Result[i].size(); j++) {
//            std::cout << Result[i][j] << "\t";
//        }
//        std::cout << "\n";
//    }
}
double end = omp_get_wtime();
std::cout << "\nЗагальний час виконання: " << (end - start) << " сек." << std::endl;
}
