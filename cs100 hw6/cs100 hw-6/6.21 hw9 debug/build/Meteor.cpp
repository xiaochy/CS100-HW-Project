#include "Meteor.h"
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

Meteor::Meteor(int x, int y, Dawnbreaker* ptr) :GameObject(IMGID_METEOR, x, y, 0, 1, 2.0, false, 0, 0), m_ptr(ptr) {

}

Dawnbreaker* Meteor::Get_Dawn_Ptr() {
	return m_ptr;
}

void Meteor::Check_collapse() {
	for (auto& object : Get_Dawn_Ptr()->GetPtr()->m_game_object) { //////ѭ��
		if (dynamic_cast<Alphatron*>(object) != nullptr && object->Get_is_dead() != true) {
			if (is_collapsed(object->GetX(), object->GetY(), GetX(), GetY(), 1.0, 2.0)) {
				object->Set_is_dead(true);		   //�᲻����������ɫ�ӵ�ͬʱײ�ϣ������᲻����������ʯһ��װ�ϣ�
				Get_Dawn_Ptr()->GetPtr()->IncreaseScore(50);//�¼ӵ�
				Explosion* real_explosion = new Explosion(object->GetX(), object->GetY());   //�����������¼ӵ�
				Get_Dawn_Ptr()->GetPtr()->AddObject(real_explosion);
				Get_Dawn_Ptr()->SetHasdestroyed(Get_Dawn_Ptr()->GetHasdestroyed() + 1);
			}
		}
		else if (dynamic_cast<Sigmatron*>(object) != nullptr && object->Get_is_dead() != true) {
			if (is_collapsed(object->GetX(), object->GetY(), GetX(), GetY(), 1.0, 2.0)) {
				object->Set_is_dead(true);
				Get_Dawn_Ptr()->GetPtr()->IncreaseScore(100);
				Explosion* real_explosion = new Explosion(object->GetX(), object->GetY());   //�����������¼ӵ�
				Get_Dawn_Ptr()->GetPtr()->AddObject(real_explosion);
				Get_Dawn_Ptr()->SetHasdestroyed(Get_Dawn_Ptr()->GetHasdestroyed() + 1);

				if (randInt(1, 5) == 1) {//�¼ӵ�
					HP_Restore_Goodie* real_hp_restore_goodie = new HP_Restore_Goodie(IMGID_HP_RESTORE_GOODIE, object->GetX(), object->GetY(), Get_Dawn_Ptr()->GetPtr());
					Get_Dawn_Ptr()->GetPtr()->AddObject(real_hp_restore_goodie);
				}
			}
		}
		else if (dynamic_cast<Omegatron*>(object) != nullptr && object->Get_is_dead() != true) {
			if (is_collapsed(object->GetX(), object->GetY(), GetX(), GetY(), 1.0, 2.0)) {
				object->Set_is_dead(true);
				Get_Dawn_Ptr()->GetPtr()->IncreaseScore(200);
				Explosion* real_explosion = new Explosion(object->GetX(), object->GetY());   //�����������¼ӵ�
				Get_Dawn_Ptr()->GetPtr()->AddObject(real_explosion);
				Get_Dawn_Ptr()->SetHasdestroyed(Get_Dawn_Ptr()->GetHasdestroyed() + 1);

				int rand = randInt(1, 5);
				if (rand == 1 || rand == 2) {
					int rand2 = randInt(1, 5);
					if (rand2 >= 1 && rand2 <= 4) {
						Power_Up_Goodie* real_power_up_goodie = new Power_Up_Goodie(IMGID_POWERUP_GOODIE, object->GetX(), object->GetY(), Get_Dawn_Ptr()->GetPtr());
						Get_Dawn_Ptr()->GetPtr()->AddObject(real_power_up_goodie);
					}
					else if (rand2 == 5) {
						Meteor_Goodie* real_meteor_goodie = new Meteor_Goodie(IMGID_METEOR_GOODIE, object->GetX(), object->GetY(), Get_Dawn_Ptr()->GetPtr());
						Get_Dawn_Ptr()->GetPtr()->AddObject(real_meteor_goodie);
					}
				}
			}
		}
	}
}

void Meteor::Update() {
	if (Get_is_dead() == true) {
		return;
	}
	if (GetY() >= WINDOW_HEIGHT) {
		Set_is_dead(true);
		return;
	}
	//��ʯ��һ�μ���Լ��Ƿ�����һֻ�л���ײ  д��
	Check_collapse();

	MoveTo(GetX(), GetY() + 2);
	SetDirection(GetDirection() + 5);

	//�ƶ�����ʯ��Ҫ�ڶ��μ���Լ��Ƿ�������һֻ�л���ײ  д��
	Check_collapse();

}
