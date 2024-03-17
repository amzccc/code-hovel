#ifndef __BASE_H__
#define __BASE_H__

class IBase {
public:
    IBase();
    virtual ~IBase();

    virtual void print() = 0;
};

#endif