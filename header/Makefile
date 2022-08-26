CXX = clang++
SRC = headers.hpp

COMMON_OPT = -std=c++17 -stdlib=libc++ -DLOCAL -I ../ac-library
DEBUG_OPT  = -O0 -g -DDEBUG -D_LIBCPP_DEBUG_LEVEL=2 -fsanitize=address,undefined
NDEBUG_OPT = -O2
PRINT_OPT  = -DDEBUG_PRINT

TARGET_DIR           = precompiled
TARGET_DEBUG_PRINT   = $(TARGET_DIR)/debug_on_print_on/$(SRC).gch
TARGET_DEBUG_NPRINT  = $(TARGET_DIR)/debug_on_print_off/$(SRC).gch
TARGET_NDEBUG_PRINT  = $(TARGET_DIR)/debug_off_print_on/$(SRC).gch
TARGET_NDEBUG_NPRINT = $(TARGET_DIR)/debug_off_print_off/$(SRC).gch

TARGETS = $(TARGET_DEBUG_PRINT)   \
		  $(TARGET_DEBUG_NPRINT)  \
		  $(TARGET_NDEBUG_PRINT)  \
		  $(TARGET_NDEBUG_NPRINT)

.PHONY: clean all

all: $(TARGETS)

clean:
	rm -f $(TARGETS)

$(TARGET_DEBUG_PRINT): $(SRC)
	$(CXX) -o $@ $^ $(COMMON_OPT) $(DEBUG_OPT) $(PRINT_OPT)

$(TARGET_DEBUG_NPRINT): $(SRC)
	$(CXX) -o $@ $^ $(COMMON_OPT) $(DEBUG_OPT)

$(TARGET_NDEBUG_PRINT): $(SRC)
	$(CXX) -o $@ $^ $(COMMON_OPT) $(NDEBUG_OPT) $(PRINT_OPT)

$(TARGET_NDEBUG_NPRINT): $(SRC)
	$(CXX) -o $@ $^ $(COMMON_OPT) $(NDEBUG_OPT)

