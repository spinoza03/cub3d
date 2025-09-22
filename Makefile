CC = cc
CFLAGS = -Wall -Wextra -Werror -g -I include
LDFLAGS = -L minilibx-linux
LDLIBS = -lmlx -lXext -lX11 -lm -lz -lreadline

NAME = cub3d

SRC = main.c utils/functions.c utils/functions2.c utils/functions3.c \
      gitnext/get_utils.c gitnext/get_lines.c parsing/pars_map.c \
      utils/functions1.c utils/functions4.c utils/ft_strtrim.c \
    #   recast/init_game.c recast/img_data.c

OBJ = ${SRC:.c=.o}
HEADER = include/cub.h

all: ${NAME}

${NAME}: ${OBJ}
	@echo -e "\033[0;32mLinking objects to create ${NAME}...\033[0m"
	${CC} ${OBJ} -o ${NAME}
	@echo -e "\033[1;32mSuccessfully compiled ${NAME}!\033[0m"

%.o: %.c ${HEADER}
	@echo -e "\033[0;33mCompiling $<...\033[0m"
	${CC} ${CFLAGS} -c $< -o $@

clean:
	@echo -e "\033[0;31mCleaning object files...\033[0m"
	rm -f ${OBJ}
	@echo -e "\033[1;32mObject files cleaned.\033[0m"

fclean: clean
	@echo -e "\033[0;31mCleaning ${NAME} executable...\033[0m"
	rm -f ${NAME}
	@echo -e "\033[1;32m${NAME} executable cleaned.\033[0m"

re: fclean all

.PHONY: clean fclean re
