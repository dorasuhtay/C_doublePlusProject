#ifndef ___class_StationBoardTest__H
#define ___class_StationBoardTest__H


#define MAX_STATIONBOARDTEST_SIZE		128
typedef struct {
	int stn_id;
	int firecmd;
	int fire_postdelay;
	int unfirecmd;
	int unfire_postdelay;
	int state;
	int counter;
}stationtestType;

class class_StationBoardTest
{
private:
	int count;
	stationtestType	*stn[MAX_STATIONBOARDTEST_SIZE];
public:
	class_StationBoardTest();
	~class_StationBoardTest();
	int getcount() {return count;}
	void add(stationtestType *data);
	int get(int index,	stationtestType *data);
	void incrementstate(int index);
	int deccrementcounter(int index);
	void setcounter(int index, int value);
	void resetstate(int index);
	void Reset();
};

#endif