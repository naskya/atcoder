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

