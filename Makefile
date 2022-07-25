NAME = ft_containers
SRCS = main.cpp
HEADER = vector.hpp stack.hpp  vector_iterator.hpp reverse_iterator.hpp utils.hpp iterator_traits.hpp map.hpp
OBJ = ${SRCS:.cpp=.o}

RM          = rm -rf
CC          = c++
CFLAGS      = -Wall -Wextra -Werror -std=c++98

%.o: 			%.cpp
				@${CC} ${CFLAGS} -c $< -o $@
				
all:          	${NAME}

$(NAME):        ${OBJ} ${HEADER}
				@$(CC) ${CFLAGS} -o ${NAME} ${OBJ}
				@echo "\x1b[32m 👯‍♀️ Compilation effectuée 👯‍♀️\x1b[0m" 
clean:
				@${RM} ${OBJ}
			   
fclean:			clean
				@${RM} ${OBJ}
				@${RM} ${NAME}
				@echo "\x1b[35m 😈 Tout a été supprimé 😈 \x1b[0m"
				
re:             fclean all
