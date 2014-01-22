#!/bin/bash
#VERSION=$(cat /var/games/trem_src/trem-pbot/version);
#VERSION=$[$VERSION+1];
#echo $VERSION > /var/games/trem_src/trem-pbot/version
#VERSION=$(printf "%03d" $VERSION);
VERSION=0;
PK3VM=pbot-vms-0.$VERSION.pk3
cp build/release-linux-x86_64/base/vm/*.qvm /var/games/tremulous/pbot/vm/
cp build/release-linux-x86_64/base/vm/cgame.qvm deploy/pbot-vm/vm/
cp build/release-linux-x86_64/base/vm/ui.qvm deploy/pbot-vm/vm/
cd deploy/pbot-vm/
zip -r $PK3VM .
mv $PK3VM /var/games/tremulous/pbot/
