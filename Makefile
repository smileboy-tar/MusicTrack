
CXX := mingw32-g++
BIN := MusicTrack.exe
RM  := rm -f

all: music_track.o
	$(CXX) main.cpp -o $(BIN) -g -O3 music_track.o

music_track.o: music_track.h music_track.cpp
	$(CXX) -c -o music_track.o music_track.cpp -g

clean:
	$(RM) $(BIN) music_track.o