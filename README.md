dram-sal ![travis-ci](https://api.travis-ci.org/dramforever/dram-sal.svg)
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

How to run
----------

This is what I do:

```
cd /path/to/repo
stack dbt.hs # Build the dbt builder
dbt <problem-name>
build/<problem-name>/<problem-name>.exe
```

A VSCode tasks.json is provided.

If you don't like this, just run files as you normally would.

Completed
---------

### Algorithm templates

| Problem name | Source | Main Algorithm/Data Structure used |
| ------------ | ------ | ---------------------------------- |
| bip-match | UOJ 78 | Bipartite graph matching with Dinic |
| chair-tree | POJ 2104 | Shared-Node Segment Trees |
| dinic | POJ 1273 | Dinic Algorithm (Max-Flow) |
| fft | UOJ 34 | FFT-based Polynomial Multiplication |
| lct | HDU 2475 | Link/cut Trees |
| machine | UOJ 35 | Suffix Array from Suffix Automaton |
| ntt | UOJ 34 | NTT-based (modulo FFT) Polynomial Multiplication |
| sa | UOJ 35 | Suffix Array |
| splay | HDU 3487 | Splay Trees |
| treap | BZOJ 1588 | No-rotate Treap |
| qtree | SPOJ QTREE | Heavy-light Decomposition |

### Pre-NOIP List

| Problem | Source | Initial Score | Final Score | Algorithm |
| ------- | ------ | ------------- | ----------- | --------- |
| sudoku | NOIP 2009 | 90 | 90 | Brute Force |
| landlords | NOIP 2014 | -- | 100 | Mostly Brute Force |
| mayan | NOIP 2011 | 100 | 100 | Brute Force |
| water | NOIP 2010 | 90 | 100 | Flood Fill + Greedy |
| social | NOI 2007 | -- | -- | Floyd with tracking |
| campfire | NOIP 2009 | 100 | 100 | (Ad-hoc) |

### Other

| Problem | Algorithm used |
| ------- | -------------- |
| bzoj\_1001 | Planar Graph Min-Cut by Shortest Path |
| bzoj\_1003 | Shortest Path, Dynamic Programming |
| bzoj\_1012\_binpart | Binary partitioning |
| bzoj\_1012\_sgt | Segment Trees |
| bzoj\_2132 | Min-Cut |
| bzoj\_2588 | Chair Trees, Repeated Doubling LCA |
| bzoj\_3673 | Union/find Sets over Binary Tree based Persistent Arrays |
| bzoj\_3673 | Union/find Sets over Binary Tree based Persistent Arrays |
| bzoj\_4516 | Suffix Automaton |
| bzoj\_4569 | Union/find Sets |
| bzoj\_4571 | Chair Trees |
| poj\_1185 | State Compressed Dynamic Programming |
| worm | Ad-hoc Dynamic Programming |

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
