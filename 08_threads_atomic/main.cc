// this example demonstrates using a mutex to avoid a race condition

#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>
#include <thread>
#include <chrono>
#include <atomic>


std::atomic<int> counter(0);


void call_from_thread(int tid)
{
  for (unsigned int i=0;i<10000;++i)
    {
      counter++;
      //counter = counter + 1;
    }
}

int main()
{  
  const int num_threads = 10;
  std::cout << "Starting " << num_threads << " threads ..." << std::endl;
  
  std::thread t[num_threads];

  for (int i = 0; i < num_threads; ++i)
    {
      t[i] = std::thread(call_from_thread, i);
    }

  std::cout << "Done launching threads ...\n" << std::endl;

  for (int i = 0; i < num_threads; ++i)
    {
      t[i].join();
    }

  std::cout << "All threads are done. counter: " << counter
	    << " (should be " << num_threads*10000 <<  ")"<< std::endl;
}
