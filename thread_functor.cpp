//using functors

#include<iostream>
#include<vector>
#include<numeric>
#include<thread>

class sumfunc {
public:
  int sum=0; 
  void operator()(int arr[], int start, int end) {
  //sum = 0;
  for (int i=start; i<end; i++) {
    sum += arr[i];
  }
//the print statements are all out of whack because both the threADS are accessig it. and the result is sum:5000sum:5000 or sum:sum:5000 or somehwat the same
  std::cout<<"sum:"<< sum << std::endl;
  }

};

int main() {
  const int num_threads = 2;
  const int array_size = 10000;
  int array[array_size];
  std::fill(array, array+array_size, 1);
  std::vector<std::thread> threads;
  int step = array_size/num_threads;
  std::vector<sumfunc *> functors;

  

  //each functor has sum inside it
  for (int i=0; i<num_threads; i++) {
    sumfunc * myfunc = new sumfunc();
    threads.push_back(std::thread(std::ref(*myfunc), array, i*step, (i+1)*step));
    functors.push_back(myfunc);
  }
  
   //without the following, alot of segmentation faults and core dump faults
  for (std::thread &t : threads) {
    if (t.joinable()) {
      t.join();
    }
  }

 
  int total = 0;
  for (int i=0; i<num_threads; i++) {
    total += functors[i]->sum;
  }

  std::cout<< "The total is "<<total<<std::endl;


return 0;
}
