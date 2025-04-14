#ifndef CLASSUSERLIST_H_INCLUDED
#define CLASSUSERLIST_H_INCLUDED


typedef struct{
    char title[32];
    char id1;
    char id2;
    char id3;
    char id4;
    char id5;
    int spare24;
    int spare25;
    int spare26;
    int spare27;
    int spare28;
    char id6;
    char id7;
    char id8;
    int count;
    int spare1;
    int spare2;
    int spare3;
    int spare4;
    int spare5;
    int spare6;
    int spare7;
    int spare8;
    int spare9;
    int spare10;
    int spare11;
    int spare12;
    char spare[32];

}onlineMRTdatafileheaderType;


#define accountflag_SUPERUSER       0xFFFFFFFF
#define accountflag_COMMONUSER      0x00000001

typedef struct{
    unsigned long accountflag;
    int accesslevel;
    int editable;
    char name[32];
    char password[128];
}UserListType;

#define MAX_UserList        255
class classUserList
{
private:
    int count;
    UserListType    *UserList[MAX_UserList];
    onlineMRTdatafileheaderType onlineMRTdatafileheader;
    char filehdr_title[32];
    char filehdr_id1;
    char filehdr_id2;
    char filehdr_id3;
    char filehdr_id4;
    char filehdr_id5;
    char filehdr_id6;
    char filehdr_id7;
    char filehdr_id8;
    int encode;
public:
	//char defaultuserName[512];
    classUserList(int aes_encoding=0);
    ~classUserList();
    int getcount(){return count;}
    void add(UserListType    *user, int editable);
    void get(int ii, UserListType    *user);
    void set(int ii, UserListType    *user);
    int load(const char *filename);
    void save(const char *filename);
    int createdefault();
    int find(const char *name2find);
    int deleteItem(int ii);
    int get(const char *name2find, UserListType    *user);
	int get(const wchar_t *name2find, UserListType    *user);

    void clear();
};

#endif // CLASSUSERLIST_H_INCLUDED
