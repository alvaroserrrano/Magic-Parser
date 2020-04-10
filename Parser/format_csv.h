#ifndef FORMAT_CSV
#define FORMAT_CSV
#include "card.h"

typedef struct params_t
{
    char *buffer;
    int buffer_size;
    void **fields;
} parser_params;

// int parse_line(char *buffer, int column_num, CARD *card);
// void (*parsers[8])(void **dest, char *buffer, int buffer_size) = {parse_int, parse_string, parse_string, parse_int, parse_string, parse_string, parse_string, parse_rarity};
void parse_column(char *buffer, int buffer_size, int column_num, CARD *card);
// void parse_index(char *buffer, int buffer_size, int column_num, CARD_INDEX *index);
void parse_string(parser_params params);
void parse_int(parser_params params);
void parse_rarity(parser_params params);
#endif // !FORMAT_CSV
