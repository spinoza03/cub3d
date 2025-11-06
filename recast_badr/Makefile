CC = cc
CFLAGS = -Wall -Wextra -Werror -g -I include -I minilibx-linux
LDFLAGS = -L minilibx-linux
LDLIBS = -lmlx -lXext -lX11 -lm -lz -lreadline

NAME = cub3d

SRC = main.c recast/iniit.c init_var.c recast/init_player.c recast/clear_screen.c \
	recast/rotate_player.c recast/render_3d.c

OBJ = ${SRC:.c=.o}
HEADER = include/cub3d.h

all: ${NAME}

${NAME}: ${OBJ}
	@echo -e "\033[0;32mLinking objects to create ${NAME}...\033[0m"
	${CC} ${OBJ} ${LDFLAGS} ${LDLIBS} -o ${NAME}
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