Tremulous GPP bots module by GlobalWarming
------------------------------------------

The current code was based on a P-Bot 2.x GPP port from Tremulous 1.1 P-Bot (http://tremulous.net/forum/index.php?topic=15329.0) which uses Tremulous version SVN2279 (from http://svn.icculus.org/tremulous/trunk/).

CHANGE LOG

v.15
* Aliens improved (fixed stuck bug) and adjusted range values
* Goons will not try to use barbs if they don't have enough
* Bots will try to use wallwalk more (70%).
* Aliens will evolve more randomly (even if they have evos, they may not use them)
* Dretch and Basilisk will not always jump on attack
* debug messages and commands have been added
* g_bot_join 0/1 added to prevent bots from joining automatically
* join message changed to: "Please join to deploy bots"
* DrawNodes function changed to update only changed nodes (performance)
* Essence update changed to every second (for debug purposes)
* Cleaned code (removed many unused commented code)

v.14
* Ant Algorithm improved:
    - BAD essence was introduced as a "regret" action (shown as nades in dnodes)
    - Decision making was recoded and values were changed
* Evolve near humans (but not near humans buildings) is now possible
* Fixed "ping-pong" (up and down) movement of bots when firing close structures.
* Bots are added on team-join (not on spawn as previous version). This is the correct way
* Bots buy weapons and extras based also in probability (before was fixed), allowing: variety and saving
* Bots are not locked to a target anymore (if they see another target, may change)
* Weapons prioritization was changed
* Message is sent to client centered on screen (not as private message)
* dnodes was moved from g_admin.c to g_main.c to be automatically updated - every 3 secs- (refreshed) to show changes in Ant Algorithm
* random values were fixed (overseeding problem)

v.13
* Bots are added/removed automatically according to the number of players.
* Any team can be joined (even though Aliens is suggested) - sent as private message on login
* Ant algorithm values changed to increases the chances to explore new paths
* Bots throw nades to tyrants
* No more "UnnamedPlayer" bots: bot can not be added if nick is taken

v.12
* Ant algorithm mostly implemented but functional (on testing)

v.11
* Player count on server browser list showing always "0", fixed.

v.10
* Battle-suits are now displayed (before they were not shown)

v.09
* Humans bots can buy and use grenades (they use them against buildings)

v.08
* Weird "possession" bug (player replaced bot) fixed

v.01 ~ 07
* Humans bots aim against buildings fixed
* Bots are now "ready" on intermission
* botcmd BOTNAME give (command added)
* Aliens wall-walking (when available) was prioritized over jumping
* ATCS Path was improved

For requests, comments or follow-ups: 
http://forum.acidtu.be/
