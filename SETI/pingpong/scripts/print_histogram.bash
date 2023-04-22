#!/bin/bash

set -e

if [[ $# != 2 ]] ; then printf "\nError: protocol name and message size expected as parameters\n\n" ; exit 1; fi

readonly ProtocolName=$1
readonly Size=$2
readonly InputDatFile="../data/${ProtocolName}_${Size}.out"
readonly OutputDatFile="../data/${ProtocolName}_${Size}_histo.dat"
readonly OutputPngFile="../data/${ProtocolName}_${Size}_histo.png"

rm -f ${OutputDatFile} ${OutputPngFile}

if [[ ! -r ${InputDatFile} ]]; then
	echo "Cannot read $InputDatFile"
	exit -1
fi

tail --lines=24 ${InputDatFile} | head --lines=21 > ${OutputDatFile}

declare -a Rstring
Rstring=($(grep repetitions ${InputDatFile} | grep Ping))

gnuplot <<-eNDgNUPLOTcOMMAND
        set term png size 900, 700
        set output "${OutputPngFile}"
	set xlabel "msec"
        set ylabel "# of samples"
	set logscale y 2
        set yrange [0.65:${Rstring[4]}]
	set boxwidth 0.9 relative
	set style fill solid 0.75
	plot "${OutputDatFile}" using 1:2 title "${ProtocolName} ${Size} bytes RTT histogram" \
                        with boxes
	clear
eNDgNUPLOTcOMMAND
xdg-open ${OutputPngFile} &

