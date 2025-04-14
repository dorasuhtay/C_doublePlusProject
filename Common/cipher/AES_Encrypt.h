#ifndef __aes_encrypt__h
#define __aes_encrypt__h

#include <stdio.h>

class AESencryptmodule1{
private:
	// The number of rounds in AES Cipher. It is simply initiated to zero. The actual value is recieved in the program.
	int Nr;		//128, 192 or 256
	// The number of 32 bit words in the key. It is simply initiated to zero. The actual value is recieved in the program.
	int Nk;	// The number of 32 bit words in the key. It is simply initiated to zero. The actual value is recieved in the program.
//   char filename[1024];
	// in - it is the array that holds the plain text to be encrypted.
	// out - it is the array that holds the key for encryption.
	// state - the array that holds the intermediate results during encryption.
	unsigned char in[16], out[16], state[4][4];
   // The array that stores the round keys.
	unsigned char RoundKey[240];
	// The Key input to the AES Program
	unsigned char Key[32];

public:
	AESencryptmodule1(int length_of_key);
   ~AESencryptmodule1();
   void text2encrypt(const char *text);
	void Cipher();
	void InvCipher();
   void writefile(FILE *fp, int dsize=0);
	void readfile(FILE *fp);
	void writefile(char *filename);
   void readfile(char *filename);
   void setkey(unsigned char *key);
   int getNBytes();
	void gettext(char *buf, int dsize=0);
private:
   void KeyExpansion();
	void AddRoundKey(int round);
   void SubBytes();
	void ShiftRows();
	void MixColumns();

	void InvShiftRows();
   void InvSubBytes();
   void InvMixColumns();

};

#endif
