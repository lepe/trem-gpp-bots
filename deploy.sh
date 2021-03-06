#!/bin/bash
#@autor: A.Lepe (GlobalWarming)
#
#----------- VARIABLES TO EDIT -----------
GAME_DIR=/var/games/tremulous
MOD=gpp-bot
# Directory to set links to pk3s (empty = none)
# can be relative or absolute
WEB_DIR=$GAME_DIR/web
# Set package version
VERSION=$(cat VERSION);

#if [1], it will copy the resulting PK3 to
#user's directory to speed testing
COPYTOUSER=1;

#(Advanced): Modify if required
DEPLOY_DIR=$GAME_DIR/$MOD
DEBUG_DIR=debug-linux-x86_64
RELEASE_DIR=release-linux-x86_64
DEBUG_BIN=tremded.x86_64

VM_PK3_DIR=assets-vm
#-----------------------------------------
ROOT_PWD=$(pwd);
if [ ! -d $DEPLOY_DIR ]; then
    echo "Directory created: $DEPLOY_DIR";
    mkdir $DEPLOY_DIR
fi

if [[ "$1" == "debug" ]]; then
    BUILD_DIR=build/$DEBUG_DIR/base
else
    BUILD_DIR=build/$RELEASE_DIR/base
fi

if [ ! -f "compile.sh" ]; then
    echo "No compilation file was found."
    echo "Be sure you are executing $0"
    echo "under the same directory."
else
    ./compile.sh $1
    if [ $? != 0 ]; then
        echo "###################"
        echo "Compilation failed";
        echo "###################"
        exit $?;
    fi
fi

PK3VM=$MOD-vms-$VERSION.pk3

if [ ! -d $VM_PK3_DIR ]; then
    echo "Directory created: $ROOT_PWD/$VM_PK3_DIR/"
    mkdir $VM_PK3_DIR
fi

cp $BUILD_DIR/vm/*.qvm $DEPLOY_DIR/vm/
cp $BUILD_DIR/vm/cgame.qvm $VM_PK3_DIR/vm/
cp $BUILD_DIR/vm/ui.qvm $VM_PK3_DIR/vm/

#SO libraries
if [[ "$1" == "debug" ]]; then
    cp $BUILD_DIR/tremded.x86_64 $GAME_DIR/
    cp $BUILD_DIR/*.so $DEPLOY_DIR/
fi

cd $VM_PK3_DIR
zip -r $PK3VM .
if [[ $COPYTOUSER == 1 ]]; then
    #copy to local version to speed-up testing
    cp $PK3VM ~/.tremulous/$MOD/
fi
#move pk3 to deploy dir
rm $DEPLOY_DIR/$MOD-vms-*.pk3
mv $PK3VM $DEPLOY_DIR
cd $ROOT_PWD

if [[ "$WEB_DIR" != "" ]]; then
    cd $WEB_DIR;
    rm $MOD-vms-*.pk3
    ln -s $DEPLOY_DIR/$PK3VM .
fi
cd $ROOT_PWD
# copy the start script if it is not there
if [ ! -f $GAME_DIR/start.sh ]; then
    cp start.sh $GAME_DIR/start.sh
fi
if [ ! -d $GAME_DIR/$MOD ]; then
    mkdir $GEAME_DIR/$MOD;
fi
if [ ! -d $GAME_DIR/$MOD/bots ]; then
    cp -R $MOD/* $GAME_DIR/$MOD/
fi
exit 0
