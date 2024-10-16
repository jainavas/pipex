LIB = ar rcs
RM = rm -f

CC = cc

RED    = \033[31m
GREEN  = \033[32m
YELLOW = \033[33m
BLUE   = \033[34m
RESET  = \033[0m

CCFLAGS = -Wall -Wextra -Werror -g3

SRC_DIR = src

SRC = pipex.c pipex2.c\

OBJ = $(SRC:.c=.o)

INCLUDE = pipex.h

NAME = pipex

LIBFTA = libft_ext/libft.a

all: mario $(NAME)

%.o: %.c
	@$(CC) $(CCFLAGS) -I/libft/libft.h -I/usr/include -Iminilibx-linux -O3 -c $< -o $@

$(NAME): $(OBJ)
	@cd libft_ext && make
	@$(CC) $(CCFLAGS) $(OBJ) -Ilibft_ext $(LIBFTA) -o $(NAME)
	@echo "$(YELLOW)        ||>>    $(BLUE)pipex $(YELLOW)compiled!!    <<||$(RESET)"

clean:
	@$(RM) $(OBJ)
	@cd libft_ext && make clean

fclean:
	@$(RM) $(NAME) $(OBJ)
	@cd libft_ext && make fclean

re: fclean all

mario:
	@echo "    ░░        ░░    ░░      $(RESET)██████░░      ░░░░    $(RESET)██████      ░░░░  ░░░░░░    ░░  "
	@echo "              ░░          $(RESET)██      ██        ░░  $(RESET)██      ██                      ░░"
	@echo "░░          ░░░░░░      ░░$(RESET)██      ██          ░░$(RESET)██      ██                      ░░"
	@echo "          ░░    ░░    ░░  $(RESET)██        ██      ░░$(RESET)██        ██                      ░░"
	@echo "░░░░░░░░░░░░░░░░    ░░░░    $(RESET)██      ██░░░░░░░░$(RESET)██      ██  ░░░░░░░░░░░░░░░░░░░░░░░░"
	@echo "    ░░░░░░░░░░        ░░      $(RESET)██      ██░░░░$(RESET)██      ██░░  ░░              ░░░░░░░░"
	@echo "  ░░░░░░░░░░              ░░$(RESET)██$(RED)▒▒$(RESET)██      ████      $(RESET)██$(RED)▒▒$(RESET)██              ░░  ░░░░░░░░"
	@echo "  ░░░░░░░░░░    ░░  ░░░░    $(RESET)██$(RED)▒▒▒▒$(RESET)██            $(RESET)██$(RED)▒▒$(RESET)██$(RESET)██            ░░░░░░░░░░░░  "
	@echo "░░░░░░░░░░        ░░░░    $(RESET)██$(RED)▒▒$(RESET)██$(RED)▒▒▒▒$(RESET)██        $(RESET)██$(RED)▒▒▒▒▒▒▒▒$(RESET)██            ░░░░░░░░    "
	@echo "░░░░░░░░░░        ░░░░  ░░$(RESET)██$(RED)▒▒▒▒▒▒▒▒▒▒$(RESET)████████$(RED)▒▒▒▒▒▒▒▒▒▒$(RESET)██  ░░░░░░░░░░  ░░░░  ░░  "
	@echo "  ░░              ░░      $(RESET)██$(RED)▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒$(RESET)██                  ░░    "
	@echo "                        ░░  $(RESET)██$(RED)▒▒▒▒▒▒▒▒$(RESET)████$(RED)▒▒▒▒▒▒$(RESET)████$(RED)▒▒$(RESET)██            ░░  ░░        "
	@echo "        ░░      ░░      ░░░░$(RESET)██$(RESET)████$(RED)▒▒▒▒▒▒▒▒▒▒▒▒▒▒$(RESET)████$(RED)▒▒$(RESET)██░░░░░░    ░░  ░░    ░░    "
	@echo "  ░░    ░░            ░░      $(RESET)████$(RED)▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒$(RESET)████░░          ░░      ░░    ░░"
	@echo "  ░░    ░░░░░░  ░░    ░░░░      ░░$(RESET)████████████████                ░░  ░░  ░░░░    "
	@echo "  ░░    ░░      ░░            ░░░░    $(RESET)██▒▒▒▒██    ░░  ░░░░  ░░    ░░        ░░  ░░"
	@echo "$(RESET)              ░░$(GREEN)████████████████████████████████████████████████████$(RESET)░░░░░░        "
	@echo "$(RESET)        ░░  ░░  $(GREEN)██░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░██$(RESET)░░░░    ░░░░  "
	@echo "$(RESET)        ░░    ░░$(GREEN)██▒▒▒▒▓▓▒▒░░░░░░░░▒▒▒▒▓▓▒▒▒▒▒▒▒▒▓▓▒▒▒▒▒▒▒▒▒▒▓▓▒▒▒▒██$(RESET)              "
	@echo "$(RESET)          ░░░░░░$(GREEN)██░░░░▒▒▒▒░░░░░░░░▒▒░░░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒░░▒▒░░░░░░▒▒██$(RESET)              "
	@echo "$(RESET)            ░░  $(GREEN)██░░░░▓▓▒▒░░░░░░░░▒▒░░░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▓▓░░▓▓░░░░▓▓██$(RESET)        ░░    "
	@echo "$(RESET)  ░░      ░░  ░░$(GREEN)██░░░░▒▒▓▓░░░░░░░░▓▓░░░░▒▒▒▒▒▒▓▓▒▒▒▒▒▒░░▒▒░░░░░░▓▓██$(RESET)        ░░░░░░"
	@echo "$(RESET)      ░░░░  ░░  $(GREEN)██░░░░▒▒▒▒░░░░░░░░▓▓░░░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▓▓░░▓▓░░░░▒▒██$(RESET)        ░░░░  "
	@echo "$(RESET)    ░░░░░░░░  ░░$(GREEN)██░░░░▒▒▒▒░░░░░░░░▒▒░░░░▓▓▒▒▒▒▒▒▒▒▒▒▒▒░░▒▒░░░░░░▓▓██$(RESET)    ░░░░░░░░░░"
	@echo "$(RESET)░░░░░░░░░░      ░░$(GREEN)████████████████████████████████████████████████$(RESET)░░░░  ░░░░░░░░  "
	@echo "$(RESET)░░░░░░░░    ░░    $(GREEN)██░░░░▓▓▓▓▒▒░░░░▓▓░░▓▓▓▓▒▒▒▒▓▓▓▓▓▓▒▒▓▓▓▓░░▓▓░░██$(RESET)░░  ░░░░░░░░░░  "
	@echo "$(RESET)░░░░░░░░          $(GREEN)██░░░░▒▒▒▒▒▒░░░░▒▒░░▓▓▓▓▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▓▓░░░░██$(RESET)      ░░░░░░    "


.PHONY: all clean fclean re