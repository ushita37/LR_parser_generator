#include "variable.h"
#include "frontend.cpp"
#include "backend.cpp"
#include "codegenerator.cpp"

int main() {
    string input_name;
//    cout << "Enter .input file name: ";
//    cin >> input_name;
    input_name = "sample1.input";
    ifstream input_stream(input_name);
    if (!input_stream) {
        cerr << "Error: Unable to open input file" << endl;
        return 1;
    }

    int input_section = 0; // 0: before the first section(start), 1: in the token section, 2: in the construction rule section, 3: subroutine section, 4: after the last section(finish)
    string input_line;
    int line_number = 0;
    while (getline(input_stream, input_line)) { // read a line from input_stream
//        cout << "line " << ++line_number << ": ";
//        cout << input_line << endl;
        input_section = frontend_process(input_line, input_section);
    }
    return 0;
}