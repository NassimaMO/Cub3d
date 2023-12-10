OBJS_DIR				=	./objs

LIBFT_DIR				=	../srcs/libft

LIBFT					=	$(LIBFT_DIR)/libft.a

LINK_FLAG				=	-L$(LIBFT_DIR) -lft

INC_DIR					=	./include

INC_FLAG				=	$(addprefix -I,$(LIBFT_DIR)/include)

MANDATORY_FILES			=	main.c

CC						= 	gcc

CFLAGS					=	-Wall -Wextra -Werror -g3

MANDATORY_OBJS			=	$(addprefix $(OBJS_DIR)/,$(MANDATORY_FILES:%.c=%.o))

NAME					=	generator

RM						=	rm -f


all						:	$(NAME)

$(OBJS_DIR)/%.o			:	%.c
							@mkdir -p $(OBJS_DIR)
							$(CC) $(CFLAGS) $(INC_FLAG) -c $< -o $@

$(NAME)					:		$(MANDATORY_OBJS) $(LIBFT)
							$(CC) $(CFLAGS) -o $(NAME) $(MANDATORY_OBJS) $(LINK_FLAG)

$(LIBFT)				:
							make -C $(LIBFT_DIR)

clean					:
							echo "cleaning object files..."
							@$(RM) $(MANDATORY_OBJS)
							@make clean -C $(LIBFT_DIR)

fclean					:		clean
							echo "cleaning executables..."
							@$(RM) $(NAME)
							@$(RM) $(LIBFT)
							

re						:		fclean
							make

.PHONY					:	all clean fclean re
