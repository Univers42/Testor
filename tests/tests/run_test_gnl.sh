echo "Compiling the program..."
make

test_files=("basic_file.txt" "empty_file.txt" "no_newline_file.txt" "newline_only_file.txt" 
            "multi_newlines.txt" "long_line_file.txt" "random_data_file.txt" "large_file.txt" 
            "buffer_multiple_file.txt" "special_chars_file.txt")
for tets_file in "${test_files[@]}"
do
    echo "Running test with file: $test_file"
    ./a.out "$test_file"
    echo "--------------";
done
echo "All tests completed!"