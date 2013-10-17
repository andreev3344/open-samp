# g++ compilers with version > 4.3 are not supported (tested with g++ 3.4 & 4.3)

all:
	gcc-3.4 -m32 -O2 -c -w -Iamx/ -DLINUX -DUNICODE -DAMX_NODYNALOAD amx/*.c
	gcc-3.4 -m32 -O2 -c -w -Iamx/ -DLINUX -DUNICODE -DAMX_NODYNALOAD amx/sqlite/*.c
	g++ -m32 -O2 -c -w -Iamx/ -DLINUX -DUNICODE -DAMX_NODYNALOAD object/*.cpp
	g++ -m32 -O2 -c -w -Iamx/ -DLINUX -DUNICODE -DAMX_NODYNALOAD pool/*.cpp
	g++ -m32 -O2 -c -w -Iamx/ -DLINUX -DUNICODE -DAMX_NODYNALOAD script/*.cpp
	g++ -m32 -O2 -c -w -Iamx/ -DLINUX -DUNICODE -DAMX_NODYNALOAD script/amx/*.cpp
	g++ -m32 -O2 -c -w -Iamx/ -DLINUX -DUNICODE -DAMX_NODYNALOAD factory/*.cpp
	g++ -m32 -O2 -c -w -Iamx/ -DLINUX -DUNICODE -DAMX_NODYNALOAD plugin/*.cpp
	g++ -m32 -O2 -c -w -Iamx/ -DLINUX -DUNICODE -DAMX_NODYNALOAD *.cpp
	g++ -m32 -O2 -c -w -Iamx/ -DLINUX -DUNICODE -DAMX_NODYNALOAD raknet/*.cpp
	ar rcs Server/libopensampsvr.a *.o
