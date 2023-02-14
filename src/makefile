CC = g++
NAME = uagenda
SRC = $(wildcard *.cpp)
OBJ = $(SRC:.cpp=.o)
RM = rm

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $^ -o $(NAME)

all: $(NAME)

test: $(NAME)
	bats tests.bats

clean:
	$(RM) -f *~ $(NAME)

oclean:
	$(RM) -f $(OBJ)

fclean: clean oclean

re: clean all
