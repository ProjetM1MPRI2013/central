#ifndef GEOGRAPHY
#define GEOGRAPHY

class Geography {
	private :
	Tile[MAP_SIZE][MAP_SIZE] map;
	
	public :
	void setAnxiety(int i, int j, float anxiety);
	float getAnxiety(int i, int j);
	Tile& getTile(int i,int j);

}

#endif // GEOGRAPHY_H
