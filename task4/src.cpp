//Comparison of two strings
#include <iostream>
#include <string.h>
#include <algorithm>
#include <vector>

using namespace std;

const char uniqChar = '*';
const string ok = "OK";
const string ko = "KO";

bool matchString(const string &strFirst, const string &strSecond);

bool matchSimpleString( string str1, string str2);

bool searchChar(string str, const char &desired = uniqChar);

int optimizeStrig(string &str);


bool getShift(const string &str, const char &value,  const int &indexValue,
              int diff, int oddUniq, int &shift);

int getDifference(const string &str1, const string &str2);

int main(int argc, char *argv[])
{
    if (argc == 3) {
        string str1 = (string)argv[1];
        string str2 = (string)argv[2];

        if (matchString(str1, str2))
            cout << ok;
        else cout << ko;

    } else cout << "There must be two string parameters!";

    return 0;
}

bool matchString(const string &strFirst, const string &strSecond) {

    string str1 = strFirst;
    string str2 = strSecond;

    if (!searchChar(str2)) {
        return matchSimpleString(str1, str2);
    }


    int uniqCnt1, uniqCnt2, chCnt1, chCnt2;
    uniqCnt1 = optimizeStrig(str1);
    uniqCnt2 = optimizeStrig(str2);
    chCnt1 = (int)str1.size() - uniqCnt1;
    chCnt2 = (int)str2.size() - uniqCnt2;

    if (chCnt1 < chCnt2) {

        return false;

    } else if (chCnt1 == chCnt2) { 

        if (uniqCnt1 > uniqCnt2) { 
            return  false;
        } else {
            if (uniqCnt1 == uniqCnt2) { 
                return  matchSimpleString(str1, str2);
            } else {
                int i = 0;
                int diff = uniqCnt2 - uniqCnt1;
                while (diff && str2[i]) { 
                    if (str2[i] == uniqChar) {
                        if (!str1[i] || str1[i] != uniqChar) {
                            str2.erase(i, 1);
                            diff--;
                            continue;
                        }
                    }

                    i++;
                }

                return matchSimpleString(str1, str2);
            } 
        }

    } else {

        int i = 0;
        vector<int> uniqIndexes;
        int tShift;
        string inStr;
        inStr.push_back(uniqChar);

        while (str2[i]) { 
            if (str1[i]) {
                if (str2[i] == uniqChar) {
                    uniqIndexes.push_back(i);
                } else {
                    if (str1[i] != str2[i]) {
                        if ( !getShift(str1, str2[i], i,
                                      getDifference(str1, str2),
                                      (int)uniqIndexes.size(), tShift) )
                            return false;

                        if (tShift > 0) {
                            while (tShift) {
                                str2.insert(i, inStr);
                                i++;
                                tShift--;
                            }
                        } else {
                            while (tShift < 0) {
                                str2.erase(uniqIndexes.back(), 1);
                                uniqIndexes.pop_back();
                                i--;
                                tShift++;
                            }
                        }
                    } 
                }
            } else {
                if (str2[i] == uniqChar) {
                    str2.erase(i, 1);
                } else return false;
            }

            i++;
        }

       
        if ((int)str1.size() > (int)str2.size()) {
            int diff = (int)str1.size() - (int)str2.size();
            if (str2[(int)str2.size() - 1] == uniqChar) {
                while (diff) {
                    str2.insert((int)str2.size() - 1, inStr);
                    diff--;
                }
            } else if ( (str2[(int)str2.size() - 1] ==
                       str1[(int)str1.size() - 1]) && str2[(int)str2.size() - 2]
                        && str2[(int)str2.size() - 2] == uniqChar) {
                while (diff) {
                    str2.insert((int)str2.size() - 2, inStr);
                    diff--;
                }
            } else return false;
        } 

    }

    return matchSimpleString(str1, str2);
}

bool matchSimpleString(string str1, string str2) {

    if (str1.size() != str2.size())
        return false;

    for (int i = 0; i < (int)str1.size(); i++) {
        if (str2[i] != uniqChar && str1[i] != str2[i])
            return false;
    }

    return true;
}

bool searchChar(string str, const char &desired) {

    for (int i = 0; i < (int)str.size(); i++) {
        if (str[i] == desired)
            return true;
    }

    return false;
}

int optimizeStrig(string &str) {

    int i = 0;
    int cnt = 0;
    bool prevUniq{false};
    while (str[i]) {
        if (str[i] == uniqChar) {
            if (prevUniq) {
                str.erase(i, 1);
                continue;
            } else {
                prevUniq = true;
                cnt++;
            }
        } else {
            if (prevUniq)
                prevUniq = false;
        }
        i++;
    }

    return cnt;
}

bool getShift(const string &str, const char &value, const int &indexValue,
              int diff, int oddUniq, int &shift) {

    if (indexValue > ((int)str.size() - 1) || indexValue < 0)
        return false;

    int i = indexValue + 1;
    while (str[i] && diff > 0) {

        if (str[i] == value) {
            shift = i - indexValue;
            return  true;
        }

        diff--;
        i++;
    }

    i = indexValue - 1;
    while (str[i] && oddUniq) {

        if (str[i] == value) {
            shift = i - indexValue;
            return  true;
        }

        oddUniq--;
        i--;
    }

    return false;
}

int getDifference(const string &str1, const string &str2) {
    int diff = (int)str1.size() - (int)str2.size();
    if(str2[(int)str2.size() - 1] == uniqChar)
        diff++;
    return  diff;
}
