//vov
#ifndef VSTRING_HPP
#define VSTRING_HPP

#include <string>
#include <sstream>
#include <vector>

template<class T>
static T vStringToNum(const std::string& str) {
    std::stringstream ss;
    ss<<str;
    T num;
    ss>>num;
    return num;
}

template<class T>
static std::string vNumToString(const T num) {
    std::stringstream ss;
    ss<<num;
    return ss.str();
}

static bool vStringHasChar(const std::string& str,const char ch) {
    return (str.find(ch)!=std::string::npos)?true:false;
}

static std::vector<std::string> vStringSplit(const std::string& s,const std::string& delim) {
    std::vector<std::string> elems;
    size_t pos = 0;
    size_t len = s.length();
    size_t delim_len = delim.length();
    if (delim_len == 0) return elems;
    while (pos < len) {
        int find_pos = s.find(delim, pos);
        if (find_pos < 0) {
            elems.push_back(s.substr(pos, len - pos));
            break;
        }
        elems.push_back(s.substr(pos, find_pos - pos));
        pos = find_pos + delim_len;
    }
    return elems;
}

#endif