#!/usr/bin/env python

import sys

empty_line_count = 0

for line in sys.stdin:
    stripped = line.rstrip()
    if stripped == '':
        empty_line_count += 1
    else:
        for r in range(empty_line_count):
            print ''
        print stripped
