TARGET = ./main.out
TST_TARGET = ./tests.out
VALGRIND_LOG = "valgrind.log"

# Main
HDRS = \
	   project/include

SRCS = \
	   project/src/main.c \
	   project/src/init_operations.c \
	   project/src/basic_operations.c \
	   project/src/math_operations.c \
	   project/src/extra_operations.c \
	   project/src/add_utils.c

# Test
TST_HDRS = \
           project/include \
		   project/tests/include

TST_SRCS = \
           project/src/init_operations.c \
	       project/src/basic_operations.c \
	       project/src/math_operations.c \
	       project/src/extra_operations.c \
		   project/src/add_utils.c \
		   project/tests/src/*.c

.PHONY: all check build test memtest testextra memtestextra rebuild clean

all: clean check build test memtest testextra memtestextra

check:
	./run_linters.sh

build: $(TARGET)

test: $(TST_TARGET)
	$(TST_TARGET)

memtest: $(TST_TARGET)
	./project/tests/memtest.sh ${TST_TARGET}

testextra: $(TST_TARGET)
	$(TST_TARGET) --with-extra

memtestextra: $(TST_TARGET)
	./project/tests/memtest.sh ${TST_TARGET} --with-extra

rebuild: clean build

$(TARGET): $(SRCS)
	$(CC) -Wall -Wextra -Werror $(addprefix -I,$(HDRS)) -o $(TARGET) $(CFLAGS) $(SRCS) -lm

$(TST_TARGET): $(TST_SRCS)
	$(CC) -Wall -Wextra -Werror $(addprefix -I,$(TST_HDRS)) -o $(TST_TARGET) $(CFLAGS) $(TST_SRCS) -lm

clean:
	rm -f $(TARGET) $(TST_TARGET) ${VALGRIND_LOG}
