// This program demonstrates that we need std::ref when passing arguments by
// reference to functions on other threads. The designers of std::thread did
// this on purpose to avoid race conditions.

#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>
#include <thread>

class Vector
{
  public:
    Vector(int size = 0)
      {
	values.resize(size);
	for (int i = 0; i < size; ++i)
	  values[i] = rand();
      }

    Vector(const Vector & other)
      {
	std::cout << "You are making a copy "
		  << &other << " -> " << this
		  << std::endl;
	values = other.values;
      }
    
    std::vector<double> values;
    
    void print()
      {
	for (unsigned int i=0;i<values.size();++i)
	  std::cout << values[i] << "\t";
	std::cout << std::endl;
      }

    double norm()
      {
	double tmp = 0.0;
	for (unsigned int i=0;i<values.size();++i)
	  tmp += values[i]*values[i];
	return sqrtf(tmp);
	
      }    
};

void by_value(Vector vec)
{
  std::cout << "I am " << std::this_thread::get_id()
	    << " and &vec = " << &vec
	    << std::endl;  
}

void by_reference(const Vector & vec)
{
  std::cout << "I am " << std::this_thread::get_id()
	    << " and &vec = " << &vec
	    << std::endl;  
}

void by_non_const_reference(Vector & vec)
{
  std::cout << "I am " << std::this_thread::get_id()
	    << " and &vec = " << &vec
	    << std::endl;  
}


int main()
{  
  unsigned int size = 10000000; // = 80 MB
  Vector x(size);
  std::cout << "Address is " << &x << std::endl;

  std::cout << "* First with regular function calls:" << std::endl;
  by_value(x);
  by_reference(x);
  by_non_const_reference(x);

  std::cout << "* Now using threads:" << std::endl;
  {
    std::thread t = std::thread(by_value, x);
    t.join();
  }
  {
    std::thread t = std::thread(by_reference, x);
    t.join();
  }
  {
    // probably won't compile:
    //    std::thread t = std::thread(by_non_const_reference, x);
    //t.join();
  }

  std::cout << "* Now using threads and std::ref:" << std::endl;
  {
    //std::thread t = std::thread(by_value, x);
    //t.join();
  }
  {
    std::thread t = std::thread(by_reference, std::ref(x));
    t.join();
  }
  {
    std::thread t = std::thread(by_non_const_reference, std::ref(x));
    t.join();
  }
  
}
