CC := gcc

CFLAGS := -std=gnu99 -Werror -Wall -Wvla #-Wcast-align -Wcast-qual -Wconversion -Wenum-compare -Wfloat-equal -Wredundant-decls -Wsign-conversion -Wextra -Wpedantic
CHECK_FLAGS := -lcheck 

OUT_DIR := out
SRC_DIR := src
INC_DIR := inc
UNIT_DIR := unit_tests

FILES := $(subst src/,,$(wildcard src/*.c))  
OBJS := $(patsubst %.c, %.o, $(notdir $(wildcard $(SRC_DIR)/*.c))) 

UT_FILES := $(subst unit_tests/,,$(wildcard unit_tests/*.c))   
UT_OBJS := $(UT_FILES:.c=.o)

UT_OBJS += $(filter-out main.o,$(OBJS))
OBJS := $(addprefix $(OUT_DIR)/,$(OBJS))
UT_OBJS := $(addprefix $(OUT_DIR)/,$(UT_OBJS))

unit_tests.exe : $(UT_OBJS)
	mkdir -p $(OUT_DIR)
	$(CC)  $(CHECK_FLAGS) $(UT_OBJS) -o $@

unit : unit_tests.exe
	./$<

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

.PHONY : clean
clean : 
	$(RM) -rf ./*.exe ./out ./func_tests/scripts/*.temp ./func_tests/data/*.tmp
