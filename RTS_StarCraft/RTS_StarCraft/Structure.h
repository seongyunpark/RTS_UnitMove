#pragma once
#include "Object.h"

class Structure : public Object
{
public:
	Structure(int posX, int posY, ePlayer playerIndex);
	~Structure();

protected:
	// �̸�
	// �����
	// ��ĩ��

public:
	virtual void Update() override;
	virtual void Render(DRD2DEngine* pEngine) override;


	virtual void SProduce();	// �ǹ� ��ɼ��� �Լ�
	virtual void SMove();		// �ǹ� �̵� �Լ�
	virtual void SBuild();		// �ǹ� ���� �Լ�. �̰� SCV�� �ϴ� ���ε� ���� �־ �ǳ�??????
	virtual void SUpgrade();	// �ǹ� ���׷��̵�. �̰� ���� �ִ°� �´°Ű���. �ٵ� �׳� ��������°͵��ְ� SCV�� ����°͵� �ִµ� ����? ȥ��������
};

// rebuild = scv�� �ٽ� ���°� / upgrade = �ǹ� ��ü�� ���۵Ǵ°�. Ŭ������ ������ �ϳ�? �ƴϸ� �׳� �Լ��� �־��ϳ�?