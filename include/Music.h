#pragma once
#include <SFML/Audio.hpp>
#include <array>
class Music
{
public:
	virtual ~Music() = default; // close music file
	static Music& instance();
	void startBackgroundMusic();
	void startKilledSound();
	void startCoinSound();
	void startClickSound();
	void startGameOverSound();
	void pauseBackgroundMusic();
	void pauseGameOverSound();
private:
	const static auto MUSICS = 4;
	Music(); // open music file
	sf::Music m_BackgroundMusic;
	std::array <sf::SoundBuffer, MUSICS> m_buffers;
	std::array<sf::Sound, MUSICS> m_sound;
};