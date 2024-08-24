#define MAX_WORD 500
#define UNUSED(X) (void)(X)

//for LUT map size
//TODO make it bigger
#define LUT_MOD_SIZE 1000

#define DELAY_REV_MARGIN 15

#define isStatus(Y) (strcmp(card->status.c_str(),Y)==0)

#define NEW_CARD_LIMIT 15

#define OPTIONS_CAST *(Options*)&
