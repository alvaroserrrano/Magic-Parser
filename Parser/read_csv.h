#ifndef READ_CSV
#define READ_CSV
#include "card.h"
#include <stdio.h>
FILE *open_file(const char *input_file, int *num_lines);
// int read_csv(FILE *fp, CARD *cards, int num_lines);
// void read_csv(FILE *fp, char *buffer, CARD *cards);
// void read_csv(FILE *fp, CARD *cards, CARD_INDEX *indexes, CARD **sorted, CARD_INDEX **sorted_indexes, int *num_sorted);
void read_csv(FILE *fp, CARD *cards, CARD **sorted, int *num_sorted);
#endif // !READ_CSV
