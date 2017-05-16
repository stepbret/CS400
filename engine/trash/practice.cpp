#include <iostream>
#include <string>
#include <vector>

int coord_x = 0;
int coord_y = 0;

int main() {
  std::vector<int> vec;
  vec.push_back(1);
  vec.push_back(2);

  for(int i = 0; i < vec.size(); i++)
    std::cout << i << ":" <<  vec[i]<< std::endl;

  vec.clear();

  for(int i = 0; i < vec.size(); i++)
    std::cout << vec[i]<< std::endl;
}

