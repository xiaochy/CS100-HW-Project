#ifndef REDBULLET_H__
#define REDBULLET_H__

#include "GameObjects.h"
class Red_bullet : public GameObject {
public:
	Red_bullet(int x, int y, int direction, int hurt, GameWorld* ptr);
	virtual void Update() override;
	//virtual bool IsEnemy() override;
	bool Check_collapse();
	GameWorld* Get_World_Ptr() const;
private:
	GameWorld* m_world_ptr;
};




#endif