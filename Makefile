
BINS=	ft_map.out std_map.out ft_vector.out std_vector.out std_stack.out ft_stack.out

VECTOR_SRCS= vector_test.cpp
MAP_SRCS= map_test.cpp
STACK_SRCS= stack_test.cpp

CPPFLAGS= -Wall -Werror -Wextra -std=c++98 -D NAMESPACE=

all:  VECTOR STACK MAP

VECTOR:
		mkdir -p LOG
		clang++ $(VECTOR_SRCS) $(CPPFLAGS)ft  -o  ft_vector.out
		clang++ $(VECTOR_SRCS) $(CPPFLAGS)std -o std_vector.out

STACK:
		clang++ $(STACK_SRCS) $(CPPFLAGS)ft  -o  ft_stack.out
		clang++ $(STACK_SRCS) $(CPPFLAGS)std -o std_stack.out

MAP:
		clang++ $(MAP_SRCS) $(CPPFLAGS)ft  -o  ft_map.out
		clang++ $(MAP_SRCS) $(CPPFLAGS)std -o std_map.out

RUN_VECTOR:
		./ft_vector.out &> LOG/ft_vector
		./std_vector.out &> LOG/std_vector
		@echo "diff LOG/ft_vector LOG/std_vector: ==========================="
		@echo "=============================================================="
		@diff LOG/std_vector LOG/ft_vector
RUN_STACK:
		./ft_stack.out &> LOG/ft_stack
		./std_stack.out &> LOG/std_stack
		@echo "diff LOG/ft_stack LOG/std_stack: ==========================="
		@echo "=============================================================="
		@diff LOG/std_stack LOG/ft_stack
RUN_MAP:
		./ft_map.out &> LOG/ft_map
		./std_map.out &> LOG/std_map
		@echo "diff LOG/ft_map LOG/std_map: ==========================="
		@echo "=============================================================="
		@diff LOG/std_map LOG/ft_map
fclean:
		rm -rf $(BINS)
		rm -rf LOG/*

re : fclean all
