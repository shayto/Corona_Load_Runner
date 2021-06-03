#include "Music.h"
//------------------------------------------------------------
Music::Music()
{
	m_BackgroundMusic.openFromFile("BackgroundMusic.wav");
	std::array <std::string, MUSICS> soundNames =
	{
		"CoinSound", "KilledSound", "MouseClick", "GameOver"
	};

	for (int i = 0; i < soundNames.size(); i++)
	{
		m_buffers[i].loadFromFile(soundNames[i] + ".wav");
	}
}
//------------------------------------------------------------
Music& Music::instance()
{
	static Music music;
	return music;
}
//------------------------------------------------------------
void Music::startCoinSound()
{
	m_sound[0].setBuffer(m_buffers[0]);
	m_sound[0].play();
}
//------------------------------------------------------------
void Music::startBackgroundMusic()
{
	m_BackgroundMusic.play();
	m_BackgroundMusic.setLoop(true);
}
//------------------------------------------------------------
void Music::startKilledSound()
{
	m_sound[1].setBuffer(m_buffers[1]);
	m_sound[1].play();
}
//------------------------------------------------------------
void Music::startClickSound()
{
	m_sound[2].setBuffer(m_buffers[2]);
	m_sound[2].play();
}
//------------------------------------------------------------
void Music::startGameOverSound()
{
	m_sound[3].setBuffer(m_buffers[3]);
	m_sound[3].play();
}
//------------------------------------------------------------
void Music::pauseBackgroundMusic()
{
	m_BackgroundMusic.pause();
}
//------------------------------------------------------------
void Music::pauseGameOverSound()
{
	m_sound[3].pause();
}
