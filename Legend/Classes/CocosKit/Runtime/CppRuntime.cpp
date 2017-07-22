//
//  CppRuntime.cpp
//  Legend
//
//  Created by soulghost on 15/7/2017.
//
//

#include "CppRuntime.h"

CppRuntime::CppRuntime() {

}

CppRuntime::~CppRuntime() {
    
}

bool CppRuntime::init() {
    commonInit();
    return true;
}

void CppRuntime::commonInit() {
    
}

void CppRuntime::linkMap(CppRuntimeMap *map) {
    map->registerClasses();
}

Ref* CppRuntime::createInstanceByClassName(string className) {
    CCASSERT(_reflectionMap.find(className) != _reflectionMap.end(), StringUtils::format("class %s has not been registerd.", className.c_str()).c_str());
    RuntimeCreateFunction createFunction = _reflectionMap[className];
    return createFunction();
}

void CppRuntime::registerClass(string className, RuntimeCreateFunction createFunction) {
    if (_reflectionMap.find(className) != _reflectionMap.end()) {
        return;
    }
    _reflectionMap[className] = createFunction;
}
