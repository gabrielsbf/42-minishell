NAME = minishell

RM = rm -rf
COMPILER = cc -Wall -Wextra -Werror

DIR_OBJS = builds/
DIR_SRCS = srcs/
DIR_INCLUDES = includes/
LIBFT_A = includes/libft/libft.a

GET_SRCS = $(shell find $(DIR_SRCS))

PRE-FILTER_SRCS = $(filter %.c, $(GET_SRCS))

FILTER_SRCS = $(filter-out %testing.c, $(PRE-FILTER_SRCS))

OBJS = $(FILTER_SRCS:%.c=$(DIR_OBJS)/%.o)

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT_A) $(DIR_OBJS)
	$(COMPILER) $(OBJS) $(LIBFT_A) -lreadline -o $(NAME)

$(DIR_OBJS):
	mkdir builds

$(LIBFT_A):
	cd includes/libft && make && cd ../..

$(DIR_OBJS)/%.o : %.c
	mkdir -p $(dir $@)
	$(COMPILER) -c $< -o $@

clean:
	$(RM) $(DIR_OBJS)
	cd includes/libft && make clean && cd ../..

fclean: clean
	$(RM) $(NAME) $(DIR_OBJS) $(LIBFT_A)


re: fclean all
