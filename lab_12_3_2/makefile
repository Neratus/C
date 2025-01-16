CC := gcc

CFLAGS := -Werror -Wall -Wextra -Wpedantic -Wcast-align -std=c99 -Wcast-qual -Wconversion -Wenum-compare -Wfloat-equal -Wredundant-decls -Wsign-conversion
CHECK_FLAGS := -lcheck 

OUT_DIR := out
SRC_DIR := src
INC_DIR := inc
UNIT_DIR := unit_tests

FILES := $(subst src/,,$(wildcard src/*.c))   
OBJS := $(FILES:.c=.o)
HEADERS := $(patsubst %.c,$(INC_DIR)/%.h,$(filter-out %main.c,$(FILES)))

UT_FILES := $(subst unit_tests/,,$(wildcard unit_tests/*.c))   
UT_OBJS := $(UT_FILES:.c=.o)

UT_OBJS += $(filter-out main.o,$(OBJS))
OBJS := $(addprefix $(OUT_DIR)/,$(OBJS))
UT_OBJS := $(addprefix $(OUT_DIR)/,$(UT_OBJS))

libarr.so: $(OBJS)
	$(CC) -shared -o $@ $^

unit_tests.exe : $(UT_OBJS) $(HEADERS) libarr.so
	mkdir -p $(OUT_DIR)
	$(CC) $(UT_OBJS) -o $@ $(CHECK_FLAGS) -L. -larr

unit : unit_tests.exe
	./$<

run: libarr.so
	python3 main.py
	
$(OUT_DIR)/check_%.o : $(UNIT_DIR)/check_%.c
	mkdir -p $(OUT_DIR)
	$(CC) $(CFLAGS) -I $(INC_DIR) -c $< -o $@

$(OUT_DIR)/%.o : $(SRC_DIR)/%.c 
	mkdir -p $(OUT_DIR)
	$(CC) $(CFLAGS) -I $(INC_DIR) -c $< -o $@

NODEPS := clean
ifeq (0, $(words $(findstring $(MAKECMDGOALS), $(NODEPS))))
	include $(SRCS:.c=.d)
endif

.PHONY : clean coverage
clean : 
	$(RM) -rf ./*.exe ./out ./func_tests/scripts/*.temp ./func_tests/data/*.tmp ./*.so test


