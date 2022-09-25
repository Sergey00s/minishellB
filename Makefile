NAME= mshell
CC = gcc -Wall -Wextra
SRC = fit_operations.c exports.c checkparse.c ft_export.c tokencheck.c main.c utils.c b_in.c unsets.c \
specialsplit.c utilsofutils.c structutils.c char2d.c redirfunc.c redirutils.c echo.c fit_operations2.c \
ft_export2.c structutils2.c utils2.c pwd.c check.c doit.c free.c path.c transactions.c delimutils.c \
exit_func.c stringformat.c preparses.c ft_myexport.c ft_others.c struct_utils.c move.c struct_utils2.c get_utils.c run.c
OBJ = $(SRC:.c=.o)
SETT = -I $(shell echo $(PWD))/lib/readline/include -L $(shell echo $(PWD))/lib/readline/lib -lreadline 
SET = libft
LIBFT= libft/libft.a
LIB = ./lib/.minishell

all: $(LIB) $(NAME) 

$(LIB):
	make -C lib

$(NAME): $(LIBFT) $(OBJ)
	$(CC) -Ims.h $(OBJ) $(SETT) -o $(NAME) $(LIBFT) -lncurses 

libft/libft.a:

$(LIBFT):
	make bonus -C ./libft

%.o : %.c
	$(CC) -c $< -o $@ -I./lib/readline/include

clean:
	rm -rf $(OBJ)

fclean: clean 
	rm -rf $(NAME)

ffclean: fclean
	make fclean -C libft

fffclean: ffclean
	rm -rf ./lib/readline $(LIB)

re: fclean all

.PHONY: all clean fclean re
