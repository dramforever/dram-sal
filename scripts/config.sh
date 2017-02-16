#!/bin/bash

mkdir -p build

ls src/ | sed -e 's#.cpp$##' | while read name
do
    if [ -d vendor/${name} ]
    then
        cp -r vendor/${name}/ build/
        extra=`ls vendor/${name} | grep '.cpp$'`
    else
        mkdir -p build/${name}
        extra=
    fi

    cat > build/${name}/Makefile <<END
${name}: $(readlink -f src/${name}.cpp)
	\$(LINK.cpp) $^ \$(LOADLIBES) \$(LDLIBS) -I . $extra -o \$@
END
done
