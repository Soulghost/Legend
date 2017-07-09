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

#include <stdio.h>

#endif /* MemoryUtil_hpp */
