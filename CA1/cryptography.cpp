#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

#define SIMPLE_ENCRYPT_METHOD "simple encrypt"
#define SIMPLE_DECRYPT_METHOD "simple decrypt"
#define COMPLICATED_ENCRYPT_METHOD "complicated encrypt"
#define COMPLICATED_DECRYPT_METHOD "complicated decrypt"
#define MAX_RANDOM 11

using namespace std;

typedef vector <int> NumbersList;
typedef string FilePath;

struct Commands
{
    string mode;
    string type;
    string key;
    FilePath input_file;
    FilePath output_file;
};

Commands get_commands();
NumbersList input_numbers(FilePath input);
string file_content(FilePath input);
int get_chars_sum(string input);
void write_numbers_to_file(FilePath file_path, NumbersList input);
void write_chars_to_file(FilePath file_path, vector <char> input);

void simple_encrypt(string key, FilePath input_file, FilePath output_file);
void complicated_encrypt(string key, FilePath input_file, FilePath output_file);
void simple_decrypt(string key, FilePath input_file, FilePath output_file);
void complicated_decrypt(string key, FilePath input_file, FilePath output_file);


int main()
{
    Commands commands = get_commands();
    string method = commands.type + " " + commands.mode;
    
    if(method == SIMPLE_ENCRYPT_METHOD)
        simple_encrypt(commands.key, commands.input_file, commands.output_file);

    if(method == COMPLICATED_ENCRYPT_METHOD)
        complicated_encrypt(commands.key, commands.input_file, commands.output_file);

    if(method == SIMPLE_DECRYPT_METHOD)
        simple_decrypt(commands.key, commands.input_file, commands.output_file);

    if(method == COMPLICATED_DECRYPT_METHOD)
        complicated_decrypt(commands.key, commands.input_file, commands.output_file);
}

Commands get_commands()
{ 
    Commands commands;
    cin >> commands.mode >> commands.type >> commands.key
        >> commands.input_file >> commands.output_file;
    return commands;
}

string file_content(FilePath input)
{
    ifstream input_file(input);
    stringstream file_content_ss;
    file_content_ss << input_file.rdbuf();
    return file_content_ss.str();
}

NumbersList input_numbers(FilePath input)
{
    ifstream input_file(input);
    NumbersList numbers;
    int number;
    while (input_file >> number)
        numbers.push_back(number);

    return numbers;
}

void write_numbers_to_file(FilePath file, NumbersList input)
{
    ofstream output_file(file);
    for(int i = 0; i < input.size(); i++)
        output_file << input[i] << endl;
}

void write_chars_to_file(FilePath file, vector <char> input)
{
    ofstream output_file(file);
    for(int i = 0; i < input.size(); i++)
        output_file << input[i];
}

int get_chars_sum(string input)
{
    int sum = 0;
    for(int i = 0; i < input.length(); i++)
        sum += input[i];
    
    return sum;
}

void simple_encrypt(string key, FilePath input_file, FilePath output_file)
{
    string input = file_content(input_file);
    NumbersList output;

    for(int i = 0; i < input.length(); i++)
        output.push_back(input[i] + key[i % key.length()]);
        
    write_numbers_to_file(output_file, output);
}

void complicated_encrypt(string key, FilePath input_file, FilePath output_file)
{
    string input = file_content(input_file);
    NumbersList output;

    srand(get_chars_sum(key));

    for(int i = 0; i < input.length(); i++)
        output.push_back(rand() % MAX_RANDOM + input[i]);

    write_numbers_to_file(output_file, output);
}

void simple_decrypt(string key, FilePath input_file, FilePath output_file)
{
    NumbersList input = input_numbers(input_file);
    vector <char> output;
    for(int i = 0; i < input.size(); i++)
        output.push_back(input[i] - key[i % key.length()]);

    write_chars_to_file(output_file, output);
}

void complicated_decrypt(string key, FilePath input_file, FilePath output_file)
{
    NumbersList input = input_numbers(input_file);
    vector <char> output;
    srand(get_chars_sum(key));
    for(int i = 0; i < input.size(); i++)
        output.push_back(input[i] - rand() % MAX_RANDOM);

    write_chars_to_file(output_file, output);
}
