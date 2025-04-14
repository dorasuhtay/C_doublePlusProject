#ifndef WCTSTRINGLIST_H_INCLUDED
#define WCTSTRINGLIST_H_INCLUDED


#include "wctString.h"

#define MAX_wctStringList   1024

class wctStringList
{
private:
    int count;
    wctString   *wctstr[MAX_wctStringList];
public:
    wctStringList();
    ~wctStringList();
    void clear();
    void add(const wchar_t *wstr);
    int getcount() {return count;}
    const wctString *get(int index);
};

#endif // WCTSTRINGLIST_H_INCLUDED
