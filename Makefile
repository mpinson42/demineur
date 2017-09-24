NAME = demineur

SRC = srcs/main.c srcs/event.c srcs/chr.c srcs/draw.c srcs/lib.c srcs/endel.c srcs/chr2.c srcs/tols.c

FLAGS = -Wall -Wextra -Werror

SRC2 = main.o event.o chr.o draw.o lib.o endel.o chr2.o tols.o

all: $(NAME)

%.o : %.c
	gcc -c -o $@ $^

$(NAME): $(SRC)
	@echo "mpinson" > auteur
	@make -C ./libft all
	@make -C ./minilibx_macos all
	@cp ./minilibx_macos/libmlx.a ./lib
	@cp ./libft/libft.a ./lib
	@gcc   -I ./include/  -L./lib  -lft -lmlx -framework OpenGL -framework AppKit -o $(NAME) $(SRC)
	@afplay musique/enclume.mp3 &


clean:
	@/bin/rm -f $(SRC2)
	@make -C ./libft clean
	@make -C ./minilibx_macos clean
	@afplay musique/destruction.mp3 &

fclean: clean
	@/bin/rm -f $(NAME)
	@make -C ./libft fclean

re: fclean all
