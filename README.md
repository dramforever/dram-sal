dram-sal
========

A library of solutions to programming problems

Hierarchy of files
------------------

- `data`
  - `problem-name`
    - `test-case-name.in`
    - `test-case-name.out`
- `src`
  - `problem-name.cpp`
- `misc`
  - `misc-snippet.cpp`

How to test
-----------

```
cd path/to/repo
mkdir build
cd build
cmake ..
make
ctest
```

Completed
---------

| Problem name | Source | Main Algorithm/Data Structure used |
| ------------ | ------ | ---------------------------------- |
| bip-match | UOJ 78 | Bipartite graph matching with Dinic |
| bzoj_1001 | | Planar Graph Min-Cut by Shortest Path |
| bzoj_2132 | | Min-Cut |
| bzoj_4516 | | Suffix Automaton |
| bzoj_4569 | | Union/find Sets |
| bzoj_4571 | | Chair Trees |
| chair-tree | POJ 2104 | Shared-Node Segment Trees |
| dinic | POJ 1273 | Dinic Algorithm (Max-Flow) |
| fft | UOJ 34 | FFT-based Polynomial Multiplication |
| lct | HDU 2475 | Link/cut Trees |
| machine | UOJ 35 | Suffix Array from Suffix Automaton |
| ntt | UOJ 34 | NTT-based (modulo FFT) Polynomial Multiplication |
| sa | UOJ 35 | Suffix Array |
| splay | HDU 3487 | Splay Trees |
| state_dp | POJ 1185 | State Compressed Dynamic Programming |
| treap | BZOJ 1588 | No-rotate Treap |

License
-------

	       DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE
		       Version 2, December 2004

    Copyright (C) 2004 Sam Hocevar <sam@hocevar.net>

    Everyone is permitted to copy and distribute verbatim or modified
    copies of this license document, and changing it is allowed as long
    as the name is changed.

	       DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE
      TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION

     0. You just DO WHAT THE FUCK YOU WANT TO.
