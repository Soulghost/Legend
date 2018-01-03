#ifndef __SGSpriteTool_H__
#define __SGSpriteTool_H__

#include "cocos2d.h"
USING_NS_CC;
using namespace std;

class SGSpriteTool{
public:
	static Sprite* createResizableImage(string imagePath, Rect rect, Point anchorPoint);
	static Sprite* createResizableImage(string imagePath);
};

#endif