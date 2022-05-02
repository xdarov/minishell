NAME =				minishell

SRCS =				minishell.c ms_cd.c ms_echo.c ms_env.c ms_unset.c ms_export.c ms_export2.c		\
					w_main.c ms_var.c ms_handler.c ms_exit.c ms_mini.c ms_pars.c ms_pars_fillcom.c	\
					ms_pars_formcom.c ms_pars_utils.c ms_pars_redir.c w_getcmd.c w_runcmd.c
		
OBJ_DIR =			obj

LIB_PATH = 			libft/
				
HEADER =			minishell.h

OBJ =				$(addprefix $(OBJ_DIR)/, $(patsubst %.c, %.o, $(SRCS)))

CC =				gcc

FLAGS =				-g -Wall -Wextra -Werror -I$(HEADER) 

FLAGS_RL =			-I /Users/$(USER)/.brew/opt/readline/include -lreadline

.PHONY:				all clean makelibft fclean re

all:				makelibft $(NAME)

makelibft:			
					@make -C $(LIB_PATH) all

$(NAME):			$(HEADER) $(OBJ)
					$(CC) $(FLAGS) $(FLAGS_RL) $(OBJ) $(LIB_PATH)libft.a -o $(NAME)

$(OBJ_DIR)/%.o:		%.c	$(HEADER)
					@mkdir -p $(OBJ_DIR)
					$(CC) $(FLAGS) -c $< -o $@

clean:
					@rm -rf $(OBJ_DIR)
					@make -C $(LIB_PATH) clean

fclean:				clean
					@$(RM) $(NAME)
					@make -C $(LIB_PATH) fclean

re:					fclean all