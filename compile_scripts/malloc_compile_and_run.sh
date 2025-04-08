#!/bin/bash

export filename='wndtn_malloc';
export srcdir='src';
export bindir='bin';
export fileext='.c';
export compilername='gcc';

command -v $compilername;
if [[ $? -ne 0 ]]; then
	echo "${compilername} not found in your system.";
	exit 1;
fi
cd ../
gcc "${srcdir}/${filename}${fileext}" -o "${bindir}/${filename}_${compilername}"; 
command "${bindir}/${filename}_${compilername}";

exit 0;