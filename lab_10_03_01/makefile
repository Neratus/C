CC := gcc

CFLAGS := -Werror -Wall -Wextra -Wpedantic -Wcast-align -std=c99 -Wcast-qual -Wconversion -Wenum-compare -Wfloat-equal -Wredundant-decls -Wsign-conversion
CHECK_FLAGS := -lcheck 

SRC := $(wildcard ./*.c)

OBJS := $(filter-out ./check_%.c, $(SRC:.c=.o))

CHECK_OBJS := $(wildcard ./check_*.c:.c=.o)

unit_tests.exe : $(CHECK_OBJS) $(OBJS)
	$(CC) $(CHECK_OBJS) $(OBJS) -o $@ $(CHECK_FLAGS) 

unit : unit_tests.exe
	./$<

./check_%.o : ./check_%.c
	$(CC) $(CFLAGS) -c $< -o $@

./%.o : ./%.c 
	$(CC) $(CFLAGS) -c $< -o $@

NODEPS := clean
ifeq (0, $(words $(findstring $(MAKECMDGOALS), $(NODEPS))))
	include $(SRCS:.c=.d)
endif

.PHONY : clean coverage
clean : 
	$(RM) -rf ./*.exe ./out ./*.o
