#include <bits/stdc++.h>

using namespace std;

string formatString(string s)
{
    int n = s.length();
    while (!((s[n - 1] > 64 && s[n - 1] < 91) || (s[n - 1] > 96 && s[n - 1] < 123)))
    {
        s.pop_back();
        n -= 1;
        if (n <= 0)
            return "";
    }
    while (!((s[0] > 64 && s[0] < 91) || (s[0] > 96 && s[0] < 123)))
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
    s[0] = tolower(s[0]);
    return s;
}

int main()
{
    fstream fi("vanban.txt", ios::in);
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
        stringstream ss(lineString);
        string w;
        bool checkDot = false;
        while (ss >> w)
        {
            if (!(!checkDot && w[0] >= 65 && w[0] <= 90))
            {

                if (w[w.length() - 1] == '.')
                    checkDot = true;
                string word = formatString(w);
                if (word != "" && (stopw.find(word) == stopw.end()))
                {

                    index[word].insert(line);
                }
            }
            // else
            //     cout << w << endl;
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