# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fgrea <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/02/20 16:19:36 by fgrea             #+#    #+#              #
#    Updated: 2017/04/25 18:13:50 by fgrea            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all, $(NAME), clean, fclean, re

ifneq ($(shell make -q -C libft; echo $$?), 0)
	.PHONY: libft/libft.a
endif

NAME = wolf3d

NOC=\033[0m
OKC=\033[32m
ERC=\033[31m
WAC=\033[33m

cc = gcc
C_FLAGS = -Wall -Wextra -Werror
FRAM = -framework OpenGL -framework AppKit minilibx_macos/libmlx.a

OBJ_PATH = ./obj/
LFT_PATH = ./libft/
INC_PATH = ./includes/
SRC_PATH = ./srcs/

OBJ_NAME = $(SRC_NAME:.c=.o)
INC_NAME = WOLF3D.h
SRC_NAME = main.c wolf3d_create_map.c wolf3d_thread_set.c \
		   wolf3d_events_capture.c wolf3d_pixel_gestion.c \
		   wolf3d_collisions_detector.c

SRC = $(addprefix $(SRC_PATH),$(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH),$(OBJ_NAME))
INC = $(addprefix -I,$(INC_PATH))

all: $(NAME)

$(NAME): $(OBJ)
			@make -C $(LFT_PATH)
			@$(CC) -o $(NAME) $(FRAM) -L $(LFT_PATH) $(MLX_PATH) -lft $^ -o $@
			@echo "$(OKC)WOLF3D:\tCOMPILED$(NOC)"
			@echo "***************************************"
			@echo "----------------__---------------------"
			@echo "--------------<(o )___.----------------"
			@echo "---------------( ._> /-----------------"
			@echo "----------------\`---'-------C.WC------"
			@echo "***************************************"


$(OBJ_PATH)%.o: $(SRC_PATH)%.c
			@mkdir -p $(OBJ_PATH) 2> /dev/null || true
			@$(CC) $(C_FLAGS) $(INC) -o $@ -c $<

clean:
			@make -C $(LFT_PATH) clean
			@rm -rf $(OBJ_PATH)
			@echo "$(WAC)WOLF3D:\tCLEANING OBJS$(NOC)"
			@echo "***************************************"


fclean: clean
			@make -C $(LFT_PATH) fclean
			@rm -f $(NAME)
			@echo "$(WAC)WOLF3D:\tCOMPILATION TRACES REMOVED$(NOC)"
			@echo "***************************************"


re: fclean
			@$(MAKE) all
