# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: juitz <juitz@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/07 18:03:50 by codespace         #+#    #+#              #
#    Updated: 2025/03/08 16:40:30 by juitz            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = RPN

CXX = c++

CXXFLAGS = -Wall -Wextra -Werror -std=c++98

SRCS =	main.cpp\
		RPN.cpp

OBJS = $(SRCS:.cpp=.o)

RM = rm -rf

all: $(NAME)
$(NAME): $(OBJS)
	@$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME)
	@echo "Program ready!"

clean: 
	@$(RM) $(OBJS)
	@echo "Program cleaned successfully!"

fclean: clean
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re