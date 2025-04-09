#!/bin/bash

function containsSrc() {
	for e in `ls`; do
		if [[ 'src' ]]; then
			return 0;
		fi
	done;
	return 1;
}

containsSrc;
if [ $? -ne 0 ]; then
	cd ../
fi
g++.exe -std=c++11 src/serialization/main.cpp -o bin/serialization;
command bin/serialization.exe;

exit 0;