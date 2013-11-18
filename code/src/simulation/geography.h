#ifndef GEOGRAPHY
#define GEOGRAPHY

class Tile ;

class Geography {
	private :
    static const int MAP_SIZE ;
    Tile map[MAP_SIZE][MAP_SIZE];
	
	public :
	void setAnxiety(int i, int j, float anxiety);
	float getAnxiety(int i, int j);
	Tile& getTile(int i,int j);

}

#endif // GEOGRAPHY_H
