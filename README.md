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

Algorithm Templates

| Problem name | Source | Main Algorithm/Data Structure used |
| ------------ | ------ | ---------------------------------- |
| chair-tree | POJ 2104 | Shared-Node Segment Trees |
| splay | HDU 3487 | Splay Trees |
| lct | HDU 2475 | Link/cut Trees |
| sa | UOJ 35 | Suffix Array |
| treap | BZOJ 1588 | No-rotate Treap |
| dinic | POJ 1273 | Dinic Algorithm (Max-Flow) |
| state_dp | POJ 1185 | State Compressed Dynamic Programming |
| fft | UOJ 34 | FFT-based Polynomial Multiplication |
| ntt | UOJ 34 | NTT-based (modulo FFT) Polynomial Multiplication |
| machine | UOJ 35 | Suffix Array from Suffix Automaton |

Others

| Problem name |
| ------------ |
| _bzoj_3065 |
| _bzoj_4571 |

To be collected
---------------

| Filename | Problem | Main Algorithm/Data Structure used |
| -------- | ------- | ---------------------------------- |
| spfa.cpp | LG T577 | SPFA |
| manager.cpp | LG P2146 | Heavy Light Decomposition |

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
