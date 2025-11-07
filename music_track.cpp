
#include <iostream>
#include "music_track.h"

using namespace std;

// delcare static varialbes in MusicTrack Class
int MusicTrack::playlist_counter = 0;


MusicTrack::MusicTrack() {
	
	this->playlist_size = 0;
	this->playlist = NULL;
}


MusicTrack::MusicTrack(const MusicTrack& mt) {
	
	this->playlist_size = mt.playlist_size;
	this->playlist = new Song[this->playlist_size];
	
	for(int i = 0; i < this->playlist_size; i++) {
		this->playlist[i].title = mt.playlist[i].title;
		this->playlist[i].duration = mt.playlist[i].duration;
	}
	
	playlist_counter++;
}

MusicTrack::~MusicTrack() {
	
	if(this->playlist) {
		delete[] this->playlist;
		playlist_counter--;
	}
}

void MusicTrack::createPlaylist(int size) {
	
	this->playlist_size = size;
	this->playlist = new Song[size];
	
	playlist_counter++;
}

void MusicTrack::addNewSongs(int size, const Song* songs) {}

void MusicTrack::removePlaylist() {
	
	if(this->playlist) {
		delete this;
		cout << "Playlist Was Removed!" << endl;
	}
}


/*
	TBD ...
	copy constructor for deep copying playlists.
*/
void MusicTrack::copyPlaylist() {}


// static functions
int MusicTrack::totalPlaylistsCreated() {}
Song& MusicTrack::longestSongInAllPlaylists(const Song* playlists) {}


// operators
void MusicTrack::operator[](int index) {}
MusicTrack& MusicTrack::operator+(const MusicTrack& mt) {}
MusicTrack& MusicTrack::operator-(const MusicTrack& mt) {}
void MusicTrack::operator--() {}


// friend functions
bool operator>=(const MusicTrack& m1, const MusicTrack& m2) {}
std::ostream& operator<<(std::ostream& os, MusicTrack& mt) {}
