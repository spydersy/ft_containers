
# include "../ft_containers.hpp"

int main() {

	ft::vector<int>				int_vect(22, 5);
	ft::vector<int>				vect(int_vect.begin(), int_vect.end());

	return 0;
}