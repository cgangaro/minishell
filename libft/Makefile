NAME			= libft.a

SRC				= ft_memset.c ft_bzero.c ft_memcpy.c ft_memccpy.c \
				ft_memmove.c ft_memchr.c ft_memcmp.c \
				ft_strlen.c ft_isalpha.c ft_isdigit.c ft_isalnum.c \
				ft_isascii.c ft_isprint.c ft_toupper.c ft_tolower.c \
				ft_strchr.c ft_strrchr.c ft_strncmp.c ft_strcpy.c ft_strlcpy.c \
				ft_strlcat.c ft_strnstr.c ft_atoi.c \
				ft_calloc.c ft_strdup.c \
				ft_substr.c ft_strjoin.c ft_strtrim.c \
				ft_split.c ft_itoa.c ft_strmapi.c \
				ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
				ft_lstnew.c ft_lstadd_front.c ft_lstsize.c \
				ft_lstlast.c ft_lstadd_back.c ft_lstdelone.c \
				ft_lstclear.c ft_lstiter.c ft_lstmap.c
INC				= libft.h
OBJ				= $(addprefix $(OBJ_PATH), $(SRC:.c=.o))

SRC_PATH		= src/
INC_PATH		= include/
OBJ_PATH		= obj/

vpath			%.c $(SRC_PATH)
vpath			%.h $(INC_PATH)
vpath			%.o $(OBJ_PATH)

CC				= gcc
IFLAGS			= -I $(INC_PATH)
CFLAGS			= -Wall -Wextra -Werror $(IFLAGS)
AR				= ar
ARFLAGS			= -rcs

all:			$(NAME)

$(NAME):		$(OBJ)
				@printf '$(BOLD)$(PURPLE)%s$(NORMAL)\n' "Linking library $@ with command:"
				@printf '$(BOLD)$(PURPLE)%s$(NORMAL)\n' "$(AR) $(ARFLAGS) $@ [FILES.o]"
				@$(AR) $(ARFLAGS) $@ $^
				@printf '$(YELLOW)%s$(NORMAL) %s $(GREEN)%s$(NORMAL)\n' "✧" "$@ ..." "OK!"

$(OBJ):			| $(OBJ_PATH)

$(OBJ_PATH)%.o:	%.c $(INC)
				@$(CC) -c $< -o $@ $(CFLAGS)
				@printf '$(YELLOW)%s$(NORMAL) %s $(GREEN)%s$(NORMAL)\n' "✧" "$@ ..." "OK!"

$(OBJ_PATH):
				@printf '$(BOLD)$(PURPLE)%s$(NORMAL)\n' "Compiling objects with command:"
				@printf '$(BOLD)$(PURPLE)%s$(NORMAL)\n' "$(CC) $(CFLAGS) -c FILE.c -o FILE.o"
				@mkdir $@

clean:
				@$(RM)r $(OBJ_PATH)

fclean:			clean
				@$(RM) $(NAME)

re:				fclean $(NAME)

.PHONY:			all clean fclean re

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
