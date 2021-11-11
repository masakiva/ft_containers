NAME		+= ft_containers

SRCS_DIR	+= ./

SRCS		+= main.cpp

vpath %.c $(SRCS_DIR)

HDRS_DIR	= ./

HDRS		+= vector.hpp
HDRS		+= vector.templatedef.hpp

vpath %.h $(HDRS_DIR)

OBJS_DIR	= ./objects/

OBJS		= $(addprefix $(OBJS_DIR), $(SRCS:.cpp=.o))

CXX			= clang++

CXXFLAGS	+= -std=c++98
CXXFLAGS	+= -Wall
CXXFLAGS	+= -Werror
CXXFLAGS	+= -Wextra

CPPFLAGS	+= -I $(HDRS_DIR)

ifeq ($(n), ft)
	CPPFLAGS	+= -D NAMESPACE=ft
else ifeq ($(n), std)
	CPPFLAGS	+= -D NAMESPACE=std
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
