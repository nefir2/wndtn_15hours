#!/bin/bash

export projname='string';
export filename='wndtn_string';
export srcdir='src';
export bindir='bin';
export fileext='.cpp';
export compilername='g++';

command -v $compilername;
if [[ $? -ne 0 ]]; then
	echo "${compilername} not found in your system.";
	exit 1;
fi
cd ../
g++ "${srcdir}/${projname}/${filename}${fileext}" -o "${bindir}/${filename}";
command "${bindir}/${filename}";

exit 0;
