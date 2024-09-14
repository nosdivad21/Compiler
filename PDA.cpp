#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <functional>
#include <stack>

using namespace std;

void scanToken(ifstream& inputFile, ofstream& outputFile, function<int(string)> SymbolToNum, function<string(string, string, string, string, ofstream&)> QuadsOut,
               function<void(string, string, string, string, ofstream&)> QuadsOut2) {
    
    string OperatorPrecedence[21][21] ={
    //     $    =    +    -    (    )    *    /    ;  ==  !=    >    <    >=    <=  IF THEN  WHILE  DO   {    }
        // $
        {"0", "<", "<", "<", "<", "0", "<", "<", "0", "<", "<", "<", "<", "<", "<", "<", "0", "<", "0", "<", "0"},
        // =
        {">", "<", "<", "<", "<", "0", "<", "<", ">", "<", "<", "<", "<", "<", "<", "0", "0", "0", "0", "<", "0"},
        // +
        {">", "0", ">", ">", "<", ">", "<", "<", ">", ">", ">", ">", ">", ">", ">", "0", ">", "0", "0", "0", "0"},
        // -
        {">", "0", ">", ">", "<", ">", "<", "<", ">", ">", ">", ">", ">", ">", ">", "0", ">", "0", "0", "0", "0"},
        // (
        {"0", "0", "<", "<", "<", "=", "<", "<", "0", "<", "<", "<", "<", "<", "<", "0", "0", "0", "0", "0", "0"},
        // )
        {">", "0", ">", ">", "0", ">", ">", ">", ">", ">", ">", ">", ">", ">", ">", "0", "0", "0", "0", "0", "0"},
        // *
        {">", "0", ">", ">", "<", ">", ">", ">", ">", ">", ">", ">", ">", ">", ">", "0", ">", "0", "0", "0", "0"},
        // /
        {">", "0", ">", ">", "<", ">", ">", ">", ">", ">", ">", ">", ">", ">", ">", "0", ">", "0", "0", "0", "0"},
        // ;
        {"0", "<", "<", "<", "<", "0", "<", "<", "0", "<", "<", "<", "<", "<", "<", "<", "0", "<", "0", "0", ">"}, 
        // ==
        {"0", "0", "<", "<", "<", ">", "<", "<", ">", "0", "0", "0", "0", "0", "0", "0", ">", "0", ">", "0", "0"},
        // !=
        {"0", "0", "<", "<", "<", ">", "<", "<", ">", "0", "0", "0", "0", "0", "0", "0", ">", "0", ">", "0", "0"},
        // >
        {"0", "0", "<", "<", "<", ">", "<", "<", ">", "0", "0", "0", "0", "0", "0", "0", ">", "0", ">", "0", "0"},
        // <
        {"0", "0", "<", "<", "<", ">", "<", "<", ">", "0", "0", "0", "0", "0", "0", "0", ">", "0", ">", "0", "0"},
        // >=
        {"0", "0", "<", "<", "<", ">", "<", "<", ">", "0", "0", "0", "0", "0", "0", "0", ">", "0", ">", "0", "0"},
        // <=
        {"0", "0", "<", "<", "<", ">", "<", "<", ">", "0", "0", "0", "0", "0", "0", "0", ">", "0", ">", "0", "0"},
        // IF
        {"<", "0", "<", "<", "<", "0", "<", "<", "<", "<", "<", "<", "<", "<", "<", "0", "=", "0", "0", "<", "0"},
        // THEN
        {">", "<", "0", "0", "0", "0", "0", "0", ">", "0", "0", "0", "0", "0", "0", "<", "0", "<", "0", "<", ">"},
        // WHILE
        {"<", "0", "<", "<", "<", "0", "<", "<", "<", "<", "<", "<", "<", "<", "<", "0", "0", "0", "=", "<", "0"},
        // DO
        {">", "<", "0", "0", "0", "0", "0", "0", ">", "0", "0", "0", "0", "0", "0", "<", "0", "<", "0", "<", ">"},
        // {
        {"0", "<", "<", "<", "<", "0", "<", "<", "=", "0", "0", "0", "0", "0", "0", "<", "<", "<", "<", "<", "="},
        // }
        {"0", "0", "0", "0", "0", "0", "0", "0", ">", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", ">"}
    };

    string word;
    string type;
    string prevOp = "$";
    string relation;
    string Quad1;
    string Quad2;
    string Quad3;
    string Quad4;
    string check;
    string temp;
    string temp2;
    string prevType;
    int Ltemp = 1;
    int Wtemp = 1;
    
    bool keep_going;
    bool ending = true;


    stack<string> myStack;
    myStack.push(prevOp);
    prevOp = "{";
    myStack.push(prevOp);
    stack<string> myStack2;
    stack<string> myStack3;




    while (inputFile >> word >> type && ending){
        check = "F";
        cout << word << endl;
        cout << type << endl;

        if (type == "CONST" || type == "VAR" || type == "Class"){
            keep_going = true;
            while (keep_going){
                inputFile >> word >> type;
                if (type == "semi" || type == "Lcurly"){
                    keep_going = false;
                }
                cout << " " << endl;
                cout << "True or false" << endl;
                cout << keep_going << endl;
                cout << "word: " + word << endl;
                cout << "type: " + type << endl;
                cout << " " << endl;
            }
        }
        else if (type == "GET" || type == "PRINT"){
            cout << "GET or PRINT" << endl;
            Quad1 = word;
            inputFile >> word >> type;
            Quad2 = word;
            inputFile >> word >> type;
            QuadsOut2(Quad1, Quad2, "?", "?", outputFile);
        }
        else if(type == "id" || type == "numLit"){
            myStack.push(word);
            cout << "Pushed1: " + word << endl;
            cout << "Doing ID or numlit" << endl;
        }
        else if(type == "addop" || type == "mop" || type == "semi" || type == "$=" || type == "Lparen" || type == "Rparen" || type == "relop" || type == "THEN" ||
                type == "DO" || type == "Lcurly" || type == "Rcurly"){
            cout << "prevOp: " + prevOp << endl;
            cout << "type: " + type << endl;
            relation = OperatorPrecedence[SymbolToNum(prevOp)][SymbolToNum(word)];
            cout << "relation: " + relation << endl;
            cout << "Doing addop, mop, relop" << endl;
            if (relation == "<"){
                myStack.push(word);
                cout << "Pushed2: " + word << endl;
                cout << "< relation" << endl;
                prevOp = word;
            }
            else if (relation == ">" || (word == "}" && prevOp == "{")){
                while ( relation == ">" || relation == "="){
                    if (relation == ">"){
                        if ((prevOp == "THEN" && type == "Rcurly") || (prevOp == "DO" && type == "Rcurly")){
                            while ((prevOp == "THEN" && type == "Rcurly") || (prevOp == "DO" && type == "Rcurly")){
                                cout << "PrevOp = THEN or DO and type == semi" << endl;
                                if (prevOp == "DO"){
                                    temp = myStack3.top();
                                    cout << "Mystack3: " + temp << endl;
                                    myStack3.pop();
                                    QuadsOut2("jmp", temp, "?", "?", outputFile);
                                    Wtemp = Wtemp - 1;
                                }
                                cout << "MyStack: " + myStack.top() << endl;
                                myStack.pop();
                                cout << "MyStack: " + myStack.top() << endl;
                                myStack.pop();
                                prevOp = myStack.top();
                                cout << "New prevOp: " + prevOp << endl;
                                temp = myStack2.top();
                                myStack2.pop();
                                QuadsOut2(temp, "?", "?", "?", outputFile);
                                Ltemp = Ltemp;
                                cout << type << endl;
                            }
                            break;

                        }
                        else{
                            Quad3 = myStack.top();
                            myStack.pop();
                            Quad1 = myStack.top();
                            myStack.pop();
                            Quad2 = myStack.top();
                            myStack.pop();
                            check = "F";
                            prevOp = myStack.top();
                            cout << "Top of stack: " + prevOp << endl;
                            Quad4 = QuadsOut(Quad1, Quad2, Quad3, check, outputFile);
                            
                            if ((type == "THEN" && prevOp == "IF") || (type == "DO" && prevOp == "WHILE") || (word == ";" && prevOp == "{") ||
                                (word == ";" && prevOp == "DO")){
                                cout << "Doing Nothing" << endl;
                            }
                            else{
                                cout << "Quad4 to stack:" + Quad4 << endl;
                                myStack.push(Quad4);
                                cout << "Pushed3: " + Quad4 << endl;
                            }
                            cout << "Quad 1" + Quad1 << endl;
                            cout << "Quad 2" + Quad2 << endl;
                            cout << "Quad 3" + Quad3 << endl;
                            cout << "Quad 4" + Quad4 << endl;
                            cout << "Top of stack: " + myStack.top() << endl;
                            relation = OperatorPrecedence[SymbolToNum(prevOp)][SymbolToNum(word)];
                            cout << "relation: " + relation << endl;
                            cout << "prevOp: " + prevOp << endl;
                            cout << "word: " + word << endl;
                        }


                        // while (!myStack.empty()) {
                        //     cout << "stack: " + myStack.top() << endl;
                        //     myStack.pop();
                        // }
                    }   
                    else{
                        if (type == "THEN" || type == "DO"){
                            cout << "Doing = precendence for then or do in > predecedence" << endl;
                            //pushing then onto stack
                            myStack.push(word);
                            cout << "Pushed4: " + word << endl;
                            prevOp = word;
                            temp = "L" + to_string(Ltemp);
                            myStack2.push(temp);
                            
                            temp = QuadsOut(word, temp, "Holder", check, outputFile);
                            temp = QuadsOut(word, "L1", "Holder", "T", outputFile);
                            
                            Ltemp = Ltemp + 1;
                            break;
                        }
                        else if (type == "Rcurly"){
                            myStack.pop();
                            prevOp = myStack.top();
                            cout << "prevOp: " + prevOp << endl;
                            relation = OperatorPrecedence[SymbolToNum(prevOp)][SymbolToNum(word)];
                            cout << "relation: " + relation << endl;
                            cout << "got rid of {" << endl;
                            temp = QuadsOut(word, "L1", "Holder", "T", outputFile);
                        
                        }
                        else if (type == "semi" && prevOp == "{"){
                            cout << "not putting ; into stack" << endl;
                            break;
                            
                        }
                        else {
                            cout << "Doing = precendence in > predecedence" << endl;
                            // while (!myStack.empty()) {
                            //     cout << "stack: " + myStack.top() << endl;
                            //     myStack.pop();
                            // }
                            temp = myStack.top();
                            cout << "temp: " + temp << endl;
                            myStack.pop();
                            myStack.pop();
                            prevOp = myStack.top();
                            myStack.push(temp);
                            cout << "Pushed5: " + temp << endl;
                            break;  
                        }  
                    }
                }
                if (word == "}" || word == ")" || (prevOp == "$" && word == ";") || word == "THEN" || word == "DO" || word == ";"){
                    ;
                }
                else {
                    myStack.push(word);
                    cout << "Pushed6: " + word << endl;
                    prevOp = myStack.top();
                }
                
            }
            else if (relation == "="){
                if (type == "Rcurly"){
                    myStack.pop();
                    prevOp = myStack.top();
                    cout << "relation =, type }" << endl;
                }
                else {
                    Quad1 = myStack.top();
                    myStack.pop();
                    myStack.pop();
                    prevOp = myStack.top();
                    myStack.push(Quad1);
                    cout << "Pushed7: " + Quad1 << endl;
                }
                
            }
            else{
                cout << "Doing else" << endl;
            }
            
        }
        
        else if (type == "IF" || type == "WHILE"){
            cout << "prevOp: " + prevOp << endl;
            cout << "type: " + type << endl;
            relation = OperatorPrecedence[SymbolToNum(prevOp)][SymbolToNum(word)];
            cout << "IF: " + relation << endl;
            if (relation == "<"){
                temp = "W" + to_string(Wtemp);
                myStack.push(word);
                cout << "Pushed8: " + word << endl;
                cout << "< relation" << endl;
                prevOp = word;
                if (type == "WHILE"){
                    Wtemp = Wtemp + 1; 
                    myStack3.push(temp);
                    QuadsOut2(word, temp, "?", "?", outputFile);
                }
                else {
                    QuadsOut2(word, "?", "?", "?", outputFile);
                }
                
                
            }
            else {
                cout << "if or while greater than relalationship" << endl;
            }
        }
        
        else{
            ;
        }

        // if (type == "Rcurly"){
        //     temp = myStack.top();
        //     myStack.pop();
        //     temp2 = myStack.top();
        //     cout << "Temp2: " + temp2 << endl;
        //     myStack.push(temp);
        // }
        
        if((prevOp == "$" && type == "Rcurly")){
                    cout << "FINAL POP" << endl;
                    temp = myStack.top();
                    cout << "Top of stack: " + temp << endl;
                    myStack.pop();
                    check = QuadsOut(Quad1, Quad2, Quad3, "T", outputFile);
                    outputFile << "  " << endl;
                    Ltemp = 1;
                    cout << "Ltemp: " + Ltemp << endl;
                    //myStack.push("$");
        }
    }
               

while (!myStack.empty()) {
        cout << "stack: " + myStack.top() << endl;
        myStack.pop();
}
    
    
}


int SymbolToNum(string ch){
    if (ch == "$") {
        return 0;
    } 
    else if (ch == "="){
        return 1;
    }
    else if (ch == "+"){
        return 2;
    }
    else if (ch == "-"){
        return 3;
    }
    else if (ch == "("){
        return 4;
    }
    else if (ch == ")"){
        return 5;
    }
    else if (ch == "*"){
        return 6;
    }
    else if (ch == "/"){
        return 7;
    }
    else if (ch == ";"){
        return 8;
    }
    else if (ch == "=="){
        return 9;
    }
    else if (ch == "!="){
        return 10;
    }
    else if (ch == ">"){
        return 11;
    }
    else if (ch == "<"){
        return 12;
    }
    else if (ch == ">="){
        return 13;
    }
    else if (ch == "<="){
        return 14;
    }
    else if (ch == "IF"){
        return 15;
    }
    else if (ch == "THEN"){
        return 16;
    }
    else if (ch == "WHILE"){
        return 17;
    }
    else if (ch == "DO"){
        return 18;
    }
    else if (ch == "{"){
        return 19;
    }
    else if (ch == "}"){
        return 20;
    }
    else{
        return 21;
    }
    
}


string QuadsOut(string op, string x, string y, string reset_check, ofstream& outputFile){
    static int Temp = 1;
    string ostr;
    string segment = "T";
    static string previous = ""; 

    if ((previous == ">" || previous == ">=" || previous == "<" || previous == "<=" || previous == "==" || previous == "!=") && (op == "THEN" || op == "DO")){
        if (previous == "<"){
            ostr = op + " " + x + " " + "jge" + " " + "?"; 
        }
        else if (previous == "<="){
            ostr = op + " " + x + " " + "jg" + " " + "?"; 
        }
        else if (previous == ">"){
            ostr = op + " " + x + " " + "jle" + " " + "?"; 
        }
        else if (previous == ">="){
            ostr = op + " " + x + " " + "jl" + " " + "?"; 
        }
        else if (previous == "=="){
            ostr = op + " " + x + " " + "jne" + " " + "?"; 
        }
        else{
            ostr = op + " " + x + " " + "je" + " " + "?"; 
        }

        outputFile << ostr << endl;
        previous = "";
        return segment;
    }
    if (reset_check == "F"){
        segment = segment + to_string(Temp);
        ostr = op + " " + x + " " + y + " " + segment;
        outputFile << ostr << endl;
        Temp = Temp + 1;
        cout << "output to quads" << endl;
        previous = op;
        return segment;

    }
    else{
        Temp = 1;
        previous = "";
        return segment;
    }
    
}

void QuadsOut2(string op, string x, string y, string reset_check, ofstream& outputFile){
    string ostr;
    ostr = op + " " + x + " " + y + " " + "?";
    outputFile << ostr << endl;
    cout << "output to quads2" << endl;
         
}

void QuadstoASM(ifstream& TokeninputFile, ifstream& SymbolinputFile, ofstream& ASMoutputFile){
    string a;
    string b;
    string c;
    string d;
    string e;
    ASMoutputFile <<"sys_exit    equ    1\n"
                    "sys_read    equ    3\n"
                    "sys_write    equ    4\n"
                    "stdin        equ    0 ; default keyboard\n"
                    "stdout        equ    1 ; default terminal screen\n"
                    "stderr        equ    3" << endl;
    ASMoutputFile << "\n\tsection .data\n" << endl;
    ASMoutputFile << "\tuserMsg        db      'Enter an integer(less than 32,765): '\n"
                    "\tlenUserMsg    equ    $-userMsg\n"
                    "\tdisplayMsg    db    'You entered: '\n"
                    "\tlenDisplayMsg    equ    $-displayMsg\n"
                    "\tnewline        db    0xA     ; 0xA 0xD is ASCII <LF><CR>\n\n"
                    "\tTen             DW      10  ;Used in converting to base ten.\n\n"
                    "\tprintTempchar    db    'Tempchar = : '\n"
                    "\tlenprintTempchar    equ     $-printTempchar\n\n"
                    "\tResult          db      'Ans = '\n"
                    "\tResultValue    db    'aaaaa'\n"
                    "\tdb    0xA\n"
                    "\tResultEnd       equ     $-Result    ; $=> here, subtract address Result\n\n"
                    "\tnum        times 6 db 'ABCDEF'\n"
                    "\tnumEnd        equ    $-num" << endl;

    
    while (SymbolinputFile >> a >> b >> c >> d >> e){
        if (b == "ConstVar" || b == "NumericLiteral"){
            ASMoutputFile << "\t" + a + " DW " + c << endl;
        }
        else{
            ;
        }
    }
    ASMoutputFile << endl;


    ASMoutputFile << "\tsection .bss" << endl;
    ASMoutputFile << " \n\tTempChar        RESB       1              ;temp space for use by GetNextChar\n"
                    "\ttestchar        RESB       1\n"
                    "\tReadInt         RESW       1              ;Temporary storage GetAnInteger.\n"
                    "\ttempint         RESW       1              ;Used in converting to base ten.\n"
                    "\tnegflag         RESB       1              ;P=positive, N=negative\n" << endl;

    SymbolinputFile.clear();
    SymbolinputFile.seekg(0, ios::beg);
    while (SymbolinputFile >> a >> b >> c >> d >> e){
        if (b == "Var" || b == "VarInt"){
            ASMoutputFile << "\t" + a + " resw 1" << endl;
        }
        else{
            ;
        }
    }
    ASMoutputFile << endl;
        
        // this is for the .TEXT section of the assembly code
    ASMoutputFile << "\tglobal _start\n" << endl;
    ASMoutputFile << "\tsection .text\n" << endl;
    ASMoutputFile << "\t_start:    nop\n" << endl;
    ASMoutputFile << "\t\tAgain:\n" << endl;

    while (TokeninputFile >> a >> b >> c >> d){
        if (a == "+"){
            ASMoutputFile << "\tmov ax,[" + b + "]" << endl;
            ASMoutputFile << "\tadd ax,[" + c + "]" << endl;
            ASMoutputFile << "\tmov [" + d + "],ax" << endl;
        }
        else if (a == "-"){
            ASMoutputFile << "\tmov ax,[" + b + "]" << endl;
            ASMoutputFile << "\tsub ax,[" + c + "]" << endl;
            ASMoutputFile << "\tmov [" + d + "],ax" << endl;
        }
        else if (a == "*"){
            ASMoutputFile << "\tmov ax,[" + b + "]" << endl;
            ASMoutputFile << "\tmul word [" + c + "]" << endl;
            ASMoutputFile << "\tmov [" + d + "], ax" << endl;
        }
        else if (a == "/"){
            ASMoutputFile << "\tmov dx, 0" << endl;
            ASMoutputFile << "\tmov ax, [" + b + "]" << endl;
            ASMoutputFile << "\tmov bx, [" + c + "]" << endl;
            ASMoutputFile << "\tdiv word bx" << endl;
            ASMoutputFile << "\tmov [" + d + "], ax" << endl;
        }
        else if (a == "="){
            ASMoutputFile << "\tmov ax,[" + c + "]" << endl;
            ASMoutputFile << "\tmov [" + b + "], ax" << endl;

        }
        else if (a[0] == 'L'){
            ASMoutputFile << a + ":" << endl;
            ASMoutputFile << "\tnop" << endl;
        }
        else if (a == "THEN"){
            ASMoutputFile << "\t" + c + " " + b << endl;
        }
        else if (a == "WHILE"){
            ASMoutputFile << b + ":" << endl;
        }
        else if (a == "DO"){
            ASMoutputFile << "\t" + c + " " + b << endl;
        }
        else if (a == "==" || a == "!=" || a == "<=" || a == ">=" || a == "<" || a == ">"){
            ASMoutputFile << "\tmov ax,[" + b + "]" << endl;
            ASMoutputFile << "\tcmp ax,[" + c + "]" << endl;
        }
        else if (a == "jmp"){
            ASMoutputFile << "\t" + a + " " + b << endl;
        }
        else if (a == "GET"){
                // this TO INPUT A NUMBER FROM THE USER
            ASMoutputFile << "\t\tcall PrintString" << endl;
            ASMoutputFile << "\t\tcall GetAnInteger"<< endl;
            ASMoutputFile << "\t\tmov ax, [ReadInt]" << endl;
            ASMoutputFile << "\t\tmov [" << b << "], ax\n" << endl;
            }
        else if (a == "PRINT"){
                // this TO OUTPUT A NUMBER TO THE USER
            ASMoutputFile << "\n\tmov ax,["<< b <<"]\n"
                            "\tcall ConvertIntegerToString\n"
                            "\tmov eax, 4    ;write   ; 'Ans = value <newline>\n"
                            "\tmov ebx, 1    ; default sys_out\n"
                            "\tmov ecx, Result       ;start address for print\n"
                            "\tmov edx, ResultEnd ;Length to write.\n"
                            "\tint 80h\n" << endl;
            }
        else {
            ;
        }
    }
    ASMoutputFile << "\n\t\t;jmp     Again\n"
                    "\n\t; exit code" << endl;
    ASMoutputFile << "fini:\n"
                    "\tmov eax,sys_exit ;terminate, sys_exit = 1 \n"
                    "\txor ebx,ebx      ;zero in ebx indicates success\n"
                    "\tint 80h\n" << endl;
    ASMoutputFile << "\n\t; subpgm to print a string\n"
        // printstring
                    "\tPrintString:\n"
                    "\tpush    ax              ;Save registers\n"
                    "\tpush    dx\n"
                    "\tmov eax, 4;Linux print device register\n"
                    "\tmov ebx, 1; print default output device\n"
                    "\tmov ecx, userMsg; pointer to string\n"
                    "\tmov edx, lenUserMsg\n"
                    "\tint 80h; interrupt 80 hex, call kernel\n"
                    "\tpop     dx              ;Restore registers\n"
                    "\tpop     ax\n"
                    "\tret\n" << endl;
    ASMoutputFile << "\n\t; subpgm to get an integer\n"
        // getaninteger
                    "\tGetAnInteger:\n"
                    "\tmov eax,3;read\n"
                    "\tmov ebx,2;device\n"
                    "\tmov ecx, num;buffer address\n"
                    "\tmov edx,6;max characters\n"
                    "\tint 0x80\n"
                    "\tmov edx,eax ; eax contains the number of character read including <lf>\n"
                    "\tmov eax, 4\n"
                    "\tmov ebx, 1\n"
                    "\tmov ecx, num\n"
                    "\tint 80h\n" << endl;
    ASMoutputFile << "\n\t; subpgm to convert a string to an integer\n"
        // convertstringtointeger
                    "\tConvertStringToInteger:\n"
                    "\tmov ax,0;hold integer\n"
                    "\tmov [ReadInt],ax ;initialize 16 bit number to zero\n"
                    "\tmov ecx,num;pt - 1st or next digit of number as a string terminated by <lf>\n"
                    "\tmov bx,0\n"
                    "\tmov bl, byte [ecx] ;contains first or next digit\n"
                    "Next:\n"
                    "\tsub bl,'0';convert character to number\n"
                    "\tmov ax,[ReadInt]\n"
                    "\tmov dx,10\n"
                    "\tmul dx;eax = eax * 10\n"
                    "\tadd ax,bx\n"
                    "\tmov [ReadInt], ax\n"
                    "\tmov bx,0\n"
                    "\tadd ecx,1 ;pt = pt + 1\n"
                    "\tmov bl, byte[ecx]\n"
                    "\tcmp bl,0xA;is it a <lf>\n"
                    "\tjne Next; get next digit\n"
                    "\tret\n" << endl;
    ASMoutputFile << "\n\t; subpgm to convert an integer to a string\n"
        // convertintegertostring
                    "\tConvertIntegerToString:\n"
                    "\tmov ebx, ResultValue + 4   ;Store the integer as a five digit char string at Result for printing\n"
                    "ConvertLoop:\n"
                    "\tsub dx,dx  ; repeatedly divide dx:ax by 10 to obtain last digit of number\n"
                    "\t; to obtain last digit of number\n"
                    "\tmov cx,10  ; as the remainder in the DX register.  Quotient in AX.\n"
                    "\tdiv cx\n"
                    "\tadd dl,'0' ; Add '0' to dl to convert from binary to character.\n"
                    "\tmov [ebx], dl\n"
                    "\tdec ebx\n"
                    "\tcmp ebx,ResultValue\n"
                    "\tjge ConvertLoop\n"
                    "\tret\n" << endl;
}

int main() {
    ifstream inputFile("output.txt"); // Open the input file
    ofstream outputFile("Quads.txt");
    

    if (!inputFile) { // Check if the input file failed to open
    cout << "Unable to open input file!" << endl;
    return 1;
        }

    if (!outputFile) { // Check if the output file failed to open
        cout << "Unable to open output file!" << endl;
        return 1;
    }

   
    scanToken(inputFile,outputFile, SymbolToNum, QuadsOut, QuadsOut2);
   
    inputFile.close(); // Close the input file
    outputFile.close(); // Close the output file

    ifstream TokeninputFile("Quads.txt");
    ifstream SymbolinputFile("SampleTable.txt");
    ofstream ASMoutputFile("Code.asm");
    

    QuadstoASM(TokeninputFile, SymbolinputFile, ASMoutputFile);

    TokeninputFile.close(); // Close the input file
    ASMoutputFile.close(); // Close the output file

    

    return 0;
}