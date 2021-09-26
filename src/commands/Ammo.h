

#ifndef WKTESTSTUFF_AMMO_H
#define WKTESTSTUFF_AMMO_H

#include "../Chat.h"

typedef unsigned long DWORD;

class Ammo : public Command {
public:
	static const int maxWeapon = 70;
private:
	static DWORD* getAmmoTableAddr(int team_id, int weapon_id, int tabletype);
	static void setWeaponAmmoOrDelay(int team_id, int weapon_id, int tabletype, int value);
public:
	virtual std::string help();
	virtual int handle(std::string & message, std::vector<std::string> & parts);
};


#endif //WKTESTSTUFF_AMMO_H
