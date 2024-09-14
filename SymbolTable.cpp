#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <functional>


using namespace std;

void scanToken(ifstream& inputFile, ofstream& outputFile, function<int(string)> charToNum, function<void(string, string, string, string, ofstream&)> ArrOut) {

    // Define the 2D array with the given data
    int table[14][14] = {
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2},
        {3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3},
        {3, 3, 3, 4, 3, 3, 10, 3, 3, 8, 11, 3, 12, 13},
        {5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5},
        {6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6},
        {7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7},
        {3, 3, 3, 3, 3, 3, 3, 4, 3, 3, 3, 3, 3, 3},
        {9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9},
        {3, 3, 3, 3, 3, 3, 3, 8, 3, 3, 3, 3, 3, 3},
        {3, 3, 3, 4, 3, 3, 10, 3, 3, 8, 11, 3, 12, 13},
        {11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11},
        {3, 3, 3, 4, 3, 3, 10, 3, 3, 8, 11, 3, 12, 13},
        {3, 3, 3, 4, 3, 3, 10, 3, 3, 8, 11, 3, 12, 13}
    };

    string killme[100];
    
    
    string word;
    string type;
    string symbol;
    string classification;
    string value;
    int input;
    int state = 0;
    int counter = 0;
    int checker;
    int add = 0;
    int j = 0;

    while (inputFile >> word >> type){
        input = charToNum(type);
        state = table[state][input];

        switch(state){
            case 1: 
                break;
            case 2: 
                ArrOut(word, type, "0", "CS", outputFile);
                break;
            case 3: 
                break;
            case 4:
                break;
            case 5:
                symbol = word;
                classification = "ConstVar";
                break;
            case 6:
                break;
            case 7: 
                value = word.substr(3);
                ArrOut(symbol, classification, value, "DS", outputFile);
                break;
            case 8:
                break;
            case 9:
                symbol = word;
                classification = "Var";
                ArrOut(symbol, classification, "0", "DS", outputFile);
                break;
            case 10:
                add = 0;
                symbol = word;
                classification = "NumericLiteral";
                value = word.substr(3);
                for (int i = 0; i < 100; i++) {

                    if (killme[i] == value) {
                        add = 1;
                    }
                }
                if (add == 1){
                }
                else{
                    ArrOut(symbol, classification, value, "DS", outputFile);
                    killme[j] = value;
                    j++;
                }  

                
            case 11:
                break;
            case 12:
                break;
            case 13:
                classification = type;
                inputFile >> word >> type;
                symbol = word;
                ArrOut(symbol, classification, "0", "CS", outputFile);
                break;
        }
    }
    ArrOut("T1", "VarInt", "0", "DS", outputFile);
    ArrOut("T2", "VarInt", "0", "DS", outputFile);
    ArrOut("T3", "VarInt", "0", "DS", outputFile);
    ArrOut("T4", "VarInt", "0", "DS", outputFile);
    ArrOut("T5", "VarInt", "0", "DS", outputFile);
    ArrOut("T6", "VarInt", "0", "DS", outputFile);
    ArrOut("T7", "VarInt", "0", "DS", outputFile);
    ArrOut("T8", "VarInt", "0", "DS", outputFile);
    ArrOut("T9", "VarInt", "0", "DS", outputFile);
    ArrOut("T10", "VarInt", "0", "DS", outputFile);
    
}


void ArrOut(string x, string y, string value, string segment, ofstream& outputFile){
    static int CSaddress = 0;
    static int DSaddress = 0;
    string ostr;
    string str_add;
    if (segment == "CS"){
        str_add = to_string(CSaddress);
        ostr = x + " " + y + " " + value + " " + str_add + " " + segment;
        outputFile << ostr << endl;
        CSaddress = CSaddress + 2;
    } 
    else {
        str_add = to_string(DSaddress);
        ostr = x + " " + y + " " + value + " " + str_add + " " + segment;
        outputFile << ostr << endl;
        DSaddress = DSaddress + 2;
    }
}

int charToNum(string ch){
    if (ch == "Class") {
        return 0;
    } 
    else if (ch == "ProgramName"){
        return 1;
    }
    else if (ch == "{"){
        return 2;
    }
    else if (ch == "CONST"){
        return 3;
    }
    else if (ch == "id"){
        return 4;
    }
    else if (ch == "$="){
        return 5;
    }
    else if (ch == "numLit"){
        return 6;
    }
    else if (ch == "comma"){
        return 7;
    }
    else if (ch == "semi"){
        return 8;
    }
    else if (ch == "VAR"){
        return 9;
    }
    else if (ch == "EOF"){
        return 10;
    }
    else if (ch == "IF" || ch == "THEN" || ch == "WHILE"
            || ch == "DO" || ch == "ODD"){
        return 12;
    }
    else if (ch == "PROCEDURE" || ch == "CALL"){
        return 13;
    }
    else {
        return 11;
    }  
}

int main() {
    ifstream inputFile("output.txt"); // Open the input file
    ofstream outputFile("SampleTable.txt"); // Open the output file

    if (!inputFile) { // Check if the input file failed to open
    cerr << "Unable to open input file!" << endl;
    return 1;
        }

    if (!outputFile) { // Check if the output file failed to open
        cerr << "Unable to open output file!" << endl;
        return 1;
    }

   
    scanToken(inputFile,outputFile, charToNum, ArrOut);
   

    inputFile.close(); // Close the input file
    outputFile.close(); // Close the output file

    return 0;
}