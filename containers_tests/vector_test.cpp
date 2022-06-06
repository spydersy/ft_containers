
# include "../ft_containers.hpp"

int main() {
  // typedef ft::iterator_traits<std::string::iterator> traits;
  // std::string::iterator it;
  // if (typeid(traits::iterator_category)==typeid(std::random_access_iterator_tag))
    // std::cout << "int* is a random-access iterator\n";

    // std::cout << "Typeid : " << typeid(ft::bidirectional_iterator_tag).name() << std::endl;
    // std::cout << "Typeid : " << typeid(std::bidirectional_iterator_tag).name() << std::endl;

    ft::vector<std::string> vect_string(10, "5");
    ft::vector<int>         vect_int(10, 1);

    ft::vector<std::string>::iterator string_it;
    ft::vector<int>::iterator         int_it;
    ft::vector<int *> vec;

    std::allocator<int*> alloc;

    ft::vector<int*>::iterator it = vec.begin();

  return 0;
}