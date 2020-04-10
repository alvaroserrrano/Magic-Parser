#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include "card.h"
#include "config.h"
#include "apue.h"

int binary_search(CARD **cards, CARD key, int num_cards)
{
    int found = -1, left = 0, right = num_cards, middle, comp;
    while (found == -1 && left <= right)
    {
        middle = (left + right) / 2;
        comp = strcmp(key.name, cards[middle]->name);
        if (comp == 0)
        {
            found = middle;
        }
        else if (comp < 0)
        {
            right = middle - 1;
        }
        else
        {
            left = middle + 1;
        }
    }
    return found;
}

void add_to_sorted(CARD **cards, CARD *card, int card_num)
{
    int i;
    for (i = card_num - 1; i >= 0 && strcmp(cards[i]->name, card->name) > 0; i--)
    {
        cards[i + 1] = cards[i];
    }
    cards[i + 1] = card;
}

// char *str_rarity(enum Rarity rarity)
// {

void print_maze(CARD *cards, int size)
{

    char *rarity_str[] = {"rare", "common", "uncommon", "mythic"};
    int i;
    const char delimiter[50] = "-------------------------------------------------";
    for (i = 0; i < size; i++)
    {
        CARD card = cards[i];
        printf("%-30s%12s\n%-34s%8s\n%s\n%s\n%s\n%42s\n\n", card.name, card.cost, card.type, rarity_str[card.rarity], delimiter, card.text, delimiter, card.stats);
    }
}

void free_maze(CARD *cards, int size)
{
    int i;
    for (i = 0; i < size; i++)
    {
        //  printf("%d\n", i);
        CARD card = cards[i];
        free(card.name);
        free(card.cost);
        free(card.type);
        free(card.text);
        free(card.stats);
    }
}

// CARD_INDEX create_index(CARD *card)
// {
//     int offset = 0;
//     CARD_INDEX index;
//     index.name = malloc(1024);
//     strcpy(index.name, card->name);
//     index.offset = offset;
//     index.cost_len = strlen(card->cost);
//     index.type_len = strlen(card->type);
//     index.text_len = strlen(card->text);
//     index.stats_len = strlen(card->stats);
//     printf("index created");
//     return index;
// }

void write_output_file(CARD **cards, int num_cards, const char *outfilename)
{
    char *rarity_str[] = {"rare", "common", "uncommon", "mythic"};
    const char delimiter[50] = "-------------------------------------------------";
    int i;
    FILE *outfile = fopen(outfilename, "w");
    if (outfile == NULL)
    {
        err_quit("Output file \"%s\" not generated", outfilename);
        fprintf(stderr, "Value of errno: %d\n", errno);
        fprintf(stderr, "Error writing to file: %s\n", strerror(errno));
        // perror("Error printed by perror");
        // exit(EXIT_FAILURE);
    }
    for (i = 0; i < num_cards; i++)
    {
        fprintf(outfile, "%-30s%12s\n%-34s%8s\n%s\n%s\n%s\n%42s\n\n",
                cards[i]->name,
                cards[i]->cost,
                cards[i]->type,
                rarity_str[cards[i]->rarity],
                delimiter,
                cards[i]->text,
                delimiter,
                cards[i]->stats);
    }
    fclose(outfile);
}

void write_int_to_file(FILE *dest, int number)
{
    if (fwrite(&number, sizeof(int), 1, dest) != 1)
    {
        err_sys("Failed writing an integer");
    }
}

void write_unsigned_to_file(FILE *dest, unsigned int number)
{
    if (fwrite(&number, sizeof(unsigned int), 1, dest) != 1)
    {
        err_sys("Failed writing unsigned");
    }
}

//Write a string to file
void write_str_to_file(FILE *dest, char *string)
{
    //Write string length to file
    int size = strlen(string);
    write_int_to_file(dest, size);
    if (fwrite(string, sizeof(char), size, dest) != size)
    {
        err_sys("Failed writing a string");
    }
}

// void write_index_file(CARD_INDEX *index, int num_cards, const char *outfilename)
// {

//     int i;
//     FILE *outfile = fopen(outfilename, "w");
//     if (outfile == NULL)
//     {
//         err_quit("Output file \"%s\" not generated", outfilename);
//         fprintf(stderr, "Value of errno: %d\n", errno);
//         fprintf(stderr, "Error writing to file: %s\n", strerror(errno));
//     }
//     char *card_name = malloc(sizeof(char) * strlen(index->name + 1));
//     if (card_name == NULL)
//     {
//         err_sys("Memory allocation failed for name at writing index");
//     }
//     int offset = 0, cost_len, type_len, text_len, stats_len, rarity_len;
//     for (i = 0; i < num_cards; i++)
//     {
//     }
//     fclose(outfile);
// }
void write_long_to_file(FILE *dest, long number)
{
    if (fwrite(&number, sizeof(long), 1, dest) != 1)
    {
        err_sys("Failed writing a long");
    }
}
