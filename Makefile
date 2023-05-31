
FLAGS=-Werror -Wextra -Wall
SERVER=server
SERVER_BONUS=server_bonus
CLIENT_BONUS=client_bonus
CLIENT=client
SRC1=server.c
SRC2=client.c
SRC3=server_bonus.c
SRC4=client_bonus.c
INCLUDES=libft/libft.a

all:
	${MAKE} -C libft/ all
	cc $(FLAGS) $(SRC1) $(INCLUDES) -o $(SERVER)
	cc $(FLAGS) $(SRC2) $(INCLUDES) -o $(CLIENT)

clean:
	${MAKE} -C libft/ clean
	
fclean: clean
	/bin/rm -f $(SERVER) $(CLIENT) #$(SERVER_BONUS) #$(CLIENT_BONUS)
	${MAKE} -C libft/ fclean

re: fclean all

