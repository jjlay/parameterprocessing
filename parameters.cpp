//
// STL includes
//

#include <map>

//
// Standard includes
//

#include <string>
#include <iostream>
#include <fstream>


//
// Prototypes
//

std::map<std::string, std::string> fetchJSON(std::string filename);
std::string trim(std::string inString);


//
// Function: parameters()
//

std::map<std::string, std::string> parameters(int argc, char *argv[]) {

    std::map<std::string, std::string> p;

    // Parameter 0 is always the program
    p["_EXECUTABLE"] = argv[0];

    std::string sw, pa;

    for (int i = 1; i < argc; i++) {
        if (argv[i][0] == '-') {
            // We have a switch
            sw = &argv[i][1];

            // Its parameter is the next item if it
            // doesn't start with a -
            if ((i < (argc-1)) && (argv[i+1][0] != '-')) {
                pa = argv[i+1];
                i++;

                p[sw] = pa;
            }
            else {
                // Otherwise the switch is the
                // parameter
                p[sw] = "";
            }
        }
    }

    for (auto v : p) {
        if (v.first == "JSON") {
            auto json = fetchJSON(v.second);
        }

    }
    return p;
}


//
// Function: fetchJSON()
//

std::map<std::string, std::string> fetchJSON(std::string filename) {

    std::map<std::string, std::string> p;
    std::string sw, pa;

    std::fstream file;
    file.open(filename, std::ios::in);

    if (!file.is_open()) {
        std::cerr << "Unable to open " << filename << std::endl;
    }
    
    std::string line;

    int start = 0;

    while (std::getline(file, line)) {
        if (line == "{") {
            if (start == 0)
                start = 1;
            else {
                std::cerr << "JSON file has syntax error" << std::endl;
                exit(-1);
            }
        }

        if (line == "}") {
            if (start == 1)
                start = 0;
            else {
                std::cerr << "JSON file has syntax error" << std::endl;
                exit(-1);
            }
        }

        if ((line != "{") && line != "}" && line.size() > 0) {
            std::cout << "Processing :: " << line << std::endl;
            line = trim(line);
            std::cout << "Line is :: " << line << std::endl;
        }


    }
    
    
    
    file.close();

    return p;
}


std::string trim(std::string inString) {
    std::string s;

    for (auto i = 0; i < inString.size(); i++) {
        auto c = inString.substr(i, 1).c_str();

        if (c[0] != 32)
            s += c;
    }

    return s;
}

