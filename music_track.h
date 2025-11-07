




#ifndef _MUSIC_TRACK_H_
#define _MUSIC_TRACK_H_


#include <string>

struct Song {
	std::string title;
	double duration;
};

class MusicTrack {
private:
	Song* playlist;
	int playlist_size;
	
	static int playlist_counter;

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
		TBD ...
		copy constructor for deep copying playlists.
	*/
	void copyPlaylist();
	
	/*
		static function to return total playlists created.
	*/
	static int totalPlaylistsCreated();
	
	/*
		static function returning the longest song and its 
		title among all playlists.
	*/
	static Song& longestSongInAllPlaylists(const Song*);

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
	MusicTrack& operator+(const MusicTrack&);
	
	/* 
		returns a new playlists with unique songs from the first playlist
	*/
	MusicTrack& operator-(const MusicTrack&);
	
	/* 
		removed the last song in playlist
	*/
	void operator--();
	
	/* 
		friend function to display all songs
	*/
	friend std::ostream& operator<<(std::ostream&, MusicTrack&);
};


#endif