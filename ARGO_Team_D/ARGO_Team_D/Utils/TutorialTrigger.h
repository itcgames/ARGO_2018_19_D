#ifndef TUTORIALTRIGGER_H
#define TUTORIALTRIGGER_H

#include "PhysicsBody.h"
#include <SDL_render.h>

#include "MathUtils.h"

struct TutorialTrigger {
	TutorialTrigger(const float x, const float y, const int w, const int h, const float angle, const float worldScale, b2World & world) :
		pb("TutorialTrigger") {
		pb.bodyDef.type = b2_staticBody;
		pb.bodyDef.position = b2Vec2((x + (w / 2.f)) / worldScale, (y + (h / 2.f)) / worldScale);
		pb.body = world.CreateBody(&pb.bodyDef);
		pb.shape.SetAsBox((w / 2.f) / worldScale, (h / 2.f) / worldScale);
		pb.fixture.density = 1.f;
		pb.fixture.friction = 0.f;
		pb.fixture.shape = &pb.shape;
		pb.fixture.isSensor = true;
		pb.data.tag = "TutorialTrigger";
		pb.data.data = this;
		pb.fixture.userData = &pb.data;
		pb.fixture.filter.categoryBits = 0x0002;
		pb.fixture.filter.maskBits = 0x0001;
		pb.body->CreateFixture(&pb.fixture);
		pb.body->SetFixedRotation(true);
		bounds.x = x;
		bounds.y = y;
		bounds.w = w;
		bounds.h = h;
		originalSize = promptBounds;
		sizeV = VectorAPI(0,0);
		step = 0.03f;
	};

	void update() {
		if (transitionIn) {
			if (percent < 1) {
				percent += step;
			}
			else {
				percent = 1;
				transitionIn = false;
			}
			currentSize = mu::lerp(sizeV, originalSizeV, percent);
			promptBounds.w = currentSize.x;
			promptBounds.h = currentSize.y;
		}
		else if (transitionOut) {
			if (percent < 1) {
				percent += step;
			}
			else {
				percent = 1;
				transitionOut = false;
			}
			currentSize = mu::lerp(originalSizeV, sizeV, percent);
			promptBounds.w = currentSize.x;
			promptBounds.h = currentSize.y;
		}
	}

	void animateIn() {
		transitionOut = false;
		transitionIn = true;
		percent = 0;
	};

	void animateOut() {
		transitionIn = false;
		transitionOut = true;
		percent = 0;
	}
	PhysicsBody pb;
	SDL_Rect bounds;
	SDL_Rect promptBounds;
	SDL_Rect originalSize;
	VectorAPI sizeV;
	VectorAPI originalSizeV;
	VectorAPI currentSize;
	std::string message;
	SDL_Surface * messageSurface;
	SDL_Texture * messageTexture;
	float timer = 0;
	float maxTime = 0;
	float percent = 0;
	float step = 0;

	bool transitionIn = false;
	bool transitionOut = false;
};

#endif //!TUTORIALTRIGGER_H