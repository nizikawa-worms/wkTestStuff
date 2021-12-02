
#include "Chat.h"
#include "Hooks.h"
#include "Utils.h"
#include "Debugf.h"
#include "commands/Sudoku.h"
#include "commands/Help.h"
#include "commands/Ammo.h"
#include "commands/Delete.h"
#include "commands/Objects.h"
#include "commands/WeaponPanel.h"
#include "W2App.h"

int Chat::onChatInput(int a1, char * msg, int a3) {
	std::string message(msg);
//	debugf("onChatInput: msg: %s\n", message.c_str());
	if(message.starts_with("/") and message.length() > 1) {
		message.erase(0, 1);
		std::vector<std::string> parts;
		Utils::tokenize(message, " ", parts);
		auto it = commands.find(parts[0]);
		if(it != commands.end()) {
			try {
				return it->second->handle(message, parts);
			} catch(std::exception & e) {
				debugf("Exception while executing command: %s\n", e.what());
				callShowChatMessage(std::format("Error: {}", e.what()), 1);
				return 0;
			}
		}
	}

	return 0;
}

DWORD origOnChatInput = 0;
int __stdcall callOriginalOnChatInput(int a1, char * msg, int a3) {
	_asm mov ecx, a1
	_asm mov eax, msg
	_asm push a3
	_asm call origOnChatInput
}

#pragma optimize( "", off )
char* onchat_eax;
int onchat_ecx;
void __stdcall Chat::hookOnChatInput(int a3) {
	_asm mov onchat_eax, eax
	_asm mov onchat_ecx, ecx
	if(!onChatInput(onchat_ecx, (char*)onchat_eax, a3)) {
		callOriginalOnChatInput(onchat_ecx, onchat_eax, a3);
	}
}
#pragma optimize( "", on )

void Chat::registerCommand(std::string name, std::unique_ptr<Command> command) {
	command->install();
	commands[name] = std::move(command);
}

void (__stdcall *addrShowChatMessage)(DWORD addrResourceObject, int color, char * msg, int unk);
void Chat::callShowChatMessage(std::string msg, int color) {
	auto ddgame = W2App::getAddrDdGame();
	if (!ddgame) return;
	addrShowChatMessage(ddgame, color, (char*)msg.c_str(), 1);
}

void Chat::install() {
	DWORD addrOnChatInput = _ScanPattern("OnChatInput", "\x81\xEC\x00\x00\x00\x00\x55\x56\x57\x8B\xF8\x8A\x07\x84\xC0\x8B\xF1\x0F\x84\x00\x00\x00\x00\x3C\x2F\x0F\x85\x00\x00\x00\x00\x8D\x44\x24\x40", "??????xxxxxxxxxxxxx????xxxx????xxxx");
	_HookDefault(OnChatInput);

	addrShowChatMessage = (void (__stdcall *)(DWORD, int, char *, int))
			_ScanPattern("ShowChatMessage", "\x81\xEC\x00\x00\x00\x00\x53\x55\x8B\xAC\x24\x00\x00\x00\x00\x80\xBD\x00\x00\x00\x00\x00\x8B\x85\x00\x00\x00\x00\x8B\x48\x24\x56\x8B\xB1\x00\x00\x00\x00\x57", "??????xxxxx????xx?????xx????xxxxxx????x");


	registerCommand("sudoku", std::make_unique<Sudoku>());
	registerCommand("help", std::make_unique<Help>());
	registerCommand("ammo", std::make_unique<Ammo>());
	registerCommand("delay", std::make_unique<Ammo>());
	registerCommand("delete", std::make_unique<Delete>());
	registerCommand("objects", std::make_unique<Objects>());
	registerCommand("panel", std::make_unique<WeaponPanel>());

}


const std::map<std::string, std::unique_ptr<Command>> &Chat::getCommands() {
	return commands;
}

