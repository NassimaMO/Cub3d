SRCS_DIR				=	./srcs

MANDATORY_DIR			=	$(SRCS_DIR)/mandatory

BONUS_DIR				=	$(SRCS_DIR)/bonus

OBJS_DIR				=	./objs

LIBFT_DIR				=	$(SRCS_DIR)/libft

LIBFT					=	$(LIBFT_DIR)/libft.a

LIBMLX_DIR				=	$(SRCS_DIR)/mlx

LIBMLX					=	$(LIBMLX_DIR)/libmlx.a

LIBMLX_UTILS_DIR		=	$(SRCS_DIR)/mlx_utils

LIBMLX_UTILS			=	$(LIBMLX_UTILS_DIR)/libmlx_utils.a


INC						=	cub3d.h

INC_BONUS				=	cub3d_bonus.h

INC_DIR					=	./include

INC_FLAG				=	$(addprefix -I,$(INC_DIR) $(LIBMLX_DIR) $(LIBFT_DIR)/include $(LIBMLX_UTILS_DIR))

LINK_FLAG				=	-L$(LIBMLX_UTILS_DIR) -lmlx_utils -lm -L$(LIBFT_DIR) -lft -L$(LIBMLX_DIR) -lmlx -lXext -lX11 -lXrender


COMMON_FILES			=	error.c init.c input.c memory.c parsing.c utils.c

MANDATORY_FILES			=	$(COMMON_FILES) main.c

MANDATORY_SRCS			=	$(addprefix $(MANDATORY_DIR)/,$(MANDATORY_FILES))

BONUS_FILES				=	main_bonus.c 

BONUS_SRCS				=	$(addprefix $(BONUS_DIR)/,$(BONUS_FILES)) $(addprefix $(MANDATORY_DIR)/,$(COMMON_FILES))

CC						= 	gcc

CFLAGS					=	-Wall -Wextra -Werror -g3

ifeq ($(WSL), 1)
CFLAGS += -DWSL_BUILD
endif


MANDATORY_OBJS			=	$(addprefix $(OBJS_DIR)/,$(MANDATORY_FILES:%.c=%.o))

BONUS_OBJS				=	$(addprefix $(OBJS_DIR)/,$(BONUS_FILES:%.c=%.o)) $(addprefix $(OBJS_DIR)/,$(COMMON_FILES:%.c=%.o)) 

NAME					=	cub3d

NAME_BONUS				=	cub3d_b

RM						=	rm -f


all						:		$(NAME)

bonus					:		$(NAME_BONUS)

$(OBJS_DIR)/%.o			:		$(MANDATORY_DIR)/%.c ${INC_DIR}/${INC}
							@mkdir -p $(OBJS_DIR)
							$(CC) $(CFLAGS) $(INC_FLAG) -c $< -o $@

$(OBJS_DIR)/%.o			:		$(BONUS_DIR)/%.c ${INC_DIR}/${INC_BONUS}
							@mkdir -p $(OBJS_DIR)
							$(CC) $(CFLAGS) $(INC_FLAG) -c $< -o $@

$(NAME)					:		$(MANDATORY_OBJS) $(LIBFT) $(LIBMLX) $(LIBMLX_UTILS)
							$(CC) $(CFLAGS) -o $(NAME) $(MANDATORY_OBJS) $(LINK_FLAG)


$(NAME_BONUS)			:		$(BONUS_OBJS) $(LIBFT) $(LIBMLX) $(LIBMLX_UTILS)
							$(CC) $(CFLAGS) -o $(NAME_BONUS) $(BONUS_OBJS) $(LINK_FLAG)


$(LIBFT)				:
							make -C $(LIBFT_DIR)

$(LIBMLX_UTILS)			:
							make -C $(LIBMLX_UTILS_DIR)

$(LIBMLX)				:
							make -C $(LIBMLX_DIR)


norm					:
							@norminette $(INC_DIR)/$(INC)
							@norminette $(INC_DIR)/$(INC_BONUS)
							@make norm -C $(LIBFT_DIR)
							@make norm -C $(LIBMLX_UTILS_DIR)
							@norminette $(MANDATORY_SRCS)
							@norminette $(BONUS_SRCS)

clean					:
							echo "cleaning object files..."
							@$(RM) $(MANDATORY_OBJS)
							@$(RM) $(BONUS_OBJS)
							@make clean -C $(LIBFT_DIR)
							@make clean -C $(LIBMLX_DIR)
							@make clean -C $(LIBMLX_UTILS_DIR)

fclean					:		clean
							echo "cleaning executables..."
							@$(RM) $(NAME)
							@$(RM) $(NAME_BONUS)
							@$(RM) $(LIBFT)
							@$(RM) $(LIBMLX)
							@$(RM) $(LIBMLX_UTILS)
							

re						:		fclean
							make

.PHONY					:	all laptop norm clean fclean re
