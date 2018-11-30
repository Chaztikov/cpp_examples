class Solution {
public:
    vector<string> anagrams(vector<string> &strs) {
        vector<string> result;
        if (strs.size() < 2) return result;
        unordered_multimap<string, int> collections;
        for (int i = 0; i < strs.size(); i++){
            string s = strs[i];
            sort(s.begin(), s.end());
            collections.insert({s, i});
        }
        auto it = collections.begin();
        while (it != collections.end()) {
            string s = it->first;
            if (collections.count(s) > 1) {
                auto range = collections.equal_range(s);
                for (auto it = range.first; it != range.second; it++){
                    result.push_back(strs[it->second]);
                }
            }
            it = collections.equal_range(s).second;
        }
        return result;
    }
};
And here is my one-pass unordered_map version.

class Solution {
public:
    vector<string> anagrams(vector<string> &strs) {
        vector<string> result;
        if (strs.size() < 2) return result;
        unordered_map<string, int> cache;
        for (int i = 0; i < strs.size(); i++) {
            string s = strs[i];
            sort(s.begin(), s.end());
            auto it = cache.find(s);
            if (it == cache.end()) {
                cache[s] = i;
            } else {
                result.push_back(strs[i]);
                if (it->second >= 0) {
                    result.push_back(strs[it->second]);
                    it->second = -1;
                }
            }
        }
        return result;
    }
};