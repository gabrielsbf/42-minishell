NAME = minishell

RM = rm -rf
COMPILER = cc -Wall -Wextra -Werror

DIR_OBJS = builds/
DIR_SRCS = srcs/
DIR_INCLUDES = includes/
LIBFT_A = includes/libft/libft.a

GET_SRCS = $(shell find $(DIR_SRCS))

FILTER_SRCS = $(filter %.c, $(GET_SRCS))

OBJS = $(FILTER_SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT_A) $(DIR_OBJS)
	$(COMPILER) $(OBJS) $(LIBFT_A) -o $(NAME) && find ./srcs -type f -name "*.o" -exec mv {} builds \;
$(DIR_OBJS):
	mkdir builds

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
