
#if !defined COMMANDLINEPARSER_H
#define COMMANDLINEPARSER_H

#include <vector>
#include <string>
#include <map>
class CommandLineParser
{
public:

    CommandLineParser(int argc_, char * argv_[],bool switches_on_=false);
    ~CommandLineParser() {}

    std::string get_arg(int i);
    std::string get_arg(std::string s);

private:

    int argc;
    std::vector<std::string> argv;

    bool switches_on;
    std::map<std::string,std::string> switch_map;
};
#endif // !defined(COMMANDLINEPARSER_H)
