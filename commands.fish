function contest -d "Prepare for atcoder contests"
    if test (count $argv) -eq 0
        echo "You need to specify the contest id (e.g. abc123)."
        return 1
    end

    if test (count $argv) -ne 1
        echo "You need to pass exatcly one argument."
        return 1
    end

    source ~/workspace/atcoder/venv/bin/activate.fish
    
    atcoder-tools gen $argv
    cd ~/workspace/atcoder/contest/$argv
    nvim .
end


function cx
    clang++                                                                               \
                                                                                          \
    -std=c++17 -stdlib=libc++                                                             \
    -DLOCAL -DDEBUG -DDEBUG_PRINT                                                         \
    -D_LIBCPP_DEBUG_LEVEL=2 -O0 -g3 -fsanitize=address,undefined                          \
    -include-pch ~/workspace/atcoder/header/precompiled/debug_on_print_on/headers.hpp.pch \
                                                                                          \
    -Wall -Wextra -Wcast-qual -Wconversion -Wdisabled-optimization -Wdouble-promotion     \
    -Winit-self -Winvalid-pch -Wmultichar -Wredundant-decls -Wshadow -Wsign-promo         \
    -Wunused-const-variable -Wno-reorder -ferror-limit=1                                  \
                                                                                          \
    -o a main.cpp
end


function cxx
    clang++                                                                                \
                                                                                           \
    -std=c++17 -stdlib=libc++                                                              \
    -DLOCAL -DDEBUG                                                                        \
    -D_LIBCPP_DEBUG_LEVEL=2 -O0 -g3 -fsanitize=address,undefined                           \
    -include-pch ~/workspace/atcoder/header/precompiled/debug_on_print_off/headers.hpp.pch \                                                                                
                                                                                           \
    -Wall -Wextra -Wcast-qual -Wconversion -Wdisabled-optimization -Wdouble-promotion      \
    -Winit-self -Winvalid-pch -Wmultichar -Wredundant-decls -Wshadow -Wsign-promo          \
    -Wunused-const-variable -Wno-reorder -ferror-limit=1                                   \
                                                                                           \
    -o a main.cpp
end


function fx
    clang++                                                                                \
                                                                                           \
    -std=c++17 -stdlib=libc++                                                              \
    -DLOCAL -DDEBUG_PRINT                                                                  \
    -O2                                                                                    \
    -include-pch ~/workspace/atcoder/header/precompiled/debug_off_print_on/headers.hpp.pch \
                                                                                           \
    -Wall -Wextra -Wcast-qual -Wconversion -Wdisabled-optimization -Wdouble-promotion      \
    -Winit-self -Winvalid-pch -Wmultichar -Wredundant-decls -Wshadow -Wsign-promo          \
    -Wunused-const-variable -Wno-reorder -ferror-limit=1                                   \
                                                                                           \
    -o a main.cpp
end


function fxx
    clang++                                                                                 \
                                                                                            \
    -std=c++17 -stdlib=libc++                                                               \
    -DLOCAL                                                                                 \
    -O2                                                                                     \
    -include-pch ~/workspace/atcoder/header/precompiled/debug_off_print_off/headers.hpp.pch \
                                                                                            \
    -Wall -Wextra -Wcast-qual -Wconversion -Wdisabled-optimization -Wdouble-promotion       \
    -Winit-self -Winvalid-pch -Wmultichar -Wredundant-decls -Wshadow -Wsign-promo           \
    -Wunused-const-variable -Wno-reorder -ferror-limit=1                                    \
                                                                                            \
    -o a main.cpp
end

