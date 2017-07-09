//
//  LGUITheme.h
//  Legend
//
//  Created by soulghost on 9/7/2017.
//
//

#ifndef LGUITheme_hpp
#define LGUITheme_hpp

#include "Legend.h"

using namespace std;
USING_NS_CC;

class LGUITheme {
public:
    SINGLETON(LGUITheme);
public:
    string cnTTF;
    string enTTF;
    
    float titleFont;
    float detailFont;
    
    Color4B titleColor;
    Color4B detailColor;

};

#endif /* LGUITheme_hpp */
