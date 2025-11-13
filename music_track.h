




#ifndef _MUSIC_TRACK_H_
#define _MUSIC_TRACK_H_


#include <string>
using namespace std;

struct Song {
	string title;
	double duration;
};

class MusicTrack {
public:
	/* these are some variable that the progarm will make use of. */

	// name of music track
	string name;

	// if music track was created
	bool valid;

private:
	Song* playlist;
	int playlist_size;
	int current_size;
	static int musicTracks;
	static Song longestSong;

public:
	MusicTrack();
	MusicTrack(const MusicTrack&);
	~MusicTrack();
	
	// functions
	void 				createPlaylist(int);
	void 				addNewSongs(int, const Song*);
	void 				removePlaylist();
	void 				copyPlaylist(MusicTrack&);
	static int 			totalPlaylistsCreated();
	static const Song& 	longestSongInAllPlaylists();

	// operators
	friend bool 	operator>=(const MusicTrack&, const MusicTrack&);
	void 			operator[](int);
	MusicTrack 		operator+(const MusicTrack&);
	MusicTrack 		operator-(const MusicTrack&);
	void 			operator--(int);
	friend ostream& operator<<(ostream&, MusicTrack&);
};

#endif
