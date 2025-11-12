

#include <iomanip>
#include <iostream>
#include "music_track.h"

using namespace std;

// static variables
int MusicTrack::musicTracks = 0;
Song MusicTrack::longestSong = (Song){"", 0};

MusicTrack::MusicTrack() {
	playlist_size = 0;
	current_size = 0;
	playlist = NULL;

	// longestSong.title = "";
	// longestSong.duration = 0;
}

MusicTrack::MusicTrack(const MusicTrack &obj) {
}

MusicTrack::~MusicTrack() {
	removePlaylist();
}

void MusicTrack::createPlaylist(int size) {
	
	playlist = new Song[size];
	playlist_size = size;
	current_size = 0;
	valid = true;
	
	musicTracks++;
}


void MusicTrack::addNewSongs(int size, const Song* songs) {
	
	if(size + current_size >= playlist_size) {
		
		// create a resized list
		Song* backlist = new Song[playlist_size + size];

		// copy old elements to this new list
		for(int i = 0; i < current_size; i++) {
			backlist[i].title = playlist[i].title;
			backlist[i].duration = playlist[i].duration;
		}

		// delete the previous playlist, and assign this list to the previous list
		delete[] playlist;
		playlist = backlist;

		playlist_size += size;
	}

	// copy new songs to the list
	for(int i = 0; i < size; i++) {
		playlist[i+current_size].title = songs[i].title;
		playlist[i+current_size].duration = songs[i].duration;

		if( songs[i].duration > longestSong.duration ) {
			longestSong = songs[i];
		}
	}

	current_size += size;
}

void MusicTrack::removePlaylist() {
	if(playlist) {
		delete[] playlist;
		playlist = NULL;
		
		current_size = 0;
		playlist_size = 0;

		cout << "Playlist \'" << name << "\' was removed successfully" << endl;
		
		musicTracks--;
		valid = false;
	}
}

void MusicTrack::copyPlaylist(MusicTrack& track) {
	
	// confirm removal
	track.removePlaylist();
	
	// deep copy
	track.playlist = new Song[playlist_size];
	track.playlist_size = playlist_size;
	track.current_size = current_size;
	
	for(int i = 0; i < current_size; i++) {
		track.playlist[i].title = playlist[i].title;
		track.playlist[i].duration = playlist[i].duration;
	}
	
	musicTracks++;
}

int MusicTrack::totalPlaylistsCreated() {
	return MusicTrack::musicTracks;
}

const Song& MusicTrack::longestSongInAllPlaylists() {	
	return MusicTrack::longestSong;
}

MusicTrack MusicTrack::operator+(const MusicTrack& obj) {

	MusicTrack common;
	common.name = "Common Songs";
	
	// worst case-senario if all the songs were common
	common.createPlaylist( this->playlist_size + obj.playlist_size );

	bool found;
	
	for(int i = 0; i < playlist_size; i++) {

		found = false;
		for(int k = 0; k < obj.playlist_size; k++) {
			
			if(this->playlist[i].title == obj.playlist[k].title) {
				
				found = true;
				break;
			}
			
		}
		
		if(found) {
			// add this song to playlist
			common.playlist[common.current_size].title = this->playlist[i].title;
			common.playlist[common.current_size].duration = this->playlist[i].duration;
			common.current_size++;
		}
	}

	return common;
}

MusicTrack MusicTrack::operator-(const MusicTrack & obj) {

	MusicTrack unique;
	unique.name = "Unique Songs";
	
	// worst case-senario if all the songs were unique
	unique.createPlaylist( this->playlist_size + obj.playlist_size );

	bool found;
	
	for(int i = 0; i < playlist_size; i++) {

		found = false;
		for(int k = 0; k < obj.playlist_size; k++) {
			
			if(this->playlist[i].title == obj.playlist[k].title) {
				
				found = true;
				break;
			}
			
		}
		
		if(!found) {
			// add this song to playlist
			unique.playlist[unique.current_size].title = this->playlist[i].title;
			unique.playlist[unique.current_size].duration = this->playlist[i].duration;
			unique.current_size++;
		}
	}

	return unique;
}

void MusicTrack::operator--(int index) {
	if(current_size > 0) {
		cout << "Removing last song..." << endl;
		current_size--;
	} else {
		cout << "No songs to remove!" << endl;
	}
}

bool operator>=(const MusicTrack& m1, const MusicTrack& m2) {
	return (m1.current_size >= m2.current_size);
}

void MusicTrack::operator[](int index) {
	cout << "Playing song \'" << playlist[index].title << "\'..." << endl;
}

ostream& operator<<(ostream& os, MusicTrack& track) {
	
	if(track.current_size == 0) {
		os << "\t" << "*No songs" << endl;
		return os;
	}
	
	for(int i = 0; i < track.current_size; i++) {
		os << "\t" << setw(4) << i << ". ";
		os << track.playlist[i].title << endl;
	}

	return os;
}
