#include <iostream>
#include <string>
#include <fstream>
#define SIZE 256

std::string keywords[] {"numb", "word", "bool", "show", "doif", "ever", "end:"};
const int DIGIT = keywords[0].length();

struct Nums
{
    std::string name;
    double value;   
};

struct Words
{
    std::string name;
    std::string value;
};

struct Bools
{
    std::string name;
    int value;
};

void error();
Nums make_numb (std::string line);
Words make_word (std::string line);
Bools make_bool (std::string line);
double operation_number(Nums numbers[], std::string test_name, std::string line);
std::string operation_string(Words my_words[], std::string test_name, std::string line);
void print (std::string line, Nums arr_numb[], Words arr_word[], Bools arr_bool[]);
bool do_if (Nums arr_number[], std::string line);
void wile (Nums arr_number[], std::string line);

int main()
{
    const int KEY_COUNT = sizeof(keywords)/sizeof(keywords[0]); 
    bool test_for_if = true;
    bool test_for_ever = false;
    int ever_line = 0;
    
    Nums arr_number[SIZE];
    Words arr_words[SIZE];
    Bools arr_bools[SIZE];
    int test1 {};
    int test2 {};
    int test3 {};

    std::ifstream text;
    std::string read_from{};
    std::string line{};
    std::ifstream check;
    std::cout << "Hello, please input the name of textual file where your code is written: ";
    std::cin >> read_from;
    text.open(read_from);
    
    if (!text.is_open())
    {
        std::cout << "Unfortunately I can't find file with name " << read_from;
        std::cout << ", please check one more time and try again." << std::endl;
        exit(0);
    }
    
    int linecount {};
    while (!text.eof())
    { 
        getline(text, line);
        ++linecount;
        if (line.substr(0, DIGIT) == keywords[6] && !test_for_ever)
        {
            test_for_if = true;
        }
        else if (line.substr(0, DIGIT) == keywords[6] && test_for_ever )
        {
            linecount = ever_line;
			text.close();
            text.open(read_from);
            std::string temp{};
            for (int i = 0; i < ever_line; i++)
            {
                getline(text,temp);         
            }
            line = temp;   
        }
             
        if (test_for_if == true)
        {
            for (int i = 0; i < KEY_COUNT; i++)
            {
               if (line.substr(0,DIGIT) == keywords[i])
                {
                    if (i == 0)
                    { 
                       Nums numb_var;
                       numb_var = make_numb(line);
                       arr_number[test1] = numb_var;
                       test1++;                   
                    }
                    else if (i == 1)
                    {
                        Words word_var;
                        word_var = make_word(line);
                        arr_words[test2] = word_var;
                        test2++;
                    } 
                    else if (i == 2)
                    {
                        Bools bool_var; 
                        bool_var = make_bool(line);
                        arr_bools[test3] = bool_var;
                        test3++;
                    }  
                    else if (i == 3)
                    {
                        print(line,arr_number, arr_words , arr_bools);
                    }
                    else if (i == 4)
                    {
                        test_for_if = do_if(arr_number,line);
                    }
                    else if (i == 5)
                    {
                        ever_line = linecount;
                        test_for_ever = do_if(arr_number,line);
                        test_for_if = test_for_ever;
                    }
                }
            }

            int is_it_keyword = 0;
            for (int i = 0; i < sizeof(keywords)/sizeof(keywords[0]); i++)
            {
                if (line.substr(0, DIGIT) == keywords[i])
                {
                    ++is_it_keyword;
                }   
            }
            if (!is_it_keyword)
            {
                std::string test_name{};
                for (int i = 0; line[i] != '=' ; i++)
                {
                    test_name.push_back(line[i]);
                }
            
                for (int i = 0; i < SIZE; i++)
                {
                    if (test_name == arr_number[i].name)
                    {
                       arr_number[i].value = operation_number (arr_number, test_name, line); 
                    }
                    else if (test_name == arr_words[i].name)
                    {
                        arr_words[i].value = operation_string (arr_words, test_name, line);
                    }   
                }
            }          
        }
    }

    text.close();
    return 0;
}

void error()
{
    std::cout << "Something's gone wrong, please revise your code follwoing our conditions" << std::endl;
    exit(0);
}

Nums make_numb (std::string line)
{
    Nums object;
    std::string name{};
    std::string value{};

    for (int i = (DIGIT+1) ;i < line.length(); i++)
    {

        if (line[i] != ' ')
        {
            name.push_back(line[i]);
        } else {
            break;
        }   
    }
    
    for (int i = (DIGIT+2) + name.length() ; i < line.length(); i++)
    {
        if (!(line[i] >= '0' && line[i] <='9'))
        {
            error();
        }
        
        if (line[i] != ' ')
        {
            value.push_back(line[i]);
        } else {
            break;
        }   
    }
    object.name = name;
    object.value = stod(value);

    return object;   
}

Words make_word (std::string line)
{
    Words object;
    std::string name{};
    std::string value{};

    for (int i = (DIGIT+1) ;i < line.length(); i++)
    {
        if (line[i] != ' ')
        {
            name.push_back(line[i]);
        } else {
            break;
        }   
    }
    
    for (int i = ( DIGIT + 2 ) + name.length() ; i < line.length(); i++)
    {
        if (line[i] != ' ')
        {
            value.push_back(line[i]);
        } else {
            break;
        }   
    }

    object.name = name;
    object.value = value;

    return object;   
}

Bools make_bool (std::string line)
{
    Bools object;
    std::string name{};

    for (int i = ( DIGIT + 1 ) ;i < line.length(); i++)
    {
        if (line[i] != ' ')
        {
            name.push_back(line[i]);
        } else {
            break;
        }   
    }

    if (line[(DIGIT+2) + name.length()] == '0' || line[(DIGIT+2) + name.length()] == 'F' )
    {
        object.value = 0;
    } else {
        object.value = 1;
    }
    object.name = name;
    return object;
}
double operation_number (Nums numbers[], std::string test_name, std::string line)
{
    std::string first{};
    std::string second{};
    double arg1{};
    double arg2{};
    char operation_symbol{};
    for (int i = test_name.length() + 1 ; i < line.length(); i++)
    {
        if (line[i] != '+' && line[i] != '-' && line[i] != '*' && line[i] != '/' && 
            line[i] != '&' && line[i] != '~' && line[i] != '|' && line[i] != '<' && 
            line[i] != '>' && line[i] != '(' && line[i] != ')' )
        {
            first.push_back(line[i]);
        } else {
            break;
        }           
    }
    operation_symbol = line[test_name.length() + first.length() + 1];
    for (int i = test_name.length() + first.length() + 2; i < line.length(); i++)
    {
        if (line[i] != ' ' )
        {
            second.push_back(line[i]);
        } else {
            break;
        }       
    }

    if(first[0] >= '0' && first[0] <= '9')
    {
        arg1 = stod(first);
    }
    if(second[0] >= '0' && second[0] <= '9')
    {
        arg2 = stod(second);
    }

    int detection_test1 {};
    int detection_test2 {};
    for (int i = 0; i < SIZE; i++)
    {
        if (first == numbers[i].name)
        {
            arg1 = numbers[i].value;
            ++detection_test1;
        }
        if(second == numbers[i].name)
        {
            arg2 = numbers[i].value;
            ++detection_test2;
        }
    }
    if (!(first[0] >= '0' && first[0] <= '9') && !(second[0] >= '0' && second[0] <= '9'))
    {
        if (detection_test1 == 0 && detection_test2 == 0)
        {
            error();
        }
    }
   
    switch (operation_symbol)
    {
        case '+': return arg1 + arg2; 
        case '-': return arg1 - arg2; 
        case '*': return arg1 * arg2; 
        case '/': return arg1 / arg2;
        case '>': return arg1 > arg2;
        case '<': return arg1 < arg2;
        case '&': return arg1 && arg2;
        case '|': return arg1 || arg2;
        case ')': return arg1 >= arg2;
        case '(': return arg1 <= arg2;
        case '~': return arg1 == arg2;
        default: return arg1; 
    }     
}

std::string operation_string(Words my_words[], std::string test_name, std::string line)
{
    std::string first{};
    std::string second{};
    std::string arg1{};
    std::string arg2{};

    for (int i = test_name.length() + 1 ; i < line.length(); i++)
    {
        if (line[i] != '+')
        {
            first.push_back(line[i]);
        }
        else
        {
            break;
        }           
    }
    for (int i = test_name.length() + first.length() + 2; i < line.length(); i++)
    {
        if (line[i] != ' ' )
        {
            second.push_back(line[i]);
        }
        else
        {
            break;
        }       
    }
        for (int i = 0; i < SIZE; i++)
    {
        if (first == my_words[i].name)
        {
            arg1 = my_words[i].value;
        }
        if(second == my_words[i].name)
        {
            arg2 = my_words[i].value;
        }
    }
    
    return arg1 + arg2;    
}

void print(std::string line, Nums arr_numb[], Words arr_word[], Bools arr_bool[])
{
    std::string output{};
    for (int i = (DIGIT+1); i < line.length(); i++)
    {
        output.push_back(line[i]);
    }
    for (int i = 0; i < SIZE; i++)
    {
        if (output == arr_numb[i].name)
        {
            std::cout << arr_numb[i].value << std::endl;
            return;
        }
        else if (output == arr_word[i].name)
        {
            std::cout << arr_word[i].value << std::endl;
            return;
        }
        else if (output == arr_bool[i].name)
        {
            std::cout << arr_bool[i].value << std::endl;
            return;    
        }       
    } 
    std::cout << output << std::endl;
}

bool do_if (Nums arr_number[], std::string line)
{
    return operation_number(arr_number, keywords[6], line);   
}
