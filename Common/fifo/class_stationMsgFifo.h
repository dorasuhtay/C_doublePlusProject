//class_stationMsgFifo
#ifndef class_stationMsgFifo__H
#define class_stationMsgFifo__H


#define STATIONMSGFIFOBUFFER_SIZE		13
typedef struct
{
	int usage;
	int usage_Max;
	int BufferSize;
	int chksumCount;
	int overrunCount;
	int totalusageCount;
}serialfifoStatisticsType;

typedef struct{
	char buf[STATIONMSGFIFOBUFFER_SIZE];
}MsgBuffer;

#define MAX_MsgBuffer_SIZE		8192

class class_stationMsgFifo{
private:
	int count;
	int headptr;
	int tailptr;
	int overrunCount;
	int checksumerror;
	int maxUsage;
	int totalusage;
	MsgBuffer *msgbuf[MAX_MsgBuffer_SIZE];
	serialfifoStatisticsType statistics;
	unsigned char Lock;
public:
	class_stationMsgFifo();
	~class_stationMsgFifo();
	void add(unsigned char *data);
	int	getcount() {return count;}
	int getHeadptr() {return headptr;}
	int getTailptr() {return tailptr;}
	void create(int size);
	int put(const unsigned char *data);
	int get(unsigned char *data);
	bool available();
	long used();
	int getoverrunCount() {return overrunCount;}
	void clear() {overrunCount=0; headptr=0; tailptr=0;}
	void IncrementErrorCount(){checksumerror++;}
	int getChecksumErrorCount(){return checksumerror;}
	void clearStatistics() {maxUsage = 0; totalusage=0;}
	int usageMax() {return maxUsage;}
	int gettotalusage() {return totalusage;}
	void getserialfifoStatistics(serialfifoStatisticsType *stat);
private:
	void updateStatistics();
};


#endif