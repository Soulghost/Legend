//
//  CppRuntime.h
//  Legend
//
//  Created by soulghost on 15/7/2017.
//
//

#ifndef __CppRuntime_H__
#define __CppRuntime_H__

#include "Legend.h"
#include "CppRuntimeMap.h"

USING_NS_CC;
using namespace std;

typedef std::function<Ref*()> RuntimeCreateFunction;

class CppRuntime : public Ref {
public:
    CppRuntime();
    ~CppRuntime();
    
    SINGLETON(CppRuntime);
    
public:
    Ref* createInstanceByClassName(string className);
    void registerClass(string className, RuntimeCreateFunction createFunction);
    void linkMap(CppRuntimeMap *map);
    
private:
    map<string, RuntimeCreateFunction> _reflectionMap;
private:
    void commonInit();
};

#define RuntimeInterface(class) \
static void rt_register() { \
RuntimeCreateFunction pointer = [](){ \
    return class::create(); \
}; \
CppRuntime::getInstance()->registerClass(CCString(class), pointer); \
}

#define RuntimeImpl(class) \
class::rt_register();

#endif
