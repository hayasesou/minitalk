NAME = minitalk
SERVER = server
CLIENT = client
CFLAGS = -Wall -Wextra -Werror 
CC = cc
SRCS = server.c client.c
OBJS = $(SRCS:.c=.o) 

BONUS = ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c\
		ft_lstiter.c ft_lstmap.c

BONUS_OBJS = $(BONUS:.c=.o)

ifdef WITH_BONUS
	OBJS += $(BONUS_OBJS)
endif

all : $(NAME)

$(NAME) : $(OBJS)
	ar rc $(NAME) $(OBJS)

.c.o :
	$(CC) $(CFLAGS) -c $< -o $@

clean :
	rm -f $(OBJS) $(BONUS_OBJS)

fclean : clean
	rm -f $(NAME)

re : fclean all

bonus : 
	make WITH_BONUS=1
