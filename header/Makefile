CXX = clang++
SRC = headers.hpp

COMMON_OPT   = -std=c++17 -stdlib=libc++ -DLOCAL -isystem ../ac-library
DEBUG_OPT    = -O0 -g3 -DDEBUG -D_LIBCPP_DEBUG=1
SANITIZE_OPT = -fsanitize=address,undefined
NDEBUG_OPT   = -O2
PRINT_OPT    = -DDEBUG_PRINT

TARGET_DIR              = precompiled
TARGET_DEBUG_PRINT      = $(TARGET_DIR)/debug_on_print_on/$(SRC).pch
TARGET_DEBUG_NPRINT     = $(TARGET_DIR)/debug_on_print_off/$(SRC).pch
TARGET_NDEBUG_PRINT     = $(TARGET_DIR)/debug_off_print_on/$(SRC).pch
TARGET_NDEBUG_NPRINT    = $(TARGET_DIR)/debug_off_print_off/$(SRC).pch
TARGET_DEBUG_PRINT_NSAN = $(TARGET_DIR)/debug_on_print_on_sanitize_off/$(SRC).pch

TARGETS = $(TARGET_DEBUG_PRINT)	\
		  $(TARGET_DEBUG_NPRINT)	\
		  $(TARGET_NDEBUG_PRINT)	\
		  $(TARGET_NDEBUG_NPRINT)	\
		  $(TARGET_DEBUG_PRINT_NSAN)

.PHONY: clean all

all: $(TARGETS)

clean:
	rm -f $(TARGETS)

$(TARGET_DEBUG_PRINT): $(SRC)
	$(CXX) -o $@ $^ $(COMMON_OPT) $(DEBUG_OPT) $(PRINT_OPT) $(SANITIZE_OPT)

$(TARGET_DEBUG_NPRINT): $(SRC)
	$(CXX) -o $@ $^ $(COMMON_OPT) $(DEBUG_OPT) $(SANITIZE_OPT)

$(TARGET_NDEBUG_PRINT): $(SRC)
	$(CXX) -o $@ $^ $(COMMON_OPT) $(NDEBUG_OPT) $(PRINT_OPT)

$(TARGET_NDEBUG_NPRINT): $(SRC)
	$(CXX) -o $@ $^ $(COMMON_OPT) $(NDEBUG_OPT)

$(TARGET_DEBUG_PRINT_NSAN): $(SRC)
	$(CXX) -o $@ $^ $(COMMON_OPT) $(DEBUG_OPT) $(PRINT_OPT)

