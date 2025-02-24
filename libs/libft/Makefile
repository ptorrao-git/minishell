CC				= cc -g
RM				= rm -rf
CFLAGS			= -Wall -Wextra -Werror -fPIC
NAME			= libft.a
LIB_SRCS		= ft_isalpha.c ft_isdigit.c ft_isascii.c ft_isalnum.c ft_strrchr.c \
				  ft_isprint.c ft_tolower.c ft_toupper.c ft_atoi.c ft_atoll.c ft_strncmp.c \
				  ft_strlen.c ft_strlcat.c ft_strlcpy.c ft_strdup.c ft_strchr.c \
				  ft_strnstr.c ft_bzero.c ft_calloc.c ft_memset.c ft_memcmp.c \
				  ft_memchr.c ft_memcpy.c ft_memmove.c ft_putchar_fd.c ft_putstr_fd.c \
				  ft_putendl_fd.c ft_putnbr_fd.c ft_itoa.c ft_substr.c ft_strjoin.c \
				  ft_strtrim.c ft_strmapi.c ft_split.c ft_striteri.c \
				  ft_printf/ft_printf.c ft_printf/ft_hexa.c ft_printf/ft_pointer.c \
				  ft_printf/ft_putchar.c ft_printf/ft_putnbr.c ft_printf/ft_putstr.c \
				  ft_printf/ft_uputnbr.c get_next_line/get_next_line_utils_bonus.c \
				  get_next_line/get_next_line_bonus.c ft_atol.c ft_iswhitespc.c \
				  ft_isquote.c ft_pipe_or_redirect.c ft_putmtr.c ft_putstr.c ft_putchar.c \
				  ft_joinpath.c ft_strcmp.c ft_strclen.c ft_lltoa.c free_join.c

LIB_OBJS 		= $(LIB_SRCS:.c=.o)

all: 			$(NAME)

$(NAME): 		$(LIB_OBJS)
				ar rc $(NAME) $(LIB_OBJS)

clean:
				$(RM) $(LIB_OBJS)

fclean: 		clean
				$(RM) $(NAME)

re: 			clean all

PHONY: all clean fclean re