#include "player.h"

// from https://wiki.videolan.org/LibVLC_Tutorial/
Player::Player(const char* src)
{
	/* Load the VLC engine */
	inst = libvlc_new (0, NULL);
	
	/* Create a new item */
	m = libvlc_media_new_location (inst, src);

	/* Create a media player playing environement */
    mp = libvlc_media_player_new_from_media (m);

    /* No need to keep the media now */
    libvlc_media_release (m);
}

Player::~Player()
{
	libvlc_media_player_stop (mp);

	/* Free the media_player */
     libvlc_media_player_release (mp);
 
     libvlc_release (inst);
}

// from https://wiki.videolan.org/LibVLC_SampleCode_Qt/
void Player::setVolume(int volume)
{
	this->volume = volume;
    libvlc_audio_set_volume (mp, volume);
}

void Player::start()
{
	libvlc_audio_set_volume (mp, this->volume);
	libvlc_media_player_play (mp);
}

void Player::stop()
{
	libvlc_media_player_stop (mp);
}
