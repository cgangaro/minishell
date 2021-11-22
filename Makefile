NAME			= minishell

LIBFT			= libft/

SRC				= main.c \
				parsing_1.c \
				parsing_2.c \
				parsing_3.c \
				redirection.c \
				execute_1.c \
				execute_2.c \
				builtin_1.c \
				builtin_2.c
UTL				= minishell_utils.c \
				cmd_utils.c \
				environ_utils.c \
				strarr_utils.c
INC				= minishell.h
OBJ				= $(addprefix $(OBJ_PATH), $(SRC:.c=.o)) $(addprefix $(OBJ_PATH), $(UTL:.c=.o))

SRC_PATH		= src/
UTL_PATH		= src/utils/
INC_PATH		= include/
OBJ_PATH		= obj/
TMP_PATH		= .tmp/

vpath			%.c $(SRC_PATH)
vpath			%.c $(UTL_PATH)
vpath			%.h $(INC_PATH)
vpath			%.h $(LIBFT)$(INC_PATH)
vpath			%.o $(OBJ_PATH)

CC				= gcc -g
IFLAGS			= -I $(INC_PATH) -I $(LIBFT)$(INC_PATH) -I/Users/$(USER)/.brew/opt/readline/include
CFLAGS			= -Wall -Wextra -Werror $(IFLAGS)
LDFLAGS			= -L $(LIBFT) -L /Users/$(USER)/.brew/opt/readline/lib
LDLIBS			= -lft -lreadline

all:			$(LIBFT) $(NAME)

$(LIBFT):
				@$(MAKE) -s -C $(LIBFT)

$(NAME):		$(OBJ)
				@printf '$(BOLD)$(PURPLE)%s$(NORMAL)\n' "Linking program $@ with command:"
				@printf '$(BOLD)$(PURPLE)%s$(NORMAL)\n' "$(LINK.c) [FILES.o] $(LDLIBS) $(OUTPUT_OPTION)"
				@$(LINK.c) $^ $(LDLIBS) $(OUTPUT_OPTION)
				@printf '$(YELLOW)%s$(NORMAL) %s $(GREEN)%s$(NORMAL)\n' "✧" "$@ ..." "OK!"

$(OBJ):			| $(COMP_MSG) $(OBJ_PATH) $(TMP_PATH)

$(OBJ_PATH)%.o:	%.c $(LIBFT)libft.a $(INC)
				@$(COMPILE.c) $< $(OUTPUT_OPTION)
				@printf '$(YELLOW)%s$(NORMAL) %s $(GREEN)%s$(NORMAL)\n' "✧" "$@ ..." "OK!"

$(OBJ_PATH):
				@printf '$(BOLD)$(PURPLE)%s$(NORMAL)\n' "Compiling objects with command:"
				@printf '$(BOLD)$(PURPLE)%s$(NORMAL)\n' "$(CC) $(CFLAGS) -c FILE.c -o FILE.o"
				@mkdir $@

$(TMP_PATH):
				@mkdir $@

clean:
				@$(RM)r $(OBJ_PATH)
				@$(RM)r $(TMP_PATH)
				@$(MAKE) clean -s -C $(LIBFT)

fclean:			clean
				@$(RM) $(NAME)
				@$(MAKE) fclean -s -C $(LIBFT)

re:				fclean all

.PHONY:			all clean fclean re $(LIBFT)

# Output formatting
NORMAL			= $(shell tput sgr0)
BOLD			= $(shell tput bold)
UNDER			= $(shell tput sgr 0)

# Foreground colors
BLACK			= $(shell tput setaf 0)
RED				= $(shell tput setaf 1)
GREEN			= $(shell tput setaf 2)
YELLOW			= $(shell tput setaf 3)
BLUE			= $(shell tput setaf 4)
PURPLE			= $(shell tput setaf 5)
CYAN			= $(shell tput setaf 6)
WHITE			= $(shell tput setaf 7)

# Backgrounds colors
BGREY			= $(shell tput setab 0)
BRED			= $(shell tput setab 0)
BGREEN			= $(shell tput setab 2)
BYELLOW			= $(shell tput setab 3)
BBLUE			= $(shell tput setab 4)
BPURPLE			= $(shell tput setab 5)
BCYAN			= $(shell tput setab 6)
BWHITE			= $(shell tput setab 7)
