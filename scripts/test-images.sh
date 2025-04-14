#!/bin/bash

requirement="$1"
tolerance="$2"
threshold="$3"
shift 3
files=("$@")

expected="../expected/$requirement"
output="../screenshots/$requirement"
errors="../errors/$requirement"
errors_file="../errors/$requirement/failed-test-cases"

mkdir -p "$errors"

success=0
total=${#files[@]}

echo ""  > "$errors_file"

for file in "${files[@]}"; do
    echo "Testing $file ..."
    echo "../$expected/$file"
    ./imgcmp "$expected/$file" "$output/$file" -o "$errors/$file" -t "$tolerance" -e "$threshold"
    
    if [[ $? -eq 0 ]]; then
        ((success++))
    else
        echo "$requirement/$file"  >> "$errors_file"
    fi
done

echo ""
echo "Matches: $success/$total"

if [[ $success -eq $total ]]; then
    echo "SUCCESS: All outputs are correct"
    exit 0
else
    failure=$((total - success))
    if [[ $failure -eq 1 ]]; then
        echo "FAILURE: $failure output is incorrect"
    else
        echo "FAILURE: $failure outputs are incorrect"

    fi
    exit $failure
fi