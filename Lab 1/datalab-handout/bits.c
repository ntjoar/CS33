/*
 * CS:APP Data Lab
 *
 * Nathan Tjoar 005081232
 *
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:

Replace the "return" statement in each function with one
or more lines of C code that implements the function. Your code
must conform to the following style:

int Funct(arg1, arg2, ...) {
    /* brief description of how your implementation works */
    int var1 = Expr1;
    ...
    int varM = ExprM;
    
    varJ = ExprJ;
    ...
    varN = ExprN;
    return ExprR;
}

Each "Expr" is an expression using ONLY the following:
1. Integer constants 0 through 255 (0xFF), inclusive. You are
not allowed to use big constants such as 0xffffffff.
2. Function arguments and local variables (no global variables).
3. Unary integer operations ! ~
4. Binary integer operations & ^ | + << >>

Some of the problems restrict the set of allowed operators even further.
Each "Expr" may consist of multiple operators. You are not restricted to
one operator per line.

You are expressly forbidden to:
1. Use any control constructs such as if, do, while, for, switch, etc.
2. Define or use any macros.
3. Define any additional functions in this file.
4. Call any functions.
5. Use any other operations, such as &&, ||, -, or ?:
6. Use any form of casting.
7. Use any data type other than int.  This implies that you
cannot use arrays, structs, or unions.

You may assume that your machine:
1. Uses 2s complement, 32-bit representations of integers.
2. Performs right shifts arithmetically.
3. Has unpredictable behavior when shifting an integer by more
than the word size.

EXAMPLES OF ACCEPTABLE CODING STYLE:
/*
 * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
 */
int pow2plus1(int x) {
    /* exploit ability of shifts to compute powers of 2 */
    return (1 << x) + 1;
}

/*
 * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
 */
int pow2plus4(int x) {
    /* exploit ability of shifts to compute powers of 2 */
    int result = (1 << x);
    result += 4;
    return result;
}

FLOATING POINT CODING RULES

For the problems that require you to implent floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants.

You are expressly forbidden to:
1. Define or use any macros.
2. Define any additional functions in this file.
3. Call any functions.
4. Use any form of casting.
5. Use any data type other than int or unsigned.  This means that you
cannot use arrays, structs, or unions.
6. Use any floating point data types, operations, or constants.


NOTES:
1. Use the dlc (data lab checker) compiler (described in the handout) to
check the legality of your solutions.
2. Each function has a maximum number of operators (! ~ & ^ | + << >>)
that you are allowed to use for your implementation of the function.
The max operator count is checked by dlc. Note that '=' is not
counted; you may use as many of these as you want without penalty.
3. Use the btest test harness to check your functions for correctness.
4. Use the BDD checker to formally verify your functions
5. The maximum number of ops for each function is given in the
header comment for each function. If there are any inconsistencies
between the maximum ops in the writeup and in this file, consider
this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 *
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce
 *      the correct answers.
 */


#endif
/*
 * bitParity - returns 1 if x contains an odd number of 0's
 *   Examples: bitParity(5) = 0, bitParity(7) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 4
 */
int bitParity(int x) {
// Split bits and recursively eliminate the bits using XOR values
	int bitsPart1 = x;
	int bitsPart2 = (x >> 16);
	bitsPart1 = (bitsPart1 ^ bitsPart2); // 16-bit comparison
	bitsPart2 = (bitsPart1 >> 8) & 0xFF;
	bitsPart1 = ((bitsPart1 & 0xFF) ^ bitsPart2); // 8-bit comparison
	bitsPart2 = (bitsPart1 >> 4) & 0xF;
	bitsPart1 = ((bitsPart1 & 0xF) ^ bitsPart2); // 4-bit comparison
	bitsPart2 = (bitsPart1 >> 2) & 3;
	bitsPart1 = ((bitsPart1 & 3) ^ bitsPart2); // 2-bit comparison
	bitsPart2 = (bitsPart1 >> 1) & 1;
	bitsPart1 = ((bitsPart1 & 1) ^ bitsPart2); // Final bit comparison
	return bitsPart1;
}
/*
 * rotateRight - Rotate x to the right by n
 *   Can assume that 0 <= n <= 31
 *   Examples: rotateRight(0x87654321,4) = 0x18765432
 *   Legal ops: ~ & ^ | + << >> !
 *   Max ops: 25
 *   Rating: 3
 */
int rotateRight(int x, int n) {
//
	int storedBits = x & ((2 << n) + ~0);
	int movedBits = (x >> n) & ((2 << (32 + (~n))) + ~0);
	storedBits = storedBits << (32 + (~n + 1));
	return storedBits | movedBits;
}
/*
 * byteSwap - swaps the nth byte and the mth byte
 *  Examples: byteSwap(0x12345678, 1, 3) = 0x56341278
 *            byteSwap(0xDEADBEEF, 0, 2) = 0xDEEFBEAD
 *  You may assume that 0 <= n <= 3, 0 <= m <= 3
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 25
 *  Rating: 2
 */
int byteSwap(int x, int n, int m) {
// Get the bits and store them in respective positions and then replace them in the value
	int retVal = 0;
	int swap1 = (x >> (n << 3)) & 0xFF; // Placing bits to swap
	int static1 = (swap1 << (n << 3)); // Getting static bits
	int swap2 = (x >> (m << 3)) & 0xFF; // Placing bits to swap
        int static2 = (swap2 << (m << 3)); // Getting static bits
	swap1 = swap1 << (m << 3);
	swap2 = swap2 << (n << 3);
	retVal = (swap1 | swap2); // Combining bits swapped
	retVal = retVal | (~(static1 | static2) & x); // Adding static bits
	return retVal;
}
/*
 * fitsShort - return 1 if x can be represented as a
 *   16-bit, two's complement integer.
 *   Examples: fitsShort(33000) = 0, fitsShort(-32768) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 1
 */
int fitsShort(int x) {
// Shift left and shift right then compare with the original to see if there is a change possible in the values
    return !(((x << 16) >> 16) ^ x); // Check if we can get it to zero using XOR
}
/*
 * bitAnd - x&y using only ~ and |
 *   Example: bitAnd(6, 5) = 4
 *   Legal ops: ~ |
 *   Max ops: 8
 *   Rating: 1
 */
int bitAnd(int x, int y) {
// Do DeMorgan's law
    return ~((~x) | (~y)); // M51A
}
/*
 * subOK - Determine if can compute x-y without overflow
 *   Example: subOK(0x80000000,0x80000000) = 1,
 *            subOK(0x80000000,0x70000000) = 0,
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3
 */
int subOK(int x, int y) {
// Look at carry and xor with return value
	int res = x + (~y + 1); // Our total
	int result = res ^ x; // Checking results
	int sign = x ^ y; // Getting Carry signage
	
	return !((sign & result) >> 31);
}
/*
 * isGreater - if x > y  then return 1, else return 0
 *   Example: isGreater(4,5) = 0, isGreater(5,4) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isGreater(int x, int y) {
// Get sign operations and check whether signs are equal or not equal
    int signX = x >> 31;
    int signY = y >> 31;
    int equal = (!(signX ^ signY)) & ((~y + x) >> 31); // Check if they  are equal
    int notEqual = signX & !signY; // Check not equal
    return !( equal | notEqual); //  Check if one or the other
}
/*
 * fitsBits - return 1 if x can be represented as an
 *  n-bit, two's complement integer.
 *   1 <= n <= 32
 *   Examples: fitsBits(5,3) = 0, fitsBits(-4,3) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
int fitsBits(int x, int n) {
// Using same logic as the fitsShort, run with shift 32-x
    return !(((x << (32 + (~n + 1)) >> (32 + (~n + 1)))) ^ x); // Look at fits short
}
/*
 * negate - return -x
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int negate(int x) {
// Use integer to negative notation
    return ~x + 1; // M51A
}
/*
 * isTmax - returns 1 if x is the maximum, two's complement number,
 *     and 0 otherwise
 *   Legal ops: ! ~ & ^ | +
 *   Max ops: 10
 *   Rating: 1
 */
int isTmax(int x) {
// Add from x and add that together so that the opposite of our complement will be 1
	int i = x + 1;
 	x = ~(x + i) + !i;
 	return !x; // Use overflow to our advantage
}
