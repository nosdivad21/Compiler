#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <functional>


using namespace std;
void scan(ifstream& inputFile, ofstream& outputFile,  function<int(char)> charToNum) {
    
    int table[30][17] = {
        {2, 4, 6, 7, 8, 9, 12, 15, 18, 22, 23, 24, 25, 26, 27, 28, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {2, 2, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {5, 4, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {11, 11, 11, 11, 11, 10, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {14, 14, 14, 14, 14, 13, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {17, 17, 17, 17, 17, 16, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {19, 19, 19, 19, 20, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {20, 20, 20, 20, 21, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20},
        {20, 20, 20, 20, 20, 20, 20, 20, 0, 20, 20, 20, 20, 20, 20, 20, 20},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {1, 1, 1, 1, 1, 29, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
    };

    string reserved1[] = {"CONST", "IF", "VAR", "THEN", "PROCEDURE",
                          "WHILE", "CALL", "DO", "ODD", "Class", "GET", "PRINT"};
    
    //set<string> reserved_output = {}

    string word;
    string ostr;
    char ch;
    int current_state;
    int row;
    int state;
    int num_holder;
    bool isTrue = true;
    bool keepgoing = true;
    int index;
    int cnt;
    int reserve;
    string last_input;
    while (inputFile.get(ch)) { // Read characters until the end of the file
        if (keepgoing == false){
            throw std::runtime_error("Incorrect code");
            std::cout << "Incorrect code" << std::endl;
        }

        if (isspace(ch)) {
            continue;
        }

            word.clear(); 
            state = charToNum(ch);
            row = table[0][state];
            current_state = table[row][state];
            //std::cout << state << std::endl;
            
            switch (state) {
            case 0: 
                //std::cout << "Case 0" << std::endl;
                reserve = 0;
                word += ch;
                ch = inputFile.peek();
                num_holder = charToNum(ch);
                while(num_holder == 0 || num_holder == 1){
                    word += ch;
                    ch = inputFile.get();
                    ch = inputFile.peek();
                    num_holder = charToNum(ch);
                }
                for (int i = 0; i <= 10; i++) {
                    if (word == reserved1[i]){
                        reserve = i;
                    }
                }

                if (reserve != 0) {
                    ostr = word + " " + reserved1[reserve];
                    outputFile << ostr << endl;
                    last_input = reserved1[reserve];
                    break;
                } 
                else {
                    if (last_input == "Class"){
                        ostr = word + " ProgramName";
                        outputFile << ostr << endl;
                        last_input = " ";
                        break; 
                    }
                    else {
                        ostr = word + " id";
                        outputFile << ostr << endl;
                        break;
                    }
                }
            case 1:
                //std::cout << "Case 1" << std::endl;
                word += ch;
                ch = inputFile.peek();
                num_holder = charToNum(ch);
                while(num_holder == 1){
                    word += ch;
                    ch = inputFile.get();
                    ch = inputFile.peek();
                    num_holder = charToNum(ch);
                }
                word = "LIT" + word;
                ostr = word + " numLit";
                outputFile << ostr << endl;
                break;
            case 2:
                //std::cout << "Case 2" << std::endl;
                word += ch;
                ostr = word + " addop";
                outputFile << ostr << endl;
                break;
                
            case 3:
                
                word += ch;
                ostr = word + " addop";
                outputFile << ostr << endl;
                break;
                
            case 4:
                
                word += ch;
                ostr = word + " mop";
                outputFile << ostr << endl;
                break;
                
            case 5:
                
                word += ch;
                ch = inputFile.peek();
                if (ch == '='){
                    word += ch;
                    ostr = word + " relop";
                    outputFile << ostr << endl;
                    ch = inputFile.get();
                }
                else {
                    ostr = word + " $=";
                    outputFile << ostr << endl;
                }
                break;
                
            case 6:
                
                word += ch;
                ch = inputFile.peek();
                if (ch == '='){
                    word += ch;
                    ostr = word + " relop";
                    outputFile << ostr << endl;
                    ch = inputFile.get();
                }
                else {
                    ostr = word + " relop";
                    outputFile << ostr << endl;
                }
                break;
                
            case 7:
                
                word += ch;
                ch = inputFile.peek();
                if (ch == '='){
                    word += ch;
                    ostr = word + " relop";
                    outputFile << ostr << endl;
                }
                else {
                    ostr = word + " relop";
                    outputFile << ostr << endl;
                }
                break;
                
            case 8:
                
                word += ch;
                ch = inputFile.peek();
                if (ch == '*'){
                    ch = inputFile.get();
                    while(isTrue){
                        ch = inputFile.get();
                        if(ch == '*'){
                            ch = inputFile.peek();
                            if(ch == '/'){
                                isTrue = false;
                                ch = inputFile.get();
                            }
                        }
                    }
                }
                else{
                    ostr = word + " mop";
                    outputFile << ostr << endl;
                }
                break;
                
            case 9:
                word += ch;
                ostr = word + " Lcurly";
                outputFile << ostr << endl;
                break;
            case 10:
                word += ch;
                ostr = word + " Rcurly";
                outputFile << ostr << endl;
                break;
            case 11:
                word += ch;
                ostr = word + " comma";
                outputFile << ostr << endl;
                break;
            case 12:
                word += ch;
                ostr = word + " semi";
                outputFile << ostr << endl;
                break;
            case 13:
                word += ch;
                ostr = word + " Lparen";
                outputFile << ostr << endl;
                break;
            case 14:
                word += ch;
                ostr = word + " Rparen";
                outputFile << ostr << endl;
                break;
            case 15:
                word += ch;
                ch = inputFile.peek();
                if (ch == '='){
                    word += ch;
                    ostr = word + " relop";
                    outputFile << ostr << endl;
                    ch = inputFile.get();
                }
                else {

                    keepgoing = false;
                }
                break;
            case 16:
                keepgoing = false;
            default:
                break;
            }   
               

        

    // if (!word.empty()) { // Output the last word if it's not empty
    //     outputFile << word << endl;
    //}
    }
}

int charToNum(char ch){
    if ((ch >= 'a' && ch <= 'z') || (ch>= 'A' && ch <= 'Z')) {
        return 0;
    } 
    else if ((ch == '0') || (ch == '1') || (ch == '2') || (ch == '3') || (ch == '4') || (ch == '5') ||
             (ch == '6') || (ch == '7') || (ch == '8') || (ch == '9')){
        return 1;
    }
    else if (ch == '+'){
        return 2;
    }
    else if (ch == '-'){
        return 3;
    }
    else if (ch == '*'){
        return 4;
    }
    else if (ch == '='){
        return 5;
    }
    else if (ch == '<'){
        return 6;
    }
    else if (ch == '>'){
        return 7;
    }
    else if (ch == '/'){
        return 8;
    }
    else if (ch == '{'){
        return 9;
    }
    else if (ch == '}'){
        return 10;
    }
    else if (ch == ','){
        return 11;
    }
    else if (ch == ';'){
        return 12;
    }
    else if (ch == '('){
        return 13;
    }
    else if (ch == ')'){
        return 14;
    }
    else if (ch == '!'){
        return 15;
    }
    else {
        return 16;
    }  
}

int main() {
    ifstream inputFile("SampleCode.txt"); // Open the input file
    ofstream outputFile("output.txt"); // Open the output file

    if (!inputFile) { // Check if the input file failed to open
    cerr << "Unable to open input file!" << endl;
    return 1;
        }

    if (!outputFile) { // Check if the output file failed to open
        cerr << "Unable to open output file!" << endl;
        return 1;
    }


    
    scan(inputFile, outputFile, charToNum); // Call the function to scan and write words

    inputFile.close(); // Close the input file
    outputFile.close(); // Close the output file

    return 0;
}