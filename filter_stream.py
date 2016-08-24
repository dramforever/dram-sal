#!/usr/bin/env python

import sys

def filter_stream(stream):
    empty_line_count = 0
    for line in stream:
        stripped = line.rstrip()
        if stripped == '':
            empty_line_count += 1
        else:
            for r in range(empty_line_count):
                yield ''
            yield stripped

if __name__ == '__main__':
    for line in filter_stream(sys.stdin):
        print(line)
