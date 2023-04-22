#!/bin/bash

set -e

gnuplot <<-eNDgNUPLOTcOMMAND
	set term png size 900, 700
	set output "../data/throughput.png"
	set logscale x 2
	set logscale y 10
	set xlabel "msg size (B)"
	set ylabel "throughput (KB/s)"
	plot "../data/tcp_throughput.dat" using 1:2 title "TCP median Throughput" \
			with linespoints, \
		"../data/tcp_throughput.dat" using 1:3 title "TCP average Throughput" \
			with linespoints, \
		"../data/udp_throughput.dat" using 1:2 title "UDP median Throughput" \
			with linespoints, \
		"../data/udp_throughput.dat" using 1:3 title "UDP average Throughput" \
		with linespoints
	clear
eNDgNUPLOTcOMMAND
