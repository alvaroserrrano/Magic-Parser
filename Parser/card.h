#ifndef CARD_H
#define CARD_H
/* #define FOREACH_RARITY(RARITY) \
    RARITY(Common)             \
    RARITY(Uncommon)           \
    RARITY(Rare)               \
    RARITY(Mythic)

#define GENERATE_ENUM(ENUM) ENUM,
#define GENERATE_STRING(STRING) #STRING,

enum RARITY_ENUM
{
    FOREACH_RARITY(GENERATE_ENUM)
};

#define str(x) #x
#define xstr(x) str(x)

*/

enum Rarity
{
    Common,
    Uncommon,
    Rare,
    Mythic
};

typedef struct _card
{
    unsigned int id;
    char *name;
    char *cost;
    unsigned int converted_cost;
    char *type;
    char *text;
    char *stats;
    // enum RARITY_ENUM rarity;
    enum Rarity rarity;
} CARD;

// typedef struct
// {
//     char *name;
//     int offset;
//     int cost_len;
//     //int converted_cost_len;
//     int type_len;
//     int text_len;
//     int stats_len;
//     int rarity_len;
// } CARD_INDEX;
typedef struct
{
    char *name;
    long offset;
    // int cost_len;
    // //int converted_cost_len;
    // int type_len;
    // int text_len;
    // int stats_len;
    // int rarity_len;
} CARD_INDEX;

#endif
