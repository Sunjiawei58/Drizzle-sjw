#include "SaucerTest.h"
#include "Logmanager2.h"
#include "s_Event.h"

SaucerTest::SaucerTest()
{
}


SaucerTest::~SaucerTest()
{
}

SaucerTest * SaucerTest::clone() const
{
	
	df::LogManager2::getInstance().writeLog("this is Saucer test clone...");
	return new SaucerTest(*this);
}

int SaucerTest::eventHandler(const df::s_Event * p_e)
{
	return 0;
}
