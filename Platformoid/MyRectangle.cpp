#include "MyRectangle.h"

MyRectangle::MyRectangle(void)
{

}


bool MyRectangle::intersect(float x,float y)
{
	Vector2f position=rectangle.getPosition();
	if (x>=position.x&&x<=(position.x+width)&&y>=position.y&&y<=(position.y+length))
		return 1;
	else
	return 0;
}

void MyRectangle::draw(RenderWindow* window)
{
	window->draw(rectangle);
}
