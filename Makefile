NAME = codexion

CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread -g

SRCS = main.c $(PARSE) $(UTILS) $(INIT_DATA) $(LOGGING) $(SIMUL)
SRCDIR = coders
PARSE = src/parse_and_validation/parse_args.c \
		src/parse_and_validation/validate_args.c
UTILS = src/utils/ft_isnumber.c \
		src/utils/ft_strisalpha.c \
		src/utils/errors.c
INIT_DATA = src/init_data/init.c \
			src/init_data/init_helpers.c
LOGGING = src/logging/log.c
SIMUL = src/simulation/coder.c \
		src/simulation/dongles.c \
		src/simulation/dongles_more.c \
		src/simulation/state.c \
		src/simulation/state2.c \
		src/simulation/run.c \
		src/simulation/heap.c

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
