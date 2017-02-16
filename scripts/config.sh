#!/bin/bash

mkdir -p build

ls src/ | sed -e 's#.cpp$##' | while read name
do
    if [ -d vendor/${name} ]
    then
        cp -r vendor/${name}/ build/
    else
        mkdir -p build/${name}
    fi

    cat > build/${name}/Makefile <<END
${name}: $(readlink -f src/${name}.cpp)
	\$(LINK.cpp) $^ \$(LOADLIBES) \$(LDLIBS) -o \$@ \`ls *.cpp\` -I .
END
done
