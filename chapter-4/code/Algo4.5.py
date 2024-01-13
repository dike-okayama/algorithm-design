# -*- coding: utf-8 -*-

import typing as t

INF = 1 << 32

Vertex: t.TypeAlias = int
Edge: t.TypeAlias = tuple[Vertex, Vertex]


def dijkstra(
    G: tuple[
        set[Vertex],  # 頂点集合
        set[Edge],  # 辺集合
    ],
    l: dict[Edge, int],  # 辺の長さ
    s: Vertex,
) -> list[int]:
    """
    グラフ G=(V,E) と 各辺の長さ l 、始点 s を受け取り、始点から各頂点への最短パスの長さを返す。
    """

    # S は確定済みの点の集合
    # 各 u∈S に対して、s からの距離は d(u) として記憶される

    V, E = G
    S = {s}
    d: list[int] = [INF] * len(G)
    d[s] = 0

    while S != V:
        u, v = min(
            [(u, v) for u, v in E if u in S and v not in S],
            key=lambda e: d[e[0]] + l[e],
        )
        S.add(v)
        d[v] = d[u] + l[u, v]

    return d
