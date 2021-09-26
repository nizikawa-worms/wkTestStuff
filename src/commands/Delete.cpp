

#include "Delete.h"
#include "../Constants.h"
#include "../W2App.h"
#include "../entities/CTask.h"
#include "../entities/CGameTask.h"
#include "../Debugf.h"

std::string Delete::help() {
	std::string msg = "Deletes all objects by type on map: /delete ";
	for(auto it : Constants::StrToCT) {
		msg += it.first + "|";
	}
	return msg;
}

int Delete::handle(std::string &message, std::vector<std::string> &parts) {
	if(parts.size() < 2) throw std::runtime_error("Not enough arguments");
	auto it = Constants::StrToCT.find(parts[1]);
	if(it == Constants::StrToCT.end()) throw std::runtime_error("Unknown classtype: " + parts[1]);

	Constants::ClassType classType = it->second;
	auto ddgame = W2App::getAddrDdGame();
	CTask * turngame = *(CTask**)(ddgame + 0x8);

	std::vector<CTask*> toDelete;
	turngame->traverse([&](CTask * obj, const int level) {if(obj->classtype == classType) toDelete.push_back(obj);});
	for(auto obj : toDelete) {
		obj->vtable4_Free(1);
	}
	return 1;
}
