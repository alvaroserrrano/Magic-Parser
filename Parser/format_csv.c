#include "card.h"
#include "format_csv.h"
#include "read_csv.h"
#include "config.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include "errno.h"

void (*parsers[8])(parser_params) = {parse_int, parse_string, parse_string, parse_int, parse_string, parse_string, parse_string, parse_rarity};

void (*index_parsers[7])(parser_params) = {parse_string, parse_int, parse_int, parse_int, parse_int, parse_int, parse_int};

void parse_column(char *buffer, int buffer_size, int column_num, CARD *card)
{
    void *fields[8] = {
        (void *)&(card->id), (void *)&(card->name), (void *)&(card->cost), (void *)&(card->converted_cost), (void *)&(card->type), (void *)&(card->text), (void *)&(card->stats), (void *)&(card->rarity)};
    parser_params params = {buffer, buffer_size, fields[column_num]};
    parsers[column_num](params);
}

void parse_string(parser_params params)
{
    *(params.fields) = malloc(sizeof(char) * (params.buffer_size + 1));
    strcpy(*(params.fields), params.buffer);
}

void parse_int(parser_params params)
{
    *(unsigned int *)params.fields = atoi(params.buffer);
}

void parse_rarity(parser_params params)
{
    if (strcmp("rare", params.buffer) == 0)
    {
        *(enum Rarity *)params.fields = Rare;
    }
    else if (strcmp(params.buffer, "uncommon") == 0)
    {
        *(enum Rarity *)params.fields = Uncommon;
    }
    else if (strcmp(params.buffer, "common") == 0)
    {
        *(enum Rarity *)params.fields = Common;
    }
    else if (strcmp(params.buffer, "mythic") == 0)
    {
        *(enum Rarity *)params.fields = Mythic;
    }
}
