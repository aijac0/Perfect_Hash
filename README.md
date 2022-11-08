# Abstract
Hash functions are used to map objects to integer indices in a hash table.
While an optimal hash function will map each possible object to a unique index, 
hash tables need to handle the instance of two different objects being mapped to the same index, called a collision.
There are many different methods of handling collisions, all of which increase the time to access an element of the hash table.
The goal of this project is to create a hash function that is guaranteed to map different objects to different indices, 
and the method to be used is described below. This would remove the necessity of handling collisions.
Of course, a unique mapping hash function requires that the size of the hash table is greater than or equal to the number of elements stored in the table.

# Method
To create a unique mapping hash function, I am exploring the idea of generating a function that maps input to outputs. In boolean algebra, such a function
can easily be created using sum of product expressions. However, this only applies to boolean variables, where the only value can be 1 or 0. Luckily, both
objects and indices are represented by a series of such boolean variables, called bits. To apply the idea of boolean expression generation to a series of bits,
we will create a series of boolean expressions, each of which computes one of the bits in the integer representing an index. Each expression is calculated by
treating the binary representation of every stored object as input to each bit expression, and creating a sum of product expression to encapsulate the information
needed to map objects to unique indices. Such a method is possible in theory, but the problem is that storing such a series of expressions would require as much
memory as that of the entire hash table. To make this idea practical, I will use methods of optimal boolean expression reduction to create a series of expressions
that uses a manageable amount of memory.
