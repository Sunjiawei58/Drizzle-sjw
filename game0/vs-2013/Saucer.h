#ifndef SAUCER_H
#define SAUCER_H
#include "s_Object.h"
class Saucer: public df::s_Object
{
private:
	int hp = 0;
	int maxEnemy = 26;
	static int totalNum;
public:


	int eventHandler(const df::s_Event *p);
	void out();
	void moveToStart();
	Saucer * clone() const;
	Saucer();
	~Saucer();

	void generateSaucer();
	void generateSaucerTestCPU();
	void generateSaucerForImg();
};


#endif