#include "include/LetterFrequencyTrie.h"

#ifdef WIN32
#define EXPORT extern "C" __declspec(dllexport)
#else
#define EXPORT
#endif



EXPORT bool ParseFile(const char *fname);

EXPORT bool Predict(char * groups, char* results, int* maxResults);

EXPORT bool PredictNextWord(char * currentWord, char* results, int* maxResults);