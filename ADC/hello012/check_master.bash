#!/bin/bash

cmp_exec=$1
my_exec=$2
params=$3

echo $my_exec $cmp_exec $params

./$cmp_exec $params > cmp_$params.txt
./$my_exec $params > my_$params.txt
diff my_$params.txt cmp_$params.txt > diff_$params.txt
/bin/rm -f my_$params.txt cmp_$params.txt

