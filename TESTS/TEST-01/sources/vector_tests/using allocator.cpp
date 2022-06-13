#include "../system/system_methods.ipp"
#include "__service.ipp"

template <class T>
void allocator_test(_vector<T, std::allocator<int> > vector) {

    for (int i = 0; i < 10; ++i) {
        vector.push_back(i);
    }
}

int main() {

    exit(run_vector_allocator_unit_test<int, std::allocator<int> >("using allocator", allocator_test));
}