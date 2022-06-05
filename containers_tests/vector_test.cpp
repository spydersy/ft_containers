
# include "../vector.hpp"

# include "../utils/enable_if.hpp"
# include "../utils/equal.hpp"
# include "../utils/is_integral.hpp"
# include "../utils/iterators_traits.hpp"
# include "../utils/lexicographical_compare.hpp"


int main() {
  typedef ft::iterator_traits<std::string::iterator> traits;
  std::string::iterator it;
  if (typeid(traits::iterator_category)==typeid(std::random_access_iterator_tag))
    std::cout << "int* is a random-access iterator\n";

  return 0;
}