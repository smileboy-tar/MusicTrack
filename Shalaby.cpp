// Online C++ compiler to run C++ program online
#include <iostream>
#include <string>

using namespace std;

struct Song
{
  string title;
  double duration;
};

class MusicTrack
{
  private:
    Song* playlist;
    int playlist_size;
    int current_size =0;
  public:
    MusicTrack()
    {
        playlist_size=0;
        createPlaylist();
    }
    MusicTrack(MusicTrack &obj)
    {
        playlist_size= obj.playlist_size;
        for(int i=0; i< playlist_size; i++)
        {
            playlist[i].title= obj.playlist[i].title;
            playlist[i].duration= obj.playlist[i].duration;
        }
    }
    ~MusicTrack()
    {
        removePlaylist();
    }
    void addNewSongs(int x)
    {
        
        if (current_size+x < playlist_size)
        {
            for(int k=0; k<x; k++)
            {
                cout << "Enter title of the song please: "<< endl;
                cin >> playlist[current_size+k].title;
                cout << "Enter duration of music: "<< endl;
                cin >> playlist[current_size+k].duration;
            }
        }
        else
        {
            cout<< "Error, playlist size exceeded"<< endl;
        }
        current_size += x;
    }
    void totalPlaylistCreated()
    {
        cout<< playlist_size << endl;
    }
    void removePlaylist()
    {
        delete[] playlist;
        cout << "Playlist array has been deleted"<< endl;
    }
    void createPlaylist()
    {
        playlist = new Song[playlist_size];
    }
};


int main() {
    
    cout << "Try programiz.pro";
    return 0;
}







