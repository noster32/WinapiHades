#include "Stdafx.h"
#include "RenderObject.h"

void RenderObject::SetTexture(uint texture) {
	this->texture = texture;
	const TextureSource& ref = gl.GetTextureInformation(texture);
	this->renderSize = Point2D(ref.range.rightTop) - ref.range.leftBottom;
}

void RenderObject::Render() {
	if (!enabled) return;

	gl.PushMatrix();

	Point2D arg;
	if (renderOp & RenderObject::FIT_TO_SCREEN_KEEP_RATIO) {
		const TextureSource& ref = gl.GetTextureInformation(texture);
		Point2D usedRange = Point2D(ref.range.rightTop) - ref.range.leftBottom;
		float aspect = (float)usedRange.x / usedRange.y;

		Point2D winsize = gl.GetWindowSize();
		Vector2D stretchRatio = Vector2D(winsize) / usedRange;

		if (stretchRatio.x < stretchRatio.y) {
			arg = Point2D(winsize.x, (int)(stretchRatio.x * usedRange.y));
		}
		else {
			arg = Point2D((int)(stretchRatio.y * usedRange.x), winsize.y);
		}
	}
	else {
		if (renderOp & RenderObject::TEXTURE_SIZE) {
			arg = Point2D();
		}
		else if (renderOp & RenderObject::GIVEN_SIZE) {
			arg = renderSize;
		}
	}

	if (renderOp & RenderObject::STRETCH_HOR)
		arg.x = gl.GetWindowSize().x;

	if (renderOp & RenderObject::STRETCH_VER)
		arg.y = gl.GetWindowSize().y;

	gl.DrawTextureAuto(transformation, texture, tick, arg);

	vector<SceneObject*>& children = GetChildrenVector();
	vector<SceneObject*>::iterator iter;
	for (iter = children.begin(); iter != children.end(); iter++) {
		(*iter)->Render();
	}

	gl.PopMatrix();
}
