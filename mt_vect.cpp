#include <iostream>
#include <thread>
#include <vector>
#include<numeric>

void sum_nums(int array[], int &sum, int start, int end) {
  sum=0;
  for (int i=start; i<end; i++) {
    sum+= array[i];
  }
}

int main()
{
  int sum=0;
  const int size_array = 10000;
  const int num_threads = 5; 
  std::vector<std::thread> my_threads;
  std::vector<int> partial_sums(num_threads);
  int array[size_array];
  std::fill(array, array + size_array, 1); 
  int step = size_array / num_threads;

  
  for (int i = 0; i <num_threads; i++) {
    my_threads.push_back(std::thread(sum_nums, std::ref(array), std::ref(partial_sums[i]), i*step, (i+1)*step));
  }

  
  sum_nums(array, sum, 0, size_array);
  std::cout<< "The sum(nonthreaded) is "<< sum << std::endl;
  

   for (std::thread &t: my_threads) {
    if (t.joinable()) {
      t.join();
    }
  }

  
  for (int i = 0; i <num_threads; i++) {
   std::cout<<"Partial sum "<< i << "  "<< partial_sums[i]<< std::endl;
  }


 std::cout << "Sum using threads = " << std::accumulate(partial_sums.begin(), partial_sums.end(), 0) << std::endl; 

  return 0;

}
