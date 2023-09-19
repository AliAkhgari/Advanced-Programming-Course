#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#define POSSIBLE_MOVES 4

using namespace std;

vector <vector <int> > matrix_creator(vector <int> input, int row, int col);
bool valid_move(vector< vector <int> > &matrix, int i_pos, int j_pos, int row, int col);
int vectors_difference(vector <int> first, vector< vector <int> > second, int row, int col, int index, int i, int j);
bool solve(vector< vector <int> > matrix, int curr_i, int curr_j, int row, int col);
void execute_with_all_cells(vector <int> input, vector< vector <int> > &matrix, int row, int col, vector <int> &sums);
void find_tour(vector <int> input, vector< vector <int> > &matrix, int curr_i, int curr_j, int row, int col, vector <int> &sums);

int main()
{
    int m, n, in;//m : satr, n : sotoon
    vector <int> input;
    vector <vector <int> > matrix;
    vector <int> sums;
    cin >> m >> n;
    for(int i = 0; i < m * n; i++)
    {
        cin >> in;
        input.push_back(in);
    }
    if(m <= 0 || n <= 0)
    {
        cout << "invalid inputs!" << endl;
        exit(0);
    }
    
    matrix = matrix_creator(input, m, n);
    execute_with_all_cells(input, matrix, m, n, sums);

    sort(sums.begin(), sums.end());
    cout << sums[sums.size() - 1] << endl;
}
vector <vector <int> > matrix_creator(vector <int> input, int row, int col)
{
    vector <vector <int> > matrix(row, vector <int> (col));
    int index = 0;
    for(int i = 0; i < row; i++)
    {
        for(int j = 0; j < col ;j++)
        {
            matrix[i][j] = input[index];
            index++;
        }
    }
    return matrix;
}
bool valid_move(vector< vector <int> > &matrix, int i_pos, int j_pos, int row, int col)
{
    if(i_pos >= row || i_pos < 0)
        return false;
    if(j_pos < 0 || j_pos >= col)
        return false;
    if(matrix[i_pos][j_pos] == 0)
        return false;
    return true;
}
int vectors_difference(vector <int> first, vector< vector <int> > second, int row, int col, int index, int i, int j)
{
    static int sum = 0;
    if(index > row * col - 1)
        return sum;
    if(j >= col)
    {
        j = 0;
        i++;
    }
    return abs(first[index] - second[i][j]) + vectors_difference(first, second, row, col, index + 1, i, j + 1);
}
bool solve(vector< vector <int> > matrix, int curr_i, int curr_j, int row, int col)
{
    int POSSIBLE_ROW_MOVES[4] = {0, 1, 0, -1};
    int POSSIBLE_COL_MOVES[4] = {1, 0, -1, 0};
    int counter = 0;
    for(int i = 0; i < POSSIBLE_MOVES; i++)
    {
        int new_i = curr_i + POSSIBLE_ROW_MOVES[i];
        int new_j = curr_j + POSSIBLE_COL_MOVES[i];
        if(valid_move(matrix, new_i, new_j, row, col) == false)
            counter++;
    }
    if(counter == 4)
        return true;
    else
        return false;
}
void find_tour(vector <int> input, vector< vector <int> > &matrix, int curr_i, int curr_j, int row, int col, vector <int> &sums)
{
    int POSSIBLE_ROW_MOVES[4] = {0, 1, 0, -1};
    int POSSIBLE_COL_MOVES[4] = {1, 0, -1, 0};
    matrix[curr_i][curr_j] = 0;
    if(solve(matrix,curr_i,curr_j,row,col))
    {
        int dif = vectors_difference(input, matrix, row, col, 0, 0, 0);
        sums.push_back(dif);        
        return;
    }
    for(int i = 0; i < POSSIBLE_MOVES; i++)
    {
        int new_i = curr_i + POSSIBLE_ROW_MOVES[i];
        int new_j = curr_j + POSSIBLE_COL_MOVES[i];
        if(valid_move(matrix, new_i, new_j, row, col) == false)
        {
            continue;
        }
        int tmp = matrix[new_i][new_j];
        matrix[new_i][new_j] = 0;
        find_tour(input, matrix, new_i, new_j, row, col, sums);
        matrix[new_i][new_j] = tmp;
    }
}
void execute_with_all_cells(vector <int> input, vector< vector <int> > &matrix, int row, int col, vector <int> &sums)
{
    for(int i = 0; i < row; i++)
    {
        for(int j = 0; j < col; j++)
        {
            if(matrix[i][j] == 0)
                continue;
            find_tour(input, matrix, i, j, row, col, sums);
            matrix = matrix_creator(input, row, col);
        }
    }
}