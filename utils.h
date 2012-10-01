#ifndef UTILS_H
#define UTILS_H

#include <vector>

class utils
{
public:
    utils();

    template <typename T>
    static T * findOrAdd(std::vector<T*> & v,  T  *t) {
        typename std::vector<T*>::iterator it;
        for (it = v.begin(); it!= v.end() && (*(*it)) != *t; it++) {}
        if(it == v.end()) {
            v.push_back(new T(*t));
            it = v.end();
            it--;
        }
        return (*it);
    }


};







#endif // UTILS_H
