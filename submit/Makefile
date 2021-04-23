NAME	= cub3d

LIB = lib/

HEADER	= -I./includes

CFLAG	= #-Wall -Wextra -Werror 

CFLAGS = -D NUM_THREADS=$(NUM_THREADS)

FLAGS = -L $(LIB)libft -lft

MACOS_MACRO = -D MACOS

LINUX_MACRO = -D LINUX

MACOS_FLAGS = -L $(LIB)mlx-mac -lmlx -framework OpenGL -framework AppKit 

LINUX_FLAGS = -L $(LIB)minilibx-linux -lmlx -lm -lX11 -lXext -lbsd


UNAME := $(shell uname)

ifeq ($(UNAME),Darwin)
	NUM_THREADS = $(shell sysctl -n hw.ncpu)
	CFLAGS += $(MACOS_MACRO)
	FLAGS += $(MACOS_FLAGS)
	CHOICE = $(LIB)mlx-mac
endif
ifeq ($(UNAME),Linux)
	NUM_THREADS = $(shell nproc --all)
	CFLAGS += $(LINUX_MACRO)
	FLAGS += $(LINUX_FLAGS)
	CHOICE = minilibx-linux
endif

SRC_NAME = main.c \

SRC_PATH = ./src
SRC = $(addprefix $(SRC_PATH)/, $(SRC_NAME))

OBJ_NAME = $(SRC_NAME:.c=.o)
OBJ_PATH = ./obj
OBJ = $(addprefix $(OBJ_PATH)/, $(OBJ_NAME))

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
	mkdir $(OBJ_PATH) 2> /dev/null || true
	gcc $(CFLAG) $(HEADER) -o $@ -c $<

BSRC_NAME = main_bonus\

BSRC_PATH = ./bonus
BSRC = $(addprefix $(SRC_PATH)/, $(SRC_NAME))

BOBJ_NAME = $(BSRC_NAME:.c=.o)
BOBJ_PATH = ./bobj
BOBJ = $(addprefix $(BOBJ_PATH)/, $(BOBJ_NAME))

$(BOBJ_PATH)/%.o: $(BSRC_PATH)/%.c
	mkdir $(BOBJ_PATH) 2> /dev/null || true
	gcc $(CFLAG) $(HEADER) -o $@ -c $<

all	: ${NAME}

$(NAME)	: $(OBJ)
	make -C $(LIB)libft
	make -C $(LIB)$(CHOICE)
	gcc -o $(NAME) $(OBJ) $(HEADER) $(CFLAGS) $(CFLAG) $(FLAGS)

bonus: $(BOBJ)
	make -C $(LIB)libft
	make -C $(LIB)$(CHOICE)
	gcc -o $(NAME) $(BOBJ) $(HEADER) $(CFLAGS) $(CFLAG) $(FLAGS)

clean	:
	make -C $(LIB)libft clean
	make -C $(LIB)$(CHOICE) clean
	rm -rf $(OBJ_PATH) $(BOBJ_PATH) $(SCREENSHOT)

fclean	: clean
	make -C $(LIB)libft fclean
	rm -rf $(NAME)

re	: fclean all

.PHONY: all clean fclean re