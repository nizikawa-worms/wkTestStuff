

#ifndef WKTESTSTUFF_CHAT_H
#define WKTESTSTUFF_CHAT_H

#include <string>
#include <map>
#include <memory>
#include <vector>

class Chat;
class Command {
public:
	virtual std::string help() {return "No description available";}
	virtual void install() {};
	virtual int handle(std::string & message, std::vector<std::string> & parts) = 0;
};

class Chat {
private:
	static int onChatInput(int a1, char * msg, int a3);
	static void __stdcall hookOnChatInput(int a3);

	static inline std::map<std::string, std::unique_ptr<Command>> commands;
public:
	static void install();
	static void registerCommand(std::string name, std::unique_ptr<Command> command);
	static void callShowChatMessage(std::string msg, int color);
	static const std::map<std::string, std::unique_ptr<Command>> &getCommands();
};


#endif //WKTESTSTUFF_CHAT_H
