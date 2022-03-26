# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pmontese <pmontes@student.42madrid.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/08 23:23:47 by pmontese          #+#    #+#              #
#    Updated: 2022/03/26 18:14:20 by pmontese         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Name of the program.
NAME	:= main

# Sources and objects.
HDRS	:=	containers/vector.hpp containers/vector_it.hpp \
			utils/iterator_traits.hpp utils/reverse_iterator.hpp utils/enable_if.hpp utils/is_integral.hpp

SRCS	:= main.cpp
OBJS	:= $(SRCS:.cpp=.o)

# Define all the compiling flags.
CXX			:= clang++
CXXFLAGS	:= -std=c++98 -Wall -Wextra #-Werror
SANITIZEFLAGS	:= -g -fsanitize=address
STDFLAG		:= -D VECTOR=std::vector

# Compile and create everything.
all: $(NAME)

# Compile the program with the objects.
$(NAME): $(OBJS) $(HDRS)
		@$(CXX) $(OBJS) -o $@

# This won't run if the source files don't exist or are not modified.
%.o: %.cpp %.hpp
		$(CXX) $(CXXFLAGS) $(SANITIZEFLAGS) -o $@ -c $<

# Rule to run the program.
run: re
		./$(NAME)

# Rule to run with the std library
runo: re
		$(CXX) $(CXXFLAGS) $(STDFLAG) main.cpp -o $(NAME)
		./$(NAME)

# Rule to remove all the object files.
clean:
		@rm -f $(OBJS)
		@rm -f $(OBJSO)
		@echo "[INFO] Objects removed!"

# Rule to remove everything that has been created by the makefile.
fclean: clean
		@rm -f $(NAME)
		@rm -f $(NAMEO)
		@echo "[INFO] $(NAME) removed!"

# Rule to re-make everything.
re: fclean all

# Makes sure that gnu make will still run even if files called
# clean / fclean / all and re already exist in the directory
.PHONY: all clean fclean format re
