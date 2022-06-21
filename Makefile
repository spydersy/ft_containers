
BINS=	ft_map.out std_map.out ft_vector.out std_vector.out std_stack.out ft_stack.out

VECTOR_SRCS= ./containers_tests/vector_test.cpp
MAP_SRCS= ./containers_tests/map_test.cpp
STACK_SRCS= ./containers_tests/stack_test.cpp

CPPFLAGS= -Wall -Werror -Wextra -std=c++98 -g3 -fsanitize=address
DEFINE_FLAG= -D NAMESPACE=

all:  VECTOR STACK MAP

VECTOR:
		@mkdir -p LOG
		clang++ $(VECTOR_SRCS) $(CPPFLAGS) $(DEFINE_FLAG)std -o std_vector.out
		clang++ $(VECTOR_SRCS) $(CPPFLAGS) $(DEFINE_FLAG)ft  -o  ft_vector.out

STACK:
		@mkdir -p LOG
		clang++ $(STACK_SRCS) $(CPPFLAGS) $(DEFINE_FLAG)ft  -o  ft_stack.out
		clang++ $(STACK_SRCS) $(CPPFLAGS) $(DEFINE_FLAG)std -o std_stack.out

MAP:
		@mkdir -p LOG
		clang++ $(MAP_SRCS) $(CPPFLAGS) $(DEFINE_FLAG)ft  -o  ft_map.out
		clang++ $(MAP_SRCS) $(CPPFLAGS) $(DEFINE_FLAG)std -o std_map.out

RUN_VECTOR:
		@mkdir -p LOG
		./ft_vector.out &> LOG/ft_vector.log
		./std_vector.out &> LOG/std_vector.log
		@echo "diff LOG/ft_vector.log LOG/std_vector.log: ===================="
		@diff LOG/std_vector.log LOG/ft_vector.log
		@echo "==============================END=============================="
RUN_STACK:
		@mkdir -p LOG
		./ft_stack.out &> LOG/ft_stack.log
		./std_stack.out &> LOG/std_stack.log
		@echo "diff LOG/ft_stack.log LOG/std_stack.log: ======================"
		@diff LOG/std_stack.log LOG/ft_stack.log
		@echo "==============================END=============================="
RUN_MAP:
		@mkdir -p LOG
		./ft_map.out &> LOG/ft_map.log
		./std_map.out &> LOG/std_map.log
		@echo "diff LOG/ft_map.log LOG/std_map.log: =========================="
		@diff LOG/std_map.log LOG/ft_map.log
		@echo "==============================END=============================="

TEST00:
		clang++ $(CPPFLAGS) ./TESTS/TEST-00/Vector_tests.cpp -o vector.out && clear && ./vector.out
		clang++ $(CPPFLAGS) ./TESTS/TEST-00/Stack_tests.cpp  -ferror-limit=0 -o stack.out  && clear && ./stack.out

TEST01:
		cd TESTS/TEST-01/ && clear && ./start.sh -st
		cd TESTS/TEST-01/ && ./start.sh -v

TEST02:
		cd TESTS/TEST-02/ && clear && ./do.sh

clean:
		rm -f LOG/*
fclean:	clean
		rm -rf $(BINS)
		rm -rf LOG
		rm -rf *.out

re : fclean all
