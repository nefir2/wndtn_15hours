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
	containsSrc;
	if [ $? -ne 0 ]; then
		echo "ты хочешь чтобы я тебе намусорил непонятно где?";
		exit $?;
	fi
fi

cd bin;
cmake ../CMakeLists.txt;
echo -e "\nmaking and run . . . \n";
make;
echo -e '\nmaking done. running the program . . . ';
command ./event_system.exe;
if [ $? -eq 0 ]; then
	echo -e '\nprogram exitted successfully.';
else
	echo -e "\nprogram\'s launch failed. exit code: \'$?\'.";
fi;

# g++.exe -std=c++11 src/serialization/main.cpp -o bin/serialization;
# command bin/serialization.exe;

exit 0;