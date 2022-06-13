
# include "../ft_containers.hpp"
# include <iostream>
# include <vector>
# include <list>

template <typename T>
void	printSize(NAMESPACE::vector<T> const &vct, bool print_content = true)
{
	const size_t size = vct.size();
	const size_t capacity = vct.capacity();
	const std::string isCapacityOk = (capacity >= size) ? "OK" : "KO";
	// Cannot limit capacity's max value because it's implementation dependent

	std::cout << "size: " << size << std::endl;
	std::cout << "capacity: " << isCapacityOk << std::endl;
	std::cout << "max_size: " << vct.max_size() << std::endl;
	if (print_content)
	{
		typename NAMESPACE::vector<T>::const_iterator it = vct.begin();
		typename NAMESPACE::vector<T>::const_iterator ite = vct.end();
		std::cout << std::endl << "Content is:" << std::endl;
		for (; it != ite; ++it)
			std::cout << "- " << *it << std::endl;
	}
	std::cout << "###############################################" << std::endl;
}


// #define TESTED_TYPE int

// int		main(void)
// {
// 	std::list<TESTED_TYPE> lst;
// 	std::list<TESTED_TYPE>::iterator lst_it;
// 	for (int i = 1; i < 5; ++i)
// 		lst.push_back(i * 3);

// 	NAMESPACE::vector<TESTED_TYPE> vct(lst.begin(), lst.end());
// 	printSize(vct);

// 	lst_it = lst.begin();
// 	for (int i = 1; lst_it != lst.end(); ++i)
// 		*lst_it++ = i * 5;
// 	vct.assign(lst.begin(), lst.end());
// 	printSize(vct);

// 	vct.insert(vct.end(), lst.rbegin(), lst.rend());
// 	printSize(vct);
// 	return (0);
// }

// int	main()
// {
// 	NAMESPACE::vector<int> vct(7);
// 	NAMESPACE::vector<int> vct_two(4);
// 	NAMESPACE::vector<int> vct_three;
// 	NAMESPACE::vector<int> vct_four;

// 	for (unsigned long int i = 0; i < vct.size(); ++i)
// 		vct[i] = (vct.size() - i) * 3;
// 	for (unsigned long int i = 0; i < vct_two.size(); ++i)
// 		vct_two[i] = (vct_two.size() - i) * 5;
// 	printSize(vct);
// 	printSize(vct_two);

// 	vct_three.assign(vct.begin(), vct.end());
// 	vct.assign(vct_two.begin(), vct_two.end());
// 	vct_two.assign(2, 42);
// 	vct_four.assign(4, 21);

// 	std::cout << "\t### After assign(): ###" << std::endl;

// 	printSize(vct);
// 	printSize(vct_two);
// 	printSize(vct_three);
// 	printSize(vct_four);

// 	vct_four.assign(6, 84);
// 	printSize(vct_four);

// 	std::cout << "\t### assign() on enough capacity and low size: ###" << std::endl;

// 	vct.assign(5, 53);
// 	vct_two.assign(vct_three.begin(), vct_three.begin() + 3);

// 	printSize(vct);
// 	printSize(vct_two);

// 	return (0);
// }



// #define TESTED_TYPE std::string

// void	checkErase(NAMESPACE::vector<TESTED_TYPE> const &vct,
// 					NAMESPACE::vector<TESTED_TYPE>::const_iterator const &it)
// {
// 	static int i = 0;
// 	std::cout << "[" << i++ << "] " << "erase: " << it - vct.begin() << std::endl;
// 	printSize(vct);
// }

// int		main(void)
// {
// 	NAMESPACE::vector<TESTED_TYPE> vct(10);

// 	for (unsigned long int i = 0; i < vct.size(); ++i)
// 		vct[i] = std::string((vct.size() - i), i + 65);
// 	printSize(vct);

// 	checkErase(vct, vct.erase(vct.begin() + 2));

// 	checkErase(vct, vct.erase(vct.begin()));
// 	checkErase(vct, vct.erase(vct.end() - 1));

// 	checkErase(vct, vct.erase(vct.begin(), vct.begin() + 3));
// 	checkErase(vct, vct.erase(vct.end() - 3, vct.end() - 1));

// 	vct.push_back("Hello");
// 	vct.push_back("Hi there");
// 	printSize(vct);
// 	checkErase(vct, vct.erase(vct.end() - 3, vct.end()));

// 	vct.push_back("ONE");
// 	vct.push_back("TWO");
// 	vct.push_back("THREE");
// 	vct.push_back("FOUR");
// 	printSize(vct);
// 	checkErase(vct, vct.erase(vct.begin(), vct.end()));

// 	return (0);
// }

#define TESTED_TYPE foo

class foo {
	public:
		foo(void) { };
		~foo(void) { };
		void m(void) { std::cout << "foo::m called [" << this->value << "]" << std::endl; };
		void m(void) const { std::cout << "foo::m const called [" << this->value << "]" << std::endl; };
		foo &operator=(int src) { this->value = src; return *this; };
		int getValue(void) const { return this->value; };
	private:
		int	value;
};

std::ostream	&operator<<(std::ostream &o, foo const &bar) {
	o << bar.getValue();
	return o;
}

int		main(void)
{
	const int size = 5;
	NAMESPACE::vector<TESTED_TYPE> vct(size);
	NAMESPACE::vector<TESTED_TYPE>::iterator it(vct.begin());
	NAMESPACE::vector<TESTED_TYPE>::const_iterator ite(vct.end());

	for (int i = 1; it != ite; ++i)
		*it++ = i;
	printSize(vct, 1);

	it = vct.begin();
	ite = vct.begin();

	std::cout << *(++ite) << std::endl;
	std::cout << *(ite++) << std::endl;
	std::cout << *ite++ << std::endl;
	std::cout << *++ite << std::endl;

	it->m();
	ite->m();

	std::cout << *(++it) << std::endl;
	std::cout << *(it++) << std::endl;
	std::cout << *it++ << std::endl;
	std::cout << *++it << std::endl;

	std::cout << *(--ite) << std::endl;
	std::cout << *(ite--) << std::endl;
	std::cout << *--ite << std::endl;
	std::cout << *ite-- << std::endl;

	(*it).m();
	(*ite).m();

	std::cout << *(--it) << std::endl;
	std::cout << *(it--) << std::endl;
	std::cout << *it-- << std::endl;
	std::cout << *--it << std::endl;

	return (0);
}
