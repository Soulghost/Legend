#include "SGValueBar.h"

bool SGValueBar::initWithRect(Rect rect){
    if (!Node::init()) {
        return false;
    }
    m_visible = true;
	this->setContentSize(rect.size);
	this->setPosition(rect.origin);
    
	return true;
}

SGValueBar* SGValueBar::valueBarWithType(SGValueBarType type, Rect rect){
	SGValueBar *bar = new SGValueBar();
	if (bar && bar->initWithRect(rect)){
        bar->autorelease();
		bar->m_type = type;
	}
	else{
		CC_SAFE_DELETE(bar);
	}
	return bar;
}

void SGValueBar::setBarPosition(Point pt){

}

void SGValueBar::setProgress(float progress){
	m_progress = progress;
}

float SGValueBar::getProgress(){
	return m_progress;
}


void SGValueBar::draw(cocos2d::Renderer *renderer, const cocos2d::Mat4 &transform, uint32_t flags){
    if (!m_visible) {
        return;
    }
    _customCommand.func = CC_CALLBACK_0(SGValueBar::onDraw, this, transform, flags);
    renderer->addCommand(&_customCommand);
}

void SGValueBar::onDraw(const kmMat4 &transform, bool transformUpdated){
	kmGLPushMatrix();
	kmGLLoadMatrix(&transform);
	Point src = Point(0, 0);
	Point dest = Point(this->getContentSize());
	// bg
	DrawPrimitives::drawSolidRect(src, dest, Color4F(55/255.0, 0, 0, 1.0));
	// bar
	Color4F color;
	switch (m_type)
	{
	case SGValueBarTypeHpbar:
		color = Color4F(1.0, 0, 0, 1.0);
		break;
	case SGValueBarTypeMpbar:
		color = Color4F(73/255.0, 150/255.0, 239/255.0, 1.0);
		break;
	case SGValueBarTypeSpbar:
		color = Color4F(234/255.0, 234/255.0, 83/255.0, 1.0);
		break;
	}
	dest.x *= m_progress;
	DrawPrimitives::drawSolidRect(src, dest, color);
	kmGLPopMatrix();
}
