# Compilation
CC					=	cc
CFLAGS				=	-Wall -Wextra -Werror -g
RLFLAGS				=	-L/usr/include -lreadline

# Names
NAME				=	minishell

# Sources & Includes
SRCS				= 	srcs/main.c \
						srcs/ft_echo.c \
						srcs/tokenizer.c \
						srcs/minishell_utils.c \
						srcs/data_utils.c \
						srcs/cmdhelper.c \
						srcs/ft_tokenadd_back.c \
						srcs/ft_newtoken.c \
						srcs/ft_tokenclear.c \
						srcs/debug.c \
						srcs/parsing_utils.c \
						srcs/ft_pwd.c \
						srcs/ft_tokencount.c \
						srcs/parsing.c \
						srcs/ft_env.c \
						srcs/ft_cd.c

OBJ_FOLDER			=	objs
LIB					=	libft/libft.a
INCLUDES			=	includes

# Objects
OBJS				=	$(patsubst srcs/%.c, $(OBJ_FOLDER)/%.o, $(SRCS))

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
	@$(CC) $(CFLAGS) $(OBJS) $(LIB) $(RLFLAGS) -o $(NAME) -I $(INCLUDES)
	$(EXE_DONE)

$(OBJ_FOLDER)/%.o: srcs/%.c
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
