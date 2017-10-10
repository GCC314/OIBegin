# OIBegin
## Begin NOIP tests simulator for beginners written by beginners.


## Introduction
OIBegin,written by C++,executed in command lines,is still a semi-completed program.However,it can simply do some work,which is to help NOIP beginner practising NOIP.


## Additional Features compared to [@ZhangZisu](https://github.com/ZhangZisu/OIBegin)
+ Support for Linux users
+ UTF-8 file code


## Make & Run
For Windows users,execute app.exe.
For Linux users,execute ./anscpp.pg.


To compile it in Windows,just run:
    g++ app.cpp -o app.exe


While in Linux,some extra work should be done:
    Install the library *ncurses-dev*:
        sudo apt-get install ncurses-dev (For Debian Users)
    Compile:
        g++ app.cpp -o anscpp.pg -lcurses -D __COMPILE_IN_LINUX -D __USING_UTF8


Well,have a nice experience!
