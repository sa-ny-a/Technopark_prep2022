TARGET = ./main.out
HDRS_DIR = project/include

SRCS = \
       project/src/main.c \
	   project/src/prime.c \
	   project/src/reverse.c \
       project/src/utils.c

.PHONY: all build rebuild check test clean

all: clean check test

$(TARGET): $(SRCS)
	$(CC) -Wpedantic -Wall -Wextra -Werror -I $(HDRS_DIR) -o $(TARGET) $(CFLAGS) $(SRCS)

build: $(TARGET)

rebuild: clean build

check:
	./run_linters.sh

test: $(TARGET)
	./btests/run.sh $(TARGET)

clean:
	rm -rf $(TARGET)
