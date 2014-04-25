#!/bin/bash
DEPLOY_DIR=/var/games/tremulous/gpp-bot
VERSION=0;
PK3VM=gpp-bot-vms-0.$VERSION.pk3
cp build/release-linux-x86_64/base/vm/*.qvm $DEPLOY_DIR/vm/
cp build/release-linux-x86_64/base/vm/cgame.qvm deploy/vm/
cp build/release-linux-x86_64/base/vm/ui.qvm deploy/vm/
cd deploy/
zip -r $PK3VM .
cp $PK3VM ~/.tremulous/gpp-bot/
mv $PK3VM $DEPLOY_DIR
