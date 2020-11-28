#include <iostream>
#include <vector>
#include <algorithm>

// this is a functor
struct add_x {
  add_x(int val) : x(val) {}  // Constructor
  int operator()(int y)  { return x + y; }

private:
  int x;
};

int main() {
// Now you can use it like this:
add_x add42(42); // create an instance of the functor class

int i = add42(8); // and "call" it

std::cout<< i << std::endl; // and it added 42 to its argument

std::vector<int> in {2,4,6,8}; // assume this contains a bunch of values)
std::vector<int> out(in.size());
// Pass a functor to std::transform, which calls the functor on every element 
// in the input sequence, and stores the result to the output sequence
std::transform(in.begin(), in.end(), out.begin(), add_x(1)); 

for (int i=0; i<in.size(); i++) {
std::cout<< "out[i] for i:"<< i<< " is "<< out[i]<< std::endl;
}

return 0;
}
