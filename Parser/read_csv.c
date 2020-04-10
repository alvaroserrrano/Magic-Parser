#include "card.h"
#include "format_csv.h"
#include "read_csv.h"
#include "error.c"
#include "config.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include "errno.h"
#include "apue.h"

FILE *open_file(const char *input_filename, int *num_lines)
{
    int line_count = 0, cursor;
    FILE *input_file = fopen(input_filename, "r");
    if (input_file == NULL)
    {
        err_quit("Input file \"%s\" not found", INPUT_FILENAME);
        fprintf(stderr, "Value of errno: %d\n", errno);
        fprintf(stderr, "Error opening the file: %s\n", strerror(errno));
        // perror("Error printed by perror");
        // exit(EXIT_FAILURE);
    }
    while (!feof(input_file))
    {
        if (fgetc(input_file) == '\n')
        {
            line_count++;
        }
    }
    //Set file position of the stream to the beginning of the file
    cursor = fseek(input_file, (off_t)0, SEEK_SET);
    if (cursor < 0)
    {
        perror("fseek()\n");
        fprintf(stderr, "fseek() failed in file %s at line # %d\n", __FILE__, __LINE__);
        err_msg("\nError code for fseek is %d\n %s\n", errno, strerror(errno));
        // exit(EXIT_FAILURE);
    }
    *num_lines = line_count;
    return input_file;
}
// void read_csv(FILE *fp, char *buffer, CARD *cards)
// void read_csv(FILE *fp, CARD *cards, CARD_INDEX *indexes, CARD **sorted, CARD_INDEX **sorted_indexes, int *num_sorted)
void read_csv(FILE *fp, CARD *cards, CARD **sorted, int *num_sorted)
{
    int i = 0, quote_count = 0, column_num = 0, card_num = 0;
    char temp;
    char buffer[MAXLINE];
    while (!feof(fp))
    {
        buffer[i] = fgetc(fp);
        if ((buffer[i] == '\n') && (quote_count % 2 == 0))
        {
            buffer[i] = '\0';
            parse_column(buffer, i, column_num, &cards[card_num]);
            //parse_index(buffer, i, column_num, &indexes[card_num]);
            //Add to sorted_arr if the card is not a duplicate
            if (binary_search(sorted, cards[card_num], card_num - 1) == -1)
            {
                add_to_sorted(sorted, &(cards[card_num]), card_num);
                //index = create_index(&cards[card_num]);
                // TODO add_to_sorted_indexes(sorted_indexes, &(indexes[card_num]), card_num);
                //write_index_file(sorted_indexes, num_sorted, INDEX_FILENAME);
                card_num++;
            }
            else
            {
                (*num_sorted)--;
            }
            i = 0;
            column_num = 0;
            // card_num++;
        }
        else if ((buffer[i] == ',') && (quote_count % 2 == 0))
        {
            buffer[i] = '\0';
            parse_column(buffer, i, column_num, &cards[card_num]);
            i = 0;
            column_num++;
        }

        else if (buffer[i] == '"')
        {
            temp = fgetc(fp);
            if (temp == '"')
            {
                buffer[i] = '"';
                i++;
            }
            else
            {
                ungetc(temp, fp);
                quote_count++;
            }
        }
        else if (buffer[i] == '\\')
        {
            temp = fgetc(fp);
            if (temp == 'n')
            {
                buffer[i] = '\n';
            }
            else
                ungetc(temp, fp);
            i++;
        }

        else
            i++;
    }
}
