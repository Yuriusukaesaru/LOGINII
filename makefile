MSVC: src/main.cpp
	cl.exe src/main.cpp /std:c++20 /Z7 /W4 /EHsc /Febin/login.exe

Clang: src/main.cpp
	clang++ src/main.cpp -g -std=c++20 -Wall -Wextra -Wpedantic -Werror -o bin/login.exe

minGW: src/main.cpp
	g++ src/main.cpp -g -std=c++20 -Wall -Wextra -Wpedantic -Werror -o bin/login.exe

.PHONY: clean
clean:
	rm bin/* main.obj
