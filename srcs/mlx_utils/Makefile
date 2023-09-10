SRCS			=	alloc.c \
					font.c \
					free_memory.c \
					get_image.c \
					img_changes_utils.c \
					init.c \
					input.c \
					iter_img.c \
					lst_utils.c \
					merge_changes.c \
					other_changes_func.c \
					pixel.c \
					resize.c \
					transparency.c \
					utils.c

LIB_NAME		=	libmlx_utils.a

LIBMLX_DIR		=	../mlx

LIBFT_DIR		=	../libft

INC_DIR			=	.

INC_FLAG		=	$(addprefix -I,$(INC_DIR) $(LIBMLX_DIR) $(LIBFT_DIR)/include)

INC				=	mlx_utils.h

OBJS_DIR		=	./objs

OBJS			=	 $(addprefix $(OBJS_DIR)/,$(SRCS:%.c=%.o))

CC				=	gcc

CFLAGS			=	-Wall -Wextra -Werror -g3

RM				=	rm -f


all				:		${LIB_NAME}

$(LIBFT)		:
					make -C $(LIBFT_DIR)

${LIB_NAME}		:		${OBJS}	
					ar rcs ${LIB_NAME} ${OBJS}

$(OBJS_DIR)/%.o	:		%.c
					@mkdir -p ${OBJS_DIR}
					${CC} ${CFLAGS} $(INC_FLAG) -c $< -o $@

norm			:
					@norminette ${SRCS}
					@norminette ${INC_DIR}/$(INC)

clean			:
					${RM} ${OBJS}

fclean			:		clean
					${RM} ${LIB_NAME}

re				:		fclean all

.PHONY			:		all clean fclean re