#!/bin/bash

function containsSrc() {
	for e in $(ls); do
		if [[ "$e" == 'src' ]]; then
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
if [ $? -ne 0 ]; then
	echo "я не могу найти bin !! я потерялся !!";
	exit 1;
fi;

cmake ../CMakeLists.txt;
echo -e "\nmaking and run . . . \n";
make;
echo -e '\nmaking done. running the program . . . ';
export abcs=`./event_system.exe`;
echo "stdout: \"$abcs\"";
if [ $? -eq 0 ]; then
	echo -e '\nprogram exitted successfully.';

	if [ -n "$abcs" ]; then
		echo 'showing outputed files.';
		for abc in $abcs; do
			echo -ne "\n\n\"$abc\":\n";
			xxd $abc;
		done;
	fi;
else
	echo -e "\nprogram\'s launch failed. exit code: \'$?\'.";
fi;

exit 0;