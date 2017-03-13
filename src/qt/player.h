#include <vlc/vlc.h>
#include <string>

class Player
{
public:
	Player(const char* src);
	~Player();
	void start();
	void stop();
	void setVolume(int volume);

private:
	libvlc_instance_t*      inst;
	libvlc_media_player_t*  mp;
	libvlc_event_manager_t* mediaEventManager;
	libvlc_media_t*         m;
	int volume;
	void sleep();
};
