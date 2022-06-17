
# include "../ft_containers.hpp"
# include <iostream>
# include <vector>
# include <list>

/*
** DEPENDENCIES :
*/

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

template <typename Ite_1, typename Ite_2>
void ft_eq_ope(const Ite_1 &first, const Ite_2 &second, const bool redo = 1)
{
	// std::cerr << "REDO : " << redo << " =================================================" << std::endl;
	// std::cerr << "Check content_00 : " << *first << " | " << *second << std::endl;
	std::cout << (first < second) << std::endl;
	// std::cerr << "Check content_01 : " << *first << " | " << *second << std::endl;
	std::cout << (first <= second) << std::endl;
	// std::cerr << "Check content_02 : " << *first << " | " << *second << std::endl;
	std::cout << (first > second) << std::endl;
	// std::cerr << "Check content_03 : " << *first << " | " << *second << std::endl;
	std::cout << (first >= second) << std::endl;
	// std::cerr << "----------------------------------------------------------" << std::endl << std::endl;
	if (redo)
		ft_eq_ope(second, first, 0);
}

/*
** PROGRAM :
*/
int	main( void )
{
	// /*
	// ** ASSIGN :
	// */
	// {
	// 	std::cout << "ASSIGN: ================================================================" << std::endl;
	// 	#define TESTED_TYPE int
	// 	NAMESPACE::vector<TESTED_TYPE> vct(7);
	// 	NAMESPACE::vector<TESTED_TYPE> vct_two(4);
	// 	NAMESPACE::vector<TESTED_TYPE> vct_three;
	// 	NAMESPACE::vector<TESTED_TYPE> vct_four;

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
	// }

	// /*
	// ** SWAP :
	// */
	// {
	// 	std::cout << "SWAP: ================================================================" << std::endl;
	// 	#define TESTED_TYPE int
	// 	NAMESPACE::vector<TESTED_TYPE> foo(3, 15);
	// 	NAMESPACE::vector<TESTED_TYPE> bar(5, 42);

	// 	NAMESPACE::vector<TESTED_TYPE>::const_iterator it_foo = foo.begin();
	// 	NAMESPACE::vector<TESTED_TYPE>::const_iterator it_bar = bar.begin();

	// 	std::cout << "BEFORE SWAP" << std::endl;

	// 	std::cout << "foo contains:" << std::endl;
	// 	printSize(foo);
	// 	std::cout << "bar contains:" << std::endl;
	// 	printSize(bar);

	// 	foo.swap(bar);

	// 	std::cout << "AFTER SWAP" << std::endl;

	// 	std::cout << "foo contains:" << std::endl;
	// 	printSize(foo);
	// 	std::cout << "bar contains:" << std::endl;
	// 	printSize(bar);

	// 	std::cout << "Iterator validity:" << std::endl;
	// 	std::cout << (it_foo == bar.begin()) << std::endl;
	// 	std::cout << (it_bar == foo.begin()) << std::endl;
	// }

	// /*
	// ** SIZE :
	// */
	// {
	// 	std::cout << "SIZE: ================================================================" << std::endl;
	// 	#define TESTED_TYPE int
	// 	const int start_size = 7;
	// 	NAMESPACE::vector<TESTED_TYPE> vct(start_size, 20);
	// 	NAMESPACE::vector<TESTED_TYPE> vct2;
	// 	NAMESPACE::vector<TESTED_TYPE>::iterator it = vct.begin();

	// 	for (int i = 2; i < start_size; ++i)
	// 		it[i] = (start_size - i) * 3;
	// 	printSize(vct, true);

	// 	vct.resize(10, 42);
	// 	printSize(vct, true);

	// 	vct.resize(18, 43);
	// 	printSize(vct, true);
	// 	vct.resize(10);
	// 	printSize(vct, true);
	// 	vct.resize(23, 44);
	// 	printSize(vct, true);
	// 	vct.resize(5);
	// 	printSize(vct, true);
	// 	vct.reserve(5);
	// 	vct.reserve(3);
	// 	printSize(vct, true);
	// 	vct.resize(87);
	// 	vct.resize(5);
	// 	printSize(vct, true);

	// 	std::cout << "is_empty: " << vct.empty() << std::endl;
	// 	vct2 = vct;
	// 	std::cout << "is_empty: " << vct.empty() << std::endl;
	// 	vct.reserve(vct.capacity() + 1);
	// 	printSize(vct, true);
	// 	printSize(vct2, true);

	// 	vct2.resize(0);
	// 	std::cout << "is_empty: " << vct.empty() << std::endl;
	// 	printSize(vct2, true);
	// }


	// /*
	// ** AT_CONST :
	// */
	// {
	// 	std::cout << "AT_CONST : ================================================================" << std::endl;
	// 	#define TESTED_TYPE int
	// 	NAMESPACE::vector<TESTED_TYPE> vct(7);

	// 	for (unsigned long int i = 0; i < vct.size(); ++i)
	// 	{
	// 		vct.at(i) = (vct.size() - i) * 3;
	// 		std::cout << "vct[]: " << vct[i] << std::endl;
	// 	}
	// 	printSize(vct);

	// 	NAMESPACE::vector<TESTED_TYPE> const vct_c(vct);

	// 	std::cout << "front(): " << vct.front() << " " << vct_c.front() << std::endl;
	// 	std::cout << "back(): " << vct.back() << " " <<  vct_c.back() << std::endl;

	// 	for (unsigned long int i = 0; i < vct_c.size(); ++i)
	// 		std::cout << "vct_c.at(): " << vct_c.at(i) << std::endl;
	// 	try {
	// 		std::cout << vct_c.at(10) << std::endl;
	// 	}
	// 	catch (std::out_of_range &e) {
	// 		std::cout << "Catch out_of_range exception!" << std::endl;
	// 	}
	// 	catch (std::exception &e) {
	// 		std::cout << "Catch exception: " << e.what() << std::endl;
	// 	}
	// 	printSize(vct_c);
	// }



	// /*
	// ** BIDIRECT_IT :
	// */
	// {
	// 	std::cout << "BIDIRECT_IT : ================================================================" << std::endl;
	// 	#define TESTED_TYPE int
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
	// }

	// /*
	// ** RITE :
	// */
	// {
	// 	std::cout << "RITE : ================================================================" << std::endl;
	// 	#define TESTED_TYPE int
	// 	const int size = 5;
	// 	NAMESPACE::vector<TESTED_TYPE> vct(size);
	// 	NAMESPACE::vector<TESTED_TYPE>::iterator it_ = vct.begin();
	// 	NAMESPACE::vector<TESTED_TYPE>::reverse_iterator it(it_);

	// 	for (int i = 0; i < size; ++i)
	// 		vct[i] = (i + 1) * 5;
	// 	printSize(vct);

	// 	std::cout << (it_ == it.base()) << std::endl;
	// 	std::cout << (it_ == (it + 3).base()) << std::endl;

	// 	std::cout << *(it.base() + 1) << std::endl;
	// 	std::cout << *(it - 3) << std::endl;
	// 	std::cout << *(it - 3).base() << std::endl;
	// 	it -= 3;
	// 	std::cout << *it.base() << std::endl;

	// 	std::cout << "TEST OFFSET" << std::endl;
	// 	std::cout << *(it) << std::endl;
	// 	std::cout << *(it).base() << std::endl;
	// 	std::cout << *(it - 0) << std::endl;
	// 	std::cout << *(it - 0).base() << std::endl;
	// 	std::cout << *(it - 1).base() << std::endl;
	// }

	// /*
	// ** RITE2 :
	// */
	// {
	// 	std::cout << "RITE2 : ================================================================" << std::endl;
	// 	#define TESTED_TYPE int
	// 	const int size = 5;
	// 	NAMESPACE::vector<TESTED_TYPE> vct(size);
	// 	NAMESPACE::vector<TESTED_TYPE>::reverse_iterator it = vct.rbegin();
	// 	NAMESPACE::vector<TESTED_TYPE>::const_reverse_iterator ite = vct.rbegin();

	// 	for (int i = 0; i < size; ++i)
	// 		it[i] = (size - i) * 5;

	// 	it = it + 5;
	// 	it = 1 + it;
	// 	it = it - 4;
	// 	std::cout << *(it += 2) << std::endl;
	// 	std::cout << *(it -= 1) << std::endl;

	// 	*(it -= 2) = 42;
	// 	*(it += 2) = 21;

	// 	std::cout << "const_ite +=/-=: " << *(ite += 2) << " | " << *(ite -= 2) << std::endl;

	// 	std::cout << "(it == const_it): " << (ite == it) << std::endl;
	// 	std::cout << "(const_ite - it): " << (ite - it) << std::endl;
	// 	std::cout << "(ite + 3 == it): " << (ite + 3 == it) << std::endl;

	// 	printSize(vct, true);
	// }


	// /*
	// ** RITE_ARROW :
	// */
	// {
	// 	std::cout << "RITE_ARROW : ================================================================" << std::endl;
	// 	const int size = 5;
	// 	NAMESPACE::vector<foo> vct(size);
	// 	NAMESPACE::vector<foo>::reverse_iterator it(vct.rbegin());
	// 	NAMESPACE::vector<foo>::const_reverse_iterator ite(vct.rend());

	// 	for (int i = 1; it != ite; ++i)
	// 		*it++ = (i * 7);
	// 	printSize(vct, 1);

	// 	it = vct.rbegin();
	// 	ite = vct.rbegin();

	// 	std::cout << *(++ite) << std::endl;
	// 	std::cout << *(ite++) << std::endl;
	// 	std::cout << *ite++ << std::endl;
	// 	std::cout << *++ite << std::endl;

	// 	it->m();
	// 	ite->m();

	// 	std::cout << *(++it) << std::endl;
	// 	std::cout << *(it++) << std::endl;
	// 	std::cout << *it++ << std::endl;
	// 	std::cout << *++it << std::endl;

	// 	std::cout << *(--ite) << std::endl;
	// 	std::cout << *(ite--) << std::endl;
	// 	std::cout << *--ite << std::endl;
	// 	std::cout << *ite-- << std::endl;

	// 	(*it).m();
	// 	(*ite).m();

	// 	std::cout << *(--it) << std::endl;
	// 	std::cout << *(it--) << std::endl;
	// 	std::cout << *it-- << std::endl;
	// 	std::cout << *--it << std::endl;
	// 	}

	/*
	** RITE_EQ_OPE :
	*/
	{
		std::cout << "RITE_EQ_OPE : ================================================================" << std::endl;
		const int size = 5;
		NAMESPACE::vector<foo> vct(size);
		NAMESPACE::vector<foo>::reverse_iterator it_0(vct.rbegin());
		NAMESPACE::vector<foo>::reverse_iterator it_1(vct.rend());
		NAMESPACE::vector<foo>::reverse_iterator it_mid;

		NAMESPACE::vector<foo>::const_reverse_iterator cit_0 = vct.rbegin();
		NAMESPACE::vector<foo>::const_reverse_iterator cit_1 = vct.rend();
		NAMESPACE::vector<foo>::const_reverse_iterator cit_mid;

		for (int i = size; it_0 != it_1; --i)
			*it_0++ = i;
		printSize(vct, 1);
		it_0 = vct.rbegin();
		cit_1 = vct.rend();
		it_mid = it_0 + 3;
		cit_mid = it_0 + 3; cit_mid = cit_0 + 3; cit_mid = it_mid;

		std::cout << std::boolalpha;
		std::cout << ((it_0 + 3 == cit_0 + 3) && (cit_0 + 3 == it_mid)) << std::endl;

		std::cout << "\t\tft_eq_ope:" << std::endl;
		// regular it
		std::cerr << "BEF_CHECK_00 : " << *(it_0 + 3) << *(it_mid) << std::endl;
		ft_eq_ope(it_0 + 3, it_mid);
		std::cerr << "BEF_CHECK_01 : " << *(it_0) << *(it_1) << std::endl;
		ft_eq_ope(it_0, it_1);
		std::cerr << "BEF_CHECK_02 : " << *(it_1 - 3) << *(it_mid) << std::endl;
		ft_eq_ope(it_1 - 3, it_mid);
		// const it
		std::cerr << "BEF_CHECK_03 : " << *(cit_0 + 3) << *(cit_mid) << std::endl;
		ft_eq_ope(cit_0 + 3, cit_mid);
		std::cerr << "BEF_CHECK_04 : " << *(cit_0) << *(cit_1) << std::endl;
		ft_eq_ope(cit_0, cit_1);
		std::cerr << "BEF_CHECK_05 : " << *(cit_1 - 3) << *(cit_mid) << std::endl;
		ft_eq_ope(cit_1 - 3, cit_mid);
		// both it
		std::cerr << "BEF_CHECK_06 : " << *(it_0 + 3) << *(cit_mid) << std::endl;
		ft_eq_ope(it_0 + 3, cit_mid);
		std::cerr << "BEF_CHECK_07 : " << *(it_mid) << *(cit_0 + 3) << std::endl;
		ft_eq_ope(it_mid, cit_0 + 3);
		std::cerr << "BEF_CHECK_08 : " << *(it_0) << *(cit_1) << std::endl;
		ft_eq_ope(it_0, cit_1);
		ft_eq_ope(it_1, cit_0);
		ft_eq_ope(it_1 - 3, cit_mid);
		ft_eq_ope(it_mid, cit_1 - 3);
	}


	/*
	** XXXXXXX :
	*/
	{
		std::cout << "XXXXXXX : ================================================================" << std::endl;

	}
	return 0;
}
