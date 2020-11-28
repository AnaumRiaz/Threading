// A demo for mutex and locks
// By Ari Saif
// Run this using one of the following methods:
//  1. With bazel:
//      bazel run --cxxopt='-std=c++17' \
//      src/main/mutex:{THIS_FILE_NAME_WITHOUT_EXTENSION}
//  2. With g++:
//      g++ -std=c++17 -lpthread \
//      src/main/mutex/{THIS_FILE_NAME}.cc  -I ./
#include <iostream>
#include <map>
#include <mutex>
#include <numeric>
#include <thread>
#include <vector>
#include <assert.h>  


std::mutex g_mutex;
int g_counter;

void Incrementer() {
  for (size_t i = 0; i < 100; i++) {
    g_mutex.lock();
    g_counter++;
    g_mutex.unlock();
  }
}

void print_map(std::map<int, int> count) {
  
  std::map<int, int>::iterator it = count.begin();
  while(it != count.end())
  {
  std::cout<<it->first<<" :: "<<it->second<<std::endl;
  it++;
  }

}

int main() {
  std::map<int, int> count;         //key-value pair
 
// run this a N times. make 100 threads and check the answers N times to make sure we are getting them right
  int N = 10;
  for (int i = 0; i < N; i++) {

    g_counter = 0;
    std::vector<std::thread> threads;

    for (int i = 0; i < 100; i++) {
      threads.push_back(std::thread(Incrementer)); }

    for (std::thread &t : threads) {
      t.join();
    }
    std::cout << "g_counter: " << g_counter << std::endl;
    //std::cout << g_counter << ", ";
    count[g_counter]++;
    print_map(count);
  }

  assert(count[10000] == N); 
}
