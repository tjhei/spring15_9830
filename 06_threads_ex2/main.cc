// template for multithreaded vector addition

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


void add(Vector &out,
	 const Vector &in1,
	 const Vector &in2,
	 unsigned int start,
	 unsigned int end)
{
  for (unsigned int i=start;i<end;++i)
    out.values[i] = in1.values[i] + in2.values[i];
}

int main()
{  
  unsigned int size = 10000000; // = 80 MB
  const int n_runs = 100;
  Vector x(size);
  Vector y(size);
  Vector z(size);

  std::cout << "Running " << n_runs << " additions... " << std::endl;
  
  // serial version
  for (int runs=0;runs<n_runs;++runs)
    add(z, x, y, 0, size);

  // parallel version
  /*
  {
    const int num_threads = 4;
    std::thread t[num_threads];
    for (int runs=0;runs<n_runs;++runs)
      {
	for (int i = 0;i < num_threads; ++i)
	  {
	    unsigned int start = 0; // TODO
	    unsigned int end = size; // TODO
	    t[i] = std::thread(add, TODO);
	  }
	for (int i = 0; i < num_threads; ++i)
	  t[i].join();
      }
  }*/
}
