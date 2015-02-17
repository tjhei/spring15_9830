#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>
#include <thread>

void call_from_thread(int tid)
{
  std::cout << "I am " << std::this_thread::get_id()
	    << " with index " << tid << std::endl;

  for (unsigned int i=0;i<10;++i)
    std::cout << i << " ";
  std::cout << std::endl;
}

int main()
{  
  const int num_threads = 4;
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

  std::cout << "All threads are done." << std::endl;
}
