// A demo for shared_mutex and shared_lock
// By Ari Saif
// Run this using one of the following methods:
//  1. With bazel:
//      bazel run --cxxopt='-std=c++17' \
//      src/main/mutex:{THIS_FILE_NAME_WITHOUT_EXTENSION}
//  2. With g++:
//      g++ -std=c++17 -lpthread \
//      src/main/mutex/{THIS_FILE_NAME}.cc  -I ./
#include <future>
#include <iostream>
#include <mutex>
#include <numeric>
#include <shared_mutex>
#include <thread>
#include <vector>

std::shared_mutex g_shared_mutex;
int g_counter;

void Incrementer() {
  for (size_t i = 0; i < 100; i++) {
    //unique will give unsharable access on the shared mutex. when this one has access, no other thread can have it, even the read ones can not acquire it
    std::unique_lock<std::shared_mutex> ul(g_shared_mutex);
    g_counter++;
  }
}

void ImJustAReader() {
  for (int i = 0; i < 100; i++) {
    //when a thread acquires this lock here, it allows more reader threads but until its done, a writer can lock the mutex
    std::shared_lock<std::shared_mutex> sl(g_shared_mutex);
    std::cout << "g_counter: " << g_counter << std::endl;
  }
}

int main() {
  std::vector<std::thread> threads;

//run 100 times incrementer and 100 times imjustareader
  for (int i = 0; i < 100; i++) {
    threads.push_back(std::thread(Incrementer));
    threads.push_back(std::thread(ImJustAReader));
  }

  for (std::thread &t : threads) {
    t.join();
  }
  std::cout << "g_counter: " << g_counter << std::endl;

  assert(g_counter == 100 * 100);
}
