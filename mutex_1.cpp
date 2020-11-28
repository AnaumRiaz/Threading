
//g++ -std=c++17 -pthread -o  mt  multithread1.cpp
#include <iostream>
#include <thread>
#include <mutex>
#include <assert.h>
#include <vector>

std::mutex my_mutex;

//instead of locks, we can use lockguard. they take care of unlocking in case of an exception or somethng causes the unlock not to be called
// here the lock_guard workds even on the cout lines. all inside the for loop this one works
void sum_nums(int array[], int &sum, int start, int end) {
  for (int i=start; i<end; i++) {
    //my_mutex.lock();
    std::lock_guard<std::mutex> lguard(my_mutex);
    sum+= array[i];
    std::cout<<i;
  }
    //put it here just to show that this print statement does print in a different strange order as different threads can access it asynchronously
    std::cout<<"\noutside scope of lockguard"<<std::endl;
    //my_mutex.unlock();
}

int main()
{
  
  int sum=0;
  const int number_threads = 4;
  const int size_array = 400;
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

