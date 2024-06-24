#pragma once



class Timer
{
public:
	Timer(float setTimeSMax, float setTimeSCurrent = 0.0f);

	void countUp(float dT);
	void countDown(float dT);
	void resetToZero();
	void resetToMax();
	bool timeSIsZero();
	bool timeSIsGreaterThanOrEqualTo(float timeSCheck);

	float getCurrentTime();
	float getMaxTime();

	void setMaxTime(float newMaxTime);

private:
	float timeSMax;
	float timeSCurrent;
};