NAME =				libft.a

SRCS =				ft_atoi.c ft_bzero.c ft_isalnum.c			\
					ft_isalpha.c ft_isascii.c ft_isdigit.c		\
					ft_isprint.c ft_memchr.c ft_memcpy.c		\
					ft_memset.c ft_strchr.c ft_strlcat.c		\
					ft_strlcpy.c ft_strlen.c ft_strncmp.c		\
					ft_strrchr.c ft_tolower.c ft_toupper.c 		\
					ft_strnstr.c ft_memmove.c ft_calloc.c		\
					ft_memcmp.c ft_strdup.c ft_substr.c			\
					ft_strjoin.c ft_strtrim.c ft_itoa.c			\
					ft_split.c ft_putchar_fd.c ft_putstr_fd.c	\
					ft_putnbr_fd.c ft_strmapi.c ft_putendl_fd.c	\
					ft_striteri.c ft_modnum.c ft_strjoin_free.c	\
					ft_biggernum.c ft_linecount.c

OBJ_DIR =			obj

SRCS_B =			ft_lstnew.c ft_lstadd_front.c ft_lstsize.c	\
					ft_lstlast.c ft_lstadd_back.c ft_lstmap.c	\
					ft_lstclear.c ft_lstiter.c ft_lstdelone.c

HEADER =			libft.h

OBJ =				$(addprefix $(OBJ_DIR)/, $(patsubst %.c, %.o, $(SRCS)))

OBJ_B =				$(addprefix $(OBJ_DIR)/, $(patsubst %.c, %.o, $(SRCS_B)))

CC =				gcc

CFLAGS =			-Wall -Wextra -Werror -I$(HEADER)

.PHONY:				all clean fclean re bonus

all:				$(NAME)

$(NAME):			$(OBJ) $(OBJ_B) $(HEADER)
					ar rcs $(NAME) $?


$(OBJ_DIR)/%.o:		%.c	$(HEADER)
					@mkdir -p $(OBJ_DIR)
					$(CC) $(FLAGS) -c $< -o $@

bonus:
					@make OBJ="$(OBJ_B)" all

clean:
					@rm -rf $(OBJ_DIR)

fclean:				clean
					@$(RM) $(NAME)

re:					fclean all