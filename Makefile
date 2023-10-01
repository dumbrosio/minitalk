# Variables
NAME		= minitalk
CC			= gcc
CFLAGS		= -Wall -Wextra -Werror
INCLUDES	= -I./includes/ -I./lib/includes/
SRC_DIR		= ./src/
OBJ_DIR		= ./obj/
LIB_DIR		= ./lib/
LIB_NAME	= lib.a
SRC_FILES	= server.c client.c
OBJ_FILES	= $(SRC_FILES:.c=.o)
SRCS		= $(addprefix $(SRC_DIR), $(SRC_FILES))
OBJS		= $(addprefix $(OBJ_DIR), $(OBJ_FILES))
LIBS		= $(addprefix $(LIB_DIR), $(LIB_NAME))

# Targets
all: $(NAME)

$(NAME): server client $(LIBS)

$(LIBS):
	(cd $(LIB_DIR) && make)

server: $(OBJ_DIR)server.o $(LIBS)
	$(CC) $(CFLAGS) $(OBJ_DIR)server.o -o server  $(INCLUDES) $(LIBS)

client: $(OBJ_DIR)client.o $(LIBS)
	$(CC) $(CFLAGS) $(OBJ_DIR)client.o -o client  $(INCLUDES) $(LIBS)

$(OBJ_DIR)%o: $(SRC_DIR)%c
	$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES)

clean:
	(cd $(LIB_DIR) && make clean)
	rm -f $(OBJS)

fclean: clean
	(cd $(LIB_DIR) && make fclean)
	rm -f server client

re: fclean all

usage:
	@echo "Usage: make [usage | all | minitalk | server | client | clean | fclean | re]"
