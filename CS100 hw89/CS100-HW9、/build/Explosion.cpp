#include "Explosion.h"
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


Explosion::Explosion(int x, int y) :GameObject(IMGID_EXPLOSION, x, y, 0, 3, 4.5, false, 0, 0), m_count(0) {

}

void Explosion::Update() {  //这里只在m_size上做减法会显示出正确的吗？还是说要生成很多个爆炸，一点点显示？
	m_count += 1;
	SetSize(4.5 - 0.2 * m_count);
	if (m_count == 20) {
		Set_is_dead(true);
		return;
	}
}

int Explosion::GetCount() const {
	return m_count;
}