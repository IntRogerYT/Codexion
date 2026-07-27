NAME = codexion

CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread -g

SRCS = main.c $(PARSE) $(UTILS) $(INIT_DATA) $(LOGGING)
SRCDIR = src
PARSE = parse_and_validation/parse_args.c \
		parse_and_validation/validate_args.c
UTILS = utils/ft_isnumber.c \
		utils/ft_strisalpha.c \
		utils/errors.c
INIT_DATA = init_data/init.c \
			init_data/init_helpers.c
LOGGING = logging/log.c

OBJDIR = objs
OBJS = $(SRCS:%.c=$(OBJDIR)/%.o)

all: $(NAME)

$(NAME): $(OBJS) coders/main.h Makefile
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -I coders -c $< -o $@

clean:
	rm -rf $(OBJDIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
