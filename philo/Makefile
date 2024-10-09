# Directories #
SRCDIR = src/
HDRDIR = inc/
# Names #
NAME = philo
# Compiler & Compilation Flags #
COMPILE_OPTIONS =  -g -Werror -Wall -Wextra -pthread
# Detail on lft means including if libft was called blalibft the command would be -lblalibft it is searching for '.a' and '.so' files
TESTFLAGS = -g3
COMPILE_FLAGS = -g3 -Werror -Wall -Wextra -O0 -c
# ADD SEARCHFLAGS FOR LIBFT ,...
# Compiler #
CC = cc
# Source Files #
SRC = $(SRCDIR)clean.c $(SRCDIR)ft_atoi.c $(SRCDIR)init.c $(SRCDIR)main.c $(SRCDIR)monitor.c $(SRCDIR)philo.c $(SRCDIR)sleep.c
HEADERS = $(HDRDIR)philo.h
# Object Files
SRC_OBJ = $(SRC:.c=.o)
BONUS_OBJ = $(BONUS_SRC:.c=.o)

# Targets #
all: $(NAME)	# Compile the entire project including bonus.

$(NAME): $(SRC_OBJ)# Compile mandatory part.
	$(CC) $(COMPILE_OPTIONS) $(SRC_OBJ) -o $(NAME)

exes: $(NAME) clean # Compile all project parts including bonus clean up after compilation.

# Compile .c to .o #
%.o: %.c
	$(CC) $(COMPILE_FLAGS) $^ -o $@

# Checkers, Testers #

# clean, fclean, re
clean:	# Clean project folders, leave executables.
	rm -f $(SRC_OBJ)
	rm -f $(MAIN_OBJ)
	rm -f $(BONUS_OBJ)
	rm -f $(TEST_OBJ)

fclean: clean	# Fully clean project folders.
	rm -f $(NAME) $(BONUS)
	@echo "\"$(NAME)\" deleted"

re: fclean	# Recompile whole project.
	$(MAKE) all

name: # print project name #
	@echo "$(NAME)"

exv: all
	valgrind --leak-check=full --show-leak-kinds=all ./philo

ex: all
	./philo

help:	# Print this helpful message
	@awk 'BEGIN { \
	FS = ":.*#"; printf "Usage:\n\tmake <target>\n\nTargets:\n"; } \
	/^[a-zA-Z_0-9-]+:.*?#/ { \
	printf "%-16s%s\n", $$1, $$2 } ' Makefile
# Syntax for this to work: target:	# Description


.PHONY: all fclean clean re name help ex exv exes
