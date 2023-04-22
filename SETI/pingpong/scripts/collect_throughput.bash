#!/bin/bash

set -e

if [[ $# != 1 ]] ; then printf "\nError: protocol name expected as a parameter\n\n" ; exit 1; fi

readonly ProtocolName=$1

rm -f ../data/${ProtocolName}_throughput.dat ../data/${ProtocolName}_unsorted.dat
declare -a Tstring
declare -a Sstring
for fname in ../data/${ProtocolName}_*.out ; do
	Tstring=($(grep Throughput $fname))
	Sstring=($(grep repetitions $fname | grep Ping))
  	echo ${Sstring[7]} ${Tstring[3]} ${Tstring[8]} >> ../data/${ProtocolName}_unsorted.dat
done
sort -n --key=1,1 ../data/${ProtocolName}_unsorted.dat > ../data/${ProtocolName}_throughput.dat
rm -f ../data/${ProtocolName}_unsorted.dat

