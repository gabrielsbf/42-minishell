NAME = minishell

RM = rm -rf
COMPILER = cc -Wall -Wextra -Werror
BUILD = mkdir builds

DIR_SRCS = srcs/
DIR_INCLUDES = includes/
LIBFT_A = includes/libft/libft.a
DIR_OBJS = builds/

GET_SRCS = $(shell find $(DIR_SRCS))

FILTER_SRCS = $(filter %.c, $(GET_SRCS))

OBJS = $(FILTER_SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT_A)
	$(BUILD) && $(COMPILER) $(OBJS) $(LIBFT_A) -o $(NAME) && find ./srcs -type f -name "*.o" -exec mv {} builds \;

$(LIBFT_A):
	cd includes/libft && make && cd ../..

.c.o:
	$(COMPILER) -c $< -o $@

clean:
	$(RM) $(DIR_OBJS)
	cd includes/libft && make clean && cd ../..

fclean: clean
	$(RM) $(NAME) $(DIR_OBJS) $(LIBFT_A)


re: fclean all
