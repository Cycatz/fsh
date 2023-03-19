#!/bin/sh

table="$1"
header="$(dirname $0)/../include/gen/overrided_syscalls.h"

:>"$header"

while read -r line; do
    printf "__SYSCALL($line)\n" >> "$header"
done < "$table"
