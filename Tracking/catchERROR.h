#ifndef ___catchERROR__H
#define ___catchERROR__H


namespace catchERROR {
	//catchERROR_No
	enum{
			SQLNOREAD = 1000,
			SQLAFFECTED
	};
};

#define __USE_DEBUG___ASSERT_POSSIBLE_ERROR

#ifdef __USE_DEBUG___ASSERT_POSSIBLE_ERROR
	#define __ASSERT_POSSIBLE_ERROR(a, b, c, d, e)	\
	{												\
		if (!a)									\
			possibleErrorCatch(b, c, d, e);			\
	}
#else
	#define __ASSERT_POSSIBLE_ERROR(a, b, c, d, e)	
#endif

#endif
