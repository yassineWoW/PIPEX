SRCS = ft_split.c ft_calloc.c ft_strstr.c get_command.c \
		ft_substr.c pipex.c ft_strjoin.c ft_strlen.c main.c \

NAME	=	pipex

CC	=	CC

CFLAGS	=	-Wall -Wextra -Werror

RM	=	rm -f

SRCS_O	=	${SRCS:.c=.o}

all	:	${NAME}

${NAME}	:	${SRCS_O}
			${CC} ${CFLAGS} $? -o $@

clean	:	
	${RM} ${SRCS_O}

fclean	:	clean
			${RM} ${NAME}

re	:	fclean all 


git	:
		git add .	;git commit -m "pipex"; git push

.PHONY	:	clean	fclean