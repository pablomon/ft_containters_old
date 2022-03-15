# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pmontese <pmontes@student.42madrid.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/08 23:23:47 by pmontese          #+#    #+#              #
#    Updated: 2022/03/15 18:23:03 by pmontese         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Name of the program.
NAME	:= test

# Name of the executable using std
NAMEO	:= testo

# Sources and objects.
HDRS	:= vector.hpp randIt.hpp
SRCS	:= main.cpp
OBJS	:= $(SRCS:.cpp=.o)

SRCSO	:= maino.cpp
OBJSO	:= $(SRCSO:.cpp=.o)

# Define all the compiling flags.
CXX			:= clang++
CXXFLAGS	:= -std=c++98 -Wall -Wextra #-Werror
SANITIZEFLAGS	:= #-fsanitize=address -g

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

$(NAMEO): $(OBJSO)
		$(CXX) $(CXXFLAGS) $(SRCSO) -o $(NAMEO)
# Rule to run with the std library
runo: $(NAMEO)
		./testo

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