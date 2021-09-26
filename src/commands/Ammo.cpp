
#include <stdexcept>
#include "Ammo.h"
#include "../Utils.h"
#include "../W2App.h"
#include "../Debugf.h"

std::string Ammo::help() {
	return "Set weapon ammunition for given team. Usage: /ammo team weapon_id ammo_num | /delay team weapon_id delay_num";
}

int Ammo::handle(std::string &message, std::vector<std::string> &parts) {
	if(parts.size() < 3) throw std::runtime_error("Not enough arguments");
	auto alliance = Utils::stringToAlliance(parts[1]);
	if(!alliance) throw std::runtime_error("Unknown alliance name: " + parts[1]);

	int tabletype = parts[0] == "delay";
	int ammo_num = std::stoi(parts[3]);
	if(parts[2] == "all") {
		for(int i=1; i < maxWeapon; i++) {
			setWeaponAmmoOrDelay(*alliance, i, tabletype, ammo_num);
		}
	} else {
		int weapon_id = std::clamp(std::stoi(parts[2]), 1, maxWeapon);
		setWeaponAmmoOrDelay(*alliance, weapon_id, tabletype, ammo_num);
	}

	return 1;
}

DWORD * Ammo::getAmmoTableAddr(int team_id, int weapon_id, int tabletype) {
	DWORD gameglobal = W2App::getAddrGameGlobal();
	DWORD weaponpanel = *(DWORD *)(gameglobal + 1352);
	int offset = tabletype ? 26104 : 25820;
	return (DWORD*)((*(DWORD *)weaponpanel + 4 * (142 * team_id + weapon_id) + offset));
}

void Ammo::setWeaponAmmoOrDelay(int team_id, int weapon_id, int tabletype, int value) {
	auto ammoptr = getAmmoTableAddr(team_id, weapon_id, tabletype);
	*ammoptr = value;
}
