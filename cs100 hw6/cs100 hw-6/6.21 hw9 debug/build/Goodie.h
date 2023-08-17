#ifndef GOODIE_H__
#define GOODIE_H__
#include "GameObjects.h"

class Goodie : public GameObject {
public:
	Goodie(int image_ID, int x, int y, GameWorld* ptr2);
	virtual void Update() override;
	//virtual bool IsEnemy() override;
	virtual bool Check_collapse();

	//Enemy* Get_Enemy_Ptr() const;
	GameWorld* Get_Goodie_World_Ptr()const;

private:
	//Enemy* m_enemy_ptr;
	GameWorld* m_goodie_world_ptr;
};

//////////////////////////////////////////////

class HP_Restore_Goodie : public Goodie {
public:
	HP_Restore_Goodie(int image_ID, int x, int y, GameWorld* ptr2); //这里我把Enemy* ptr去掉了
	virtual void Update() override;
	virtual bool Check_collapse() override;

};

/// ////////////////////////////////////////


class Power_Up_Goodie : public Goodie {
public:
	Power_Up_Goodie(int image_ID, int x, int y, GameWorld* ptr2);
	virtual void Update() override;
	virtual bool Check_collapse() override;

};

/// ///////////////////////////////////////////

class Meteor_Goodie : public Goodie {
public:
	Meteor_Goodie(int image_ID, int x, int y, GameWorld* ptr2);
	virtual void Update() override;
	virtual bool Check_collapse() override;

};



#endif 