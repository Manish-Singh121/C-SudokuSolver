#include <iostream>
#include <vector>

using namespace std;

int showProgress = false;

void print(vector<vector<int>> &arr)
{
    cout << endl;
    for (int row = 0; row < 9; row++)
    {
        if (row % 3 == 0)
            cout << " ----------------------------" << endl;
        for (int col = 0; col < 9; col++)
        {
            if (col % 3 == 0)
                cout << " | ";
            cout << arr[row][col] << " ";
        }
        cout << " | " << endl;
    }

    cout << " ----------------------------" << endl
         << endl;
}

bool isValid(vector<vector<int>> &arr, int row, int col, int num)
{
    if (arr[row][col] != 0)
        return false;

    int grid_x = (col / 3) * 3;
    int grid_y = (row / 3) * 3;

    for (int i = 0; i < 9; i++)
    {
        if (arr[row][i] == num)
            return false;
        if (arr[i][col] == num)
            return false;
        if (arr[grid_y + i / 3][grid_x + i % 3] == num)
            return false;
    }

    return true;
}

vector<int> availNum(vector<vector<int>> &arr, int row, int col)
{
    vector<int> avail;
    for (int i = 1; i <= 9; i++)
    {
        if (isValid(arr, row, col, i))
            avail.push_back(i);
    }
    return avail;
}

void nextEmpty(vector<vector<int>> &arr, int row, int col, int &nextRow, int &nextCol)
{
    int idx = 9 * 9;
    for (int i = row * 9 + col + 1; i < 9 * 9; i++)
    {
        if (arr[i / 9][i % 9] == 0)
        {
            idx = i;
            break;
        }
    }
    nextRow = idx / 9;
    nextCol = idx % 9;
}

bool solve(vector<vector<int>> &arr, int row, int col)
{
    if (showProgress)
    {
        system("cls");
        print(arr);
    }

    if (row > 8)
        return true;

    if (arr[row][col] != 0)
    {
        int nextRow, nextCol;
        nextEmpty(arr, row, col, nextRow, nextCol);
        return solve(arr, nextRow, nextCol);
    }

    vector<int> avail = availNum(arr, row, col);

    if (avail.size() == 0)
        return false;

    for (int i = 0; i < avail.size(); i++)
    {
        int num = avail[i];
        arr[row][col] = num;

        int nextRow, nextCol;
        nextEmpty(arr, row, col, nextRow, nextCol);

        if (solve(arr, nextRow, nextCol))
            return true;

        arr[row][col] = 0;
    }

    return false;
}

int main(int argc, char const *argv[])
{
    vector<vector<int>> board = {
        {5, 3, 0, 0, 7, 0, 0, 0, 0},
        {6, 0, 0, 1, 9, 5, 0, 0, 0},
        {0, 9, 8, 0, 0, 0, 0, 6, 0},
        {8, 0, 0, 0, 6, 0, 0, 0, 3},
        {4, 0, 0, 8, 0, 3, 0, 0, 1},
        {7, 0, 0, 0, 2, 0, 0, 0, 6},
        {0, 6, 0, 0, 0, 0, 2, 8, 0},
        {0, 0, 0, 4, 1, 9, 0, 0, 5},
        {0, 0, 0, 0, 8, 0, 0, 8, 9},
    };

    // showProgress = true;

    print(board);

    solve(board, 0, 0);

    print(board);

    return 0;
}
