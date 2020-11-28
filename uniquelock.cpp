
//g++ -std=c++17 -pthread -o  mt  multithread1.cpp
#include <iostream>
#include <thread>
#include <mutex>
#include <assert.h>
#include <vector>

std::mutex my_mutex;

void sum_nums(int array[], int &sum, int start, int end) {
  for (int i=start; i<end; i++) {
    std::unique_lock<std::mutex> lunique(my_mutex);
    sum+= array[i];
    //inn unique lock, we can lock/unlock. but the cout statement prints all over the place because many threads access it at varying times
    lunique.unlock();
    std::cout<<"\nmddle unlocked "<<i;
    lunique.lock();
  }
   
  std::cout<<"\noutside scope of lockguard"<<std::endl;
   
}

int main()
{
  
  int sum=0;
  const int number_threads = 5;
  const int size_array = 100;
  int step = size_array/number_threads;
  int array[size_array];
  std::fill(array, array + size_array, 1); 
  std::vector<std::thread> threads;

  /* for (int i =0; i <10; i++) {
    std::cout<< array[i] << std::endl;
  }*/

  
  sum_nums(array, sum, 0, size_array);
  std::cout<< "The sum(nonthreaded) is "<< sum << std::endl;
  
  int sum2 = 0;
  for (int i =0; i<number_threads; i++) {
    threads.push_back(std::thread(sum_nums, std::ref(array), std::ref(sum2), i*step, (i+1)*step));
}
  //std::thread t1(sum_nums, std::ref(array), std::ref(sum2), 0, size_array/2);
  //std::thread t2(sum_nums, std::ref(array), std::ref(sum2), size_array/2, size_array);

  for (std::thread &t : threads) {
    if (t.joinable()) {
      t.join();
     }
  }
 
  std::cout<< "The sum(threaded) is "<< sum2 << std::endl;
  //assert(sum2 == 10000);
  return 0;

}

