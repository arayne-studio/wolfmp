CC=i686-w64-mingw32-g++.exe
ASIO_INCLUDE=./asio/asio/include

dllmain: dllmain.cpp
	$(CC) -I$(ASIO_INCLUDE) -shared -std=c++17 --static -o wolfmp.dll *.cpp -lws2_32
