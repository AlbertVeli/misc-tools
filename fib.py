#!/usr/bin/env python3

import numpy as np

def fib(n):
    """
    Calculate the n-th Fibonacci number using iterative matrix exponentiation.

    Parameters
    ----------
    n : int
        The index of the Fibonacci number to compute, starting from zero.

    Returns
    -------
    int (or object for large numbers)
        The n-th Fibonacci number.

    Notes
    -----
    This function uses the matrix representation of the Fibonacci recurrence relation.

    If dtype is uint64 the function will overflow at n = 94
    since fib(94) = 19740274219868223167 > 2^64 - 1.
    Overcome this by using (the slower) dtype = object if n > 93.
    """
    if n > 93:
        dt = object
    else:
        dt = np.uint64

    m = np.array([[1, 1], [1, 0]], dtype = dt)

    pow_m = np.linalg.matrix_power(m, n)

    return pow_m[0, 1]

# Print the first 100 to see that it actually works
for n in range(100):
    # Right-align n using an f-string
    print(f'{n: >2d}:', fib(n))
