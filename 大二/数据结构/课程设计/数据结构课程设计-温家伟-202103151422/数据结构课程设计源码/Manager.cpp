#include "Manager.h"
#include <algorithm>

bool Manager::read(const std::string& fileName)
{
    string arr[100];
    ifstream infile(fileName, ios::in | ios::_Nocreate);

    int i = 0;
    while (infile >> arr[i])
    {
        string left;
        string right;
        char sign;
        for (auto e : arr[i])
        {
            if (e > '9' || e < '0')
            {
                sign = e;
                left = string(arr[i].begin(), arr[i].begin() + arr[i].find(sign));
                right = string(arr[i].begin() + arr[i].find(sign)+1, arr[i].end());
                Expression temp;
                temp._left = string2Bignum(left);
                temp._right = string2Bignum(right);
                temp._sign = sign;
                if (temp._sign == '+')
                {
                    temp._result = temp._left + temp._right;
                }
                else if (temp._sign == '-')
                {
                    temp._result = temp._left - temp._right;
                }
                else if (temp._sign == '*')
                {
                    temp._result = temp._left * temp._right;
                }
                else if (temp._sign == '/')
                {
                    temp._result = temp._left / temp._right;
                }
                else if (temp._sign == '%')
                {
                    temp._result = temp._left % temp._right;
                }
                else if (temp._sign == '^')
                {
                    temp._result = temp._left ^ temp._right;
                }
                _bignums.push_back(temp);
            }
        }
        ++i;
    }
    infile.close();

    return true;

}

void Manager::write(const std::string& fileName, string wstr) const
{
    ofstream outfile(fileName, ios::out | ios::_Nocreate | ios::app);
    // Ğ´ÈëÊı¾İ
    outfile << wstr.c_str() << endl;
    outfile.close();
}

void Manager::setBignum(const int& index, const Expression& bignum)
{
    _bignums[index] = bignum;
}

void Manager::deleteBignum(const int& index)
{
    _bignums.erase(_bignums.end() + index);
}

void Manager::addBignum(const Expression& bignum)
{
    _bignums.push_back(bignum);
}

const Expression& Manager::getBignums(const int& index) const
{
    return _bignums[index];
}

const size_t Manager::size() const
{
    return _bignums.size();
}

Bignum<List<int>> Manager::string2Bignum(string str)
{
    Bignum<List<int>> ret;
    for (auto e : str)
    {
        ret.push_back(e - '0');
    }
    return ret;
}