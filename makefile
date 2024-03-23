SRCS = ft_split.c ft_calloc.c ft_strstr.c get_command.c \
		ft_substr.c pipex.c ft_strjoin.c ft_strlen.c main.c \

NAME	=	pipex

CC	=	cc

CFLAGS	=	-Wall -Wextra -Werror

SRCS_O	=	${SRCS:.c=.o}

all	:	${NAME}

${NAME}	:	${SRCS_O}
			${CC} ${CFLAGS} $? -o $@

clean	:	
	@rm -f ${SRCS_O}

fclean	:	clean
	@rm -f ${NAME}

re	:	fclean all 

.PHONY	:	clean	fclean