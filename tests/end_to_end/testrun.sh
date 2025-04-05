#!/usr/bin/zsh

run=(*.data)

if [ ${#run[@]} -eq 0 ]; then
    echo "Test data files doesnt exist"
    exit 1
fi

res=(*.out)

if [ ${#run[@]} -ne ${#res[@]} ]; then
    echo "Num of data and answer files not equal"
    exit 1
fi

for i in {1..${#run[@]}}; do
    file="${run[i]}"
    output="${res[i]}"
    echo "testing $file result:"
    ../../build/sieve < "$file"
    echo "Expected result:"
    echo "$(cat $output)"
    echo "-----------------------------"
done
