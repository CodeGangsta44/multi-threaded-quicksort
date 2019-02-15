#include "quick_sort.h"
#include <thread>

void swap(int &a, int &b){
  int swap = a;
  a = b;
  b = swap;
}

void copy_array(int* dest_arr, int* src_arr, int len){
  for (int i = 0; i < len; i++) dest_arr[i] = src_arr[i];
}

int partition(int* arr, int f, int l){
  int i = f - 1;
  int x = arr[l];
  for (int j = f; j < l; j++){
    if (arr[j] <= x) {
      i++;
      swap(arr[i], arr[j]);
    }
  }
  arr[l] = arr[i + 1];
  arr[i + 1] = x;
  return i + 1;
}

void quick_sort_multi_thread(int* arr, int f, int l, int* th_count, int max_th){

  if (f >= l) return;
  int c = partition(arr, f, l);

  if (*th_count < max_th){

    if (*th_count == max_th - 1){
      std::thread t1(quick_sort_multi_thread, arr, f, c - 1, th_count, max_th);
      quick_sort(arr, c + 1, l);
      t1.join();
    } else {
      (*th_count) += 2;
      std::thread t1(quick_sort_multi_thread, arr, f, c - 1, th_count, max_th);
      std::thread t2(quick_sort_multi_thread, arr, c + 1, l, th_count, max_th);
      t1.join();
      t2.join();
    }

  } else {
    quick_sort(arr, f, c - 1);
    quick_sort(arr, c + 1, l);
  }
}

void quick_sort(int* arr, int f, int l){
  if (f >= l) return;
  int c = partition(arr, f, l);

  quick_sort(arr, f, c - 1);
  quick_sort(arr, c + 1, l);
}
