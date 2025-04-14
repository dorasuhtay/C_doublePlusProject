#ifndef ___class_cmdLogList__H
#define ___class_cmdLogList__H

typedef struct{
	int ref;
	int cmd;
	int timesecond;
} cmd_LogType;

#define MAX_CMDLOG_SIZE		512

#define SAFE_DELETE(p)  { if(p) { delete (p);     (p)=0; }}

class class_cmdLogList{
private:
	int count;
	cmd_LogType *cmd_Log[MAX_CMDLOG_SIZE];
public:
	class_cmdLogList()
	{
		int ii;
		for (ii=0;ii<MAX_CMDLOG_SIZE;ii++)
			cmd_Log[ii]=0;
		count = 0;
	}

	~class_cmdLogList()
	{
		Clear();
	}	

	void Clear()
	{
		int ii;
		for (ii=0;ii<MAX_CMDLOG_SIZE;ii++)
			SAFE_DELETE(cmd_Log[ii]);
		count = 0;
	}	
	
	int getcount() {return count;}
	void Add(int ref, int cmd_enum, int second)
	{
		if (count>=MAX_CMDLOG_SIZE) return;
		cmd_Log[count] = new cmd_LogType[];
		cmd_Log[count]->ref = ref;
		cmd_Log[count]->cmd = cmd_enum;
		cmd_Log[count]->timesecond = second;
		count++;
	}

	void Set(int index, int ref, int cmd_enum, int second)
	{
		if (index>=MAX_CMDLOG_SIZE) return;
		if (index<0) return;
		if (!cmd_Log[index]) return;
		cmd_Log[index]->ref = ref;
		cmd_Log[index]->cmd = cmd_enum;
		cmd_Log[index]->timesecond = second;
	}

	int find(int ref, int cmd_enum)
	{
		int ii;
		for(ii=0;ii<count;ii++)
		{
			if(!cmd_Log[ii]) continue;
			if ((cmd_Log[ii]->ref==ref)&&(cmd_Log[ii]->cmd==cmd_enum))
				return ii;
		}
		return -1;
	}

	int get(int index, int *ref, int *cmd_enum, int *second)
	{
		if (index>=MAX_CMDLOG_SIZE) return 0;
		if (index<0) return 0;
		if (!cmd_Log[index]) return 0; 
		*ref = cmd_Log[index]->ref;
		*cmd_enum = cmd_Log[index]->cmd;
		*second = cmd_Log[index]->timesecond;
		return 1;
	}

};

#endif
	