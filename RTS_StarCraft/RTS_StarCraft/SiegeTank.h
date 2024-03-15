#pragma once
class SiegeTank : public GCarUnit
{
public:
	SiegeTank();
	~SiegeTank();

protected:
	void StopTank(); // SiegeTank 가 땅에 박혀서 멈추는 함수
};

