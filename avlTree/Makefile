# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pmontese <pmontes@student.42madrid.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/08 23:23:47 by pmontese          #+#    #+#              #
#    Updated: 2022/04/01 12:23:28 by pmontese         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Name of the program.
NAME	:= main

# Sources and objects.
HDRS	:=	avlNode.hpp avlTree.hpp 
SRCS	:= #	main.cpp avlTree.cpp avlNode.cpp
OBJS	:= 	$(SRCS:.cpp=.o)

# Define all the compiling flags.
CXX			:= clang++
CXXFLAGS	:= -std=c++98 -Wall -Wextra #-Werror
SANITIZEFLAGS	:= #-g -fsanitize=address
STDFLAG		:= -D STD='"STANDAR"'

# Compile and create everything.
all: $(NAME)

# Compile the program with the objects.
$(NAME): $(OBJS) $(HDRS)
		$(CXX) $(HDRS) $(OBJS) $@

# This won't run if the source files don't exist or are not modified.
%.o: %.cpp %.hpp
		$(CXX) $(CXXFLAGS) $(SANITIZEFLAGS) -o $@ -c $<

# Rule to run the program.
run: all
	$(CXX) $(CXXFLAGS) $(SANITIZEFLAGS) $(SRCS) -o $(NAME)
	./$(NAME)

# Rule to run with the std library
std:
	$(CXX) $(CXXFLAGS) $(SANITIZEFLAGS) $(STDFLAG) $(SRCS) -o $(NAMESTD)

# Rule to remove all the object files.
clean:
		@rm -f $(OBJS)
		@rm -f $(OBJSO)
		@echo "[INFO] Objects removed!"

# Rule to remove everything that has been created by the makefile.
fclean: clean
		@rm -f $(NAME)
		@rm -f $(NAMESTD)
		@echo "[INFO] $(NAME) removed!"

# Rule to re-make everything.
re: fclean all

# Makes sure that gnu make will still run even if files called
# clean / fclean / all and re already exist in the directory
.PHONY: all clean fclean format re
