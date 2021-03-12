# File Utilities
Scripts for quick manipulation of bioinformatics files

## Sam file splitting

* C++ script for splitting a sam alignment file into individual files organized by unique molecular identifier and chromosome
* helpful for parallelizing processes that only rely on info from reads of the same umi_chromosome combination
* paths must currently be changed within the script (will change soon)
