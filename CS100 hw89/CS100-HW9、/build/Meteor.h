#ifndef METEOR_H__
#define METEOR_H__
#include "GameObjects.h"

class Meteor : public GameObject {
public:
	Meteor(int x, int y, Dawnbreaker* ptr);
	virtual void Update() override;
	//virtual bool IsEnemy() override;
	void Check_collapse();
	Dawnbreaker* Get_Dawn_Ptr();
private:
	Dawnbreaker* m_ptr;
};


#endif