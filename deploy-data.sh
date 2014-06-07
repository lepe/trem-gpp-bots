#!/bin/bash
#@autor: A.Lepe (GlobalWarming)
#
#----------- VARIABLES TO EDIT -----------
GAME_DIR=/var/games/tremulous
MOD=gpp-bot
# Directory to set links to pk3s (empty = none)
# can be relative or absolute
WEB_DIR=web
# Set package version
VERSION=$(cat VERSION);

#if [1], it will copy the resulting PK3 to
#user's directory to speed testing
COPYTOUSER=1;

#(Advanced): Modify if required
DEPLOY_DIR=$GAME_DIR/$MOD

DATA_PK3_DIR=assets-data
#-----------------------------------------
ROOT_PWD=$(pwd);
cd $DATA_PK3_DIR

PK3DATA="data-$MOD-${VERSION%.*}.pk3"

zip -r $PK3DATA .
if [[ $COPYTOUSER == 1 ]]; then
    #copy to local version to speed-up testing
    cp $PK3DATA ~/.tremulous/$MOD/
fi
#move pk3 to deploy dir
rm $DEPLOY_DIR/data-$MOD-*.pk3
mv $PK3DATA $DEPLOY_DIR
cd $ROOT_PWD

if [[ "$WEB_DIR" != "" ]]; then
    cd $WEB_DIR;
    rm data-$MOD-*.pk3
    ln -s $DEPLOY_DIR/$PK3DATA .
fi

cd $ROOT_PWD
