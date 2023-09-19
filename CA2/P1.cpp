#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int average_ceil(int a, int b);
void Reverse(string &input, int low, int high);
string encryption(string input, int low, int high);

int main()
{
    string input;
    getline(cin, input);
    cout << encryption(input, 0, input.length()) << endl;
}

int average_ceil(int a, int b)
{
    if(a+b % 2 == 0)
        return (a+b)/2;
    return (a+b)/2 + 1;
}

void Reverse(string &input, int low, int high)
{
    if(low < high)
    {
        swap(input[low], input[high]);
        return Reverse(input, low + 1, high - 1);
    }
}

string encryption(string input, int low, int high)
{
    if(input.length() == 1)
        return input;
    Reverse(input, low, high - 1);
    int mid = average_ceil(low, high);
    string first_half, second_half;
    for(int i = 0; i < mid; i++)
        first_half += input[i];
    for(int i = mid; i < input.length(); i++)
        second_half += input[i];
    return encryption(first_half, 0, first_half.length()) + encryption(second_half, 0, second_half.length());
}