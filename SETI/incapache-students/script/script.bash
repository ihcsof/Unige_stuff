#!/bin/bash

for i in {1..1000}
do
	wget -r localhost:8080 > /dev/null 
	wget -r localhost:8080 > /dev/null
done

