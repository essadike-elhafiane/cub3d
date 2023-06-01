NAME = cub
CC = cc 
flg = 
RM = rm -f 


SRC= get_next_linee/get_next_line.c get_next_linee/get_next_line_utils.c main.c parsing/checkmap.c\
	libftt/ft_atoi.c libftt/ft_isdigit.c 

FILES = ft_striteri.c ft_memcmp.c  ft_bzero.c ft_putnbr_fd.c ft_strmapi.c ft_itoa.c \
	ft_putendl_fd.c ft_putchar_fd.c ft_putstr_fd.c ft_strtrim.c ft_strjoin.c ft_strdup.c \
	ft_calloc.c  ft_isalnum.c ft_isalpha.c \
	ft_isascii.c ft_isdigit.c ft_isprint.c \
	ft_memchr.c ft_memset.c ft_memcpy.c \
	ft_strlen.c ft_strncmp.c ft_strlcat.c ft_strlcpy.c ft_atoi.c \
	ft_strchr.c ft_strrchr.c ft_strnstr.c \
	ft_tolower.c ft_toupper.c ft_memmove.c ft_split.c \
	ft_substr.c

B_FILES = ft_lstiter.c ft_lstclear.c ft_lstdelone.c ft_lstlast.c ft_lstsize.c \
	ft_lstadd_back.c ft_lstadd_front.c ft_lstnew.c 

OBJ=$(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $@

%.o: %.c cube.h
	$(CC) -c $< -o $@

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re : fclean all
