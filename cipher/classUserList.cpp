#include "StdAfx.h"
#include "classUserList.h"
//#include "vncauth.h"
#include "aes_encrypt.h"
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <tchar.h>
/*
typedef struct{
    char name[32];
    char password[128];
    int accesslevel;
}UserListType;

#define MAX_UserList        255
class classUserList
{
private:
    int count;
    UserListType    *UserList[MAX_UserList];
public:
    classUserList();
    ~classUserList();
    int getcount(){return count;}
};
*/
#define SAFE_DELETE(p)  { if(p) { delete (p);     (p)=NULL; } }



classUserList::classUserList(int aes_encoding)
{
    int ii;
    encode = aes_encoding;
	//defaultuserName[0] = 0;
    for (ii=0;ii<MAX_UserList;ii++)
    {
        UserList[ii] = 0;
    }
    count = 0;
    memset(&onlineMRTdatafileheader, 0x0, sizeof(onlineMRTdatafileheaderType));
    strcpy(filehdr_title,"%^a%jh#Di.%76q8wi^&%&^Ryt%%.,F\0");
    filehdr_id1 = '>';
    filehdr_id2 = '&';
    filehdr_id3 = '!';
    filehdr_id4 = 'a';
    filehdr_id5 = '#';
    filehdr_id6 = '4';
    filehdr_id7 = '7';
    filehdr_id8 = 'k';     /*s
    trcpy(filehdr_title,"EF$%#!c^97!l&#");
    filehdr_id1 = '*';
    filehdr_id2 = 'k';
    filehdr_id3 = 'b';
    filehdr_id4 = '!';
    */
}

classUserList::~classUserList()
{
    clear();
/*
    int ii;
    for (ii=0;ii<MAX_UserList;ii++)
    {
        SAFE_DELETE(UserList[ii]);
    }
*/
}

void classUserList::clear()
{
    int ii;
    for (ii=0;ii<MAX_UserList;ii++)
        SAFE_DELETE(UserList[ii]);
    count = 0;
}


int classUserList::deleteItem(int ii)
{
    int jj;
    if (ii>=MAX_UserList) return 0;
    if (ii<0) return 0;
    if (!UserList[ii]) return 0;
    if (!UserList[ii]->editable) return 0;
    count--;
    for (jj=ii;jj<count;jj++)
    {
        memcpy(UserList[jj], UserList[jj+1], sizeof(UserListType));
    }
    return 1;
}


void classUserList::add(UserListType    *user, int editable)
{
    if (count>=MAX_UserList) return;
    UserList[count] = new UserListType;
    memcpy(UserList[count], user, sizeof(UserListType));
    UserList[count]->editable = editable;
    count++;
}

void classUserList::get(int ii, UserListType    *user)
{
    if (ii>=MAX_UserList) return;
    if (ii<0) return;
    if (!UserList[ii]) return;
    memcpy(user, UserList[ii], sizeof(UserListType));
}

void classUserList::set(int ii, UserListType    *user)
{
    if (ii>=MAX_UserList) return;
    if (ii<0) return;
    if (!UserList[ii]) return;
    memcpy(UserList[ii], user, sizeof(UserListType));
}


int classUserList::find(const char *name2find)
{
    int ii;
//    UserListType ul;
    for (ii=0;ii<count;ii++)
    {
  //      get(ii, &ul);
        if (!UserList[ii]) continue;
        if (strcmp(UserList[ii]->name, name2find)==0)
            return ii;
    }
    return -1;
}


//RETURN -1 if unsuccessful
//       otherwise return the index and the userlist record
int classUserList::get(const char *name2find, UserListType    *user)
{
    int ii = find(name2find);
    if (ii<0) return ii;
    get(ii, user);
    return ii;
}

int classUserList::get(const wchar_t *name2find, UserListType    *user)
{
	char name[128];
	int ii;
	for (ii=0;ii<_tcslen(name2find);ii++)
		name[ii] = name2find[ii];
	name[ii] = 0x0;
	return get(name, user);
}

//-------------------------------------------
//The file header is not ciphered
//every record after that is cipher with the
//following keys MAX_CIPHERKEYS repeated
//-------------------------------------------
#define MAX_CIPHERKEYS      8
unsigned char encode_key[MAX_CIPHERKEYS][32]  =
{
    "1213732682w4567890ANBCDRUUITG",
    "6526272765045678tfhNBCterUIRG",
    "df87217682ujwqry90ANBCDGFHIGF",
    "1a3awjdfh98372iu32uied67NFGGG",
    "6kjhdu3r2uih23wq8akJkCDRUUIGG",
    "1452jefwjehkjwehKJHrBCDRHIRTY",
    "53HJSDFSNNSUJjjskjh7BDD6HJGHG",
    "7645ssf3930sdmjbfwjd23qwKHIGG",
};
/*
unsigned char encode_key[MAX_CIPHERKEYS][32]  =
{
    "1213121221w4567890ANBCDRUUITG",
    "6565765765045678tfhNBCterUIRG",
    "dfhfghfgh304567890ANBCDGFHIGF",
    "1a32hgfhdf43sdhf90ANBC67NFGGG",
    "65h34f839fw4567890ANBCDRUUIGG",
    "14526w4we304545fhftrBCDRHIRTY",
    "5374deewqq0436hhfdhNBDD6HJGHG",
    "7645ssf3930456df90AWERJHKHIGG",
};
*/


int classUserList::load(const char *filename)
{
    int ii;
    int error = 0;
    FILE *fp;
    fp = fopen(filename, "r+b");
    if (fp)
    {
        fread(&onlineMRTdatafileheader, 1, sizeof(onlineMRTdatafileheaderType), fp);
        if (strcmp(filehdr_title, onlineMRTdatafileheader.title)!=0) error++;
        if (filehdr_id1!=onlineMRTdatafileheader.id1) error++;
        if (filehdr_id2!=onlineMRTdatafileheader.id2) error++;
        if (filehdr_id3!=onlineMRTdatafileheader.id3) error++;
        if (filehdr_id4!=onlineMRTdatafileheader.id4) error++;
        if (filehdr_id5!=onlineMRTdatafileheader.id5) error++;
        if (filehdr_id6!=onlineMRTdatafileheader.id6) error++;
        if (filehdr_id7!=onlineMRTdatafileheader.id7) error++;
        if (filehdr_id8!=onlineMRTdatafileheader.id8) error++;
        if (!error)
        {
            clear();
            UserListType ul;
            AESencryptmodule1 *AESencrpypt=0;
            if (encode)
                AESencrpypt = new AESencryptmodule1(256);
            int encode_keyptr = 0;
            for (ii=0;ii<onlineMRTdatafileheader.count;ii++)
            {
                if (encode)
                {
                    AESencrpypt->setkey(encode_key[encode_keyptr]);
                    encode_keyptr = (encode_keyptr+1)%MAX_CIPHERKEYS;
                    int nibblesize = AESencrpypt->getNBytes();
                    char *sptr = (char *)&ul;
                    int kk;
                    for (kk=0;kk<sizeof(UserListType)/nibblesize;kk++)
                    {
                        AESencrpypt->readfile(fp);
                        AESencrpypt->InvCipher();
                        AESencrpypt->gettext(sptr);
                        sptr+=nibblesize;
                    }
                    ul.name[sizeof(ul.name)-1] = 0x0;
                    ul.password[sizeof(ul.password)-1] = 0x0;
                }
                else
                    fread(&ul, 1, sizeof(UserListType), fp);
                add(&ul, ul.editable);
            }
            SAFE_DELETE(AESencrpypt);
        }
        fclose(fp);
    }
    else
        error++;
    return error;
}



void classUserList::save(const char *filename)
{
    int ii;
    int error = 0;

    FILE *fp;
    fp = fopen(filename, "w+b");
    if (fp)
    {
        strcpy(onlineMRTdatafileheader.title, filehdr_title);
        onlineMRTdatafileheader.id1 = filehdr_id1;
        onlineMRTdatafileheader.id2 = filehdr_id2;
        onlineMRTdatafileheader.id3 = filehdr_id3;
        onlineMRTdatafileheader.id4 = filehdr_id4;
        onlineMRTdatafileheader.id5 = filehdr_id5;
        onlineMRTdatafileheader.id6 = filehdr_id6;
        onlineMRTdatafileheader.id7 = filehdr_id7;
        onlineMRTdatafileheader.id8 = filehdr_id8;
        onlineMRTdatafileheader.count = getcount();
        fwrite(&onlineMRTdatafileheader, 1, sizeof(onlineMRTdatafileheaderType), fp);

        UserListType ul;
        AESencryptmodule1 *AESencrpypt=0;
        if (encode)
            AESencrpypt = new AESencryptmodule1(256);
        int encode_keyptr = 0;
        for (ii=0;ii<onlineMRTdatafileheader.count;ii++)
        {
            get(ii, &ul);
            if (encode)
            {
                AESencrpypt->setkey(encode_key[encode_keyptr]);
                encode_keyptr = (encode_keyptr+1)%MAX_CIPHERKEYS;
                int nibblesize = AESencrpypt->getNBytes();
                const char *sptr = (const char *)&ul;
                int kk;
                for (kk=0;kk<sizeof(UserListType)/nibblesize;kk++)
                {
                    AESencrpypt->text2encrypt(sptr);
                    sptr+=nibblesize;
                    AESencrpypt->Cipher();
                    AESencrpypt->writefile(fp);
                }
            }
            else
                fwrite(&ul, 1, sizeof(UserListType), fp);
        }
        SAFE_DELETE(AESencrpypt);
        fclose(fp);
    }
}

void genRandomBytes(unsigned char *where, int size)
{
    int i;
    unsigned int seed = (unsigned int) time(0);
    srand(seed);
    for (i=0; i < size; i++)
    {
        where[i] = (unsigned char)(rand() & 255);
    }
}


int classUserList::createdefault()
{
    char password[128];
    unsigned char tempbuf[128];
    UserListType ul;

    //-----------------------------------------
    //non editable accounts (Used for recovery)
    //-----------------------------------------
    strcpy(ul.name,"root");
    strcpy(ul.password,"rootrecovery");
    ul.accesslevel=255;
    ul.accountflag = accountflag_SUPERUSER;
    add(&ul, 0);

    strcpy(ul.name,"root1");
    strcpy(ul.password,"root1recovery");
    ul.accesslevel=255;
    ul.accountflag = accountflag_SUPERUSER;
    add(&ul, 0);

    //-----------------------------
    //editable accounts
    //-----------------------------
    strcpy(ul.name,"adminroot");
    strcpy(ul.password,"smcpl");
    ul.accesslevel=255;
    ul.accountflag = accountflag_SUPERUSER;
    add(&ul, 1);

    strcpy(ul.name,"admin");
    strcpy(ul.password,"smc");
    ul.accesslevel=250;
    ul.accountflag = accountflag_SUPERUSER;
    add(&ul, 1);

    strcpy(ul.name,"user-factory");
    strcpy(ul.password,"password");
    ul.accesslevel=250;
    ul.accountflag = accountflag_SUPERUSER;
    add(&ul, 1);

    strcpy(ul.name,"admin1");
    strcpy(ul.password,"hfj6wnhd");
    ul.accesslevel=250;
    ul.accountflag = accountflag_SUPERUSER;
    add(&ul, 1);

    strcpy(ul.name,"admin2");
    strcpy(ul.password,"yhsdihw");
    ul.accesslevel=250;
    ul.accountflag = accountflag_SUPERUSER;
    add(&ul, 1);

    strcpy(ul.name,"user");
    //genRandomBytes(ul.password, sizeof(ul.password));
    //vncEncryptPasswd("whiteegg", ul.password);
    strcpy(ul.password,"sjdundik");
    ul.accesslevel=100;
    ul.accountflag = accountflag_COMMONUSER;
    add(&ul, 1);

    strcpy(ul.name,"user1");
    strcpy(ul.password,"user1password");
    add(&ul, 1);

    strcpy(ul.name,"user2");
    strcpy(ul.password,"user2password");
    add(&ul, 1);

    strcpy(ul.name,"user3");
    strcpy(ul.password,"user3password");
    add(&ul, 1);

    strcpy(ul.name,"user4");
    strcpy(ul.password,"user4password");
    add(&ul, 1);

    strcpy(ul.name,"user5");
    strcpy(ul.password,"user5password");
    add(&ul, 1);

    strcpy(ul.name,"user6");
    strcpy(ul.password,"user6password");
    add(&ul, 1);

    strcpy(ul.name,"user7");
    strcpy(ul.password,"user7password");
    add(&ul, 1);

    strcpy(ul.name,"user8");
    strcpy(ul.password,"user8password");
    add(&ul, 1);

    strcpy(ul.name,"user9");
    strcpy(ul.password,"user9password");
    add(&ul, 1);

    strcpy(ul.name,"user10");
    strcpy(ul.password,"user10password");
    add(&ul, 1);

    return 1;
}
