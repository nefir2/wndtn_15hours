#!/bin/bash

export filename='wndtn_string';
export srcdir='src';
export bindir='bin';
export fileext='.cpp';
export compilername='g++';

command -v $comilername;
if [[ $? -ne 0 ]]; then
	echo "${compilername} not found in your system.";
	exit 1;
fi

g++ "${srcdir}/${filename}${fileext}" -o "${bindir}/${filename}";
command "${bindir}/${filename}";

exit 0;
