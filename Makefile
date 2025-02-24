# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ptorrao- <ptorrao-@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/24 16:55:42 by ddias-fe          #+#    #+#              #
#    Updated: 2024/12/10 15:59:07 by ptorrao-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# _______________________________________________________________
#|___________________________[VARIABLES]_________________________|
#|_______________________________________________________________|

CC				= cc -g
RM				= rm -rf
CFLAGS			= -Wall -Wextra -Werror
NAME			= minishell

INC				= -I./include
LIBFT			= libs/libft/libft.a

READLINE_PATH	= vendor/readline/
RLFLAG			= -L$(READLINE_PATH)/lib -lreadline

GENERAL			= main.c
PARSING			= parser.c mini_split.c mini_split_wc.c lexer.c \
				expander.c cmd.c cmd_utils.c syntax_checker_utils.c \
				syntax_checker.c expander_utils.c expander_utils_2.c
UTILS			= init.c init2.c free.c free_process.c utils.c utils2.c
EXECUTOR		= pwd.c cd.c echo.c env.c exec_utils.c exit.c \
				export.c export_utils.c executor.c redirect.c unset.c signals.c \
				heredoc.c cmd_path.c export_parser.c export_executor.c export_utils_2.c \
				executor2.c cd_utils.c redirect_utils.c signals2.c echo_utils.c

# _______________________________________________________________
#|___________________________[SRC FILES]_________________________|
#|_______________________________________________________________|

SRC				= $(GENERAL)\
					$(PARSING)\
					$(UTILS)\
					$(EXECUTOR)\

VPATH 			= src\
					src/parsing\
					src/utils\
					src/executor\
					src/executor/builtins\
					src/executor/builtins/utils\

OBJ_DIR			= obj

OBJ 			= $(SRC:%.c=$(OBJ_DIR)/%.o)

# _______________________________________________________________
#|_____________________________[RULES]___________________________|
#|_______________________________________________________________|

all:			$(NAME)

$(OBJ_DIR):
				mkdir -p obj

$(OBJ_DIR)/%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@ $(INC)

$(NAME):		$(OBJ_DIR) $(OBJ) $(LIBFT)
				$(CC) $(CFLAGS) $(OBJ) $(RLFLAG) $(LIBFT) -o $(NAME)

$(LIBFT):		libs/libft/*.c
				make -C libs/libft
				mv libs/libft/*.o obj/
				mv libs/libft/ft_printf/*.o obj/
				mv libs/libft/get_next_line/*.o obj/

clean:
				$(RM) $(OBJ_DIR) readline.supp

fclean: 		clean
				$(RM) $(NAME)
				$(RM) $(LIBFT)

re: 			fclean all

valgrind: 
	@echo "{\n   leak readline\n   Memcheck:Leak\n...\n   fun:readline\n}\n{\n   leak add_history\n   Memcheck:Leak\n...\n   fun:add_history\n}" > readline.supp
	@valgrind --suppressions=readline.supp --leak-check=full -s --show-leak-kinds=all --track-fds=yes ./$(NAME)

gdb:
	gdb -tui ./$(NAME)

.PHONY: 		all clean fclean re
