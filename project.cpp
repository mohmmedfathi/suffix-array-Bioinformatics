#include <iostream>
#include<bits/stdc++.h>
using namespace std;

int main(int argc,char *argv[])
{
    fstream genome;
    genome.open(argv[1],ios::in); // read genome file

    if (!(genome.is_open()))
    {
        printf("Cannot open the genome file to read!");
        exit(0);
    }
    vector<string>suffixes;
    map <string,int> suffix_idx_map;

    string str;
    bool h = 0;
    while (getline(genome,str))
    {
        if (h) // to skip first line
        {
            for (int i =0; i<str.size(); i++)
            {
                string temp =  str.substr(i,str.size() - i);

                suffix_idx_map[temp] = i;
                suffixes.push_back(temp);
            }
        }
        else
            h=1;

    }

    sort(suffixes.begin(),suffixes.end());

    ofstream file(argv[2],ios::out | ios::binary); // write as binary
    if (!file)
    {
        cout << "Cannot open the file!" << endl;
        exit(1);
    }
    int n = 0;
    for (int i = 0; i<suffixes.size(); i++)
    {
        file.write((char*)&suffixes[i],sizeof(suffixes[i]));
        char idx = '0' + suffix_idx_map[suffixes[i]];

        file.write(&idx,sizeof(idx));
    }
    file.close();
    genome.close();
    return 0;
}
