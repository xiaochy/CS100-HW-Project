#ifndef EXPLOSION_H__
#define EXPLOSION_H__
#include "GameObjects.h"

class Explosion : public GameObject {
public:
	Explosion(int x, int y);
	virtual void Update() override;
	//virtual bool IsEnemy() override;
	int GetCount() const;
private:
	int m_count;
};


#endif