# SACA-K

C++ implementation of SACA-K algorithm for linear-time O(1)-workspace suffix sorting for constant alphabets implemented for [Bioinformatics](https://www.fer.unizg.hr/predmet/bio) project on Faculty of Electrical Engineering and Computing, University of Zagreb.

#Installation instructions
Clone the repository and run `run_tests.sh` script. Script will compile needed source files and run tests located in `test_data` directory. For each input test file, suffix array will be created with original Ge Nong's implementation and with this implemetation. Generated output suffix array files will be compared and statistics files will be saved (time and memory performance, input file size).

You can also use this implementation on your own input files - `main.cpp` file is endpoint for generating suffix arrays. If you used testing script, main.cpp will be built into saca_k.out file which you can use for generating suffix arrays of your own input files. Usage: `saca_k.out input_file output_file`. Suffix array is saved as binary int array in output_file location.