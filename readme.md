#wkTestStuff v. 0.2.0
_Worms Armageddon wormkit module that adds some commands to in-game chat. Useful for testing stuff. Use with debug console. Most commands will desynchronize the game, so don't use it in multiplayer games._

## Commands:
- **<tt>/help</tt>** - lists available commands and their parameters
- **<tt>/sudoku red|blue|green|yellow|magent|cyana</tt>** - causes all worms of specified alliance to drown instantly
- **<tt>/objects</tt>** - lists addresses of global objects and ctasks
- **<tt>/delete ctaskname</tt>** - deletes specified ctask objects by type. some object types might crash the game
- **<tt>/ammo team weapon_id|all ammo_num</tt>** - sets ammunition of any weapon. -1 is infinite ammo
- **<tt>/delay team weapon_id|all delay_num</tt>** - sets delay of any weapon
- **<tt>/panel off addition|alpha|dither1|dither2 or 0|1|2|3|4</tt>** - makes weapon panel semi-transparent when pinned with wkPin, using one of 4 blending modes
