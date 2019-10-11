# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: midrissi <midrissi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/10/09 12:43:35 by midrissi          #+#    #+#              #
#    Updated: 2019/06/21 07:03:01 by tlechien         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
SRC = ft_atoi.c ft_isalnum.c ft_bzero.c ft_isalpha.c \
ft_isascii.c ft_isdigit.c ft_isprint.c ft_itoa.c \
ft_lstadd.c ft_lstdel.c ft_lstdelone.c ft_lstiter.c \
ft_lstmap.c ft_lstnew.c ft_memalloc.c ft_memccpy.c \
ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memdel.c \
ft_memmove.c ft_memset.c ft_putchar.c ft_putchar_fd.c \
ft_putendl.c ft_putendl_fd.c ft_putnbr.c ft_putnbr_fd.c \
ft_putstr.c ft_putstr_fd.c ft_strcat.c ft_strchr.c \
ft_strclr.c ft_strcmp.c ft_strcpy.c ft_strdel.c \
ft_strdup.c ft_strequ.c ft_striter.c ft_striteri.c \
ft_strjoin.c ft_strlcat.c ft_strlen.c ft_strmap.c \
ft_strtrim.c ft_strsplit.c ft_strstr.c ft_strsub.c \
ft_toupper.c ft_strmapi.c ft_strncat.c ft_strncmp.c \
ft_strncpy.c ft_strnequ.c ft_strnew.c ft_strnstr.c \
ft_strrchr.c ft_tolower.c get_next_line.c ft_itoa_base.c \
ft_nputchar.c ft_ftoa.c ft_utoa_base.c ft_count_char.c \
ft_lstpushback.c ft_lstrev.c ft_lstdestroy.c ft_count_words.c ft_printf.c \
numbers.c format_geters.c handlers.c ft_splitdel.c \
ft_abs.c ft_get_color.c ft_percent.c ft_interpolate.c ft_split_count.c \
ft_strcjoin.c ft_strsplitstr.c ft_count_words_str.c ft_lastindexof.c \
ft_indexof.c ft_levenshtein.c ft_substr.c ft_isonly_digit.c ft_strlen2.c \
ft_splitdup.c ft_min.c ft_max.c ft_nlastindexof.c ft_exit.c ft_isspace.c \
ft_strreplace.c

_END			=	\x1b[0m
_BOLD			=	\x1b[1m
_UNDER			=	\x1b[4m
_REV			=	\x1b[7m
_GREY			=	\x1b[30m
_RED			=	\x1b[31m
_GREEN			=	\x1b[32m
_YELLOW			=	\x1b[33m
_BLUE			=	\x1b[34m
_PURPLE			=	\x1b[35m
_CYAN			=	\x1b[36m
_WHITE			=	\x1b[37m
_IGREY			=	\x1b[40m
_IRED			=	\x1b[41m
_IGREEN			=	\x1b[42m
_IYELLOW		=	\x1b[43m
_IBLUE			=	\x1b[44m
_IPURPLE		=	\x1b[45m
_ICYAN			=	\x1b[46m
_IWHITE			=	\x1b[47m
MSG				= $(_BOLD)$(_BLUE)Compiling the libft:$(_END)

OBJPATH			= .obj/
SRCPATH			=	srcs/

SRCS			:= $(SRC:%=$(SRCPATH)%)
OBJ				:= $(SRC:%.c=$(OBJPATH)%.o)

COMP		= gcc
CFLAGS		= -Wall -Wextra -Werror -I./includes -c #-g -v#-fsanitize=address
AR			= ar rcs

LONGEST		?=	$(shell echo $(notdir $(SRCS)) | tr " " "\n" | awk ' { if (\
			length > x ) { x = length; y = $$0 } }END{ print y }' | wc -c)

all: $(NAME)

$(NAME): $(OBJ)
	@echo "\r\033[K$(_BOLD)$(_PURPLE)Making ${NAME}...$(_END)"
	@$(AR) $(NAME) $(OBJ)
	@echo "\r\033[K$(_BOLD)$(_GREEN)${NAME} is ready for use$(_END)"

$(OBJ): $(OBJPATH)%.o: $(SRCPATH)%.c
	@mkdir -p $(OBJPATH)
	@$(COMP) $(CFLAGS) -o $@ $<
	@printf "\r\033[K$(MSG) $(_BOLD)$(_CYAN)%-$(LONGEST)s\$(_END)" $(notdir $<)

clean:
	@rm -rf $(OBJPATH)
	@echo "$(_BOLD)$(_RED)Successfully removed all objects from the libft\
	$(_END)"

fclean: clean
	@rm -f $(NAME)
	@echo "$(_BOLD)$(_RED)Successfully removed ${NAME} from the libft$(_END)"

re: fclean all

.PHONY: all clean fclean re
