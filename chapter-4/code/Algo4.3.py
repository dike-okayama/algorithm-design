# -*- coding: utf-8 -*-

import operator


def earliest_deadline_first_algorithm(
    jobs: list[tuple[int, int]]  # [(d_1, t_1), ...]
) -> list[tuple[int, int]]:
    """Earliest Deadline First Algorithm"""

    jobs = sorted(jobs, key=operator.itemgetter(0))

    schedule: list[tuple[int, int]] = []
    f = 0
    for d, t in jobs:
        f += t
        schedule.append((d, f))

    return schedule


if __name__ == "__main__":
    jobs: list[tuple[int, int]] = [
        (1, 3),
        (2, 5),
        (4, 2),
        (5, 1),
        (6, 4),
    ]  # [(d_1, t_1), ...]
    assert earliest_deadline_first_algorithm(jobs) == [
        (1, 3),
        (2, 8),
        (4, 10),
        (5, 11),
        (6, 15),
    ]
