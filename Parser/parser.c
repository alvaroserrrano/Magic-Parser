/*
Alvaro Serrano Rivas
Systems Programming WMU Spring 2020
MTG Car Data Parser

Takes input from cards.csv and outputs a sorted list of entries to cards.txt

--The input file has some duplicate cards (same name). These are not parsed

--Some cards are missing the stats field and thus have two consecutive delimeters (,,). The function strtok() does not handle this properly. A custom parser is written

--Two fields are not used in the output, but should still be parsed and included in the CARD struct for all entries.

--Each field in the .csv that is text begins and ends with a quote (id and converted_cost do not, they are numbers), but that isn’t shown in the output. 

--The card’s text field sometimes has two double-quotes. This is the proper way to encode a literal double-quote in a .csv file. The output file only shows one

--Any actual new line in the card’s text field is shown with the actual \ (backslash) and n characters. This is turned into a '\n' (newline) character!
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include "card.h"
#include "config.h"
#include "read_csv.h"
#include "apue.h"
#include "utils.h"

int main(int argc, char const *argv[])
{
    int num_lines, num_cards, num_sorted;
    // char *rarity_str[] = {"rare", "common", "uncommon", "mythic"};
    FILE *fp = open_file(INPUT_FILENAME, &num_lines);
    char *header_buffer = (char *)malloc(128);
    CARD *cards = (CARD *)malloc(sizeof(CARD) * num_lines);
    if (cards == NULL) //if memory not available, it will return null
    {
        puts("malloc failed");
        puts(strerror(errno));
        // exit(EXIT_FAILURE); //exit status failure
        err_sys("Could not allocate memory for cards");
    }
    // CARD_INDEX *indexes = (CARD_INDEX *)malloc(sizeof(CARD_INDEX) * num_lines);
    // if (indexes == NULL) //if memory not available, it will return null
    // {
    //     puts("malloc failed");
    //     puts(strerror(errno));
    //     // exit(EXIT_FAILURE); //exit status failure
    //     err_sys("Could not allocate memory for cards");
    // }
    // FILE *index_file = fopen(INDEX_FILENAME, "wb");
    // FILE *cards_file = fopen(CARDS_FILENAME, "wb");
    CARD **sorted;
    // CARD_INDEX **sorted_indexes;
    fgets(header_buffer, 128, fp); //Skip first line

    num_cards = num_lines - 1; //total number of cards with duplicates

    num_sorted = num_cards;

    sorted = malloc(sizeof(CARD *) * num_sorted);
    if (sorted == NULL) //if memory not available, it will return null
    {
        puts("malloc failed");
        puts(strerror(errno));
        // exit(EXIT_FAILURE); //exit status failure
        err_sys("Could not allocated memory for sorted cards");
    }
    //sorted_indexes = malloc(sizeof(CARD_INDEX *) * num_sorted);
    // if (sorted_indexes == NULL) //if memory not available, it will return null
    // {
    //     puts("malloc failed");
    //     puts(strerror(errno));
    //     // exit(EXIT_FAILURE); //exit status failure
    //     err_sys("Could not allocated memory for sorted cards");
    // }

    // read_csv(fp, line_buffer, cards);
    // read_csv(fp, cards, indexes, sorted, sorted_indexes, &num_sorted);
    read_csv(fp, cards, sorted, &num_sorted);

    // long offset = 0;

    // for (i = 0; i < num_sorted; i++)
    // {
    //     //write card data
    //     write_str_to_file(cards_file, sorted[i]->name);
    //     write_str_to_file(cards_file, sorted[i]->cost);
    //     // write_str_to_file(cards_file, (char *)sorted[i]->converted_cost);
    //     write_unsigned_to_file(cards_file, sorted[i]->converted_cost);
    //     // printf("%d", sorted[i]->converted_cost);
    //     //write_str_to_file(cards_file, sorted[i]->converted_cost);
    //     write_str_to_file(cards_file, sorted[i]->type);
    //     write_str_to_file(cards_file, sorted[i]->text);
    //     write_str_to_file(cards_file, sorted[i]->stats);
    //     //printf(" rari %d\n", sorted[i]->rarity);
    //     write_str_to_file(cards_file, rarity_str[sorted[i]->rarity]);
    //     // printf("%s", rarity_str[sorted[i]->rarity]);
    //     //write card index
    //     write_str_to_file(index_file, sorted[i]->name);
    //     write_long_to_file(index_file, (long)offset);
    //     // printf("%ld - %s\n", offset, sorted[i]->name);
    //     offset += strlen(sorted[i]->name) + strlen(sorted[i]->cost) + strlen(sorted[i]->type) + strlen(sorted[i]->text) + strlen(sorted[i]->stats) + strlen(rarity_str[sorted[i]->rarity]) + sizeof(unsigned int) + (sizeof(int) * 6);

    //     // offset += strlen(sorted[i]->name) + strlen(sorted[i]->cost) + strlen(sorted[i]->type) + strlen(sorted[i]->text) + strlen(sorted[i]->stats) + strlen(rarity_str[sorted[i]->rarity]) + sizeof(unsigned int);
    // }

    // write_int_to_file(index_file, -1);

    fclose(fp);
    // fclose(index_file);
    // fclose(cards_file);

    // print_maze(cards, num_cards);

    write_output_file(sorted, num_sorted, OUTPUT_FILENAME);
    //write_index_file(sorted, num_sorted, INDEX_FILENAME);

    free(header_buffer);
    header_buffer = NULL;
    printf("%d\n", num_sorted);
    free_maze(cards, num_sorted);
    free(sorted);

    // exit(EXIT_SUCCESS);
    printf("Parser done\n");
    return 0;
}
