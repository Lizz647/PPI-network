# PPI-network

[toc]

**Welcome! Here we aim to design a C library to help find all-pairs shortest path in PPI-network.** 

**Now version 1.0 are released, come and enjoy our project!**

![488B8486C426324E1802BE26BC85D1FC](/home/lizz02/final/488B8486C426324E1802BE26BC85D1FC.jpg)

-----------------

## Get Start

- All you need to do is clone this repository to your own computer and make the project.
  - `git clone git@github.com:Lizz647/PPI-networks.git`
  - `cd PPI-networks`
  - `make`
- To use our project properly, follow the instructions below:

--------------

### NAME

PPI - create a protein-protein interaction net and analyze the shortest path for all-pair.



### SYNOPSIS

**PPI **[*OPTION*]... [*FILE*]...



### DESCRIPTION

**PPI** helps to find out the strength of the interaction between two protein. Its basic function is to create a protein-protein interaction net using a text file from STRING database and is able to find the shortest path between each pair. 

It provides several algorithms and options for users to get information with executing time as short as possible. There's also an affiliated python program that visualizes the output path in the input net.

### Options

* **-F**, **--Floyd**

  : Use Floyd algorithm. Output the shortest path for all-pair.

* **-D[protein]**, **--Dijkstra=[protein]**

  : Use Dijkstra algorithm. Output the shortest path between [protein] and any other proteins. The default value is the first protein appeared in file.

* **-R[protein1]/[protein2]**

  : Use Dijkstra algorithm. Output only the shortest path between [protein1] and [protein2].

* **-S[protein]**, **--SPFA=[protein]**

  : Use SPFA algorithm. Analogous to **-D/--Dijkstra** in function.

* **-B[protein]**, **--Bellman=[protein]**

  : Use Bellman-Ford algorithm. Analogous to **-D/--Dijkstra** in function.

* **-d[protein]**, **--Dijheap=[protein]**

  : Use a modified Dijkstra algorithm.  Analogous to **-D/--Dijkstra** in function.

* **-s[protein]**, **--starSPFA=[protein]**

  : Use a modified SPFA algorithm.  Analogous to **-D/--Dijkstra** in function.



### EXAMPLES

**./PPI -F miniversion.txt**

: Output the shortest path for all-pair in miniversion.txt

**./PPI -d4932.Q0010 midversion.txt**

: Output the shortest path between 4932.Q0010 and any other proteins in midversion.txt

**./PPI -R4932.Q0010/4932.YKL203C bigversion.txt **

: Output the shortest path between 4932.Q0010 and 4932.YKL203C in bigversion.txt.

### EXIT VALUE

**0**

: Success

**-1**

: not enough arguments

**1**

: invalid option

### BUGS

Unknown

### Copyright

Copyrtight © 2021 Xiao, Yan, Song. This is free software: you are free to change and redistribute it. There is NO WARRANITY, to the extent permitted by law.

---------------------



## Conclusion Remarks

- We are glad to receive precious suggestions from all of you, come and help us improve the project!