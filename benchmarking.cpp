#include <iostream>
#include <chrono>
#include "quick_sort.h"

template<class T>
void result(int* array, int length, T start_time, T end_time, const char* name){
  for (int i = 0; i < length - 1; i++){
    if (array[i] > array[i + 1]){
      std::cout << std::endl << "Wrong element!" << std::endl;
      break;
    }
    if (i == length - 2) std::cout << name << " - OK" << "\t Time: "
       << std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time)
       .count() << " microseconds" << std::endl;
  }
}

void test(){
  srand(time(NULL));
  int N;
  N = 100000;
  int* th_count = new int(0);
  int max_th = 1000; // maximum number of threads allowed

  int* initial_array = new int[N];
  int* array1 = new int[N];
  int* array2 = new int[N];

  for (int i = 0; i < N; i++) initial_array[i] = rand() % 50 - 100;

  copy_array(array1, initial_array, N);
  copy_array(array2, initial_array, N);

  auto start_time = std::chrono::high_resolution_clock::now();
  quick_sort_multi_thread(array1, 0, N - 1, th_count, max_th);
  auto end_time = std::chrono::high_resolution_clock::now();
  result(array1, N, start_time, end_time, "Multi-thread\t");

  start_time = std::chrono::high_resolution_clock::now();
  quick_sort(array2, 0, N - 1);
  end_time = std::chrono::high_resolution_clock::now();
  result(array2, N, start_time, end_time, "Single-thread\t");

  std::cout << "Sorted!" << std::endl;
}
