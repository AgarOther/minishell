# Compilation
CC					=	cc
CFLAGS				=	-Wall -Wextra -Werror -g
RLFLAGS				=	-L/usr/include -lreadline

# Names
NAME				=	minishell

# Sources & Includes
SRCS				= 	srcs/main.c \
						srcs/ft_echo.c

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
