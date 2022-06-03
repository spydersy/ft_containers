
# include "vector.hpp"
# include "is_integral.hpp"

// int main()
// {
//     vector<int> vect(5, 12);
//     return 0;
// }

int main() {
  std::cout << std::boolalpha;
  std::cout << "is_integral:" << std::endl;
  std::cout << "char: " << ft::is_integral<char>::value << std::endl;
  std::cout << "int: " << ft::is_integral<int>::value << std::endl;
  std::cout << "float: " << ft::is_integral<float>::value << std::endl;
  return 0;
}