

#ifndef WKTESTSTUFF_DELETE_H
#define WKTESTSTUFF_DELETE_H

#include "../Chat.h"
#include "../Constants.h"

class Delete : public Command {
public:
	virtual std::string help();
	virtual int handle(std::string & message, std::vector<std::string> & parts);
};

#endif //WKTESTSTUFF_DELETE_H
