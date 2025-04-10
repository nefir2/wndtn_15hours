#!/bin/bash

cd ../bin/

if [ $? -ne 0 ]; then
	echo "bin not found.";
	exit $?;
fi;

cmake ../;
make;
if [ $? -ne 0 ]; then 
	exit $?;
fi;
command explorer server.exe;
command explorer client.exe;
java ../sources/client/java/Client.java;
dotnet run ../sources/client/csharp/Servers_Client.csproj;

# echo -e "building java client . . . \n";
# javac ../sources/client/java/Client.java && jar cvf client.jar Client.class && 