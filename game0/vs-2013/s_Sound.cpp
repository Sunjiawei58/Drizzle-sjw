#include "s_Sound.h"

using namespace df;
s_Sound::s_Sound()
{
}


s_Sound::~s_Sound()
{
//	SFML!sf::SoundBuffer!resetBuffer();
	sound.resetBuffer();  // ?
}


int s_Sound::loadSound(std::string filename)
{
	if (sound_buffer.loadFromFile(filename) == false)
	{
		return -1;   // -1 for failure
	}
	else
	{
		sound.setBuffer(sound_buffer);
		return 1;
	}
}

void s_Sound::setLabel(std::string new_label)
{
	label = new_label;
}

std::string s_Sound::getLabel() const
{
	return label;
}

void s_Sound::play(bool loop)
{
	sound.setLoop(loop);
	sound.play();
}

void s_Sound::stop()
{
	sound.stop();
}

void s_Sound::pause()
{
	sound.pause();
}

sf::Sound s_Sound::getSound() const
{
	return sound;
}