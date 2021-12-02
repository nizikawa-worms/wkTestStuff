
#include "WeaponPanel.h"
#include "../Debugf.h"
#include <format>
#include "../Hooks.h"

std::string WeaponPanel::help() {
	return "Set weapon panel transparency mode when pinned with wkPin. Usage: /panel off | addition | alpha | dither1 | dither2 OR /panel 0 | 1 | 2 | 3 | 4";
}

int WeaponPanel::parseMode(const std::string & name) {
	auto it = modes.find(name);
	if(it == modes.end()) throw std::runtime_error("Unknown blending mode: " + name);
	return it->second;
}

int WeaponPanel::handle(std::string &message, std::vector<std::string> &parts) {
	if(parts.size() < 2) throw std::runtime_error("Not enough arguments");
	transparencyMode = parseMode(parts[1]);
	return 1;
}


DWORD addrDrawWeaponPanel_ret;
void __declspec(naked) WeaponPanel::DrawWeaponPanel_patch1() {
	_asm cmp [esi+0x1DC], 0
	_asm jz transparent
_asm normal:
	_asm push 0
	_asm jmp docall
_asm transparent:
	_asm push transparencyMode
_asm docall:
	_asm push ebx
	_asm push edi
	_asm push 0
	_asm push eax
	_asm jmp addrDrawWeaponPanel_ret
}


void WeaponPanel::install() {
	transparencyMode = parseMode(Config::getPanelTransparency());
	DWORD addrDrawWeaponPanel = _ScanPattern("DrawWeaponPanel", "\x8B\x86\x00\x00\x00\x00\x83\xEC\x10\x85\xC0\x53\x55\x57\x0F\x84\x00\x00\x00\x00\x8B\x5E\x50\x8B\x7E\x4C\x8B\x0E\x8B\x81\x00\x00\x00\x00\x6A\x00\x53\x57\x6A\x00\x50\x8B\x81\x00\x00\x00\x00", "??????xxxxxxxxxx????xxxxxxxxxx????xxxxxxxxx????");
	// addrDrawWeaponPanel = 005695A2
	DWORD addrDrawWeaponPanel_patch1 = addrDrawWeaponPanel + 0x22;
	addrDrawWeaponPanel_ret = addrDrawWeaponPanel + 0x29;
	_HookAsm(addrDrawWeaponPanel_patch1, (DWORD) &DrawWeaponPanel_patch1);
}
