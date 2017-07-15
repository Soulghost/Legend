//
//  LGRuntimeMap.h
//  Legend
//
//  Created by soulghost on 16/7/2017.
//
//

#ifndef __LGRuntimeMap_H__
#define __LGRuntimeMap_H__

#include "CppRuntime.h"

class LGRuntimeMap : public CppRuntimeMap {
public:
    virtual void registerClasses() override;
};

#endif
