#!/bin/bash
#@autor: A.Lepe (GlobalWarming)
#
#----------- VARIABLES TO EDIT -----------
MOD=gpp-bot
# Set DEDICATED=2 if you want to set
# your sever as public. (1 means private)
DEDICATED=1
#(Advanced): Modify if required
DEBUG_BIN=tremded-debug.x86_64
TREMDED_BIN=tremded-gpp.x86_64
#-----------------------------------------
if [[ "$1" == "--help" ]]; then
    echo "Usage: $0 [debug]";
    exit 0;
fi;

FSGAME=""
SERVERCFG="server.cfg"
if [[ "$MOD" != "" ]]; then
    FSGAME="+set fs_game $MOD";
    SERVERCFG="$MOD/$SERVERCFG";
fi

if [[ "$1" == "debug" ]];then
    if [ ! -f $DEBUG_BIN ]; then
        echo "Debug server binary not found. "
        echo "Please compile using the 'debug'"
        echo "argument and if you still get this"
        echo "message, change DEBUG_BIN value in"
        echo "'$0' file.";
        exit 1;
    fi
    if [[ ! -f $SERVERCFG ]]; then
        echo "$SERVERCFG not found.";
        echo "Debug may not work properly";
    else
        TESTSV=$(grep "vm_game" $SERVERCFG);
        if [[ "$TESTSV" == "" ]]; then
            echo 'set vm_ui 0' >> $SERVERCFG;
            echo 'set vm_game 0' >> $SERVERCFG;
            echo 'set vm_cgame 0' >> $SERVERCFG;
        else 
            sed -i 's/set vm_ui 2/set vm_ui 0/' $SERVERCFG;
            sed -i 's/set vm_game 2/set vm_game 0/' $SERVERCFG;
            sed -i 's/set vm_cgame 2/set vm_cgame 0/' $SERVERCFG;
        fi
    fi
    if [[ "$2" == "gdb" ]]; then
    gdb --args ./$DEBUG_BIN +set dedicated $DEDICATED $FSGAME +exec server.cfg
    else 
    valgrind --leak-check=yes ./$DEBUG_BIN +set dedicated $DEDICATED $FSGAME +exec server.cfg
    fi
else
    if [ ! -f $TREMDED_BIN ]; then
        echo "Server binary not found. "
        echo "Please change TREMDED_BIN value in"
        echo "'$0' file.";
        exit 1;
    fi
    sed -i 's/set vm_ui 0/set vm_ui 2/' $SERVERCFG;
    sed -i 's/set vm_game 0/set vm_game 2/' $SERVERCFG;
    sed -i 's/set vm_cgame 0/set vm_cgame 2/' $SERVERCFG;
    ./$TREMDED_BIN +set dedicated $DEDICATED +set fs_game gpp-bot +exec server.cfg
fi
