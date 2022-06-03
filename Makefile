
BINS=	ft_map.out std_map.out ft_vector.out std_vector.out std_stack.out ft_stack.out

VECTOR_SRCS= ./containers_tests/vector_test.cpp
MAP_SRCS= ./containers_tests/map_test.cpp
STACK_SRCS= ./containers_tests/stack_test.cpp

CPPFLAGS= -Wall -Werror -Wextra -std=c++98 -D NAMESPACE=

all:  VECTOR STACK MAP

VECTOR:
		@mkdir -p LOG
		clang++ $(VECTOR_SRCS) $(CPPFLAGS)ft  -o  ft_vector.out
		clang++ $(VECTOR_SRCS) $(CPPFLAGS)std -o std_vector.out

STACK:
		@mkdir -p LOG
		clang++ $(STACK_SRCS) $(CPPFLAGS)ft  -o  ft_stack.out
		clang++ $(STACK_SRCS) $(CPPFLAGS)std -o std_stack.out

MAP:
		@mkdir -p LOG
		clang++ $(MAP_SRCS) $(CPPFLAGS)ft  -o  ft_map.out
		clang++ $(MAP_SRCS) $(CPPFLAGS)std -o std_map.out

RUN_VECTOR:
		@mkdir -p LOG
		./ft_vector.out &> LOG/ft_vector.log
		./std_vector.out &> LOG/std_vector.log
		@echo "diff LOG/ft_vector.log LOG/std_vector.log: ==================="
		@diff LOG/std_vector.log LOG/ft_vector.log
		@echo "=============================================================="
RUN_STACK:
		@mkdir -p LOG
		./ft_stack.out &> LOG/ft_stack.log
		./std_stack.out &> LOG/std_stack.log
		@echo "diff LOG/ft_stack.log LOG/std_stack.log: ====================="
		@diff LOG/std_stack.log LOG/ft_stack.log
		@echo "=============================================================="
RUN_MAP:
		@mkdir -p LOG
		./ft_map.out &> LOG/ft_map.log
		./std_map.out &> LOG/std_map.log
		@echo "diff LOG/ft_map.log LOG/std_map.log: ========================="
		@diff LOG/std_map.log LOG/ft_map.log
		@echo "=============================================================="

clean:
		rm -f LOG/*
fclean:	clean
		rm -rf $(BINS)
		rm -rf LOG

re : fclean all
