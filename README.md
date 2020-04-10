# Magic-Parser
parser takes the included .csv file and outputs a sorted list of entries to a text file.

1.     Parse each line (entry) in the file into a CARD struct. See the included header file for a definition.

2.     Once the entire dataset is in memory, sort them by card name. Do not use a C library like qSort()

3.     Output the sorted entries to a text file. Format it in the way shown below:

Sorin, Vampire Lord              {4}{B}{B}
Legendary Planeswalker — Sorin      mythic
------------------------------------------
Up to one target creature gets +2/+0 until end of turn.
Sorin, Vampire Lord deals 4 damage to any target. You gain 4 life.
Until end of turn, each Vampire you control gains "{T}: Gain control of target creature."
------------------------------------------
                                         
 
Roc Charger                         {2}{W}
Creature — Bird                   uncommon
------------------------------------------
Flying
Whenever Roc Charger attacks, target attacking creature without flying gains flying until end of turn.
------------------------------------------
                                       
These are not sorted, just an example of the output format

For the following records:

#1109 192693,"Sorin, Vampire Lord","{4}{B}{B}",6,"Legendary Planeswalker — Sorin",": Up to one target creature gets +2/+0 until end of turn.\n: Sorin, Vampire Lord deals 4 damage to any target. You gain 4 life.\n: Until end of turn, each Vampire you control gains ""{T}: Gain control of target creature.""","4","mythic"
#1112 176816,"Roc Charger","{2}{W}",3,"Creature — Bird","Flying\nWhenever Roc Charger attacks, target attacking creature without flying gains flying until end of turn.","1/3","uncommon"
CSV Pitfalls
There are some things to keep in mind with the included dataset:

1.     There are some duplicate cards (they have the exact same name). Do not add them when parsing.

2.     Some cards are missing the stats field and thus have two consecutive delimeters (,,). The function strtok() does not handle this properly, write your own parser!

3.     Two fields are not used in the output, but should still be parsed and included in the CARD struct for all entries.

4.     Notice that each field in the .csv that is text begins and ends with a quote (id and converted_cost do not, they are numbers), but that isn’t shown in the output. Get rid of it!

5.     Also notice that the card’s text field sometimes has two double-quotes. This is the proper way to encode a literal double-quote in a .csv file. When outputting to a file, there should only be one shown!

6.     Finally, any actual new line in the card’s text field is shown with the actual \ (backslash) and n characters. You must turn these into a '\n' (newline) character!

Makefile
