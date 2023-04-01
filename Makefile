
NAME   = analyser
CFLAGS = -Wall -Wextra -Werror -g -c 
CC     = clang
LFLAGS = -L./libs/libft -lft 

TARGET = src/main.c 

OBJS    = $(addprefix ./dist/,$(TARGET:.c=.o))
LIBFT   = ./dist/libft.a 
OBJ_DIR = dist dist/src 


all: $(NAME)

$(NAME): $(LIBFT) $(OBJS) 
	cp ./libs/libft/libft.a $(LIBFT)
	$(CC) $(OBJS) $(LFLAGS) -o $(NAME)

$(LIBFT): $(OBJ_DIR)
	make -C ./libs/libft

$(OBJ_DIR):
	mkdir $(OBJ_DIR)

dist/%.o: $(TARGET)
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf $(OBJS)
	rm -rf $(OBJ_DIR)

fclean: clean
	rm $(NAME)
	rm -f ./libs/libft/libft.a

re: fclean $(NAME)
