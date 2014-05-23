#!/bin/bash
#@autor: A.Lepe (GlobalWarming)
#
if [[ "$1" == "--help" ]]; then
    echo "Usage: $0 [debug]";
    exit 0;
fi;
if [[ "$1" == "debug" ]]; then
    #be sure there is nothing in there (sometimes make clean is not enough)
    rm -rf build/debug*
    sed -i 's/BUILD_SERVER     =0/BUILD_SERVER     =1/' Makefile
    sed -i 's/BUILD_GAME_SO    =0/BUILD_GAME_SO    =1/' Makefile
    #add: V=1 CFLAGS="" ... to show quake tools execution commands
    CFLAGS="" CC=clang make debug
else
    CLNG=$(which clang);
    sed -i 's/BUILD_SERVER     =1/BUILD_SERVER     =0/' Makefile
    sed -i 's/BUILD_GAME_SO    =1/BUILD_GAME_SO    =0/' Makefile
    if [ "$CLNG" != "" ]; then
        CFLAGS="-pedantic -std=c99" CC=clang make
    else
        CFLAGS="" make
        echo "[clang] is not installed, it is highly recommended to install it!";
    fi
fi
if [[ $? != 0 ]]; then
    echo "Compilation failed.";
#    rm -r build/*
fi
exit $?
