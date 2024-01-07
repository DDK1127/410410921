#include <iostream>
#include <iomanip>
#include <vector>

#define size 12

using namespace std;
// Z-shaped layout problem
int main()
{
    // vector<vector<int> > matrix(0);
    // for(int i = 0; i < 10; i++){
    //     vector<int> row(0);
    //     for(int j = 0; j < 10; j++){
    //         row.push_back(i*j);
    //     }
    //     matrix.push_back(row);
    // }

    // for(int i = 0; i < 10; i++){
    //     for(int j = 0; j < 10; j++){
    //         cout << "matrix[" << i << "][" << j << "] = " << matrix[i][j];
    //     }
    //     cout << endl;
    // }
    int x, y;
    int matrix[size][size];
    int a[size][size];

    int value = 0;
    int *p = &matrix[0][0];

    for (int i = 0; i < size * size; i++)
        *(p++) = i;

    cout << "Start Matrix is =>" << endl;
    for (int i = 0; i < size; i++){
        for (int j = 0; j < size; j++)
            cout << setw(4) << *(*(matrix + i) + j);

        cout << endl;
    }

    x = 0, y = 0;
    for (int i = 0; i < size; i++){
        for (int j = 0; j < size; j++){
            *(*(a + x) + y) = *(*(matrix + i) + j);

            if ((x == 0 || x == size - 1) && y % 2 == 0){y++;continue;} // v
            if ((y == 0 || y == size - 1) && x % 2 == 1){x++;continue;} // ->
            if ((x + y) % 2 == 0){x--;y++;} // <- v
            else if ((x + y) % 2 == 1){x++;y--;} // -> ^
        }
    }
    cout << endl <<  "after Z-shaped_layout =>" << endl;
    for (int i = 0; i < size; i++){
        for (int j = 0; j < size; j++)
            cout << setw(4) << *(*(a + i) + j);

        cout << endl;
    }

    return 0;
}