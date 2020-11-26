//this one is using threads but giving the wrong answer becuase 2 threads access the same variable sum2

//g++ -std=c++17 -pthread -o  mt  multithread1.cpp
#include <iostream>
#include <thread>

void sum_nums(int array[], int &sum, int start, int end) {
  for (int i=start; i<end; i++) {
    sum+= array[i];
  }
}

int main()
{
  int sum=0;
  const int size_array = 10000;
  int array[size_array];
  std::fill(array, array + size_array, 1); 
  

  /* for (int i =0; i <10; i++) {
    std::cout<< array[i] << std::endl;
  }*/

  
  sum_nums(array, sum, 0, size_array);
  std::cout<< "The sum(nonthreaded) is "<< sum << std::endl;
  
  int sum2 = 0;
  std::thread t1(sum_nums, array, std::ref(sum2), 0, size_array/2);
  std::thread t2(sum_nums, array, std::ref(sum2), size_array/2, size_array);

  t1.join();
  t2.join();
 
 std::cout<< "The sum(threaded) is "<< sum2 << std::endl;

  return 0;

}
