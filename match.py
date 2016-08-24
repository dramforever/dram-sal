import sys
from subprocess import *
import random
import string
from collections import defaultdict

from pydatagen import *

import filter_stream

NUM_TESTS=20

seed = random.randint(1, 100000)
random.seed(seed)

print('         Testing with random seed %d' % seed)

def runner(prog, inp):
    proc = Popen(['build/' + prog], stdin=PIPE, stdout=PIPE, universal_newlines=True)
    try:
        outs, err = proc.communicate(inp, timeout = 2)
    except:
        proc.kill()
        return None
    if proc.returncode == 0:
        return outs
    else:
        return None

has_failure = False

def testing(*progs):
    def inner(func):
        global has_failure
        print('         Testing %s' % func.__name__)
        cur_failure = False
        for i in range(NUM_TESTS):
            outs = defaultdict(list)
            inp = func()
            for prog_name in progs:
                pre_output = runner(prog_name, inp)
                if pre_output is None:
                    print('[  **  ] %s: %s failed on %d' % (func.__name__, prog_name, i + 1))
                    has_failure = True
                    cur_failure = True
                else:
                    output = '\n'.join(filter_stream.filter_stream(pre_output.splitlines(keepends=True)))
                    outs[output].append(prog_name)
            if len(outs) > 1:
                has_failure = True
                cur_failure = True
                print('[  **  ] %s: %d: Outputs differ. Groups: ' % (func.__name__, i + 1), end='')
                print(sorted([v for _, v in outs.items()]))
        if cur_failure:
            print('[ FAIL ] Test %s failed' % func.__name__)
        else:
            print('[  OK  ] Test %s passed' % func.__name__)

    return inner

@testing('sa', 'machine')
def suffix_array():
    size = random.choice([1, 12, 2000, 5000, 100000])
    st = ''.join(random.choice(string.ascii_lowercase) for _ in range(size))

    return st + '\n'

@testing('fft', 'ntt')
def fourier():
    n = random.randint(1, 10000)
    m = random.randint(1, 10000)
    x1 = map(str, randlist(n+1, range(9)))
    x2 = map(str, randlist(m+1, range(9)))
    return ' '.join([str(n), str(m)]) + '\n' + ' '.join(x1) + '\n' + ' '.join(x2) + '\n'

if has_failure: sys.exit(1)
