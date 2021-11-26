NAME		+= ft_containers

SRCS_DIRS	+= main/

SRCS		+= main.cpp
#SRCS		+= main_vector.cpp
#SRCS		+= main_stack.cpp
SRCS		+= main_map.cpp
SRCS		+= RBnode.class.cpp
SRCS		+= RBtree.class.cpp

vpath %.cpp $(SRCS_DIRS)

HDRS_DIRS	+= ./
HDRS_DIRS	+= vector/
HDRS_DIRS	+= stack/
HDRS_DIRS	+= map/
HDRS_DIRS	+= main/

HDRS		+= vector.hpp
HDRS		+= vector.templatedef.hpp
HDRS		+= vector_iterator.hpp
HDRS		+= iterator_traits.hpp
HDRS		+= reverse_iterator.hpp
HDRS		+= enable_if.hpp
HDRS		+= is_integral.hpp
HDRS		+= equal.hpp
HDRS		+= lexicographical_compare.hpp
HDRS		+= stack.hpp
HDRS		+= map.hpp
HDRS		+= map.templatedef.hpp
HDRS		+= pair.hpp
HDRS		+= RBtree.class.hpp
HDRS		+= RBnode.class.hpp

HDRS		+= main.hpp

vpath %.hpp $(HDRS_DIRS)

OBJS_DIR	= objects/

OBJS		= $(addprefix $(OBJS_DIR), $(SRCS:.cpp=.o))

CXX			= clang++

CXXFLAGS	+= -std=c++98
CXXFLAGS	+= -Wall
CXXFLAGS	+= -Werror
CXXFLAGS	+= -Wextra

CPPFLAGS	+= $(foreach DIR, $(HDRS_DIRS), $(addprefix -I , $(DIR)))

ifeq ($(n), std)
	CPPFLAGS	+= -D NAMESPACE=std
else
	CPPFLAGS	+= -D NAMESPACE=ft
endif

ifeq ($(d), 0)
	CXXFLAGS	+= -Wpadded
	CXXFLAGS	+= -g3
	CXXFLAGS	+= -fsanitize=address,undefined
	LDFLAGS		+= -fsanitize=address,undefined
endif

all:			$(NAME)

$(NAME):		$(OBJS)
				$(CXX) $(LDFLAGS) -o $@ $(OBJS) $(LDLIBS)

$(OBJS_DIR)%.o:	%.cpp
				$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

$(OBJS):		$(HDRS) Makefile | $(OBJS_DIR)

$(OBJS_DIR):
				mkdir $@

clean:
				$(RM) -r $(OBJS_DIR)

fclean:			clean
				$(RM) $(NAME)

re:				fclean all

.PHONY:			all clean fclean re
