#!/bin/sh

table="$1"
header="$2"

:>"$header"

while read -r line; do
    printf "__SYSCALL($line)\n" >> "$header"
done < "$table"
