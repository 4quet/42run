# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lfourque <lfourque@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/11/04 08:44:51 by lfourque          #+#    #+#              #
#    Updated: 2017/06/06 17:07:27 by lfourque         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC_DIR = src/
INC_DIR = inc/
OBJ_DIR = obj/

NAME = 42run
SRC_FILES = main.cpp\
			App.init.cpp\
			App.input.cpp\
			App.draw.cpp\
			App.cpp\
			GLFW.cpp\
			Shader.cpp\
			Camera.cpp\
			utils.cpp\
			Cube.cpp\
			Plane.cpp\
			Table.cpp\
			TextureManager.cpp\
			Counter.cpp

SRC = $(addprefix $(SRC_DIR), $(SRC_FILES))
OBJ	= $(subst $(SRC_DIR), $(OBJ_DIR), $(SRC:.cpp=.o))

CC = clang++
CFLAGS = -Wall -Wextra -Werror

GLFW_LIB = `pkg-config --libs glfw3`
GLFW_INC = `pkg-config --cflags glfw3`
GLM_INC = inc/glm
FWK = -framework OpenGL -L lib -lSOIL

all: $(NAME)
	@echo "\033[32m•\033[0m $(NAME) ready"

$(NAME): $(OBJ)
	$(CC) -o $(NAME) $(GLFW_LIB) $(FWK) $^

$(OBJ_DIR)%.o: $(SRC_DIR)%.cpp
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -I $(INC_DIR) -I $(GLM_INC) $(GLFW_INC) -I inc/libSOIL -o $@ -c $<

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all re fclean clean
