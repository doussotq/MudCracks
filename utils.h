#ifndef UTILS_H
#define UTILS_H

#include <vector>

class utils
{
public:
    utils();

    template <typename T>
    static int findOrAdd(std::vector<T*> & v,  T  *t) {
        unsigned int c=0;
        typename std::vector<T*>::iterator it;
        for (it = v.begin(); it!= v.end() && (*(*it)) != *t; it++) {
        c++;
        }
        if(it == v.end()) {
            c=v.size();
            v.push_back(new T(*t));
            it = v.end();
            it--;            
        }
        return c;
    }


};







#endif // UTILS_H
