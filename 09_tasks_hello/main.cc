#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <thread>

#include <deal.II/base/timer.h>
#include <deal.II/base/thread_management.h>
#include <deal.II/base/multithread_info.h>

using namespace dealii;

int hello(int id)
{
  std::cout << "start " << id
	    << " on " << std::this_thread::get_id()
	    << std::endl;
  
  std::this_thread::sleep_for(std::chrono::milliseconds(rand()%1000));
  
  std::cout << "end " << id <<std::endl;
 
  return id;
}


int add_range(int a, int b)
{
  std::cout << "range " << a << " " << b << std::endl;
  return b-a;
}


int main()
{
  // note: you can set
  //   export DEAL_II_NUM_THREADS=7
  // in the terminal to control the number of threads used
  multithread_info.set_thread_limit();
  std::cout << "cpus: " << multithread_info.n_cpus
	    << " threads: " << multithread_info.n_threads()
	    << " main thread: " << std::this_thread::get_id()
	    << std::endl;

  if (0)
    {
      Threads::Task<int> task = Threads::new_task (&hello, 1234);
      // do some other stuff
      int value = task.return_value(); // or task.join()
    }  

  if (1)
    {
      int tasks = 10;//5*multithread_info.n_threads();
      
      Threads::TaskGroup<int> task_group;
      for (int i=0;i<tasks;++i)
	{
	  task_group += Threads::new_task (&hello, i);
	}
      
      task_group.join_all();
    }

  
}
