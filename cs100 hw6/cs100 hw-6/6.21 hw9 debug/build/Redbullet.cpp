#include "Redbullet.h"
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

Red_bullet::Red_bullet(int x, int y, int direction, int hurt, GameWorld* ptr) :GameObject(IMGID_RED_BULLET, x, y, direction, 1, 0.5, false, 0, hurt), m_world_ptr(ptr) {

}

bool Red_bullet::Check_collapse() {
	if (Get_World_Ptr()->GetDawnbreaker()->Get_is_dead() != true) {
		if (is_collapsed(Get_World_Ptr()->GetDawnbreaker()->GetX(), Get_World_Ptr()->GetDawnbreaker()->GetY(), GetX(), GetY(), 1.0, 0.5)) {
			if (Get_World_Ptr()->GetDawnbreaker()->GetHp() - GetHurt() <= 0) {
				Get_World_Ptr()->GetDawnbreaker()->SetHp(0);
				Get_World_Ptr()->GetDawnbreaker()->Set_is_dead(true);
			}
			else {
				Get_World_Ptr()->GetDawnbreaker()->SetHp(Get_World_Ptr()->GetDawnbreaker()->GetHp() - GetHurt());
			}
			Set_is_dead(true);
			return true;
		}
		else {
			return false;
		}
	}
	return false;
}

void Red_bullet::Update() {
	if (Get_is_dead() == true) {
		return;
	}
	if (GetY() < 0) {
		Set_is_dead(true);
		return;
	}
	//红色子弹需要第一次检查自己是否正在与破晓号发生碰撞  写！
	if (Check_collapse()) {
		return;
	}


	if (GetDirection() == 180) {
		MoveTo(GetX(), GetY() - 6);
	}
	else if (GetDirection() == 162) {
		MoveTo(GetX() + 2, GetY() - 6);
	}
	else if (GetDirection() == 198) {
		MoveTo(GetX() - 2, GetY() - 6);
	}

	//移动后，红色子弹需要第二次检查自己是否正在与破晓号相撞  写！

	if (Check_collapse()) {
		return;
	}

}

GameWorld* Red_bullet::Get_World_Ptr() const {
	return m_world_ptr;
}

