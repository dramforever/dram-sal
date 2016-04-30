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
| chair-tree | POJ 2104 | Shared-Node Segment Trees |
| splay | HDU 3487 | Splay Trees |
| lct | HDU 2475 | Link/cut Trees |
| sa | BZOJ 1031 | Suffix Array |
| treap | BZOJ 1588 | No-rotate Treap |
| dinic | POJ 1273 | Dinic Algorithm (Max-Flow) |
| state_dp | POJ 1185 | State Compressed Dynamic Programming |

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

