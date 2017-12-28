#ifndef __SGValueBar_H__
#define __SGValueBar_H__

#include "cocos2d.h"

USING_NS_CC;
using namespace std;

typedef enum{
	SGValueBarTypeHpbar = 0,
	SGValueBarTypeMpbar,
	SGValueBarTypeSpbar
}SGValueBarType;

class SGValueBar : public Node {
public:
	bool initWithRect(Rect rect);
	static SGValueBar *valueBarWithType(SGValueBarType type, Rect rect);
	void setBarPosition(Point pt);
	void setTint(ProgressTimer *bar, Sprite *bg);
	void setProgress(float progress);
	float getProgress();
    void setVisible(bool visible){ m_visible = visible; }
private:
	SGValueBarType m_type;
	float m_progress;
    bool m_visible;
public:
	//virtual void draw(Renderer *renderer, const kmMat4 &transform, bool transformUpdated);
    virtual void draw(Renderer *renderer, const Mat4 &transform, uint32_t flags);
private:
	CustomCommand _customCommand;
	void onDraw(const kmMat4 &transform, bool transformUpdated);

};

#endif
