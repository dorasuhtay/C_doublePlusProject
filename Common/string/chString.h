#ifndef __chString__H
#define __chString__H

#if defined(_MSC_VER)
	#include <string.h>
	#define LONG64		__int64
	#define ULONG64		unsigned __int64
	#define LONG32		__int32
	#define ULONG32		unsigned __int32
#endif

//#define USE_UNICODE_____chString

#ifdef USE_UNICODE_____chString
#define W_CHAR_T    wchar_t
#define nHEX_ZERO   L"0x00"
#define nFLOAT_ZERO L"0.0"
#define wct_emptyString		L""
#define wct_8ZeroString		L"00000000"
#else
#define W_CHAR_T    char
#define nHEX_ZERO   "0x00"
#define nFLOAT_ZERO "0.0"
#define wct_emptyString		""
#define wct_8ZeroString		"00000000"
#endif

class chString {
protected:
    W_CHAR_T	*wstring;
    char		*bstring;
    int     length;		/**< String length*/
    int	    bufferlength;	/**< Buffer length - as less string length*/

    static const char HexChars[];

    /** MAx length int a print version */
    static const int BCharMaxlength;  		/**< BChar Max length in string format 		*/
    static const int BShortMaxlength;  		/**< BShort Max length in string format 	*/
    static const int BIntMaxlength; 		/**< BInt Max length in string format 		*/
    static const int BLongMaxlength; 		/**< BLong Max length in string format 		*/
    static const int BLong64Maxlength; 	        /**< BLong64 Max length in string format 	*/

    static const int BUCharMaxlength; 		/**< BUChar Max length in string format 	*/
    static const int BUShortMaxlength; 		/**< BUShort Max length in string format 	*/
    static const int BUIntMaxlength; 		/**< BUInt Max length in string format 		*/
    static const int BULongMaxlength; 		/**< BULong Max length in string format 	*/
    static const int BULong64Maxlength; 	/**< BULong64 Max length in string format 	*/

    static const int BFloatMaxlength; 		/**< BFloat Max length in string format 	*/
    static const int BDoubleMaxlength;          /**< BDouble Max length in string format 	*/
    static const int BLDoubleMaxlength; 	/**< BLDouble Max length in string format 	*/

    // Maximum value rounded 10 to convert faster to string

    static const int BChar10Max; 			/**< BChar Max length in string format 		*/
    static const int BShort10Max;			/**< BShort Max length in string format 	*/
    static const int BIntMax10;				/**< BInt Max length in string format 		*/
    static const int BLongMax10;			/**< BLong Max length in string format 		*/
    static const int BLong6410Max;			/**< BLong64 Max length in string format 	*/

    static const int BUChar10Max;			/**< BUChar Max length in string format 	*/
    static const int BUShort10Max;			/**< BUShort Max length in string format 	*/
    static const int BUInt10Max;		 	/**< BUInt Max length in string format 		*/
    static const int BULong10Max;		 	/**< BULong Max length in string format 	*/
    static const int BULong6410Max; 	                /**< BULong64 Max length in string format 	*/

    static const int BFloat10Max; 		        /**< BFloat Max length in string format 	*/
    static const int BDouble10Max;              	/**< BDouble Max length in string format 	*/
    static const int BLDouble10Max; 	                /**< BLDouble Max length in string format 	*/

public:
    chString()
	{
        // Set every thing to zeros
		initObj();
		/*
       this->wstring = 0;
	   this->bstring = 0;
       this->length = 0;
       this->bufferlength = 0;
	   allocateIfNeeded(1);
	   */
    }

    /**
     * @brief Constructor with buffer size
     * @param inBufferlength The buffer size
     * When you know approximatly the buffer you will use
     * this constructor is the more appropriate
     */

    explicit chString(int inBufferlength)
	{
		initObj();
		//this->bstring = 0;
        if(inBufferlength > 0){ 					// buffer size > 0
           this->wstring = new W_CHAR_T[inBufferlength];	                // allocate buffer
           this->wstring[0] = '\0';					// set first char \0
        }
        else{
           this->wstring = 0;						// else NULL
        }

       this->bufferlength = inBufferlength;                             // Copy buffer length
       this->length = 0;						// str length = 0
    }

    /**
     * @brief Copy Constructor
     * @param inString The original string
     */

    chString(const chString& inString)
	{
		initObj();
        if(inString.length){						// if original string is not empty
           this->length = inString.length;
           this->bufferlength = inString.length + 1;
           this->wstring = new W_CHAR_T[bufferlength];                      //allocate buffer
            chString::Copy(inString.wstring,wstring); 			// copy and save size
        }
        else{
           this->wstring = 0;						// set to zeros
           this->length = 0;						//
           this->bufferlength = 0;					//
        }
    }

    /**
     * @brief Copy Constructor with char*
     * @param inString The original string
     */

         explicit chString(const W_CHAR_T* const inString)
		 {
			 initObj();
			int inlength;

        if(inString && (inlength = chString::Strlen(inString))){	// if original string is not empty
           this->length = inlength;
           this->bufferlength = inlength + 1;
           this->wstring = new W_CHAR_T[bufferlength];		//allocate buffer
            Copy(inString,wstring); 								// copy and save size
        }
        else{
           this->wstring = 0;									// set to zeros
           this->length = 0;									//
           this->bufferlength = 0;								//
        }
    }

   /**
     * @brief Destructor
     */
    virtual ~chString();
	/*
	{
        if(wstring) delete wstring;
		if (this->bstring) delete this->bstring;
    }*/

    /**
 * @brief String length
 * @return length
 */
    int getLength() const{
        return this->length;
    }
	int Length() const{
        return this->length;
    }
    /**
 * @brief Clear string but keep buffer in memory
 */
    void clear(){
        if(wstring && this->length)
            this->wstring[0] = '\0';
        this->length = 0;
    }
    /**
     * @brief Check if there is enough free space, if not
     * @brief allocate and copy string
     * @param in_requeriedSpace the space that is needed
     * @return true if space was allocate
     */
    //bool allocateIfNeeded(const int in_requeriedSpace);
    bool allocateIfNeeded(const int inRequeriedSpace);
    /**
     * @brief Append with char*
     * @param inString The original string
     */

    chString& append(const W_CHAR_T * const inString);
    /**
     * @brief Append with chString
     * @param inString The original string
     */
    chString& append(const chString& inString);

    /**
     * @brief Append with char
     * @param in_char The char
     */
      chString& append(const W_CHAR_T in_char);
    /**
     * @brief Append with chString
     * @param inString The original string
     */
    chString operator+(const chString& inString) const;
    /**
     * @brief Append with chString
     * @param inString The original string
     */
    chString operator+(const W_CHAR_T* const inString) const;
    /**
     * @brief Get a char from the string
     * @param in_index the char position
     * @return the char or BCharMax if index too large
     */
    W_CHAR_T operator[](const int in_index) const;
    /**
     * @brief Set the string
     * @param inString the new string
     * @return the current string after modifying
     */
    chString& operator=(const chString & inString);
     /**
     * @brief Set the string
     * @param inString the new string
     * @return the current string after modifying
     */
    chString& operator=(const W_CHAR_T* const inString);

	#ifdef USE_UNICODE_____chString
	chString& operator=(const char * const inString);
	int Copy(const char* const in_src, W_CHAR_T* const in_dest);
	#endif

    /**
     * @brief Test if 2 string are equals
     * @param inString the string to test
     * @return true if string are equal
     */
    bool operator==(const chString& inString) const;
    /**
     * @brief Test if 2 string are equals
     * @param inString the string to test
     * @return true if string are equal
     */
    bool operator==(const W_CHAR_T* const inString) const;

    /**
     * @brief Test if 2 string are different
     * @param inString the string to test
     * @return true if string are different
     */
    bool operator!=(const chString& inString) const{
        return !((*this)==inString);
    }

    /**
     * @brief To get the buffer
     * @return the string buffer of char
     */
    const W_CHAR_T *wdata() const
    {
		if (this->wstring)
			return this->wstring;
		return wct_emptyString;
    }

    /**
     * @brief To get the buffer
     * @return the string buffer of char
     */
    const char *cdata() 
    {
		int ii;
		if (this->bstring)
			delete this->bstring;
		this->bstring = new char [length+1];

		for (ii=0;ii<length;ii++)
			this->bstring[ii] = (char)this->wstring[ii];
		this->bstring[ii] = 0;
        return this->bstring;
    }

    /**
     * @brief Count the length of a string
     * @param inString the string to test
     * @return the length
     * The method count until '\n' or '\0'
     */

    static int Strlen(const W_CHAR_T* const inString);

    /**
     * @brief Count the length of a string
     * @param in_src the source
     * @param in_dest the destination
     * @return the length of the copy
     * The method copy until '\n' or '\0'
     */

    static int Copy(const W_CHAR_T* const in_src, W_CHAR_T* const in_dest);

    /**
     * @brief Add a string to another
     * @param inString the string to add
     * @return the string concat in in_string1
     */
    chString& operator+=(const chString& inString){
        append(inString);
        return *this;
    }

    /**
     * @brief Add a string to another
     * @param inString the string to add
     * @return the string concat in in_string1
     */
	#ifdef USE_UNICODE_____chString
    chString& operator+=(const W_CHAR_T* const inString){
        append(inString);
        return *this;
    }
#else
	    chString& operator+=(const char* const inString){
		size_t ii;
		W_CHAR_T *wchar = new W_CHAR_T[strlen(inString)+2];
		for (ii=0; ii<strlen(inString);ii++)
			wchar[ii] = inString[ii];
		wchar[ii] = 0;
        append(wchar);
		delete wchar;
        return *this;
    }
#endif
    // ------------------------------------------------------------------- //
    // ------------------------  Convertion Function --------------------- //
    // ------------------------------------------------------------------- //
    /** @brief Append a value to the current string */
    chString& append(const short& in_value){
        if(in_value == 0 ) append('0');
        else stoa(in_value);
        return *this;
    }
    /** @brief Append a value to the current string */
    chString& append(const unsigned short& in_value){
        if(in_value == 0u ) append('0');
        else ustoa(in_value);
        return *this;
    }
    /** @brief Append a value to the current string */
    chString& append(const int& in_value){
        if(in_value == 0 ) append('0');
        else itoa(in_value);
        return *this;
    }
    /** @brief Append a value to the current string */
    chString& append(const unsigned int& in_value){
        if(in_value == 0u ) append('0');
        else uitoa(in_value);
        return *this;
    }
    /** @brief Append a value to the current string */
    chString& append(const long& in_value){
        if(in_value == 0 ) append('0');
        else litoa(in_value);
        return *this;
    }
    /** @brief Append a value to the current string */
    chString& append(const unsigned long& in_value){
        if(in_value == 0u ) append('0');
        else ulitoa(in_value);
        return *this;
    }
    /** @brief Append a value to the current string */

    //chString& appendHex(const int& in_value, bool hexprefix=1)

	chString& appendHex(const unsigned char in_value, bool hexprefix=1){
        if(in_value == 0 ) append(nHEX_ZERO);
        else
        ucthex(in_value,hexprefix);
        return *this;
    }

    chString& appendHex(const int& in_value, bool hexprefix=1){
        if(in_value == 0 ) append(nHEX_ZERO);
        else
        ithex(in_value,hexprefix);
        return *this;
    }
    /** @brief Append a value to the current string */
    chString& appendHex(const unsigned int& in_value, bool hexprefix=1){
        if(in_value == 0u ) append(nHEX_ZERO);
        else uithex(in_value, hexprefix);
        return *this;
    }
    /** @brief Append a value to the current string */
    chString& appendHex(const long& in_value, bool hexprefix=1){
        if(in_value == 0 ) append(nHEX_ZERO);
        else lthex(in_value, hexprefix);
        return *this;
    }
    /** @brief Append a value to the current string */
    chString& appendHex(const unsigned long& in_value, bool hexprefix=1){
        if(in_value == 0u ) append(nHEX_ZERO);
        else ulthex(in_value, hexprefix);
        return *this;
    }

    chString& appendHex(const LONG64& in_value, bool hexprefix=1){
        if(in_value == 0 ) append(nHEX_ZERO);
        else l64thex(in_value, hexprefix);
        return *this;
    }
	 
    chString& appendHex(const ULONG64& in_value, bool hexprefix=1){
        if(in_value == 0 ) append(nHEX_ZERO);
        else ul64thex(in_value, hexprefix);
        return *this;
    }

/*
    chString& appendHex(const LONGLONG& in_value, bool hexprefix=1){
        if(in_value == 0 ) append(nHEX_ZERO);
        else l64thex(in_value, hexprefix);
        return *this;
    }

    chString& appendHex(const ULONGLONG& in_value, bool hexprefix=1){
        if(in_value == 0 ) append(nHEX_ZERO);
        else ul64thex(in_value, hexprefix);
        return *this;
    }
*/
    chString& appendBinary(const unsigned char& in_value){
        if(in_value == 0u ) append(wct_8ZeroString);
        else bytetbinary(in_value);
        return *this;
    }

    /** @brief Append a value to the current string */
    chString& append(const float& in_value){
        if(in_value < 0.0000001 && in_value > -0.0000001 ) append(nFLOAT_ZERO);
        else ftoa(in_value);
        return *this;
    }
    /** @brief Append a value to the current string */
    chString& append(const double& in_value){
        if(in_value < 0.0000001 && in_value > -0.0000001 ) append(nFLOAT_ZERO);
        else dtoa(in_value);
        return *this;
    }

private:
    // ------------------------------------------------------------------- //
    // ------------------------  ItoA functions      --------------------- //
    // ------------------------------------------------------------------- //

	void ucthex(unsigned char val, bool hexprefix);
    void ithex(int val, bool hexprefix);                //Convert int to hex
    void uithex(unsigned int val, bool hexprefix);      //Convert unsigned int to hex
    void lthex(long val, bool hexprefix);               //Convert long to hex
    void ulthex(unsigned long val,bool hexprefix);      //Convert unsigned long to hex

	void initObj()
	{
        // Set every thing to zeros
       this->wstring = 0;
	   this->bstring = 0;
       this->length = 0;
       this->bufferlength = 0;
	   allocateIfNeeded(1);
	}

	void l32thex(LONG32 val, bool hexprefix);
    void ul32thex(ULONG32 val, bool hexprefix);
    void l64thex(LONG64 val, bool hexprefix);
    void ul64thex(ULONG64 val, bool hexprefix);

    void bytetbinary(unsigned char val);
    /**
     * @brief Convert int to char
     */
    void stoa (short num);

    /**
     * @brief Convert unsigned short to char
     */
    void ustoa (unsigned short num);

    /**
     * @brief Convert int to char
     */
    void itoa (int num);

    /**
     * @brief Convert unsigned int to char
     */
    void uitoa (unsigned int num);

    /**
     * @brief Convert int to char
     */
    void litoa (long num);

    /**
     * @brief Convert int to char
     */
    void ulitoa (unsigned long num);

    /**
     * @brief Convert int to char
     */
    void ftoa (float num);

    /**
     * @brief Convert int to char
     */
    void dtoa (double num);


};





/**
* @brief Test if 2 string are equals
* @param in_string1 the string to test
* @param in_string2 the string to test
* @return true if string are equal
*/
/*bool operator==(const chString& in_string1, const chString& in_string2);*/


/**
* @brief Create a string from two string by concatening
* @param in_string1 the string to start
* @param in_string2 the string to ebd
* @return the new string
*/
/*chString operator+(const chString& in_string1, const chString& in_string2);*/






#endif

