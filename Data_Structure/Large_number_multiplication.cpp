#include <iostream>
#include <memory.h>

using namespace std;
int *multi(int *num1, int size1, int *num2, int size2)
{
    int size = size1 + size2;
    int *ret = new int[size];

    memset(ret, 0, sizeof(int) * size);

    for (int i = 0; i < size2; ++i)
    {
        int k = i;
        for (int j = 0; j < size1; ++j)
            ret[k + j] += (num2[size2 - 1 - i] - '0') * (num1[size1 - 1 - j] - '0');
    }

    for (int i = 0; i < size; ++i)
    {
        if (ret[i] >= 10)
        {
            ret[i + 1] += ret[i] / 10;
            ret[i] %= 10;
        }
    }
    return ret;
};

int main()
{
    string str1, str2;
    cin >> str1 >> str2;
    int num1[str1.size()], num2[str2.size()];
    for (int i = 0; i < str1.size(); i++)
        num1[i] = (int)str1[i];
    for (int i = 0; i < str2.size(); i++)
        num2[i] = (int)str2[i];
    // int num1[3] = {1,1,1};
    // int num2[3] = {2, 2, 2};

    int *ret = multi(num1, str1.size(), num2, str2.size());
    int size = str1.size() + str2.size();

    for (int i = size-2; i >= 0; i--)
        cout << ret[i];
    cout << endl;

    delete[] ret;
    return 0;
}