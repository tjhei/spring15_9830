#include <iostream>

template <int dim>
class Point
{
  public:
    double elements[dim];

    void print();
    
};

template <int dim>
void Point<dim>::print()
{
  for (int i=0;i<dim;++i)
    std::cout << elements[i] << " ";
  std::cout << std::endl;
}


template <>
void Point<5>::print()
{
  std::cout << "we are doing something special!" << std::endl;
}





int main()
{
  Point<3> p;
  p.elements[0] = 1.0;
  p.print();
  
}
