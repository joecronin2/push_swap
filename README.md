*This project has been created as part of the 42 curriculum by jcronin*

## Description
This assignment is about sorting, algorithms, and complexity. The goal is to sort an array of integers, passed as an argument to the program. However, this is not a standard sorting exercise; There are significant restrictions on the operations available to sort the problem. 
There are two stacks:
- Stack A: Initially contains the unordered array of integers.
- Stack B: Starts empty.
The program must sort stack A, using only a specific set of permitted operations. These operations include:
- Push: pop from one stack, and push the number to the other stack.
- Rotate: rotates a stack up or down. All numbers are shifted by one element, and the top/bottom number is rotated to the other end of the stack, depending on the direction of the rotation.
- Swap: swap the top 2 numbers on both stacks.
The program displays the operations required to sort the array passed as an argument, separated by newlines.


```push_swap``` can be solved in various ways. I use the 'radix' algorithm. It doesn't produce the most mathematically optimal solution, but is still very reliable and fast. To get the mathematically optimal (or close) solution, a greedy algorithm is needed ('turk sort' seems to be the most common).


### Main algorithm steps
- look at the LSB (Least Significant Bit) of the numbers in stack a, and move all numbers where the LSB is 0 to the other stack. 
- After no numbers remain in stack a with an LSB of zero, all numbers in stack b are pushed back to stack a. 
- Repeat this for every bit, going right to left, from LSB to MSB. 

### Indexing
Because radix operates on the literal bits of the numbers it sorts, negative integers can't be sorted with it because the binary representation of negative integers is different than positive integers. Short explanation: signed negative numbers can have 2 binary representations:

- Sign bit: the simple solution. A single bit in a data type like a number is reserved to determine the sign. For instance, the first bit being 1 can mean that the number is positive, and zero can mean that the number is negative. This approach is intuitive and simple but has some problems. Firstly: zero now has 2 forms: +0 and -0, and both have a differing binary representation. Secondly: arithmetic operations don't work the same. For instance, if the MSB is the sign bit, the addition of +0 and +0 overflows, resulting in the output being 1 (10000000 + 10000000 = 00000001)
- Two's complement fixes both these problems. There's only a single representation for zero, and signed arithmetic operations still work. To turn a positive integer to negative with two's complement, all bits are flipped, and 1 is added. 
Example:
01010101 (85)
10101011 (-85)
As you can see, the binary value of the negative integer is 'greater' than the positive. 

In order to make radix compatible with negative numbers, the initial stack is 'indexed'. This means all numbers in the stack are replaced with the corresponding index each number would occupy in a sorted stack. Example:

```352 93 -59 2 -> 3 2 0 1```

Indexing also potentially makes the algorithm faster in some cases, because the sort has to handle less bits. For instance, take a stack of size 3 of which the largest number is INT_MAX. The resulting number index of this largest number would be just 2, which makes it so the algorithm doesn't need to go over all bits, as only 2 operations are required for each bit (2 = 10).

For an input array of sizes 3 and 5, a different method of sorting is used to ensure a minimal amount of operations.

## Instructions
The project can be compiled with ```make all```, temporary build files removed with ```make clean```, and all compiled binaries are removed with ```make fclean```.

- The program requires an array of valid integers.
- Each integer is to be passed as a separate argument. 
- At least one argument must be provided.
- A valid integer must fall within the range of ```INT_MIN - INT_MAX```, and contain no non-digit characters.
- The array must not contain duplicates.

Example:
```./push_swap 7 3 9 2```

The correctness of the output can be verified with the provided checker as such:

```ARG="8 2 4 0" ; ./push_swap $ARG | ./checker_OS $ARG```

## Resources
I used mainly search engines when needed. The only thing in this project that was new to me was the logic of the radix sort. I questioned LLMs about the process of the radix sort to get an understanding. No AI was used to write, debug, or automate writing code in this project. 
