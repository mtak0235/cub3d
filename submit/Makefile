NAME =  cub3D

HEAD = includes

SRCDIR = srcs/

LIB = lib/

FILES = minirt.c

SRCS = $(addprefix $(SRCDIR), $(FILES))

OBJS = ${SRCS:.c=.o}

CC = gcc -g

RM =  rm -rf

CFLAGS = -I $(HEAD) -D NUM_THREADS=$(NUM_THREADS)

FLAGS = -L $(LIB)libft -lft

MACOS_MACRO = -D MACOS

LINUX_MACRO = -D LINUX

MACOS_FLAGS = -L $(LIB)minilibx_opengl_20191021 -lmlx -framework OpenGL -framework AppKit 

LINUX_FLAGS = -L $(LIB)minilibx-linux -lmlx -lm -lX11 -lXext -lbsd

UNAME := $(shell uname)

ifeq ($(UNAME),Darwin)
	NUM_THREADS = $(shell sysctl -n hw.ncpu)
	CFLAGS += $(MACOS_MACRO)
	FLAGS += $(MACOS_FLAGS)
endif
ifeq ($(UNAME),Linux)
	NUM_THREADS = $(shell nproc --all)
	CFLAGS += $(LINUX_MACRO)
	FLAGS += $(LINUX_FLAGS)
endif

all: ${NAME}

${NAME}: ${OBJS}
	make -C $(LIB)libft
	make -C $(LIB)minilibx-linux
	${CC} ${CFLAGS} $(OBJS) $(FLAGS) -o ${NAME}


clean:
	make clean -C $(LIB)libft
	make clean -C $(LIB)minilibx-linux
	${RM} ${OBJS}

fclean: clean
	make fclean -C $(LIB)libft
	${RM} ./${NAME}

re: fclean all

.PHONY: all clean fclean re
