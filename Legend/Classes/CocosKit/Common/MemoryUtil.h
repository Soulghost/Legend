//
//  MemoryUtil.h
//  Legend
//
//  Created by soulghost on 9/7/2017.
//
//

#ifndef MemoryUtil_hpp
#define MemoryUtil_hpp

#define MEMCLEAR(ptr) \
do { \
ptr->release(); \
ptr=nullptr; \
}while(0);

#define MEMSETTER(ptr) \
do { \
_##ptr = ptr; \
_##ptr->retain(); \
}while(0);

#define CREATE_MEMSETTER_ADD(class, ptr) \
do { \
    class *ptr = class::create();  \
    MEMSETTER(ptr); \
    this->addChild(ptr); \
}while(0);

#define SINGLETON(__TYPE__) \
    static __TYPE__* getInstance() { \
    static __TYPE__ *instance = nullptr; \
    if (instance == nullptr) { \
        instance = new(std::nothrow) __TYPE__(); \
        if (instance && instance->init()) { \
            return instance; \
        } else { \
            delete instance; \
            instance = nullptr; \
            return nullptr; \
        } \
    } \
    return instance; \
} \
bool init(); \

#define CREATE_FUNC_PARAMS_1(__TYPE__, __INIT__, P1T, P1V) \
bool init##__INIT__(P1T P1V); \
static __TYPE__* create##__INIT__(P1T P1V) \
{ \
__TYPE__ *pRet = new(std::nothrow) __TYPE__(); \
if (pRet && pRet->init##__INIT__(P1V)) \
{ \
pRet->autorelease(); \
return pRet; \
} \
else \
{ \
delete pRet; \
pRet = nullptr; \
return nullptr; \
} \
}

#define CREATE_FUNC_PARAMS_2(__TYPE__, __INIT__, P1T, P1V, P2T, P2V) \
bool init##__INIT__(P1T P1V, P2T P2V); \
static __TYPE__* create##__INIT__(P1T P1V, P2T P2V) \
{ \
__TYPE__ *pRet = new(std::nothrow) __TYPE__(); \
if (pRet && pRet->init##__INIT__(P1V, P2V)) \
{ \
pRet->autorelease(); \
return pRet; \
} \
else \
{ \
delete pRet; \
pRet = nullptr; \
return nullptr; \
} \
}

#define CREATE_FUNC_PARAMS_3(__TYPE__, __INIT__, P1T, P1V, P2T, P2V, P3T, P3V) \
bool init##__INIT__(P1T P1V, P2T P2V, P3T P3V); \
static __TYPE__* create##__INIT__(P1T P1V, P2T P2V, P3T P3V) \
{ \
__TYPE__ *pRet = new(std::nothrow) __TYPE__(); \
if (pRet && pRet->init##__INIT__(P1V, P2V, P3V)) \
{ \
pRet->autorelease(); \
return pRet; \
} \
else \
{ \
delete pRet; \
pRet = nullptr; \
return nullptr; \
} \
}

#endif /* MemoryUtil_hpp */
