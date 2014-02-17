#!/bin/bash
echo "Change mode from release to debug in Makefile"
make clean
make
DEPLOY_DIR=/var/games/tremulous/pbot-gpp
VERSION=0;
PK3VM=pbot-gpp-vms-0.$VERSION.pk3
cp build/debug-linux-x86_64/base/vm/*.qvm $DEPLOY_DIR/vm/
cp build/debug-linux-x86_64/base/vm/cgame.qvm deploy/pbot-vm/vm/
cp build/debug-linux-x86_64/base/vm/ui.qvm deploy/pbot-vm/vm/
cd deploy/pbot-vm/
zip -r $PK3VM .
mv $PK3VM $DEPLOY_DIR
