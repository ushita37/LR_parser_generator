#ifndef LR0_SYNTAX_H
#define LR0_SYNTAX_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

extern std::vector <std::string> non_terminal_vec;
extern std::string starting_symbol;
extern std::map <std::string, std::vector<std::vector<std::string>>> production_rule_map;


#endif //LR0_SYNTAX_H
