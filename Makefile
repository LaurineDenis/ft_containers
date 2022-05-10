NAME = ft_containers
SRCS = main.cpp

SRCS_NAME = $(addprefix "includes"/, $(SRCS))

OBJ = ${SRCS_NAME:.cpp=.o}
OBJS = $(addprefix "objs"/, $(OBJ))

RM          = rm -rf
CC          = c++
CFLAGS      = -Wall -Wextra -Werror -std=c++98

objs/%.o: 		includes/%.cpp
				@mkdir -p objs
				@${CC} ${CFLAGS} -c $< -o $@
				
all:          	${NAME}

$(NAME):        ${OBJS}
				@$(CC) ${CFLAGS} -o ${NAME} ${OBJS}
				@echo "\x1b[32m 👯‍♀️ Compilation effectuée 👯‍♀️\x1b[0m" 
clean:
				@${RM} objs
			   
fclean:			clean
				@${RM} objs
				@${RM} ${NAME}
				@echo "\x1b[35m 😈 Tout a été supprimé 😈 \x1b[0m"
				
re:             fclean all