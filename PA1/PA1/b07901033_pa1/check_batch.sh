#!/bin/zsh
echo "using $1"

for filename in `ls -r inputs/*.in`; do
    echo "NTUSorting $filename" 
    # echo "./bin/NTU_sort" "$1" "$filename" "outputs/$(basename "$filename").out"
    echo "python3 utility/mycheck.py" "$filename" "outputs/$(basename "$filename").out"
    "python utility/mycheck.py" "$filename" "outputs/$(basename "$filename").out"
    echo "==================================================="
    # echo $(echo "$filename" | sed -e 's/\.[^.]*$//')
    # ./bin/NTU_sort "$1" "$filename" "outputs/$(basename "$filename" .out)"
    # for ((i=0; i<=3; i++)); do
    #     ./MyProgram.exe "$filename" "Logs/$(basename "$filename" .txt)_Log$i.txt"
    # done
done