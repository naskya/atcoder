set atcoder_dir ~/workspace/atcoder


function contest -d "Prepare for atcoder contests"
    if test (count $argv) -eq 0
        echo "You need to specify the contest id (e.g. abc123)."
        return 1
    end

    if test (count $argv) -ne 1
        echo "You need to pass exatcly one argument."
        return 1
    end

    source {$atcoder_dir}/venv/bin/activate.fish
    
    atcoder-tools gen $argv
    cd {$atcoder_dir}/contest/$argv
    nvim .
end


function compile_debug_on_print_on
    clang++                                                                               \
                                                                                          \
    -std=c++17 -stdlib=libc++                                                             \
    -DLOCAL -DDEBUG -DDEBUG_PRINT                                                         \
    -D_LIBCPP_DEBUG_LEVEL=2 -O0 -g3 -fsanitize=address,undefined                          \
    -include-pch {$atcoder_dir}/header/precompiled/debug_on_print_on/headers.hpp.pch      \
                                                                                          \
    -Wall -Wextra -Wcast-qual -Wconversion -Wdisabled-optimization -Wdouble-promotion     \
    -Winit-self -Winvalid-pch -Wmultichar -Wredundant-decls -Wshadow -Wsign-promo         \
    -Wunused-const-variable -Wno-reorder -ferror-limit=1 $argv
end


function cx
    compile_debug_on_print_on -o a main.cpp
end


function compile_debug_on_print_off
    clang++                                                                                \
                                                                                           \
    -std=c++17 -stdlib=libc++                                                              \
    -DLOCAL -DDEBUG                                                                        \
    -D_LIBCPP_DEBUG_LEVEL=2 -O0 -g3 -fsanitize=address,undefined                           \
    -include-pch {$atcoder_dir}/header/precompiled/debug_on_print_off/headers.hpp.pch      \
                                                                                           \
    -Wall -Wextra -Wcast-qual -Wconversion -Wdisabled-optimization -Wdouble-promotion      \
    -Winit-self -Winvalid-pch -Wmultichar -Wredundant-decls -Wshadow -Wsign-promo          \
    -Wunused-const-variable -Wno-reorder -ferror-limit=1 $argv
end


function cxx
    compile_debug_on_print_off -o a main.cpp
end


function compile_debug_off_print_on
    clang++                                                                                \
                                                                                           \
    -std=c++17 -stdlib=libc++                                                              \
    -DLOCAL -DDEBUG_PRINT                                                                  \
    -O2                                                                                    \
    -include-pch {$atcoder_dir}/header/precompiled/debug_off_print_on/headers.hpp.pch      \
                                                                                           \
    -Wall -Wextra -Wcast-qual -Wconversion -Wdisabled-optimization -Wdouble-promotion      \
    -Winit-self -Winvalid-pch -Wmultichar -Wredundant-decls -Wshadow -Wsign-promo          \
    -Wunused-const-variable -Wno-reorder -ferror-limit=1 $argv
end


function fx
    compile_debug_off_print_on -o a main.cpp
end


function compile_debug_off_print_off
    clang++                                                                                 \
                                                                                            \
    -std=c++17 -stdlib=libc++                                                               \
    -DLOCAL                                                                                 \
    -O2                                                                                     \
    -include-pch {$atcoder_dir}/header/precompiled/debug_off_print_off/headers.hpp.pch      \
                                                                                            \
    -Wall -Wextra -Wcast-qual -Wconversion -Wdisabled-optimization -Wdouble-promotion       \
    -Winit-self -Winvalid-pch -Wmultichar -Wredundant-decls -Wshadow -Wsign-promo           \
    -Wunused-const-variable -Wno-reorder -ferror-limit=1 $argv
end


function fxx
    compile_debug_off_print_off -o a main.cpp
end


function tgr
    rm -rf g
    mkdir g
    mkdir g/s
    mkdir g/c
    cp main.cpp g/s/main.cpp
    cp main.cpp g/s/naive.cpp
    echo "\n\n---\n\n" > g/s/s.txt
end


function tgu
    cp main.cpp g/s/main.cpp
end


function tg1
    compile_debug_on_print_off -o g/s/main.out g/s/main.cpp
    python3 {$atcoder_dir}/testcase-generator/main.py \
    test ./g/s/main.out                               \
    -i g/s/s.txt -p g/c/ -c $argv
end


function tg2 
    compile_debug_on_print_off -o g/s/main.out g/s/main.cpp
    compile_debug_on_print_off -o g/s/naive.out g/s/naive.cpp
    python3 {$atcoder_dir}/testcase-generator/main.py \
    test ./g/s/main.out ./g/s/naive.out               \
    -i g/s/s.txt -p g/c/ -c $argv
end

