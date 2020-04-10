#ifndef UTILS
#define UTILS
//binary search
int binary_search(CARD **cards, CARD key, int num_cards);
//quicksort
void add_to_sorted(CARD **sorted, CARD *card, int card_num);
// char *str_rarity(enum Rarity rarity);
void print_maze(CARD *cards, int size);
void free_maze(CARD *cards, int size);
void write_output_file(CARD **cards, int num_cards, const char *outfilename);
//void write_index_file(CARD **cards, int num_cards, const char *outfilename);
// void write_int_to_file(FILE *dest, int number);
// void write_long_to_file(FILE *dest, int number);
// void write_str_to_file(FILE *dest, char *string);
void write_unsigned_to_file(FILE *dest, unsigned int number);
// CARD_INDEX create_index(CARD *card);
#endif
