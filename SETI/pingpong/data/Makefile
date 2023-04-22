PINGPONGADDR=localhost
PINGPONGPORT=1491
TCP_EXE=../bin/tcp_ping
UDP_EXE=../bin/udp_ping

all: throughput ../data

../data:
	mkdir ../data

throughput: ../data/throughput.png

all_data: all_udp_data all_tcp_data

all_udp_data: ../data/udp_32.out ../data/udp_48.out ../data/udp_64.out ../data/udp_96.out ../data/udp_128.out ../data/udp_192.out ../data/udp_256.out ../data/udp_384.out ../data/udp_512.out ../data/udp_768.out ../data/udp_1024.out ../data/udp_1536.out ../data/udp_2048.out ../data/udp_3072.out ../data/udp_4096.out ../data/udp_6144.out ../data/udp_8192.out ../data/udp_12288.out ../data/udp_16384.out ../data/udp_24576.out ../data/udp_32768.out

all_tcp_data: ../data/tcp_32.out ../data/tcp_48.out ../data/tcp_64.out ../data/tcp_96.out ../data/tcp_128.out ../data/tcp_192.out ../data/tcp_256.out ../data/tcp_384.out ../data/tcp_512.out ../data/tcp_768.out ../data/tcp_1024.out ../data/tcp_1536.out ../data/tcp_2048.out ../data/tcp_3072.out ../data/tcp_4096.out ../data/tcp_6144.out ../data/tcp_8192.out ../data/tcp_12288.out ../data/tcp_16384.out ../data/tcp_24576.out ../data/tcp_32768.out ../data/tcp_49152.out ../data/tcp_65536.out ../data/tcp_98304.out ../data/tcp_131072.out ../data/tcp_196608.out ../data/tcp_262144.out ../data/tcp_393216.out ../data/tcp_524288.out

../data/udp_32.out:
	$(UDP_EXE) $(PINGPONGADDR) $(PINGPONGPORT) 32 501 > ../data/udp_32.out || mv -f ../data/udp_32.out ../data/udp_32.out.broken

../data/udp_48.out:
	$(UDP_EXE) $(PINGPONGADDR) $(PINGPONGPORT) 48 501 > ../data/udp_48.out || mv -f ../data/udp_48.out ../data/udp_48.out.broken

../data/udp_64.out:
	$(UDP_EXE) $(PINGPONGADDR) $(PINGPONGPORT) 64 501 > ../data/udp_64.out || mv -f ../data/udp_64.out ../data/udp_64.out.broken

../data/udp_96.out:
	$(UDP_EXE) $(PINGPONGADDR) $(PINGPONGPORT) 96 501 > ../data/udp_96.out || mv -f ../data/udp_96.out ../data/udp_96.out.broken

../data/udp_128.out:
	$(UDP_EXE) $(PINGPONGADDR) $(PINGPONGPORT) 128 501 > ../data/udp_128.out || mv -f ../data/udp_128.out ../data/udp_128.out.broken

../data/udp_192.out:
	$(UDP_EXE) $(PINGPONGADDR) $(PINGPONGPORT) 192 501 > ../data/udp_192.out || mv -f ../data/udp_192.out ../data/udp_192.out.broken

../data/udp_256.out:
	$(UDP_EXE) $(PINGPONGADDR) $(PINGPONGPORT) 256 501 > ../data/udp_256.out || mv -f ../data/udp_256.out ../data/udp_256.out.broken

../data/udp_384.out:
	$(UDP_EXE) $(PINGPONGADDR) $(PINGPONGPORT) 384 501 > ../data/udp_384.out || mv -f ../data/udp_384.out ../data/udp_384.out.broken

../data/udp_512.out:
	$(UDP_EXE) $(PINGPONGADDR) $(PINGPONGPORT) 512 501 > ../data/udp_512.out || mv -f ../data/udp_512.out ../data/udp_512.out.broken

../data/udp_768.out:
	$(UDP_EXE) $(PINGPONGADDR) $(PINGPONGPORT) 768 501 > ../data/udp_768.out || mv -f ../data/udp_768.out ../data/udp_768.out.broken

../data/udp_1024.out:
	$(UDP_EXE) $(PINGPONGADDR) $(PINGPONGPORT) 1024 501 > ../data/udp_1024.out || mv -f ../data/udp_1024.out ../data/udp_1024.out.broken

../data/udp_1536.out:
	$(UDP_EXE) $(PINGPONGADDR) $(PINGPONGPORT) 1536 501 > ../data/udp_1536.out || mv -f ../data/udp_1536.out ../data/udp_1536.out.broken

../data/udp_2048.out:
	$(UDP_EXE) $(PINGPONGADDR) $(PINGPONGPORT) 2048 501 > ../data/udp_2048.out || mv -f ../data/udp_2048.out ../data/udp_2048.out.broken

../data/udp_3072.out:
	$(UDP_EXE) $(PINGPONGADDR) $(PINGPONGPORT) 3072 501 > ../data/udp_3072.out || mv -f ../data/udp_3072.out ../data/udp_3072.out.broken

../data/udp_4096.out:
	$(UDP_EXE) $(PINGPONGADDR) $(PINGPONGPORT) 4096 501 > ../data/udp_4096.out || mv -f ../data/udp_4096.out ../data/udp_4096.out.broken

../data/udp_6144.out:
	$(UDP_EXE) $(PINGPONGADDR) $(PINGPONGPORT) 6144 501 > ../data/udp_6144.out || mv -f ../data/udp_6144.out ../data/udp_6144.out.broken

../data/udp_8192.out:
	$(UDP_EXE) $(PINGPONGADDR) $(PINGPONGPORT) 8192 501 > ../data/udp_8192.out || mv -f ../data/udp_8192.out ../data/udp_8192.out.broken

../data/udp_12288.out:
	$(UDP_EXE) $(PINGPONGADDR) $(PINGPONGPORT) 12288 501 > ../data/udp_12288.out || mv -f ../data/udp_12288.out ../data/udp_12288.out.broken

../data/udp_16384.out:
	$(UDP_EXE) $(PINGPONGADDR) $(PINGPONGPORT) 16384 501 > ../data/udp_16384.out || mv -f ../data/udp_16384.out ../data/udp_16384.out.broken

../data/udp_24576.out:
	$(UDP_EXE) $(PINGPONGADDR) $(PINGPONGPORT) 24576 501 > ../data/udp_24576.out || mv -f ../data/udp_24576.out ../data/udp_24576.out.broken

../data/udp_32768.out:
	$(UDP_EXE) $(PINGPONGADDR) $(PINGPONGPORT) 32768 501 > ../data/udp_32768.out || mv -f ../data/udp_32768.out ../data/udp_32768.out.broken

../data/tcp_32.out:
	$(TCP_EXE) $(PINGPONGADDR) $(PINGPONGPORT) 32 501 > ../data/tcp_32.out || mv -f ../data/tcp_32.out ../data/tcp_32.out.broken

../data/tcp_48.out:
	$(TCP_EXE) $(PINGPONGADDR) $(PINGPONGPORT) 48 501 > ../data/tcp_48.out || mv -f ../data/tcp_48.out ../data/tcp_48.out.broken

../data/tcp_64.out:
	$(TCP_EXE) $(PINGPONGADDR) $(PINGPONGPORT) 64 501 > ../data/tcp_64.out || mv -f ../data/tcp_64.out ../data/tcp_64.out.broken

../data/tcp_96.out:
	$(TCP_EXE) $(PINGPONGADDR) $(PINGPONGPORT) 96 501 > ../data/tcp_96.out || mv -f ../data/tcp_96.out ../data/tcp_96.out.broken

../data/tcp_128.out:
	$(TCP_EXE) $(PINGPONGADDR) $(PINGPONGPORT) 128 501 > ../data/tcp_128.out || mv -f ../data/tcp_128.out ../data/tcp_128.out.broken

../data/tcp_192.out:
	$(TCP_EXE) $(PINGPONGADDR) $(PINGPONGPORT) 192 501 > ../data/tcp_192.out || mv -f ../data/tcp_192.out ../data/tcp_192.out.broken

../data/tcp_256.out:
	$(TCP_EXE) $(PINGPONGADDR) $(PINGPONGPORT) 256 501 > ../data/tcp_256.out || mv -f ../data/tcp_256.out ../data/tcp_256.out.broken

../data/tcp_384.out:
	$(TCP_EXE) $(PINGPONGADDR) $(PINGPONGPORT) 384 501 > ../data/tcp_384.out || mv -f ../data/tcp_384.out ../data/tcp_384.out.broken

../data/tcp_512.out:
	$(TCP_EXE) $(PINGPONGADDR) $(PINGPONGPORT) 512 501 > ../data/tcp_512.out || mv -f ../data/tcp_512.out ../data/tcp_512.out.broken

../data/tcp_768.out:
	$(TCP_EXE) $(PINGPONGADDR) $(PINGPONGPORT) 768 501 > ../data/tcp_768.out || mv -f ../data/tcp_768.out ../data/tcp_768.out.broken

../data/tcp_1024.out:
	$(TCP_EXE) $(PINGPONGADDR) $(PINGPONGPORT) 1024 501 > ../data/tcp_1024.out || mv -f ../data/tcp_1024.out ../data/tcp_1024.out.broken

../data/tcp_1536.out:
	$(TCP_EXE) $(PINGPONGADDR) $(PINGPONGPORT) 1536 501 > ../data/tcp_1536.out || mv -f ../data/tcp_1536.out ../data/tcp_1536.out.broken

../data/tcp_2048.out:
	$(TCP_EXE) $(PINGPONGADDR) $(PINGPONGPORT) 2048 501 > ../data/tcp_2048.out || mv -f ../data/tcp_2048.out ../data/tcp_2048.out.broken

../data/tcp_3072.out:
	$(TCP_EXE) $(PINGPONGADDR) $(PINGPONGPORT) 3072 501 > ../data/tcp_3072.out || mv -f ../data/tcp_3072.out ../data/tcp_3072.out.broken

../data/tcp_4096.out:
	$(TCP_EXE) $(PINGPONGADDR) $(PINGPONGPORT) 4096 501 > ../data/tcp_4096.out || mv -f ../data/tcp_4096.out ../data/tcp_4096.out.broken

../data/tcp_6144.out:
	$(TCP_EXE) $(PINGPONGADDR) $(PINGPONGPORT) 6144 501 > ../data/tcp_6144.out || mv -f ../data/tcp_6144.out ../data/tcp_6144.out.broken

../data/tcp_8192.out:
	$(TCP_EXE) $(PINGPONGADDR) $(PINGPONGPORT) 8192 501 > ../data/tcp_8192.out || mv -f ../data/tcp_8192.out ../data/tcp_8192.out.broken

../data/tcp_12288.out:
	$(TCP_EXE) $(PINGPONGADDR) $(PINGPONGPORT) 12288 501 > ../data/tcp_12288.out || mv -f ../data/tcp_12288.out ../data/tcp_12288.out.broken

../data/tcp_16384.out:
	$(TCP_EXE) $(PINGPONGADDR) $(PINGPONGPORT) 16384 501 > ../data/tcp_16384.out || mv -f ../data/tcp_16384.out ../data/tcp_16384.out.broken

../data/tcp_24576.out:
	$(TCP_EXE) $(PINGPONGADDR) $(PINGPONGPORT) 24576 501 > ../data/tcp_24576.out || mv -f ../data/tcp_24576.out ../data/tcp_24576.out.broken

../data/tcp_32768.out:
	$(TCP_EXE) $(PINGPONGADDR) $(PINGPONGPORT) 32768 501 > ../data/tcp_32768.out || mv -f ../data/tcp_32768.out ../data/tcp_32768.out.broken

../data/tcp_49152.out:
	$(TCP_EXE) $(PINGPONGADDR) $(PINGPONGPORT) 49152 501 > ../data/tcp_49152.out || mv -f ../data/tcp_49152.out ../data/tcp_49152.out.broken

../data/tcp_65536.out:
	$(TCP_EXE) $(PINGPONGADDR) $(PINGPONGPORT) 65536 501 > ../data/tcp_65536.out || mv -f ../data/tcp_65536.out ../data/tcp_65536.out.broken

../data/tcp_98304.out:
	$(TCP_EXE) $(PINGPONGADDR) $(PINGPONGPORT) 98304 501 > ../data/tcp_98304.out || mv -f ../data/tcp_98304.out ../data/tcp_98304.out.broken

../data/tcp_131072.out:
	$(TCP_EXE) $(PINGPONGADDR) $(PINGPONGPORT) 131072 501 > ../data/tcp_131072.out || mv -f ../data/tcp_131072.out ../data/tcp_131072.out.broken

../data/tcp_196608.out:
	$(TCP_EXE) $(PINGPONGADDR) $(PINGPONGPORT) 196608 501 > ../data/tcp_196608.out || mv -f ../data/tcp_196608.out ../data/tcp_196608.out.broken

../data/tcp_262144.out:
	$(TCP_EXE) $(PINGPONGADDR) $(PINGPONGPORT) 262144 501 > ../data/tcp_262144.out || mv -f ../data/tcp_262144.out ../data/tcp_262144.out.broken

../data/tcp_393216.out:
	$(TCP_EXE) $(PINGPONGADDR) $(PINGPONGPORT) 393216 501 > ../data/tcp_393216.out || mv -f ../data/tcp_393216.out ../data/tcp_393216.out.broken

../data/tcp_524288.out:
	$(TCP_EXE) $(PINGPONGADDR) $(PINGPONGPORT) 524288 501 > ../data/tcp_524288.out || mv -f ../data/tcp_524288.out ../data/tcp_524288.out.broken

../data/throughput.png: ../data/tcp_throughput.dat ../data/udp_throughput.dat
	../scripts/gplot.bash

../data/udp_throughput.dat: all_udp_data
	../scripts/collect_throughput.bash udp

../data/tcp_throughput.dat: all_tcp_data
	../scripts/collect_throughput.bash tcp

clean:
	rm -f ../data/throughput.png ../data/tcp_throughput.dat ../data/udp_throughput.dat ../data/udp_32.out ../data/udp_32.out.broken ../data/udp_48.out ../data/udp_48.out.broken ../data/udp_64.out ../data/udp_64.out.broken ../data/udp_96.out ../data/udp_96.out.broken ../data/udp_128.out ../data/udp_128.out.broken ../data/udp_192.out ../data/udp_192.out.broken ../data/udp_256.out ../data/udp_256.out.broken ../data/udp_384.out ../data/udp_384.out.broken ../data/udp_512.out ../data/udp_512.out.broken ../data/udp_768.out ../data/udp_768.out.broken ../data/udp_1024.out ../data/udp_1024.out.broken ../data/udp_1536.out ../data/udp_1536.out.broken ../data/udp_2048.out ../data/udp_2048.out.broken ../data/udp_3072.out ../data/udp_3072.out.broken ../data/udp_4096.out ../data/udp_4096.out.broken ../data/udp_6144.out ../data/udp_6144.out.broken ../data/udp_8192.out ../data/udp_8192.out.broken ../data/udp_12288.out ../data/udp_12288.out.broken ../data/udp_16384.out ../data/udp_16384.out.broken ../data/udp_24576.out ../data/udp_24576.out.broken ../data/udp_32768.out ../data/udp_32768.out.broken ../data/tcp_32.out ../data/tcp_32.out.broken ../data/tcp_48.out ../data/tcp_48.out.broken ../data/tcp_64.out ../data/tcp_64.out.broken ../data/tcp_96.out ../data/tcp_96.out.broken ../data/tcp_128.out ../data/tcp_128.out.broken ../data/tcp_192.out ../data/tcp_192.out.broken ../data/tcp_256.out ../data/tcp_256.out.broken ../data/tcp_384.out ../data/tcp_384.out.broken ../data/tcp_512.out ../data/tcp_512.out.broken ../data/tcp_768.out ../data/tcp_768.out.broken ../data/tcp_1024.out ../data/tcp_1024.out.broken ../data/tcp_1536.out ../data/tcp_1536.out.broken ../data/tcp_2048.out ../data/tcp_2048.out.broken ../data/tcp_3072.out ../data/tcp_3072.out.broken ../data/tcp_4096.out ../data/tcp_4096.out.broken ../data/tcp_6144.out ../data/tcp_6144.out.broken ../data/tcp_8192.out ../data/tcp_8192.out.broken ../data/tcp_12288.out ../data/tcp_12288.out.broken ../data/tcp_16384.out ../data/tcp_16384.out.broken ../data/tcp_24576.out ../data/tcp_24576.out.broken ../data/tcp_32768.out ../data/tcp_32768.out.broken ../data/tcp_49152.out ../data/tcp_49152.out.broken ../data/tcp_65536.out ../data/tcp_65536.out.broken ../data/tcp_98304.out ../data/tcp_98304.out.broken ../data/tcp_131072.out ../data/tcp_131072.out.broken ../data/tcp_196608.out ../data/tcp_196608.out.broken ../data/tcp_262144.out ../data/tcp_262144.out.broken ../data/tcp_393216.out ../data/tcp_393216.out.broken ../data/tcp_524288.out ../data/tcp_524288.out.broken

