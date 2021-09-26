#ifndef WKTESTSTUFF_CONFIG_H
#define WKTESTSTUFF_CONFIG_H

#include <string>
#include <json.hpp>
#include <set>
#include <filesystem>

class Config {
public:
	static inline const std::string iniFile = "wkTestStuff.ini";
	static inline const std::string moduleName = "wkTestStuff";

private:
	static inline bool moduleEnabled = true;
	static inline bool devConsoleEnabled = true;
	static inline bool ignoreVersionCheck = false;
	static inline bool useOffsetCache = true;

	static inline std::filesystem::path waDir;
public:
	static void readConfig();
	static bool isModuleEnabled();
	static bool isDevConsoleEnabled();
	static int waVersionCheck();

	static std::string getVersionStr();
	static std::string getBuildStr();
	static std::string getModuleStr();
	static std::string getFullStr();

	static const std::filesystem::path &getWaDir();

	static bool isUseOffsetCache();
	static std::string getWaVersionAsString();
};


#endif //WKTESTSTUFF_CONFIG_H
