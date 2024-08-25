#include "variable.h"

using namespace std;

// global variables
vector <string> non_terminal_vec;
string starting_symbol;
// vector<string> is one of production rules correspond to left side
// <vector<vector<string>>> is set of production rules correspond to one left side
map <string, vector<vector<string>>> production_rule_map;

void frontend_section1(string input_line) {
    // get non_terminal vector
    // skip reading "%nset "
    string non_terminal_symbol;

    if (input_line.find("%nset ") == 0) {
        input_line = input_line.substr(6);  // skip "%nset ", get after 6th character

        // get non_terminal vector separated by space
        while (input_line != "\n" && input_line != "\r\n" && !input_line.empty()) {
            // skip spaces
            while (input_line[0] == ' ') {
                input_line = input_line.substr(1);
            }
            // get non-terminal symbol
            non_terminal_symbol = input_line.substr(0, input_line.find(" "));
            non_terminal_vec.push_back(non_terminal_symbol);
            // skip non-terminal symbol which is already read
            input_line = input_line.substr(non_terminal_symbol.size());
        }

        // print non_terminal vector
        cout << "non_terminal vector: ";
        for (int i = 0; i < non_terminal_vec.size(); i++){
            cout << non_terminal_vec[i] << ", ";
        }
        cout << endl;
    }
}

void frontend_section2(string input_line){
    // left side of colon is non-terminal symbol
    // first non-terminal symbol is the start symbol
    string non_terminal_symbol;
    if(starting_symbol.empty() && input_line.find(":") != string::npos){
        starting_symbol = input_line.substr(0, input_line.find(":"));
        cout << "starting symbol: " << starting_symbol << endl;
        non_terminal_symbol = starting_symbol;
    } else if (input_line.find(":") != string::npos){
        non_terminal_symbol = input_line.substr(0, input_line.find(":"));
        cout << "non-terminal symbol: " << non_terminal_symbol << endl;
    } else {
        return;
    }

    // right side of colon is production rule
    vector<string> production_rule;
    input_line = input_line.substr(input_line.find(":")+1); // skip non-terminal symbol and colon
    while (input_line != "\n" && input_line != "\r\n" && !input_line.empty()) {
        // key is non-terminal symbol (left side), value is vector of production rules (right side)

        // skip spaces
        while (input_line[0] == ' ') {
            input_line = input_line.substr(1);
        }
        cout << "input_line=" << input_line << endl;
        // get right side
        string tmp_element = input_line.substr(0, input_line.find(" "));
        production_rule.push_back(tmp_element);
        cout << "space location=" << input_line.find(" ") << ", tmp_element=" << tmp_element << endl;
        if (input_line.find(" ") != string::npos) {
            input_line = input_line.substr(input_line.find(" "));
        } else {
            input_line.clear();    // end of line
        }

    }
    // print production rule
    cout << "production rule=";
    for (int i = 0; i < production_rule.size(); i++){
        cout << production_rule[i] << " ";
    }
    cout << endl;
    production_rule_map[non_terminal_symbol].push_back(production_rule);

}

int frontend_process(string input_line, int input_section){
    // a line begin with "//" is a comment
    if (input_line.find("//") == 0) {
        return input_section;
    } else if (input_line.find("%%") == 0) {
        // "%%" is the separator of sections
        return input_section + 1;
    } else if (input_line.empty()) {    // skip empty line
        return input_section;
    }
    if (input_section == 0){
        input_section = 1;  // start the section1
    }
    if (input_section == 1){
        frontend_section1(input_line);
    }
    if (input_section == 2){
         frontend_section2(input_line);

         cout << "\n\n\n";
            for (auto iter = production_rule_map.begin(); iter != production_rule_map.end(); iter++){
                cout << "key=" << iter->first << ", value=";
                for (int i = 0; i < iter->second.size(); i++){  // print production rules of one non-terminal symbol "key"
                    for (int j = 0; j < iter->second[i].size(); j++){   // print symbols of one production rule
                        cout << iter->second[i][j] << " ";
                    }
                    cout << ", ";
                }
                cout << endl;
            }
    }
    // section 3 will be implemented later
    /*
    if (input_section == 3){
        frontend_section3(input_line);
    }
     */
    return input_section;   // return the number of input_section
}
