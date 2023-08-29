NAME = cub3D
CC = cc  -Wall -Wextra -Werror
RM = rm -f 

SRC= get_next_line/get_next_line.c get_next_line/get_next_line_utils.c main.c parsing/checkmap.c\
	libft/ft_atoi.c libft/ft_isdigit.c graphic/graph.c  graphic/casting.c libft/ft_substr.c libft/ft_strncmp.c \
	graphic/hook.c graphic/render_wall.c graphic/frame_player.c graphic/draw_player_mini_map.c\
	parsing/checkmap1.c parsing/error_message.c parsing/check_identifier.c libft/ft_strtrim.c

OBJ=$(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) ./libft/libmlx42.a -Iinclude -lglfw -L"/Users/$(USER)/.brew/opt/glfw/lib/" -o $@

%.o: %.c cube.h libft/libft.h get_next_line/get_next_line.h
	$(CC) -c $< -o $@

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re : fclean all
