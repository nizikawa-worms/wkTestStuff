
#ifndef WKLIVESPLIT_SUDOKU_H
#define WKLIVESPLIT_SUDOKU_H

#include "../Chat.h"
class Sudoku : public Command {
public:
	virtual std::string help();
	virtual int handle(std::string & message, std::vector<std::string> & parts);
};


#endif //WKLIVESPLIT_SUDOKU_H
