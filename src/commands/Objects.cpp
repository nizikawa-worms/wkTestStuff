
#include "Objects.h"
#include "../W2App.h"
#include "../entities/CTask.h"
#include "../Debugf.h"
#include "../Constants.h"

std::string Objects::help() {
	return "Lists global and ctask objects";
}

int Objects::handle(std::string &message, std::vector<std::string> &parts) {
	auto ddgame = W2App::getAddrDdGame();
	CTask * turngame = *(CTask**)(ddgame + 0x8);

	debugf("DDGame: 0x%X DDMain: 0x%X GameGlobal: 0x%X DDDisplay: 0x%X W2Wrapper: 0x%X\n", ddgame, W2App::getAddrDDMain(), W2App::getAddrGameGlobal(), W2App::getAddrDdDisplay(), W2App::getAddrW2Wrapper());

	turngame->traverse([&](CTask * obj, const int level) {
		for(int i=0; i < level; i++) printf("\t");
		printf("Obj: 0x%X Type: %d (%s)\n", obj, obj->classtype, (Constants::CTtoSTR.find(obj->classtype) != Constants::CTtoSTR.end()) ? Constants::CTtoSTR.at(obj->classtype).c_str() : "???");
	});
	return 1;
}
