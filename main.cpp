


#include <iostream>
#include <iomanip>
#include "music_track.h"

using namespace std;

enum MenuInput {
	MENU, 		// display menu
	SELECT,		// select current playlist
	CURRENT,	// curretn playlist
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

const char* PROMPT = (const char*)">>  ";

void PrintMenu();

int main() {
	
	// in this case we only have two music tracks
	const int MAX_MT_SIZE = 10;

	// keep track of music tracks
	int mt_index = 0;

	// music tracks
	MusicTrack tracks[MAX_MT_SIZE];

	// Pointer to the current selected music track
	MusicTrack* curMT = NULL;

	// program is done
	bool done = false;
	
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
		
			case SELECT: 
			{
				const int size = MusicTrack::totalPlaylistsCreated();
				if(mt_index == 0) {
					cout << "No playlists were created!" << endl;
					break;
				}

				cout << "Select playlist by index" << endl;
				for(int i = 0; i < size; i++) {
					cout << '\t' << setw(2) << i << ". " << tracks[i].name << endl;
				}

				int index;
				cout << PROMPT;
				cin >> index;

				curMT = tracks + index;
				cout << "Current music track was switched" << endl;
			} break;

			case CURRENT:
			{
				cout << "  " << curMT->name << endl;
			} break;

			case CREATE: 	// create a new playlist
			{
				int size;

				cout << "Enter the name of playlist: ";
				cin >> tracks[mt_index].name;

				cout << "Enter the size of playlist: ";
				cin >> size;

				tracks[mt_index].createPlaylist(size);

				if(curMT == NULL) {
					cout << "Current music track is set to index " << mt_index << endl;
					curMT = tracks + mt_index;
				}
				mt_index++;
			} break;
			
			case ADD: 		// add songs to playlist
			{
				if(!curMT) { 
					cout << "Please select a music track" << endl;
					break;
				}

				int nsongs;
				cout << "Enter number of songs: ";
				cin >> nsongs;

				Song* songs = new Song[nsongs];
				for(int i = 0; i < nsongs; i++) {

					cout << "Song " << i << " Title: ";
					cin >> songs[i].title;

					cout << "Song " << i << " Duration: ";
					cin >> songs[i].duration;
				}

				curMT->addNewSongs(nsongs, songs);

				delete[] songs;
			} break;
			
			case REMOVE: 	// remove a playlist
			{
				if(!curMT) { 
					cout << "Please select a music track" << endl;
					break;
				}

				cout << "Removing current playlist!" << endl;
				curMT->removePlaylist();
				curMT = NULL;
			} break;
			
			case COPY: 		// copy a playlist
			{
				cout << "Copying current music track to index " << mt_index << endl;
				curMT->copyPlaylist( tracks[mt_index] );
				mt_index++;
			} break;
			
			case INFO: 		// display total playlists created
			{
				cout << "Total playlists created: ";
				cout << MusicTrack::totalPlaylistsCreated() << endl;
			} break;
			
			case LONG: 	 	// Show longest song
			{
				const Song& song = MusicTrack::longestSongInAllPlaylists();

				cout << "Longest song: " << endl;
				cout << "Title: " << song.title << endl;
				cout << "Duration: " << song.duration << endl;
			} break;
			
			case CMP: 		// compare two playlists
			{
				cout << "Comparing current playlist with: ";
				for(int i = 0; i < mt_index; i++) {
					cout << '\t' << setw(2) << i << ". " << tracks[i].name << endl;
				}

				int index;
				cout << PROMPT;
				cin >> index;

				cout << "Comparing current playlist with playlist " << index << endl;
				if( *curMT >= tracks[index] ) {
					cout << "Current Music Track has more or equal songs" << endl;
				} else {
					cout << "Current Music Track has less songs" << endl;
				}
			} break;
			
			case PLAY: 		// play a song by index
			{
				cout << "Select Song to play: ";
				cout << (*curMT);

				int index;
				cin >> index;

				// just like that
				curMT[index];
			} break;
			
			case COMMON: 	// display common songs
			{
				for(int i = 0; i < mt_index; i++) {
					cout << '\t' << setw(2) << i << ". " << tracks[i].name << endl;
				}

				cout << "Commong songs with: ";

				int index;
				cin >> index;

				cout << "Getting common songs with current music track and track " << index << endl;
				
				MusicTrack common = ( *curMT + tracks[index] );
				cout << common;
			} break;
			
			case UNIQUE: 	// display unique songs
			{
				for(int i = 0; i < mt_index; i++) {
					cout << '\t' << setw(2) << i << ". " << tracks[i].name << endl;
				}

				cout << "Unique songs with: ";

				int index;
				cin >> index;

				cout << "Getting unique songs with current music track and track " << index << endl;
				
				MusicTrack unique  = ( *curMT - tracks[index] );
				cout << unique;
			} break;
			
			case POP: 		// remove last song
			{
				cout << "Removing last song of current music track" << endl;
				(*curMT)--;
			} break;
			
			case SONGS: 	// print all songs
			{
				cout << "Songs of current music track" << endl;
				cout << (*curMT);
			} break;
			
			case EXIT:  	// exit
			{
				cout << "Exiting..." << endl;
				done = 1;
			} continue;
			
			default: cout << "Invaild Input" << endl;
		}
	}
	
	// freeing up
	for(int i = 0; i < MAX_MT_SIZE; i++) {
		tracks[i].removePlaylist();
	}

	// delete[] tracks;

	return 0;
}

void PrintMenu() {
	
	const char* LINE = (const char*)"=========";
	
	cout << endl << LINE << "Menu" << LINE << endl;
	cout << setw(2) << (int)MenuInput::MENU    << ". " << "Show menu"                       << endl;
	cout << setw(2) << (int)MenuInput::SELECT  << ". " << "Select Current MusicTrack"       << endl;
	cout << setw(2) << (int)MenuInput::CURRENT << ". " << "Current MusicTrack"              << endl;
	cout << setw(2) << (int)MenuInput::CREATE  << ". " << "Create a new playlist"           << endl;
	cout << setw(2) << (int)MenuInput::ADD     << ". " << "Add songs to playlist"           << endl;
	cout << setw(2) << (int)MenuInput::REMOVE  << ". " << "Remove a playlist"               << endl;
	cout << setw(2) << (int)MenuInput::COPY    << ". " << "Copy a playlist"                 << endl;
	cout << setw(2) << (int)MenuInput::INFO    << ". " << "Display total playlists created" << endl;
	cout << setw(2) << (int)MenuInput::LONG    << ". " << "Show longest song"               << endl;
	cout << setw(2) << (int)MenuInput::CMP     << ". " << "Compare two playlists"           << endl;
	cout << setw(2) << (int)MenuInput::PLAY    << ". " << "Play a song by index"            << endl;
	cout << setw(2) << (int)MenuInput::COMMON  << ". " << "Display common songs"            << endl;
	cout << setw(2) << (int)MenuInput::UNIQUE  << ". " << "Display unique songs"            << endl;
	cout << setw(2) << (int)MenuInput::POP     << ". " << "Remove last song"                << endl;
	cout << setw(2) << (int)MenuInput::SONGS   << ". " << "Print all songs"                 << endl;
	cout << setw(2) << (int)MenuInput::EXIT    << ". " << "Exit"                            << endl;
}
