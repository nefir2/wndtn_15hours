#!/bin/bash

export filename='wndtn_malloc';
export fileext='.c';
export srcdir='src';
export bindir='bin';
export compilername='gcc';

command -v $compilername;
if [[ $? -ne 0 ]]; then
	echo "${compilername} not found in your system.";
	exit 1;
fi

gcc "${srcdir}/${filename}${fileext}" -o "${bindir}/${filename}_${compilername}"; 
command `pwd`/$bindir/"${filename}_${compilername}";

exit 0;