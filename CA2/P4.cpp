#include <iostream>
#include <string>
#include <vector>
#include <functional>

using namespace std;

unsigned long int generatePasswordHash(string password);
void go_through(const vector <char> &alphabet, vector <int> &indexes, const int &size);
string create_string(const vector <char> &alphabet,vector <int> &indexes, const int &size);
bool check(string &password, const unsigned long int &hash);
string create_last_string(const vector <char> &alphabet,vector <int> &indexes, const int &size);
void generate_password(const vector <char> &alphabet, vector <int> &indexes, const int &size, const unsigned long int &hash);

int main()
{
    int size;
    string alphabet;
    unsigned long int hash_number;
    cin >> size >> alphabet >> hash_number;
    vector <char> alphabet_vect;
    copy(alphabet.begin(), alphabet.end(), back_inserter(alphabet_vect));
    vector <int> indexes(alphabet.size());
    generate_password(alphabet_vect, indexes, size, hash_number);

}
unsigned long int generatePasswordHash(string password)
{
    return hash<string>()(password);
}
void go_through(const vector <char> &alphabet, vector <int> &indexes, const int &size)
{
    for(int i = size - 1; i >= 0; i--)
    {
        if(indexes[i] == alphabet.size())
        {
            indexes[i] = 0;
            indexes[i-1]++;
        }
    }
}
string create_string(const vector <char> &alphabet,vector <int> &indexes, const int &size)
{
    string password;
    for(int i = 0; i < size; i++)
    {
        char c = alphabet[indexes[i]];
        password += c;
    }
    return password;
}
bool check(string &password, const unsigned long int &hash)
{
    if(hash == generatePasswordHash(password))
        return true;
    return false;
}
string create_last_string(const vector <char> &alphabet,vector <int> &indexes, const int &size)
{
    string password;
    for(int i = 0; i < size; i++)
    {
        char c = alphabet[alphabet.size() - 1];
        password += c;
    }
    return password;
}
void generate_password(const vector <char> &alphabet, vector <int> &indexes, const int &size, const unsigned long int &hash)
{
    for(int i = 0; i < 500; i++)
    {
        string password = create_string(alphabet, indexes, size);
        if(check(password, hash))
        {
            cout << password << endl;
            return;
        }
        if(password == create_last_string(alphabet, indexes, size))
        {
            cout << "NOT FOUND!" << endl;
            return;
        }
        indexes[size - 1]++;
        go_through(alphabet, indexes, size); 
    }
    generate_password(alphabet, indexes, size, hash);
}