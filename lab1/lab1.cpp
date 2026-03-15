#include <iostream>
#include <windows.h>
#include <omp.h>

int main(){
  SetConsoleOutputCP(65001);

  #pragma omp parallel
  omp_set_num_threads(4);
  std::cout << "I am "<< omp_get_thread_num() <<"thread from " << omp_get_num_threads() << "threads" << std::endl;


  return 0;
}
