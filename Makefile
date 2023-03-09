NAME		=		socket

SERVER		=		server

CLIENT		=		client

#######################
#	DIR
#######################

SRC_DIR		=		src/

INC_DIR		=		include/

BUILD_DIR	=		.build/

LIBFT_DIR	=		libft/

#######################
#	FILES
#######################

LIBFT		=		$(LIBFT_DIR)libft.a

SRCS_SERVER	=		server.c \

OBJS_SERVER	=		$(addprefix $(BUILD_DIR), $(SRCS_SERVER:.c=.o))

SRCS_CLIENT	=		client.c \

OBJS_CLIENT	=		$(addprefix $(BUILD_DIR), $(SRCS_CLIENT:.c=.o))

SRCS		=		socket_utils.c \

OBJS		=		$(addprefix $(BUILD_DIR), $(SRCS:.c=.o))

DEPS		=		$(OBJS_SERVER:.o=.d) \
					$(OBJS_CLIENT:.o=.d) \
					$(OBJS:.o=.d) \

#######################
#	COMPILATIONS
#######################

CFLAGS		=		-Wall -Werror -Wextra

DFLAGS		=		-MMD -MP

LFLAGS		=		-L $(LIBFT_DIR) -lft

IFLAGS		=		-I $(INC_DIR) -I $(LIBFT_DIR)includes

#######################
#	RULES
#######################


all:				$(LIBFT)
					$(MAKE) $(SERVER)
					$(MAKE) $(CLIENT)

-include			$(DEPS)

$(SERVER):			$(OBJS_SERVER) $(OBJS)
					$(CC) $^ $(LFLAGS) $(CFLAGS) -o $@

$(CLIENT):			$(OBJS_CLIENT) $(OBJS)
					$(CC) $^ $(LFLAGS) $(CFLAGS) -o $@


$(LIBFT):			FORCE
					$(MAKE) all -C $(LIBFT_DIR)

FORCE:

$(BUILD_DIR)%.o:	$(SRC_DIR)%.c
					mkdir -p $(shell dirname $@)
					$(CC) $(CFLAGS) $(DFLAGS) $(IFLAGS) -c $< -o $@

clean:
					$(MAKE) clean -C $(LIBFT_DIR)
					$(RM) $(OBJS_SERVER) $(OBJS_CLIENT) $(DEPS)

fclean:
					$(MAKE) fclean -C $(LIBFT_DIR)
					$(RM) $(OBJS_SERVER) $(OBJS_CLIENT) $(DEPS) $(SERVER) $(CLIENT)

re:					fclean
					$(MAKE)

.PHONY:				all clean fclean re FORCE