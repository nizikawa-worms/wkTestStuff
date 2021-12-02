

#ifndef WKTESTSTUFF_WEAPONPANEL_H
#define WKTESTSTUFF_WEAPONPANEL_H

#include "../Chat.h"

class WeaponPanel : public Command {
private:
	static void DrawWeaponPanel_patch1();
	static inline int transparencyMode = 0;
	static inline std::map<std::string, int> modes = {
			{"off", 0}, {"addition", 0x200000}, {"alpha", 0x4000000}, {"dither1", 0x8000000}, {"dither2", 0x10000000},
			{"0", 0}, {"1", 0x200000}, {"2", 0x4000000}, {"3", 0x8000000}, {"4", 0x10000000}
			};
	static int parseMode(const std::string & name);
public:
	virtual std::string help();
	virtual int handle(std::string & message, std::vector<std::string> & parts);
	virtual void install();
};


#endif //WKTESTSTUFF_WEAPONPANEL_H
