#include "s_Music.h"

using namespace df;
s_Music::s_Music()
{
}


int s_Music::loadMusic(std::string filename)
{
	if (music.openFromFile(filename) == false)
	{
		return -1;  // not found
	}
	else
	{
		return 1; // 1 for ok;
	}
}

void s_Music::setLabel(std::string new_label)
{
	label = new_label;
}

std::string s_Music::getLabel() const
{
	return label;
}

void s_Music::play(bool loop)
{
	music.setLoop(loop);
	music.play();
}

void s_Music::pause()
{
	music.pause();
}

sf::Music* s_Music::getMusic()
{
	sf::Music* p_music = &music;
	return p_music;
}