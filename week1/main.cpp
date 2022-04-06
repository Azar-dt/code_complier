#include <bits/stdc++.h>

using namespace std;

bool isAlphabet(char x)
{
    return (x > 64 && x < 91) || (x > 96 && x < 123);
}

string formatString(string s)
{
    int n = s.length();
    while (!isAlphabet(s[n - 1]))
    {
        s.pop_back();
        n -= 1;
        if (n <= 0)
            return "";
    }
    while (!isAlphabet(s[0]))
    {
        for (int i = 0; i < n - 1; i++)
        {
            s[i] = s[i + 1];
        }
        s.pop_back();
        n -= 1;
        if (n <= 0)
            return "";
    }
    for (int i = 0; i < s.length(); i++)
    {
        s[i] = tolower(s[i]);
    }
    return s;
}

void handleIndex(bool checkDot, map<string, set<int>> &index, set<string> stopw, string w, int line)
{
    if (!(!checkDot && w[0] >= 65 && w[0] <= 90))
    {
        if (stopw.find(w) == stopw.end())
        {

            index[w].insert(line);
        }
    }
    else
        cout << w << checkDot << endl;
}

int main()
{
    fstream fi("vanban1.txt", ios::in);
    fstream fstopw("stopw.txt", ios::in);
    set<string> stopw;
    int line = 0;
    map<string, set<int>> index;
    if (fi.fail() || fstopw.fail())
    {
        cout << "Can not open file /n";
        return 0;
    }

    while (!fstopw.eof())
    {
        string s;
        fstopw >> s;
        stopw.insert(s);
    }

    while (!fi.eof())
    {
        line++;
        string lineString;
        getline(fi, lineString);
        string w;
        bool checkDot = false;
        int idx = 0;
        while (idx < lineString.length())
        {
            char c = lineString[idx];
            if (isAlphabet(c))
            {
                w.push_back(c);
            }
            if (!isAlphabet(c))
            {
                if (c != ' ')
                    checkDot = false;
                if (w != "")
                    handleIndex(checkDot, index, stopw, w, line);
                w.clear();
                if (c == '.')
                    checkDot = true;
            }
            idx++;
        }
    }

    fstream fo("index.txt", ios::out);
    for (auto x : index)
    {
        fo << x.first << " " << x.second.size();
        for (auto i : x.second)
        {
            fo << "," << i;
        }
        fo << endl;
    }
    return 0;
}