#include <iostream>
#include <vector>
#include <string>

using namespace std;

int product(vector <int> input, int current_index, int first_index, int last_index);
void push_products(vector <int> &input, int current_index, int size);
void pop_inputs(vector <int> &input, int current_index, int size);
void print_vector(vector <int> input);

int main()
{
    int in;
    vector <int> input;
    while(cin >> in)
    {
        input.push_back(in);
    }
    int size = input.size();
    push_products(input, 0, size);
    pop_inputs(input, 0, size);
    print_vector(input);
}

int product(vector <int> input, int current_index, int first_index, int last_index)
{
    if(input[0] == 0 && input.size() == 1)
    {
        return 0;
    }
    if(current_index == first_index)
        first_index++;
    if(first_index > last_index)
    {
        return 1;
    }
    return input[first_index] * product(input, current_index, first_index + 1, last_index);
}

void push_products(vector <int> &input, int current_index, int size)
{
    if(current_index > size - 1)
    {
        return;
    }
    input.push_back(product(input, current_index, 0, size - 1));
    push_products(input, current_index+1, size);
}
void pop_inputs(vector <int> &input, int current_index, int size)
{
    if(current_index > size - 1)
    {
        return;
    }
    input.erase(input.begin());
    pop_inputs(input, current_index+1, size);
}
void print_vector(vector <int> input)
{
    for(int i = 0; i < input.size(); i++)
    {
        cout << input[i];
        if(i != input.size() - 1)
            cout << " ";
    }
    cout << endl;
}
