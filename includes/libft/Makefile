NAME = libft.a

RM = rm -f
CC = cc
AR = ar rcs
CC_FLAGS=-Wall -Wextra -Werror
DIR_SRCS = source/
DIR_INCLUDES = includes/
DIR_BONUS = bonus/

GET_SRCS = $(shell find $(DIR_SRCS))

GET_BONUS = $(shell find $(DIR_BONUS))

FILTER_BONUS = $(filter %.c, $(GET_BONUS))

FILTER_SRCS = $(filter %.c, $(GET_SRCS))

OBJS = $(FILTER_SRCS:.c=.o)

BONUS_OBJS = $(FILTER_BONUS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(AR) $(NAME) $(OBJS)

.c.o:
	$(CC) $(CC_FLAGS) -c $< -o $@ -I $(DIR_INCLUDES)

bonus: $(NAME) $(BONUS_OBJS)
	$(AR) $(NAME) $(BONUS_OBJS)

re: fclean all

clean:
	$(RM) $(OBJS) $(BONUS_OBJS)

fclean: clean
	$(RM) $(NAME)
