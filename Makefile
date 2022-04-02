TARGET = ./main.out
TARGET_TEST = ./main_test.out
HDRS_DIR = project/include

SRCS = \
		project/src/main.c \
		project/src/utils.c \
		project/src/write_utils.c

SRCS_TEST = \
        project/src/main_test.c \
		project/src/test.c \
		project/src/utils.c \
	    project/src/write_utils.c

.PHONY: all build rebuild check test memtest clean

all: clean check test memtest clean_test test_test memtest_test

$(TARGET): $(SRCS)
	$(CC) -Wpedantic -Wall -Wextra -Werror -I $(HDRS_DIR) -o $(TARGET) $(CFLAGS) $(SRCS)

build: $(TARGET)

rebuild: clean build

check:
	./run_linters.sh

test: $(TARGET)
	./btests/run.sh $(TARGET)

memtest: $(TARGET)
	./btests/run.sh $(TARGET) --memcheck

clean:
	rm -rf $(TARGET) *.dat

$(TARGET): $(SRCS)
	$(CC) -Wpedantic -Wall -Wextra -Werror -I $(HDRS_DIR) -o $(TARGET) $(CFLAGS) $(SRCS)

$(TARGET_TEST): $(SRCS_TEST)
	$(CC) -Wpedantic -Wall -Wextra -Werror -I $(HDRS_DIR) -o $(TARGET_TEST) $(CFLAGS) $(SRCS_TEST)

build_test: $(TARGET_TEST)

test_test: $(TARGET_TEST)
	./btests/run.sh $(TARGET_TEST)

memtest_test: $(TARGET_TEST)
	./btests/run.sh $(TARGET_TEST) --memcheck

clean_test:
	rm -rf $(TARGET_TEST) *.dat

$(TARGET_TEST): $(SRCS_TEST)
	$(CC) -Wpedantic -Wall -Wextra -Werror -I $(HDRS_DIR) -o $(TARGET_TEST) $(CFLAGS) $(SRCS_TEST)