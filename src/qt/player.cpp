#include "player.h"
#include <iostream>
#include "bitcoingui.h"

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
		
	volume = 50;
	/*
	libvlc_event_manager_t* eventMgr = libvlc_media_player_event_manager(mp);
	libvlc_event_attach(eventMgr, libvlc_MediaMetaChanged, Player::updateTitle, &m);
	*/
}

Player::~Player()
{
	libvlc_media_player_stop (mp);

	/* Free the media_player */
	libvlc_media_player_release (mp);
 
	libvlc_release (inst);
}
/*
std::string Player::getTitle()
{
	//std::string title = libvlc_media_get_meta(m, libvlc_meta_NowPlaying);
	//std::cout << title << std::endl;
	return title;
}

void updateTitle(const struct libvlc_event_t* ev, void *data)
{
	libvlc_media_t* media = (libvlc_media_t*) data;
	// this line seems to crash; it would be great if we could use the native VLC capabilites for this,
	// as we wouldn't have to rely on the huge cpp-net library.
	Player::title = libvlc_media_get_meta(media, libvlc_meta_NowPlaying);
}
*/
// from https://wiki.videolan.org/LibVLC_SampleCode_Qt/
void Player::setVolume(int volume)
{
	this->volume = volume;
	libvlc_audio_set_volume (mp, volume);
}

void Player::start()
{
	libvlc_media_player_play (mp);
	//libvlc_audio_set_volume (mp, volume);
}

void Player::stop()
{
	// the difference between pause and stop is that pause keeps the current volume, while
	// stops always seems to reset it. There seem to be no other differences.
	libvlc_media_player_pause (mp);
}
