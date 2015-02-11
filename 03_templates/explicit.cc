#include <iostream>

template <int dim>
struct NumberCache
{};

template <>
struct NumberCache<1>
{
    unsigned int n_levels;
    unsigned int n_lines;
};

template <>
struct NumberCache<2>
{
    unsigned int n_levels;
    unsigned int n_lines;
    unsigned int n_quads;
};

int main()
{
  NumberCache<2> nc;
  nc.n_quads = 2;
  std::cout << nc.n_quads << std::endl;
  
}
