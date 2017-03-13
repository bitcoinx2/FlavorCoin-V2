#include "player.h"
#include <iostream>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/thread/thread.hpp> 
#include "bitcoingui.h"

// from https://wiki.videolan.org/LibVLC_Tutorial/
Player::Player(const char* src)
{
	const char * const vlc_args[] = {"-q"}; // no logging messages

	/* Load the VLC engine */
	inst = libvlc_new (sizeof(vlc_args) / sizeof(vlc_args[0]), vlc_args);

	/* Create a new item */
	m = libvlc_media_new_location (inst, src);

	/* Create a media player playing environement */
	mp = libvlc_media_player_new_from_media (m);

	/* No need to keep the media now */
	libvlc_media_release (m);

	volume = 50;
}

// due to a bug in VLC (https://github.com/caprica/vlcj/issues/59),
// the volume cannot be set right after start(). So what we're doing is
// setting the volume to 0 before stopping, and waiting some time after
// play() until we set it to the right volume again. this will only mean
// a short delay until the audio can be heard.
void Player::sleep()
{
	boost::this_thread::sleep(boost::posix_time::milliseconds(500));
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
	libvlc_audio_set_volume(mp, volume);
}

void Player::start()
{
	libvlc_media_player_play (mp);
	sleep();
	libvlc_audio_set_volume(mp, volume);
}

void Player::stop()
{
	libvlc_audio_set_volume(mp, 0);
	sleep();
	libvlc_media_player_stop (mp);
}
