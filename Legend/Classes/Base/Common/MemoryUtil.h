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

#endif /* MemoryUtil_hpp */
