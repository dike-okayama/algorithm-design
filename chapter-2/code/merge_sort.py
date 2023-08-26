# -*- coding: utf-8 -*-

from __future__ import annotations

import random
import reprlib
import time
import typing as t


def merge_sort(a: list[int]) -> list[int]:
    '''
    Returns a sorted array.

    >>> merge_sort([2, 1, 5, 4, 3])
    [1, 2, 3, 4, 5]
    >>> merge_sort([5, 4, 3, 2, 1])
    [1, 2, 3, 4, 5]
    >>> merge_sort([1, 2, 3, 4, 5])
    [1, 2, 3, 4, 5]
    '''

    if len(a) == 1:
        return a

    left = merge_sort(a[:len(a) // 2])
    right = merge_sort(a[len(a) // 2:])

    return _merge(left, right)


def _merge(a: list[int], b: list[int]) -> list[int]:

    i = j = 0
    out: list[int] = []

    while i < len(a) and j < len(b):
        if a[i] < b[j]:
            out.append(a[i])
            i += 1
        else:
            out.append(b[j])
            j += 1

    while i < len(a):
        out.append(a[i])
        i += 1

    while j < len(b):
        out.append(b[j])
        j += 1

    return out


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

    print('Running the Merge Sort Algorithm')

    input('> Press enter to continue ...')

    N = 10_000
    a = list(range(N))

    print(f'\n** Random Case 1 ({N=}) **')
    random.shuffle(a)
    timeit(merge_sort, a)

    print(f'\n** Random Case 2 ({N=}) **')
    random.shuffle(a)
    timeit(merge_sort, a)

    print('\nTask Completed\n')


if __name__ == '__main__':
    main()
