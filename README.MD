Algo
===============================
This repository contains implementations of various known algorithms from selected fields of algorithm design in computer science, 
mathematics, data mining and etc. A not so unrealistic goal is to have the source code 100% unit tested and a 100% code coverage. 

# Constraints

The algorithms are implemented **only** using the C++ standard library.

The examples in `examples/` may use additional libraries but should not be required when building the library itself.

# Resources

### Documentation 

See the `doc/` folder for documentation.

### Data
For generating and plotting data, the [Orange](https://orange.biolab.si) data mining tool is used. It's super easy to 
output a data set in csv format to play with. The result of the C++ algorithms may then be plotted with the 
same tool. Not a single line of code.

### Unit tests
The C++ code is tested with the [Google Test](https://github.com/google/googletest) framework.

