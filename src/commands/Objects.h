

#ifndef WKTESTSTUFF_OBJECTS_H
#define WKTESTSTUFF_OBJECTS_H


#include "../Chat.h"

class Objects : public Command {
public:
	virtual std::string help();
	virtual int handle(std::string & message, std::vector<std::string> & parts);
};


#endif //WKTESTSTUFF_OBJECTS_H
