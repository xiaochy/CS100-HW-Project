#include "Goodie.h"
using namespace std;

bool is_collapsed(int x1, int y1, int x2, int y2, double size1, double size2) {
	double d = sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
	if (d < 30 * (size1 + size2)) {
		return true;
	}
	else {
		return false;
	}
}

Goodie::Goodie(int image_ID, int x, int y, GameWorld* ptr2) :GameObject(image_ID, x, y, 0, 2, 0.5, false, 0, 0), m_goodie_world_ptr(ptr2) {

}

void Goodie::Update() {

}

bool Goodie::Check_collapse() {
	return false;
}


//
//Enemy* Goodie::Get_Enemy_Ptr() const{
//	return m_enemy_ptr;
//}

GameWorld* Goodie::Get_Goodie_World_Ptr()const {
	return m_goodie_world_ptr;
}

/// ///////////////////////////////////////////

HP_Restore_Goodie::HP_Restore_Goodie(int image_ID, int x, int y, GameWorld* ptr2) :Goodie(IMGID_HP_RESTORE_GOODIE, x, y, ptr2) {

}

bool HP_Restore_Goodie::Check_collapse() {
	if (Get_Goodie_World_Ptr()->GetDawnbreaker()->Get_is_dead() != true) {
		if (is_collapsed(Get_Goodie_World_Ptr()->GetDawnbreaker()->GetX(), Get_Goodie_World_Ptr()->GetDawnbreaker()->GetY(), GetX(), GetY(), 1.0, 0.5)) {  //第一二个位置统一写破晓号的位置
			if ((Get_Goodie_World_Ptr()->GetDawnbreaker()->GetHp() + 50) > 100) {
				Get_Goodie_World_Ptr()->GetDawnbreaker()->SetHp(100);
			}
			else {
				Get_Goodie_World_Ptr()->GetDawnbreaker()->SetHp(Get_Goodie_World_Ptr()->GetDawnbreaker()->GetHp() + 50);
			}

			Get_Goodie_World_Ptr()->IncreaseScore(20);
			Set_is_dead(true);
			return true;
		}
		else {
			return false;
		}
	}
	return false;

}

void HP_Restore_Goodie::Update() {
	if (Get_is_dead() == true) {
		return;
	}
	if (GetY() < 0) {
		Set_is_dead(true);
		return;
	}

	//HP道具需要第一次检查自己是否正在与破晓号相撞   写！
	if (Check_collapse()) {
		return;
	}

	MoveTo(GetX(), GetY() - 2);
	//HP道具需要第二次检查自己是否正在与破晓号相撞   写！
	if (Check_collapse()) {
		return;
	}

}
/// /////////////////////////////////////////////////

Power_Up_Goodie::Power_Up_Goodie(int image_ID, int x, int y, GameWorld* ptr2) :Goodie(IMGID_POWERUP_GOODIE, x, y, ptr2) {

}

bool Power_Up_Goodie::Check_collapse() {
	if (Get_Goodie_World_Ptr()->GetDawnbreaker()->Get_is_dead() != true) {
		if (is_collapsed(Get_Goodie_World_Ptr()->GetDawnbreaker()->GetX(), Get_Goodie_World_Ptr()->GetDawnbreaker()->GetY(), GetX(), GetY(), 1.0, 0.5)) {
			Get_Goodie_World_Ptr()->GetDawnbreaker()->SetPowerGoodie(Get_Goodie_World_Ptr()->GetDawnbreaker()->GetPowerGoodie() + 1);
			Get_Goodie_World_Ptr()->IncreaseScore(20);
			Set_is_dead(true);
			return true;
		}
		else {
			return false;
		}
	}
	return false;
}

void Power_Up_Goodie::Update() {
	if (Get_is_dead() == true) {
		return;
	}
	if (GetY() < 0) {
		Set_is_dead(true);
		return;
	}

	//升级道具需要第一次检查自己是否正在与破晓号相撞   写！
	if (Check_collapse()) {
		return;
	}

	MoveTo(GetX(), GetY() - 2);
	//升级道具需要第二次检查自己是否正在与破晓号相撞   写！
	if (Check_collapse()) {
		return;
	}

}

/// ///////////////////////////////////////////////////////////


Meteor_Goodie::Meteor_Goodie(int image_ID, int x, int y, GameWorld* ptr2) :Goodie(IMGID_METEOR_GOODIE, x, y, ptr2) {

}

bool Meteor_Goodie::Check_collapse() {
	if (Get_Goodie_World_Ptr()->GetDawnbreaker()->Get_is_dead() != true) {
		if (is_collapsed(Get_Goodie_World_Ptr()->GetDawnbreaker()->GetX(), Get_Goodie_World_Ptr()->GetDawnbreaker()->GetY(), GetX(), GetY(), 1.0, 0.5)) {
			Get_Goodie_World_Ptr()->GetDawnbreaker()->SetMeteorGoodie(Get_Goodie_World_Ptr()->GetDawnbreaker()->GetMeteorGoodie() + 1);
			Get_Goodie_World_Ptr()->IncreaseScore(20);
			Set_is_dead(true);
			return true;
		}
		else {
			return false;
		}
	}
	return false;

}

void Meteor_Goodie::Update() {
	if (Get_is_dead() == true) {
		return;
	}
	if (GetY() < 0) {
		Set_is_dead(true);
		return;
	}
	//陨石道具需要第一次检查自己是否正在与破晓号相撞   写！
	if (Check_collapse()) {
		return;
	}

	MoveTo(GetX(), GetY() - 2);
	//陨石道具需要第一次检查自己是否正在与破晓号相撞   写！
	if (Check_collapse()) {
		return;
	}

}