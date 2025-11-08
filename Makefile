
CXX   := mingw32-g++
BIN   := MusicTrack.exe
RM    := rm -f
FLAGS := -W -g -O3
UNITS := music_track.o


all: $(UNITS)
	$(CXX) main.cpp -o $(BIN) $(FLAGS) $(UNITS)

music_track.o: music_track.h music_track.cpp
	$(CXX) -c -o music_track.o music_track.cpp $(FLAGS)

clean:
	$(RM) $(BIN) $(UNITS)