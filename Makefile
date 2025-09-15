CC = cc
CFLAGS = -Wall -Wextra -Werror -g
NAME = cub3d

SRC = main.c utils/functions.c utils/functions2.c utils/functions3.c gitnext/get_utils.c gitnext/get_lines.c parsing/pars_map.c \
	utils/functions1.c utils/ft_strtrim.c

OBJ = ${SRC:.c=.o}
HEADER = include/cub.h

all: ${NAME}

print_message:
	$(STYLISH_MESSAGE)

${NAME}: ${OBJ}
	@echo -e "\033[0;32mLinking objects to create ${NAME}...\033[0m"
	${CC} ${CFLAGS} ${OBJ} -lreadline -o ${NAME}
	@echo -e "\033[1;32mSuccessfully compiled ${NAME}!\033[0m"

%.o: %.c ${HEADER}
	@echo -e "\033[0;33mCompiling $<...\033[0m"
	${CC} ${CFLAGS} -I include -c $< -o $@

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