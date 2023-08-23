#include <unordered_set>
#include <unordered_map>
#include <algorithm>
#include <string>
#include <vector>
#include <iostream>
using namespace std;
class Solution
{
public:
    int firstUniqChar(string s)
    {
        unordered_map<char, int> map;
        for (char c : s)
            map[c]++;

        //  for (const auto& pair : map) // auto == std::pair<const int, int>
        for (int i = 0; i < s.size(); i++)
        {
            if (map[s[i]] == 1)
                return i;
        }
        return -1;
    }
    bool canConstruct(string ransomNote, string magazine)
    {

        unordered_map<char, int> map;
        int i, j;

        for (const char &val : magazine)
            map[val]++;
        for (const char &val : ransomNote)
        {
            if (!map.count(val))
                return false;
            if (--map[val] == 0)
                map.erase(val);
        }
        return true;
    }
    bool isAnagram(string s, string t)
    {
        int i;
        sort(s.begin(), s.end());
        sort(t.begin(), t.end());
        return s == t;
    }
};

int main()
{
    Solution s;
    string ransomNote = "anagtam", magazine = "nagaram";
    int res = s.isAnagram(ransomNote, magazine);
    cout << res;
    // for (const auto &row : res)
    // {
    //     for (const auto &element : row)
    //     {
    //         std::cout << element << ' ';
    //     }
    // }
    return 0;
}