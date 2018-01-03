#include "SGSpriteTool.h"

Sprite* SGSpriteTool::createResizableImage(string imagePath, Rect rect, Point anchorPoint){
	Sprite *image = Sprite::create(imagePath);
	Size contentSize = image->getContentSize();
	Size destSize = rect.size;
	float ratioX = destSize.width / contentSize.width;
	float ratioY = destSize.height / contentSize.height;
	image->setAnchorPoint(anchorPoint);
	image->setScaleX(ratioX);
	image->setScaleY(ratioY);
	image->setPosition(rect.origin);
	return image;
}

Sprite* SGSpriteTool::createResizableImage(string imagePath){
	return createResizableImage(imagePath, Rect(30, 30, 60, 60), Point(0.5, 0.5));
}

