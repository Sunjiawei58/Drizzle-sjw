
#ifndef S_SOUND_H
#define S_SOUND_H

#include <string>
#include <SFML/Audio.hpp>
namespace df
{


	class s_Sound
	{
	private:
		sf::Sound sound;
		sf::SoundBuffer sound_buffer;
		std::string label;
	public:
		s_Sound();
		~s_Sound();

		int loadSound(std::string filename);

		void setLabel(std::string new_label);

		std::string getLabel() const;

		void play(bool loop = false);

		void stop();

		void pause();

		sf::Sound getSound() const;
	};
}
#endif
