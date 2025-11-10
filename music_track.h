




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
	// name of playlist
	string name;

private:
	// songs in this music track
	Song* playlist;
	
	// size of playlists
	int playlist_size;

	// current size of playlists
	int current_size;

	// to keep track of how many music tracks were created
	static int musicTracks;

	// longest song in playlists
	static Song longestSong;

public:
	MusicTrack();
	// MusicTrack(int);
	MusicTrack(const MusicTrack&);
	~MusicTrack();
	
	/* 
		default constructor that dynamically allocates memory 
		for a playlist and initializes its size.
	*/
	void createPlaylist(int);
	
	/*
		receives one or more new songs and adds them to the 
		playlist (with resizing if needed).
	*/
	void addNewSongs(int, const Song*);

	/*
		Destructor that frees dynamic memory and confirms removal.
	*/
	void removePlaylist();
	
	/*
		copy constructor for deep copying playlists.
	*/
	void copyPlaylist(MusicTrack&);
	
	/*
		static function to return total playlists created.
	*/
	static int totalPlaylistsCreated();
	
	/*
		static function returning the longest song and its 
		title among all playlists.
	*/
	static const Song& longestSongInAllPlaylists();

	/* 
		friend function to compare two playlists
	*/
	friend bool operator>=(const MusicTrack&, const MusicTrack&);
	
	/*
		play song at specific index
	*/
	void operator[](int);
	
	/* 
		returns a new playlist with common songs between two playlists
	*/
	MusicTrack operator+(const MusicTrack&);
	
	/* 
		returns a new playlists with unique songs from the first playlist
	*/
	MusicTrack operator-(const MusicTrack&);
	
	/* 
		removed the last song in playlist
	*/
	void operator--(int);
	
	/* 
		friend function to display all songs
	*/
	friend ostream& operator<<(ostream&, MusicTrack&);
};

#endif
