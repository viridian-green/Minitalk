CC = cc
FLAGS = -Wall -Wextra -Werror
RM = rm -rf

SERVER = server
CLIENT = client

SRC_SERVER = server.c
SRC_CLIENT = client.c

all: $(SERVER) $(CLIENT)

$(SERVER): $(SRC_SERVER)
	$(CC) $(FLAGS) $(SRC_SERVER) -o server

$(CLIENT): $(SRC_CLIENT)
	$(CC) $(FLAGS) $(SRC_CLIENT) -o client

clean:


fclean: clean
	$(RM) $(SERVER) $(CLIENT)

re: fclean all

.PHONY: all clean fclean re