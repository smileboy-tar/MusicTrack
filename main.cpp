


#include <iostream>
#include <iomanip>
#include "music_track.h"

using namespace std;

enum MenuInput {
	MENU, 		// display menu
	CREATE, 	// create a new playlist
	ADD, 		// add songs to playlist
	REMOVE, 	// remove a playlist
	COPY, 		// copy a playlist
	INFO, 		// display total playlists created
	LONG, 	 	// Show longest song
	CMP, 		// compare two playlists
	PLAY, 		// play a song by index
	COMMON, 	// display common songs
	UNIQUE, 	// display unique songs
	POP, 		// remove last song
	SONGS, 		// print all songs
	EXIT,  		// exit
};

struct Track {
	// the music track itself
	MusicTrack* mt;
		
	// name of track
	string name;
	
	/* 
		boolean if this track is holding valid data, 
		and is not deleted already
	*/
	bool empty;
	
	/*
		if this music track was copyied from 
		another music track. If -1, it is original
	*/
	int copiedFrom;
};


const char* PROMPT = (const char*)">>  ";

bool PickTrack(int size, const Track* tracks, int* index);
bool PickTwoTracks(int size, const Track* tracks, int* index1, int* index2);
void PrintMenu();

int main() {
	
	bool done = false;
	const int MAX_MT_SIZE = 10;
	
	// music tracks
	Track* tracks = new Track[MAX_MT_SIZE];
	int mt_size = 0;
	
	PrintMenu();
	while(!done) {
		
		MenuInput input;
		
		cout << PROMPT;
		cin >> (int&)input;
		
		switch(input) {
			case MENU: 		// display menu
			{
				PrintMenu();
			} break;
			
			case CREATE: 	// create a new playlist
			{
				int size;
				string name;
				
				cout << "Enter the name of Track: " << endl << PROMPT;
				cin >> name;
				
				cout << "Enter the Playlist size: " << endl << PROMPT;
				cin >> size;
				
				tracks[mt_size].mt = new MusicTrack;
				tracks[mt_size].mt->createPlaylist(size);
				tracks[mt_size].name = name;
				tracks[mt_size].empty = false;
				tracks[mt_size].copiedFrom = -1;
				
				cout << "Playlist " << mt_size++ << " was created!" << endl;
			} break;
			
			case ADD: 		// add songs to playlist
			{
				// track index
				int ti;
				bool cancel = PickTrack(mt_size, tracks, &ti);
				
				if(cancel) {
					cout << "Canceling prompt..." << endl;
					continue;
				}
				
				int size;
				cout << "How many songs do you want to add " << endl << PROMPT;
				cin >> size;
				
				Song* songs = new Song[size];
				for(int i = 0; i < size; i++) {
					cout << "Enter song " << i << " title: ";
					cin >> songs[i].title;
					
					cout << "Enter song " << i << " duration: ";
					cin >> songs[i].duration;
				}
				
				tracks[ti].mt->addNewSongs(size, songs);
				
				cout << "Songs were added successfully!" << endl;
			} break;
			
			case REMOVE: 	// remove a playlist
			{
				// track index
				int ti;
				bool cancel = PickTrack(mt_size, tracks, &ti);
				
				if(cancel) {
					cout << "Canceling prompt..." << endl;
					continue;
				}
				
				cout << "MusicTrack " << ti << " was removed successfully!" << endl;
				// mt_size--;
			} break;
			
			case COPY: 		// copy a playlist
			{
				// track index
				int ti;
				bool cancel = PickTrack(mt_size, tracks, &ti);
				
				if(cancel) {
					cout << "Canceling prompt..." << endl;
					continue;
				}
				
				tracks[mt_size].mt = new MusicTrack(*tracks[ti].mt);
				tracks[mt_size].name = tracks[ti].name;
				tracks[mt_size].empty = 0;
				tracks[mt_size].copiedFrom = ti;
				
				cout << "New copy of MusicTrack has been added!" << endl;
			} break;
			
			case INFO: 		// display total playlists created
			{
				// track index
				int ti;
				bool cancel = PickTrack(mt_size, tracks, &ti);
				
				if(cancel) {
					cout << "Canceling prompt..." << endl;
					continue;
				}
				
				tracks[ti].mt->totalPlaylistsCreated();
			} break;
			
			case LONG: 	 	// Show longest song
			{
				// track index
				int ti;
				bool cancel = PickTrack(mt_size, tracks, &ti);
				
				if(cancel) {
					cout << "Canceling prompt..." << endl;
					continue;
				}
				
				const Song& song = tracks[ti].mt->longestSongInAllPlaylists();
				cout << "Longest Song is " << song.title << ", Duration " << song.duration << endl;
			} break;
			
			case CMP: 		// compare two playlists
			{
				// track index
				int ti1, ti2;
				bool cancel = PickTwoTracks(mt_size, tracks, &ti1, &ti2);
				
				if(cancel) {
					cout << "Canceling prompt..." << endl;
					continue;
				}
				
				if( *tracks[ti1].mt >= *tracks[ti2].mt ) {
					cout << "Track " << ti1 << " is larger than or equal " << ti2 << endl;
				} else {
					cout << "Track " << ti1 << " is smaller than Track " << ti2 << endl;
				}
			} break;
			
			case PLAY: 		// play a song by index
			{
				// track index
				int ti;
				bool cancel = PickTrack(mt_size, tracks, &ti);
				
				if(cancel) {
					cout << "Canceling prompt..." << endl;
					continue;
				}
				
				int index;
				cout << "Enter song index " << endl << PROMPT;
				cin >> index;
				tracks[ti].mt[index];
			} break;
			
			case COMMON: 	// display common songs
			{
				// track index
				int ti1, ti2;
				bool cancel = PickTwoTracks(mt_size, tracks, &ti1, &ti2);
				
				if(cancel) {
					cout << "Canceling prompt..." << endl;
					continue;
				}
				
				cout << "Common songs between Track " << ti1 << ", and Track " << ti2 << endl;
				MusicTrack common = *tracks[ti1].mt + *tracks[ti2].mt;
				common.display((const char*)"\t");
			} break;
			
			case UNIQUE: 	// display unique songs
			{
				// track index
				int ti1, ti2;
				bool cancel = PickTwoTracks(mt_size, tracks, &ti1, &ti2);
				
				if(cancel) {
					cout << "Canceling prompt..." << endl;
					continue;
				}
				
				cout << "Unique songs between Track " << ti1 << ", and Track " << ti2 << endl;
				MusicTrack unique = *tracks[ti1].mt - *tracks[ti2].mt;
				unique.display((const char*)"\t");
			} break;
			
			case POP: 		// remove last song
			{
				// track index
				int ti;
				bool cancel = PickTrack(mt_size, tracks, &ti);
				
				if(cancel) {
					cout << "Canceling prompt..." << endl;
					continue;
				}
				
				cout << "Removing last element of Track " << ti << endl;
				tracks[ti].mt--;
			} break;
			
			case SONGS: 	// print all songs
			{
				cout << "Printing all songs in all MusicTracks..." << endl;
				for(int i = 0; i < mt_size; i++) {
					
					if(!tracks[i].empty) {
						
						cout << "\tTrack " << i << " :" << endl;
						if(tracks[i].copiedFrom != -1) {
							
							cout << "\tCopied from " << tracks[i].copiedFrom << endl;
						} else {
							
							cout << "\tTrack " << i << " :" << endl;
							tracks[i].mt->display((const char*)"\t\t");	
						}
					}
				}
			} break;
			
			case EXIT:  	// exit
			{
				cout << "Exiting..." << endl;
				done = 1;
			} continue;
			
			default: cout << "Invaild Input" << endl;
		}
	}
	
	for(int i = 0; i < mt_size; i++) {
		
		if(!tracks[i].empty) {
			
			delete tracks[i].mt;
		}
	}
	delete[] tracks;
	
	return 0;
}

void PrintMenu() {
	
	const char* LINE = (const char*)"=========";
	
	cout << endl << LINE << "Menu" << LINE << endl;
	cout << setw(2) << (int)MenuInput::MENU   << ". " << "Show menu"                       << endl;
	cout << setw(2) << (int)MenuInput::CREATE << ". " << "Create a new playlist"           << endl;
	cout << setw(2) << (int)MenuInput::ADD    << ". " << "Add songs to playlist"           << endl;
	cout << setw(2) << (int)MenuInput::REMOVE << ". " << "Remove a playlist"               << endl;
	cout << setw(2) << (int)MenuInput::COPY   << ". " << "Copy a playlist"                 << endl;
	cout << setw(2) << (int)MenuInput::INFO   << ". " << "Display total playlists created" << endl;
	cout << setw(2) << (int)MenuInput::LONG   << ". " << "Show longest song"               << endl;
	cout << setw(2) << (int)MenuInput::CMP    << ". " << "Compare two playlists"           << endl;
	cout << setw(2) << (int)MenuInput::PLAY   << ". " << "Play a song by index"            << endl;
	cout << setw(2) << (int)MenuInput::COMMON << ". " << "Display common songs"            << endl;
	cout << setw(2) << (int)MenuInput::UNIQUE << ". " << "Display unique songs"            << endl;
	cout << setw(2) << (int)MenuInput::POP    << ". " << "Remove last song"                << endl;
	cout << setw(2) << (int)MenuInput::SONGS  << ". " << "Print all songs"                 << endl;
	cout << setw(2) << (int)MenuInput::EXIT   << ". " << "Exit"                            << endl;
}