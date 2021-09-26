

#ifndef WKTESTSTUFF_HELP_H
#define WKTESTSTUFF_HELP_H

#include "../Chat.h"

class Help : public Command {
public:
	virtual std::string help();
	virtual int handle(std::string & message, std::vector<std::string> & parts);
};


#endif //WKTESTSTUFF_HELP_H
