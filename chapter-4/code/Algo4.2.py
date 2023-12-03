# -*- coding: utf-8 -*-

import itertools
import typing as t

N: int = int(input())
I: list[tuple[int, int]] = [
    t.cast(
        tuple[int, int],
        tuple(map(int,
                  input().split())),
    ) for _ in range(N)
]

compressed = {
    e: i
    for i, e in enumerate(sorted(set(itertools.chain.from_iterable(I))))
}

imos = [0] * (2 * N + 2)
for left, right in I:
    imos[compressed[left]] += 1
    imos[compressed[right] + 1] -= 1
imos = list(itertools.accumulate(imos))

D = max(imos)

ends: list[int] = [0] * D
ans: list[list[str]] = [[] for _ in range(D)]

for i in range(N):
    for j in range(D):
        if ends[j] < I[i][0]:
            ends[j] = I[i][1]
            ans[j].append(chr(i + ord('a')))
            break

print(ans)
