#!/bin/bash
# expects diff file name as a parameter
if [[ $# != 1 ]] ; then printf "\nError: diff file name missing\n\n" ; exit 1; fi
a=$(stat --format="%s" $1)
if [[ $a == 0 ]] ; then echo "OK" ; else echo "FAIL" ; fi
