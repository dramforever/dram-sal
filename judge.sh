#!/usr/bin/env bash

if [ x$1 == x -o x$2 == x -o x$3 == x -o x$4 == x ]; then
    echo "Wrong usage"
    exit -1
fi

OUTPUT=out.$$

if ! time ./$1 <$2 >${OUTPUT}; then
    echo "* Program failed"
    exit 1
fi

FILTERED_OUT=filtered.$$.out
python $4 <${OUTPUT} >${FILTERED_OUT}

FILTERED_STD=filtered.$$.std
python $4 <$3 >${FILTERED_STD}

if diff -u ${FILTERED_STD} ${FILTERED_OUT}; then
    rm ${OUTPUT}
    rm ${FILTERED_OUT}
else
    echo "* Output incorrect"
    rm ${OUTPUT}
    rm ${FILTERED_OUT}
    exit 1
fi
