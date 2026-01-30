NAME = roucas_cli

CC = cc

CFLAGS = -Wall -Wextra -Werror

INCLUDES = -Iinclude

SRC = src/main.c src/roucas_io.c src/products_utils.c src/product_factory.c \
src/parse_utils.c src/csv_utils.c src/load_products.c src/print_products.c \
src/print_stats.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
