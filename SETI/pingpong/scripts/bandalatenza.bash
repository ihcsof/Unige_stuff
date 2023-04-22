#!/bin/bash

# di def. gli errori vengono ignorati, set -e interrompe l'exec di uno script in caso di errore
set -e

#arg di default
TYPE=${1:-1}
# possibilita' di specificare con argomenti da riga di comando il grafico th_mediano o th_medio:
if [[ $# < 1 ]] ; then
	printf "Using default 1 for median. Specify 2 for average\n";
elif [[ $TYPE != 1 && $TYPE != 2 ]] ; then
	printf "Invalid argument for histogram type\n";
	exit 1;
fi

#arr protocolli
declare -a protocols=("tcp" "udp")

#ciclo sui due protocolli
for prot in "${protocols[@]}"
do

	# estrazione con head e tail delle righe | estrazione del campo (separat: blank) 
	# | convers. con sed (bc non supporta notaz. esponenziale). 
	# NB: g sostituisce tutte le occorrenze
	
	# ottengo la dimensione del pacchetto della prima e ultima riga
	N1=$(head -n 1 ../data/${prot}_throughput.dat | cut -f1 -d' ' | sed -E 's/[eE][+]?/*10^/g')
	N2=$(tail -n 1 ../data/${prot}_throughput.dat | cut -f1 -d' ' | sed -E 's/[eE][+]?/*10^/g')

	# ottengo il throughput mediano della prima e ultima riga
	TN1=$(head -n 1 ../data/${prot}_throughput.dat | cut -f$(($TYPE + 1)) -d' ' | sed -E 's/[eE][+]?/*10^/g')
	TN2=$(tail -n 1 ../data/${prot}_throughput.dat | cut -f$(($TYPE + 1)) -d' ' | sed -E 's/[eE][+]?/*10^/g')

	# T(N) * D(N) = N --> D(N) = N / T(N)
	# Calcolo i parametri B(banda) ed L0(latenza) per il modello b-l
	d1=$(echo "scale=9; d1=(($N1) / ($TN1)); d1" | bc)
	d2=$(echo "scale=9; d2=(($N2) / ($TN2)); d2" | bc)
	b=$(echo "scale=9; b=((($N2) - ($N1)) / ($d2 - $d1)); b" | bc)
	l0=$(echo "scale=9; l0=(($d1 * ($N2) - $d2 * ($N1)) / (($N2) - ($N1))); l0" | bc)

	# Realizzazione grafici con gnuplot
	gnuplot <<-eNDgNUPLOTcOMMAND
		set term png size 900, 700
		set output "../data/${prot}graph.png"
		set logscale x 2
		
		# per stampare su terminale (senza set output: default stdout)
		# set term dumb
		
		set logscale y 10
		set xlabel "msg size (B)"
		set ylabel "throughput (KB/s)"
		
		# Th = N / D con D = l0 + N/B
		blfun(x) = x / ($l0 + x / $b)
		
		plot "../data/${prot}_throughput.dat" using 1:2 title "${prot} ping-pong Throughput" with linespoints, \
			blfun(x) title "Latency-Bandwidth model with L=$l0 and B=$b" with linespoints
		clear
	eNDgNUPLOTcOMMAND
done
