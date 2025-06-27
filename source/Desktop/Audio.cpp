#include <Hall/Audio.h>
extern "C" 
{
	#include "raylib.h"
}
#include <exception>

//Sound does not behave exactly as on wueHans


struct Channel
{
	::Sound sound;
	bool isLooping;
	double currentPosition;
	double loopStart;
	double loopEnd;
};

::Channel channels[8];

void _UpdateAudio(float frameTime)
{
	//This implements looping :/
	for(int i = 0; i < 8; i++)
	{
		Channel& channel = channels[i];
		if(::IsSoundPlaying(channel.sound))
		{
			channel.currentPosition += frameTime;
			if(channel.isLooping && channel.currentPosition >= channel.loopEnd)
			{
				::StopSound(channel.sound);
				::PlaySound(channel.sound);
				channel.currentPosition = 0;
			}
		}
	}
}

static float VolumeCon(unsigned char volume)
{
	return (float)volume / 255.0f;
}

void Hall::SetGlobalVolume(unsigned char volume)
{
	//volume = 255 is max volume
	float volume_f = VolumeCon(volume);
	::SetMasterVolume(volume_f);
}

void Hall::SetupMono(int channelID, const short* data, int sampleCount, unsigned char volume)
{
	::Wave wave;
	wave.channels = 1;
	wave.data = (void*)data;
	//A frame seems to be exactly one point in time. So a frame consists of one sample per channel
	wave.frameCount = (sampleCount / 1);
	wave.sampleRate = 32000;
	wave.sampleSize = 16;

	::Sound sound = ::LoadSoundFromWave(wave);
	::SetSoundVolume(sound, VolumeCon(volume));

	channels[channelID].sound = sound;
	channels[channelID].isLooping = false;
}

void Hall::SetupMono(int channelID, const short* data, int sampleCount, unsigned int loopStart, unsigned int loopEnd, unsigned char volume)
{
	if(loopStart != 0)
		throw std::exception("loopStart != 0 IS NOT SUPPORTED IN DESKTOP VERSION OF HALL");

	::Wave wave;
	wave.channels = 1;
	wave.data = (void*)data;
	//A frame seems to be exactly one point in time. So a frame consists of one sample per channel
	wave.frameCount = (sampleCount / 1);
	wave.sampleRate = 32000;
	wave.sampleSize = 16;

	::Sound sound = ::LoadSoundFromWave(wave);
	::SetSoundVolume(sound, VolumeCon(volume));


	channels[channelID].sound = sound;
	channels[channelID].isLooping = true;
	channels[channelID].currentPosition = 0;
	channels[channelID].loopStart = loopStart / (float)32000;
	channels[channelID].loopEnd = loopEnd / (float)32000;
}

void Hall::SetupStereo(int channelID_left, int channelID_right, const short* data, int sampleCount, unsigned char volume)
{
	::Wave wave;
	wave.channels = 2;
	wave.data = (void*)data;
	//A frame seems to be exactly one point in time. So a frame consists of one sample per channel
	wave.frameCount = (sampleCount / 2);
	wave.sampleRate = 32000;
	wave.sampleSize = 16;

	::Sound sound = ::LoadSoundFromWave(wave);
	::SetSoundVolume(sound, VolumeCon(volume));

	channels[channelID_left].sound = sound;
	channels[channelID_left].isLooping = false;
}

void Hall::SetupStereo(int channelID_left, int channelID_right, const short* data, int sampleCount, unsigned int loopStart, unsigned int loopEnd, unsigned char volume)
{
	if(loopStart != 0)
		throw std::exception("loopStart != 0 IS NOT SUPPORTED IN DESKTOP VERSION OF HALL");

	::Wave wave;
	wave.channels = 2;
	wave.data = (void*)data;
	//A frame seems to be exactly one point in time. So a frame consists of one sample per channel
	wave.frameCount = (sampleCount / 2);
	wave.sampleRate = 32000;
	wave.sampleSize = 16;

	::Sound sound = ::LoadSoundFromWave(wave);
	::SetSoundVolume(sound, VolumeCon(volume));


	channels[channelID_left].sound = sound;
	channels[channelID_left].isLooping = true;
	channels[channelID_left].currentPosition = 0;
	channels[channelID_left].loopStart = loopStart / (float)32000;
	channels[channelID_left].loopEnd = loopEnd / (float)32000;
}

void Hall::Play(unsigned char channelSelect)
{
	for(int i = 0; i < 8; i++)
	{
		bool select = (channelSelect >> i) & 1;
		if(select)
		{
			::PlaySound(channels[i].sound);
			channels[i].currentPosition = 0;
		}
	}
}

void Hall::Pause(unsigned char channelSelect)
{
	for(int i = 0; i < 8; i++)
	{
		bool select = (channelSelect >> i) & 1;
		if(select)
		{
			::PauseSound(channels[i].sound);
			channels[i].currentPosition = 0;
		}
	}
}

void Hall::SetData(unsigned char channelSelect, short* data)
{
	throw std::exception("Hall::SetData IS NOT SUPPORTED IN DESKTOP VERSION OF HALL");
}

void Hall::SetLoop(unsigned char channelSelect, bool isLooping)
{
	for(int i = 0; i < 8; i++)
	{
		bool select = (channelSelect >> i) & 1;
		if(select)
		{
			channels[i].isLooping = isLooping;
		}
	}
}

void Hall::SetLoopBoundaries(unsigned char channelSelect, int start, int end)
{
	if(start != 0)
		throw std::exception("loopStart != 0 IS NOT SUPPORTED IN DESKTOP VERSION OF HALL");

	for(int i = 0; i < 8; i++)
	{
		bool select = (channelSelect >> i) & 1;
		if(select)
		{
			channels[i].loopStart = start / 32000.0f;
			channels[i].loopStart = end / 32000.0f;
		}
	}
}

void Hall::SetPosition(unsigned char channelSelect, int position)
{
	throw std::exception("Hall::SetPosition IS NOT SUPPORTED IN DESKTOP VERSION OF HALL");
}

void Hall::SetSample(unsigned char channelSelect, short sample)
{
	throw std::exception("Hall::SetSample IS NOT SUPPORTED IN DESKTOP VERSION OF HALL");
}

void Hall::SetVolume(unsigned char channelSelect, unsigned char volume)
{
	for(int i = 0; i < 8; i++)
	{
		bool select = (channelSelect >> i) & 1;
		if(select)
		{
			::SetSoundVolume(channels[i].sound, VolumeCon(volume));
		}
	}
}