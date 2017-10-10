__os_windows:app.cpp
	g++ app.cpp -o app.exe
__os_linux:
	g++ app.cpp -o app.pg -lcurses -D __COMPILE_IN_LINUX -D __USING_UTF8
