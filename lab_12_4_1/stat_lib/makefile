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

app.exe : $(OUT_DIR)/main.o $(HEADERS) libarr.a
	mkdir -p $(OUT_DIR)
	$(CC) $(OBJS) $< -o $@ -lm -L. -larr

unit_tests.exe : $(UT_OBJS) $(HEADERS) libarr.a
	mkdir -p $(OUT_DIR)
	$(CC) $(UT_OBJS) -o $@ $(CHECK_FLAGS) -L. -larr

unit : unit_tests.exe
	./$<
	
$(OUT_DIR)/check_%.o : $(UNIT_DIR)/check_%.c
	mkdir -p $(OUT_DIR)
	$(CC) $(CFLAGS) -I $(INC_DIR) -c $< -o $@

libarr.a: $(OBJS)
	ar cr libarr.a $^
	ranlib libarr.a

$(OUT_DIR)/main.o: main.c
	mkdir -p $(OUT_DIR)
	$(CC) $(CFLAGS) -I $(INC_DIR) -c $< -o $@

$(OUT_DIR)/%.o : $(SRC_DIR)/%.c 
	mkdir -p $(OUT_DIR)
	$(CC) $(CFLAGS) -I $(INC_DIR) -c $< -o $@

func : app.exe
	./func_tests/scripts/func_tests.sh

debug : CFLAGS += -g3
debug : app.exe

release : app.exe

debug_asan : CFLAGS += -fno-omit-frame-pointer
debug_asan : CC := clang
debug_asan : CC += -fsanitize=address
debug_asan : debug

debug_msan : CFLAGS += -fPIE  -fno-omit-frame-pointer
debug_msan : CC := clang
debug_msan : CC += -fsanitize=memory
debug_msan : debug

debug_ubsan : CFLAGS += -fno-omit-frame-pointer
debug_ubsan : CC := clang
debug_ubsan : CC += -fsanitize=undefined
debug_ubsan : debug

NODEPS := clean
ifeq (0, $(words $(findstring $(MAKECMDGOALS), $(NODEPS))))
	include $(SRCS:.c=.d)
endif


.PHONY : clean coverage
clean : 
	$(RM) -rf ./*.exe ./out ./func_tests/scripts/*.temp ./func_tests/data/*.tmp *.a

coverage : 
	lcov --directory ./out/main.gcda --capture --output-file ./out/coverage_main.info
	lcov --directory ./out/array_tools.gcda --capture --output-file ./out/coverage_array_tools.info
	lcov -a ./out/coverage_main.info -a ./out/coverage_array_tools.info -o ./out/coverage.info
	genhtml ./out/coverage.info --output-directory ./out/html
	xdg-open ./out/html/index.html

go : clean app.exe func coverage
	clean
	app.exe
	func
	coverage
