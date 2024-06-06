CC = cc
FLAGS = -Wall -Wextra -Werror
RM = rm -rf

LIBFT = libft/libft.a
FT_PRINTF = ft_printf/printf.a

SERVER = server
CLIENT = client

SRC_SERVER = server.c
SRC_CLIENT = client.c

all: $(SERVER) $(CLIENT)

$(LIBFT):
	$(MAKE) -C ./libft

$(FT_PRINTF):
	$(MAKE) -C ./ft_printf

$(SERVER): $(SRC_SERVER) $(LIBFT) $(FT_PRINTF)
	$(CC) $(FLAGS) $(SRC_SERVER) $(LIBFT) $(FT_PRINTF) -o server

$(CLIENT): $(SRC_CLIENT) $(LIBFT) $(FT_PRINTF)
	$(CC) $(FLAGS) $(SRC_CLIENT) $(LIBFT) $(FT_PRINTF) -o client

clean:
	$(MAKE) clean -C ./libft
	$(MAKE) clean -C ./ft_printf

fclean: clean
	$(MAKE) fclean -C ./libft
	$(MAKE) fclean -C ./ft_printf
	$(RM) $(SERVER) $(CLIENT)

re: fclean all

.PHONY: all clean fclean re