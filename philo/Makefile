# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tkajanek <tkajanek@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/26 16:33:08 by tkajanek          #+#    #+#              #
#    Updated: 2023/07/28 20:02:07 by tkajanek         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 			= philo
CC 				= cc
CFLAGS 			+= -Wall -Wextra -Werror -pthread -fsanitize=thread
SRC_PATH 		= src/
OBJ_PATH		= obj/
SRCS			= main.c argument_check.c \
				philo_routine.c philo_routine_eating.c \
				executioner_routine.c utils.c
OBJS			= $(SRCS:.c=.o)
SRCS_WITH_PATH	= $(addprefix $(SRC_PATH), $(SRCS))
OBJS_WITH_PATH	= $(addprefix $(OBJ_PATH), $(OBJS))

all: $(NAME)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@mkdir -p $(OBJ_PATH)
	$(CC) -c $< -o $@ -I ./includes/
# $@ specifies the output file name,
# which will be replaced with the name
# of the target ($(OBJ_PATH)%.o)

$(NAME):$(OBJS_WITH_PATH)
	$(CC) $(OBJS_WITH_PATH) -o $(NAME)

clean:
	rm -rf $(OBJ_PATH)

fclean:	clean
	rm -f $(NAME)
	
re:	fclean all

.PHONY: all re clean fclean