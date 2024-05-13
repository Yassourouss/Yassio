# 1. Introduction 
Hello, And welcome to my End-of-Studies Project. 
This is my attempt to implement SOME/IP Protocol using C++.
The networking part is handled using Boost ASIO 
# 2. Compilation
To compile the project, you first need to install boost library :   
`sudo apt-get install libboost-all-dev`  
You can then access the downloaded folder SimpleClient :  
```
../$ cd SimpleClient
../SimpleClient$ cd build/
../SimpleClient/build$ cmake -S ../ -B .
../SimpleClient/build$ make
```
And done, you've successfully built the project. 
To run the server, just type : `./SimpleServer`  
Same goes for the client : `./SimpleClient`
