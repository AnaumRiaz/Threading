#include <iostream>
#include <numeric>
#include <thread>
#include <vector>


int main() {
  const int number_of_threads = 100;
  uint64_t number_of_elements = 10000;
  uint64_t step = number_of_elements / number_of_threads;
  std::vector<std::thread> threads;
  std::vector<int> partial_sums(number_of_threads);
  int array[number_of_elements];
  std::fill(array, array + number_of_elements, 1); 

  for (int i = 0; i < number_of_threads; i++) {
    threads.push_back(std::thread([i, &partial_sums, step, &array] {
      for (int j = i * step; j < (i + 1) * step; j++) {
        partial_sums[i] += array[j];
      }
    }));
  }

  for (std::thread &t : threads) {
    if (t.joinable()) {
      t.join();
    }
  }

  int total = std::accumulate(partial_sums.begin(), partial_sums.end(), uint64_t(0));
  std::cout << "total: " << total << std::endl;

  return 0;
}
