serial version 

cd serie/
make build
./sudoku-serial file_with_board >../result.txt
../check size_l < result.txt
or
make run, will build and run all tests



parallel version 

cd parallel/
make build
./sudoku-omp file_with_board >../result.txt
../check size_l < result.txt
or
make run, will build and run all tests