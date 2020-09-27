#!/bin/sh

scopped_foo() {
    declare SCOPED_FOO="bar"
}

foo() {
    FOO="bar"
}

scopped_foo
echo "SCOPED_FOO: ${SCOPED_FOO}"

foo
echo "FOO: ${FOO}"
