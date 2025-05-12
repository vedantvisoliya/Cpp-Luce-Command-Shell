#include <iostream>
#include <string>
#include <fstream>
#include <filesystem>
#include <iomanip>
#include <ctime>
using namespace std;
namespace fs = filesystem; 

enum validCommands{
    echo,
    exit0,
    invalid,
    type,
    clear,
    cls,
    ls,
    cd,
    touch,
    del,
    rm,
    find0,
    getDate,
    mkdir,
    md,
    rmdir,
    rd,
    rename0
};

validCommands isValid(string command){
    command = command.substr(0,command.find(' '));
    if(command == "echo"){return validCommands::echo;}
    if(command == "exit"){return validCommands::exit0;}
    if(command == "type"){return validCommands::type;}
    if(command == "cls"){return validCommands::cls;}
    if(command == "clear"){return validCommands::clear;}
    if(command == "ls"){return validCommands::ls;}
    if(command == "cd"){return validCommands::cd;}
    if(command == "touch"){return validCommands::touch;}
    if(command == "del"){return validCommands::del;}
    if(command == "rm"){return validCommands::rm;}
    if(command == "find"){return validCommands::find0;}
    if(command == "get-date"){return validCommands::getDate;}
    if(command == "mkdir"){return validCommands::mkdir;}
    if(command == "md"){return validCommands::md;}
    if(command == "rmdir"){return validCommands::rmdir;}
    if(command == "rd"){return validCommands::rd;}
    if(command == "rename"){return validCommands::rename0;}
    return validCommands::invalid;
}

bool isValidType(string command){
    if(isValid(command) == echo){return true;} 
    if(isValid(command) == exit0){return true;}
    if(isValid(command) == type){return true;}
    if(isValid(command) == cls){return true;}
    if(isValid(command) == clear){return true;}
    if(isValid(command) == cd){return true;}
    if(isValid(command) == touch){return true;}
    if(isValid(command) == del){return true;}
    if(isValid(command) == rm){return true;}
    if(isValid(command) == find0){return true;}
    if(isValid(command) == getDate){return true;}
    if(isValid(command) == mkdir){return true;}
    if(isValid(command) == md){return true;}
    if(isValid(command) == rmdir){return true;}
    if(isValid(command) == rd){return true;}
    if(isValid(command) == rename0){return true;}
    return false;
} 

void listDirectoryContent(){
    const string dirPath = ".";

    try{
        // checking if the path is valid
        if(!fs::is_directory(dirPath)){
            cerr << "\033[31m" << "Error" << ": directory not found" << "\033[0m" << endl;
            return;
        }

        // iterating through the current directory

        cout << left << setw(30) << "Name"
             << setw(15) << "Type"
             << "Size (Byte)" << endl;
        cout << string(60, '-') << endl;
        for(const auto& entry : fs::directory_iterator(dirPath)){
            string name = entry.path().filename().string();
            string type = entry.is_directory() ? "Directory":"File";
            uintmax_t size = entry.is_regular_file() ? fs::file_size(entry):0;
            
            cout << left << setw(30) << name
                 << setw(15) << type
                 << size << endl;
        }
    }
    catch(const fs::filesystem_error& e){
        cerr << "\033[31m" << "Error accessing directory: " << e.what() << "\033[0m" << endl;
    }
}

void getCurrentPath(){
    string currentPath = fs::current_path().string();
    try{    
        cout << "LCS " << currentPath;  
    }
    catch (const fs::filesystem_error& e){
        cerr << "\033[31m" << "Error accessing path: " << e.what() << "\033[0m" << endl;
    }
}

void changeDirectory(string newPath){
    try{
        fs::current_path(newPath);
    }
    catch (const fs::filesystem_error& e){
        cerr << "\033[31m" << "Error: " << e.what() << "\033[0m" << endl;
    }
}

void createFile(string fileName){
    try{
        if(fs::exists(fileName)){
            cerr << "\033[31m" << "Error: " << "\033[36m" << fileName << "\033[31m" << " already exists" << "\033[0m" << endl;
        }
        else{
            ofstream file(fileName);
            cout << "\033[32m" << "\033[36m" << fileName << "\033[32m" << ": created successfully" << "\033[0m" << endl;
        }
    }
    catch (const exception& e){
        cerr << "\033[31m" << "Error: " << e.what() << "\033[0m" << endl;
    }
}

void removeFileDir(string fileDirName){
    if(fs::exists(fileDirName)){
        fs::remove(fileDirName);
        cout << "\033[36m" << fileDirName << "\033[32m" << " removed successfully" << "\033[0m" << endl;
    }
    else{
        cerr << "\033[31m" << "Error: " << "\033[36m" << fileDirName << "\033[31m" << " does not exists" << "\033[0m" << endl;
    }
}

void checkFileOrDirExists(string fileOrDir){
    if(fs::exists(fileOrDir)){
        cout << "\033[36m" <<  fileOrDir << "\033[32m" << ": found" << "\033[0m" << endl;
    }
    else{
        cerr << "\033[31m" << "Error: " << "\033[36m" << fileOrDir << " not found" << "\033[0m" << endl;
    }
}

void getDateTime(){
    time_t timestamp;
    time(&timestamp);
    cout << endl;
    cout << "\033[1;34m" << ctime(&timestamp) << "\033[0m" << endl;
}

void createDir(string dirName){
    try{
        if(fs::exists(dirName)){
            cerr << "\033[31m" << "Error: " << "\033[36m" << dirName << "\033[31m" << " already exists" << "\033[0m" << endl;
        }
        else{
            fs::create_directory(dirName);
            cout << "\033[36m" << dirName << "\033[32m" << ": created successfully" << "\033[0m" << endl;
        }
    }
    catch (const fs::filesystem_error& e){
        cerr << "\033[31m]" << "Error: " << e.what() << "\033[0m" << endl;
    }
}

void renameFileDir(string& input) {
    input = input.erase(0, input.find(' ')+1);
    string oldName = input.substr(0, input.find('^'));
    string newName = input.substr(input.find('^')+1);
    try {
        if (fs::exists(oldName)) {
            if (fs::exists(newName)) {
                cerr << "\033[31m" << "Error: '" << "\033[36m" << newName << "\033[31m" << "' already exists." << "\033[0m" << endl;
                return;
            } else {
                fs::rename(oldName, newName);
                cout << "\033[32m]" << "'" << "\033[36m" << oldName << "\033[36m" << "' renamed to '" << "\033[36m" << newName << "\033[32m" << "' successfully." << "\033[0m" << endl;
            }
        } else {
            cerr << "\033[31m" << "Error: '" << "\033[36m" << oldName << "\033[31m" << "' does not exist." << "\033[0m" << endl;
        }
    } catch (const fs::filesystem_error& e) {
        cerr << "\033[31m" << "Error: " << e.what() << "\033[0m" << endl;
    }
}

int main(){
    cout << "LUCE SHELL Version[1.0.0, 2024]" << endl;
    cout << "Copyright (C) Vedant Visoliya. All rights reserved." << endl;
    // varibles
    bool done = false;
    string input;
    string newPath;
    // looping

    do{
        getCurrentPath();

        cout << "$ ";
        cout << "\033[1;35m";
        getline(cin, input);
        cout << "\033[0m";

        switch (isValid(input)){
            case exit0:
                done = true;
                break;
            case echo:
                input = input.substr(input.find(" ")+1, input.length());
                cout << input << endl;
                break;
            case type:
                input = input.substr(input.find(" ")+1, input.length());
                if(isValidType(input))
                {
                    cout << input << " is a builtin command" << endl;
                }
                else{
                    cout << input << ": command not found" << endl;
                }
                break;
            case clear:
                cout << "\033[2J\033[H" << endl;
                break;
            case cls:
                cout << "\033[2J\033[H" << endl;
                break;
            case ls:
                listDirectoryContent();
                break;
            case cd:
                newPath = fs::current_path().string();
                input = input.substr(input.find(" ")+1, input.length());
                if(input == ".."){
                    changeDirectory(input);
                }
                else if (input == "/"){
                    changeDirectory(input);
                }
                else{
                    newPath = newPath + "\\" + input;
                    changeDirectory(newPath);
                } 
                break;
            case touch:
                input = input.substr(input.find(" ")+1, input.length());
                createFile(input);
                break;
            case del:
                input = input.substr(input.find(" ")+1, input.length());
                removeFileDir(input);
                break;
            case rm:
                input = input.substr(input.find(" ")+1, input.length());
                removeFileDir(input);
                break;
            case find0:
                input = input.substr(input.find(" ")+1, input.length());
                checkFileOrDirExists(input);
                break;
            case getDate:
                getDateTime();
                break;
            case mkdir:
                input = input.substr(input.find(" ")+1, input.length());
                createDir(input);
                break;
            case md:
                input = input.substr(input.find(" ")+1, input.length());
                createDir(input);
                break;
            case rmdir:              
                input = input.substr(input.find(" ")+1, input.length());
                removeFileDir(input);
                break;
            case rd:
                input = input.substr(input.find(" ")+1, input.length());
                removeFileDir(input);
                break;
            case rename0:
                renameFileDir(input);
                break;
            default:
                input = input.substr(0, input.find(" "));
                cout << input << ": command not found" << endl;
                break;
        }

    }while(!done);
    return 0;
}