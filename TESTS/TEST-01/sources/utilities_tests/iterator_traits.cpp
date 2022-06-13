#include "../system/system_methods.ipp"
#include "../../../../ft_containers.hpp"

// #include "../utils/backup_reverse_iterator.hpp"
// #include "../utils/is_integral.hpp"
// #include "../utils/random_access_iterator.hpp"
// #include "../utils/enable_if.hpp"
// #include "../utils/iterators_traits.hpp"
// #include "../utils/reverse_iterator.hpp"

#include VECTOR

bool iterator_traits_test() {
	std::vector<string> res;
	std::vector<string> res2;
	g_start1 = g_end1 = timer();

	res.push_back(typeid(std::vector<int>::iterator::iterator_category).name());
	res.push_back(typeid(std::vector<int>::iterator::value_type).name());
	res.push_back(typeid(std::vector<int>::iterator::difference_type).name());
	res.push_back(typeid(std::vector<int>::iterator::iterator_type).name());
	res.push_back(typeid(std::vector<int>::iterator::pointer).name());
	res.push_back(typeid(std::vector<int>::iterator::reference).name());
	res.push_back(typeid(std::vector<int>::reverse_iterator::iterator_category).name());
	res.push_back(typeid(std::vector<int>::reverse_iterator::value_type).name());
	res.push_back(typeid(std::vector<int>::reverse_iterator::difference_type).name());
	res.push_back(typeid(std::vector<int>::reverse_iterator::pointer).name());
	res.push_back(typeid(std::vector<int>::reverse_iterator::reference).name());

	res2.push_back(typeid(_vector<int>::iterator::iterator_category).name());
	res2.push_back(typeid(_vector<int>::iterator::value_type).name()); //done
	res2.push_back(typeid(_vector<int>::iterator::difference_type).name()); //done
	res2.push_back(typeid(_vector<int>::iterator::iterator_type).name());
	res2.push_back(typeid(_vector<int>::iterator::pointer).name()); //done
	res2.push_back(typeid(_vector<int>::iterator::reference).name()); //done
	res2.push_back(typeid(_vector<int>::reverse_iterator::iterator_category).name());
	res2.push_back(typeid(_vector<int>::reverse_iterator::value_type).name());
	res2.push_back(typeid(_vector<int>::reverse_iterator::difference_type).name());
	res2.push_back(typeid(_vector<int>::reverse_iterator::pointer).name());
	res2.push_back(typeid(_vector<int>::reverse_iterator::reference).name());

	return res == res2;
}

int main() {

	exit(run_bool_unit_test("iterators_traits", iterator_traits_test));
}
