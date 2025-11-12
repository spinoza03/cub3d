CC = cc
CFLAGS = -Wall -Wextra -Werror -g -I include -I minilibx-linux
LDFLAGS = -L minilibx-linux
LDLIBS = -lmlx -lXext -lX11 -lm -lz -lreadline

NAME = cub3d

SRC_PARS = main.c utils/functions.c utils/functions2.c utils/functions3.c \
      gitnext/get_utils.c gitnext/get_lines.c parsing/pars_map.c \
      utils/functions1.c utils/functions4.c utils/ft_strtrim.c \
	  parsing/loading_textures.c validation.c init.c parsing/start_pars.c \
	  parsing/utils.c

SRC_RECAST = recast_badr/recast/init_win.c \
             recast_badr/recast/init_player.c \
             recast_badr/recast/render_3d.c \
			 recast_badr/recast/handle_key.c\
			 recast_badr/recast/draw_player.c\
			 recast_badr/recast/render_3d_utils.c \
			 recast_badr/recast/render_3d_draw.c \

SRC = ${SRC_PARS} ${SRC_RECAST}

OBJ = ${SRC:.c=.o}
HEADER = include/cub.h

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

.PHONY: all clean fclean re
