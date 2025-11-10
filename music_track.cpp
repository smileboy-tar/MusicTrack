

#include <iostream>
#include "music_track.h"

using namespace std;


MusicTrack(MusicTrack &obj)
    {
        playlist_size= obj.playlist_size;
        for(int i=0; i< playlist_size; i++)
        {
            playlist[i].title= obj.playlist[i].title;
            playlist[i].duration= obj.playlist[i].duration;
        }
    }
//copy playlist

static int MusicTrack::totalPlaylistCreated()
    {
	return musictracks;
	
	
    }
static Song& MusicTrack::longestSongInAllPlaylists()   {	
	return longestSong;
    }
MusikTrack& MusicTrack::operator-(const MusicTrack & obj)
    {
	MusicTrack playlist;
	for(int i=0; i<size; i++)
	{
	  if(playlist[i].title != obj[i].title && playlist[i].duration != obj[i].duration){
	   addNewsongs(playlist);}
	  
	}
	
	return playlist
    }
void MusicTrack::operator--()
{
	 current_size--;
	if(current_size <0)
	{
	 current_size=0;
	}
}
freind