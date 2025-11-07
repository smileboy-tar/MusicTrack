


#include <iostream>
#include <iomanip>
#include "music_track.h"

using namespace std;

enum MenuInput {
	CREATE = 1, 	// create a new playlist
	ADD, 			// add songs to playlist
	REMOVE, 		// remove a playlist
	COPY, 			// copy a playlist
	INFO, 			// display total playlists created
	LONGEST, 		// Show longest song
	CMP, 			// compare two playlists
	PLAY, 			// play a song by index
	COMMON, 		// display common songs
	UNIQUE, 		// display unique songs
	POP, 			// remove last song
	SONGS, 			// print all songs
	EXIT,  			// exit
};

const char* PROMPT = (const char*)">>  ";

void PrintMenu();

int main() {

	PrintMenu();
	
	return 0;
}

void PrintMenu() {
	
	const char* LINE = (const char*)"=========";
	
	cout << endl << LINE << "Menu" << LINE << endl;
	cout << setw(2) << (int)MenuInput::CREATE  << ". " << "Create a new playlist"           << endl;
	cout << setw(2) << (int)MenuInput::ADD     << ". " << "Add songs to playlist"           << endl;
	cout << setw(2) << (int)MenuInput::REMOVE  << ". " << "Remove a playlist"               << endl;
	cout << setw(2) << (int)MenuInput::COPY    << ". " << "Copy a playlist"                 << endl;
	cout << setw(2) << (int)MenuInput::INFO    << ". " << "Display total playlists created" << endl;
	cout << setw(2) << (int)MenuInput::LONGEST << ". " << "Show longest song"               << endl;
	cout << setw(2) << (int)MenuInput::CMP     << ". " << "Compare two playlists"           << endl;
	cout << setw(2) << (int)MenuInput::PLAY    << ". " << "Play a song by index"            << endl;
	cout << setw(2) << (int)MenuInput::COMMON  << ". " << "Display common songs"            << endl;
	cout << setw(2) << (int)MenuInput::UNIQUE  << ". " << "Display unique songs"            << endl;
	cout << setw(2) << (int)MenuInput::POP     << ". " << "Remove last song"                << endl;
	cout << setw(2) << (int)MenuInput::SONGS   << ". " << "Print all songs"                 << endl;
	cout << setw(2) << (int)MenuInput::EXIT    << ". " << "Exit"                            << endl;
}