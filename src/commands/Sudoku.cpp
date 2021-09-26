

#include "Sudoku.h"
#include "../W2App.h"
#include "../entities/CGameTask.h"
#include "../entities/CTaskTeam.h"
#include "../entities/CTaskWorm.h"
#include "../Debugf.h"
#include "../Utils.h"


int Sudoku::handle(std::string &message, std::vector<std::string> &parts) {
	if(parts.size() < 2) throw std::runtime_error("Not enough arguments");
	auto alliance = Utils::stringToAlliance(parts[1]);
	if(!alliance) throw std::runtime_error("Unknown alliance name: " + parts[1]);

	auto ddgame = W2App::getAddrDdGame();
	CTask * turngame = *(CTask**)(ddgame + 0x8);
	for(auto child : turngame->children) {
		if(child->classtype == Constants::ClassType::ClassType_Task_Team) {
			CTaskTeam * team = (CTaskTeam*)child;
			if(team->unknown44 == *alliance) {
				for(auto child2 : team->children) {
					if(child2->classtype == Constants::ClassType::ClassType_Task_Worm) {
						CTaskWorm * worm = (CTaskWorm*)child2;
						worm->vtable38_SetState(133); // drown
					}
				}
			}
		}
	}

	return 1;
}

std::string Sudoku::help() {
	return "Drown all teams belonging to specified alliance. Usage: /sudoku red|blue|green|yellow|magenta|cyan";
}
