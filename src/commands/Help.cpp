
#include "Help.h"
#include "../Debugf.h"
#include <format>

std::string Help::help() {
	return "Print a list of available commands";
}

int Help::handle(std::string &message, std::vector<std::string> &parts) {
	for(auto & it : Chat::getCommands()) {
		debugf("Command: /%s - %s\n", it.first.c_str(), it.second->help().c_str());
		Chat::callShowChatMessage(std::format("/{} - {}", it.first, it.second->help()), 6);
	}
	return 1;
}