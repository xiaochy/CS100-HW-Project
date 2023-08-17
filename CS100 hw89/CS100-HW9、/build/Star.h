#ifndef STAR_H__
#define STAR_H__
#include "GameObjects.h"

class Star : public GameObject {
public:
	Star(int y);
	virtual void Update() override;
	//virtual bool IsEnemy() override;
};


#endif