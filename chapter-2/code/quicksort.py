# -*- coding: utf-8 -*-

from __future__ import annotations

import random
import reprlib
import time
import typing as t


def quicksort(a: list[int]) -> list[int]:
    '''
    Returns a sorted array.

    >>> quicksort([2, 1, 5, 4, 3])
    [1, 2, 3, 4, 5]
    >>> quicksort([5, 4, 3, 2, 1])
    [1, 2, 3, 4, 5]
    >>> quicksort([1, 2, 3, 4, 5])
    [1, 2, 3, 4, 5]
    '''

    if len(a) <= 1:
        return list(a)
    return (quicksort([lt for lt in a[1:] if lt < a[0]]) + a[0:1] +
            quicksort([ge for ge in a[1:] if ge >= a[0]]))


def timeit(func: t.Callable[..., t.Any], *args: t.Any,
           **kwargs: t.Any) -> None:
    '''Prints the execution time of a function.'''

    print('  input :', reprlib.repr(*args, **kwargs))
    start_time = time.perf_counter()
    out = func(*args, **kwargs)
    print('  output:', reprlib.repr(out))
    end_time = time.perf_counter()
    total_time = end_time - start_time
    print(f'  Took {total_time:.4f} seconds')


def main() -> None:

    import sys

    sys.setrecursionlimit(10**7)

    print('Comparison of Quick Sort Speed Based on Different Instances')

    input('> Press enter to continue ...')

    N = 10_000
    a = list(range(N))

    print(f'\n** Random Case 1 ({N=}) **')
    random.shuffle(a)
    timeit(quicksort, a)

    print(f'\n** Random Case 2 ({N=}) **')
    random.shuffle(a)
    timeit(quicksort, a)

    print(f'\n** Worst Case ({N=}) **')
    a.sort()
    timeit(quicksort, a)

    print('\nTask Completed\n')


if __name__ == '__main__':
    main()
