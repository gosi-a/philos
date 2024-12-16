# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: mstencel <mstencel@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2024/12/03 13:22:25 by mstencel      #+#    #+#                  #
#    Updated: 2024/12/16 12:41:25 by mstencel      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #


RESET = \033[0m
FUCHSIA = \033[35m
B_FUCHSIA = \033[1;35m
DARK_GREEN = \033[38;5;82m
GREEN = \033[32m
BRIGHT_CYAN = \033[96m

NAME = philo

SRC_FILES = main.c\
			checks.c\
			clean_bye.c\
			init.c\
			parse.c\
			philos.c\
			time.c\
			utils.c

OBJ_PATH = obj

OBJ_FILES = $(SRC_FILES:%.c=$(OBJ_PATH)/%.o)

HEADER = philo.h

CC = cc

CFLAGS = -Wall -Werror -Wextra
# CFLAGS += -fsanitize=thread -g
THREAD_FLAG = -pthread

RM = rm -f
RD = rm -rf

all: $(NAME)

$(NAME): $(OBJ_FILES) $(HEADER)
	@$(CC) $(OBJ_FILES) $(CFLAGS) $(THREAD_FLAG) -o $(NAME)
	@echo "$(B_FUCHSIA)$(NAME)$(RESET) $(BRIGHT_CYAN)created$(RESET)"

$(OBJ_PATH)/%.o:%.c
	@mkdir -p $(OBJ_PATH)
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@$(RM) $(OBJ_FILES)
	@$(RD) $(OBJ_PATH)
	@echo "$(B_FUCHSIA)obj/*.o$(RESET) $(BRIGHT_CYAN)removed$(RESET)"

fclean: clean
	@$(RM) $(NAME)
	@echo "$(B_FUCHSIA)$(NAME)$(RESET) $(BRIGHT_CYAN)removed$(RESET)"

re: fclean all
	@echo "$(GREEN)***all made again***$(RESET)"

.PHONY: all, clean, fclean, re
