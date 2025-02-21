# Compilation
CC					=	cc
CFLAGS				=	-Wall -Wextra -Werror -g -I $(INCLUDES)
RLFLAGS				=	-L/usr/include -lreadline

# Names
NAME				=	minishell

# Sources & Includes
SRCS				= 	srcs/main.c \
						srcs/debug.c \
						srcs/built-ins/ft_cd.c \
						srcs/built-ins/ft_echo.c \
						srcs/built-ins/ft_env.c \
						srcs/built-ins/ft_exit.c \
						srcs/built-ins/ft_export.c \
						srcs/built-ins/ft_pwd.c \
						srcs/built-ins/ft_unset.c \
						srcs/parsing/parsing.c \
						srcs/parsing/ft_list_remove_if.c \
						srcs/tokenizer/ft_newtoken.c \
						srcs/tokenizer/ft_tokenadd_back.c \
						srcs/tokenizer/ft_tokenclear.c \
						srcs/tokenizer/ft_tokencount.c \
						srcs/tokenizer/tokenizer.c \
						srcs/utils/commands_utils.c \
						srcs/utils/data_utils.c \
						srcs/utils/minishell_utils.c \
						srcs/utils/parsing_utils.c	\
						srcs/utils/classic_cmds.c

OBJ_FOLDER			=	objs
LIB					=	libft/libft.a
INCLUDES			=	includes

# Objects
OBJS				=	$(patsubst srcs/%, $(OBJ_FOLDER)/%, $(SRCS:.c=.o))

# Custom Makefile Flags
MAKEFLAGS			+=	--no-print-directory --silent

# Custom Colors
PURPLE				=	\033[1;35m
LIGHT_GREEN			=	\033[1;32m
RESET				=	\033[0m

# Custom messages
EXE_DONE			=	@echo "🎉$(PURPLE) $(NAME) compiled! 🎉$(RESET)\n"
ALL_CLEAN			=	@echo "🧹$(LIGHT_GREEN) Project's objects cleaned! 🧹$(RESET)\n"
ALL_FCLEAN			=	@echo "🧹$(LIGHT_GREEN) Project's objects & Executables cleaned! 🧹$(RESET)\n"

# Rules

all : check_relink

check_relink:
	@if [ ! -d $(OBJ_FOLDER) ]; then \
		mkdir $(OBJ_FOLDER); \
	fi
	@if [ -f $(NAME) ]; then \
		echo '✅$(LIGHT_GREEN) Nothing to be done for "all"! ✅$(RESET)\n'; \
	else \
		$(MAKE) $(NAME); \
	fi

$(NAME): libft $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LIB) $(RLFLAGS) -o $(NAME)
	$(EXE_DONE)

$(OBJ_FOLDER)/%.o: srcs/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

libft : 
	@if [ ! -f $(LIB) ]; then \
        make -C ./libft; \
	fi

clean :
	$(MAKE) clean -C ./libft
	@rm -rf $(OBJ_FOLDER)
	$(ALL_CLEAN)

fclean :
	$(MAKE) fclean -C ./libft
	@rm -f $(NAME)
	@rm -f $(NAME_BONUS)
	@rm -rf $(OBJ_FOLDER)
	$(ALL_FCLEAN)

re : fclean all

f : $(NAME)

.PHONY: all clean fclean re libft f
