# MPI Calculating Factorial Application

## Task
1. Implement simple MPI application "mpi_factorial" in a way like you write production code (structured code with alignments, comments where needed, etc.).
2. The application calculates factorial of N (N!), N is defined as command line argument.
3. The application calculation is scaled over NP processors passed to utility mpirun:
```
$ mpirun -np <NP> mpi_factorial <N>
```
4. Each proccess instance calculates multiplication of individual 1/NP portion of factorial multipliers.
5. Root instance additianaly multiplies calculated parts from all instances and prints the final result value of N!.
6. Run the application by using:
```
$ mpirun -np 4 mpi_factorial 100
```
and
```
$ mpirun -np 1 mpi_factorial 100
```
7. Send us the application source code, mpirun results, comment about N! results got from mpiruns with different NP parameters.

## Build

Install dependencies:
```
sudo apt install mpich
sudo apt install libgmp-dev
```

Build:
```
mkdir build && cd build
cmake -DCMAKE_BUILD_TYPE=Debug $PATH_TO_SOURCES_ROOT_DIR && make
```

After build `build/bin` directory will contain two executables: `mpi_factorial` conforming Task's conditions and `tests`. The latter is used for running tests on Task's solver implementation and should be used as part of `run_tests.sh` script, which is located in build directory.

`mpi_factorial` also provides an command-line argument `--to-file`, which can be placed after factorial number to write result into a file rather than on output.

Usage example:
```
mpirun -np 4 mpi_factorial 1000 --to-file
```

## Results Analysis
