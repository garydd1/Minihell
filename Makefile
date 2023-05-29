
################################################################################
#                                     CONFIG                                   #
################################################################################

NAME        := minishell
CC        := gcc
DEBUB        := gcc 
FLAGS    := -Wall -Wextra -Werror 
LIBFT = ./libft/libft.a
HEADER = ./minishell.h
RLHEADER = -I "/Users/$(USER)/.brew/opt/readline/include"
OBJ_DIR = ./obj
USER = $(shell whoami)
LIBS = -L "/Users/$(USER)/.brew/opt/readline/lib" -lreadline
################################################################################
#                                 PROGRAM'S SRCS                               #
################################################################################

SRCS        :=      $(wildcard *.c) $(wildcard built-in/*.c) $(wildcard signals/*.c)
                          
OBJS        = $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))

$(OBJ_DIR)/%.o: %.c $(HEADER) 
	@mkdir -p $(@D)
	@$(CC) -c $< -o $@ $(FLAGS) $(RLHEADER)

################################################################################
#                                  Makefile  objs                              #
################################################################################


CLR_RMV		:= \033[0m
RED		    := \033[1;31m
GREEN		:= \033[1;32m
YELLOW		:= \033[1;33m
BLUE		:= \033[1;34m
CYAN 		:= \033[1;36m
RM		    := rm -rf


${NAME}:	${OBJS} $(LIBFT)
			@echo "$(GREEN)Compilation ${CLR_RMV}of ${YELLOW}$(NAME) ${CLR_RMV}..."
			@${CC}  ${OBJS} $(LIBFT) $(LIBS) ${FLAGS} -o ${NAME} 
			@echo "$(GREEN)$(NAME) created[0m ✔️"

$(LIBFT): 
	@echo "Your beloved ${YELLOW}libft..."
	@make -C ./libft

all:		${NAME}

bonus:		all

debug:
	@${DEBUB}  ${OBJS} $(LIBFT) $(LIBS) ${FLAGS} -o debug

clean:
			@ ${RM} $(OBJ_DIR) *.o
			@ echo "$(RED)Deleting $(CYAN)$(NAME) $(CLR_RMV)objs ✔️"

fclean:		clean
			@ ${RM} ${NAME} *.out
			@ echo "$(RED)Deleting $(CYAN)$(NAME) $(CLR_RMV)binary ✔️"
			make fclean -C ./libft

re:			fclean all

.PHONY:		all clean fclean re


