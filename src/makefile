CC = g++
NAME = uagenda
SRC = $(wildcard *.cpp)
RM = rm

$(NAME): $(SRC)
	$(CC) $(CFLAGS) $^ -o $(NAME)

all: $(NAME)

test: $(NAME)
	bats tests.bats

clean:
	$(RM) -f *~ $(NAME)

re: clean all
