NAME = push_swap
CC = gcc
CFLAGS = -Wall -Wextra -Werror
LIBFT_DIR = libft
STACKOPS_DIR = stackops

SRCS = pushswap.c \
       utils.c \
	   pushswap_sort_helper.c \
       $(STACKOPS_DIR)/stackops_push.c \
       $(STACKOPS_DIR)/stackops_swap.c \
       $(STACKOPS_DIR)/stackops_rotate.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(MAKE) -C $(LIBFT_DIR)
	$(CC) $(CFLAGS) $(OBJS) -L$(LIBFT_DIR) -lft -lm -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -I$(LIBFT_DIR) -I$(STACKOPS_DIR) -c $< -o $@

clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	rm -f $(OBJS)

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re 