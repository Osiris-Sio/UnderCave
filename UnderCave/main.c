/*
UnderCave
Authors :
    Osiris Sio (Louis AMEDRO)
    Lirei
licence CC BY SA
*/

// Standard Extensions :
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

// Overall variables :
// Game settings (language and player name) :
char filename[15] = "intro", language[3] = "??", name[20] = "???";

// Hero's features (depending on the hero class)
int number_hero = 0;                       // 1. Priest (Easy) / 2. Knight (Intermediate) / 3. Orc (Advanced) / 4. Mage (Hard)
int max_monster_hp, hp;                    // Health Points
int ap;                                    // Attack Points
int healing_potion_number, additionnal_hp; // Healing Potions effect
// Effect Power Potion (increase hero Attack Points) :
int power_potion_number, potion_attack_number_lasting = 0 /*how many attaks until the power potion is removed*/, using_potion_effects_number /*additionnal uses*/, additionnal_attacks /*hp removed to the the enemy*/;
int gold; // Money (Gold)

// monster :
int max_monster_hp, monster_hp, monster_min, monster_max;

//====================================================================================================
// Wanted line reader
//====================================================================================================

void read_line(int line_number, char *filename)
// Print the line number of the file "filename", passed in parameters,
{
    // Variable :
    char path_total[100], provisional_language[3];
    path_total[0] = '\0'; // Initiate the empty string

    if (strcmp(language, "??") == 0)
        snprintf(provisional_language, sizeof(provisional_language), "%s", "fr");
    else
        snprintf(provisional_language, sizeof(provisional_language), "%s", language);

    // Concatenate the different values to create the file path
    strcat(path_total, "texts/");
    strcat(path_total, provisional_language);
    strcat(path_total, "/");
    strcat(path_total, filename);
    strcat(path_total, ".txt");

    // Open and read the file with "path_total"
    FILE *pointed_file = fopen(path_total, "r");

    // String to keep each line of the file line, 1024 monster_max bytes
    char string[1024];
    int actual_line = 1;

    // Read the file line by line while we don't have the actual line
    while (fgets(string, sizeof(string), pointed_file) != NULL && actual_line <= line_number)
    {
        // If the actual line is the asked line, print it and close the file (and while stops)
        if (actual_line == line_number)
        {
            // If there's a string (not empty) and the last bit is a carriage return, we delete it.
            if (strlen(string) > 0 && string[strlen(string) - 1] == '\n')
                string[strlen(string) - 1] = '\0';

            if (strlen(string) > 0 && string[strlen(string) - 1] == '\r') // For Linux
                string[strlen(string) - 1] = '\0';

            printf("%s", string);
        }
        actual_line += 1;
    }
    // Close the file
    fclose(pointed_file);
}

//====================================================================================================
// Print
//====================================================================================================

void print_sword()
// Print the interaction area for the player
{
    printf("\n=={==========> ");
}

void print_logo(bool actions)
{
    printf("\n");
    printf("....................................................\n");
    printf("  _   _           _            ____                \n");
    printf(" | | | |_ __   __| | ___ _ __ / ___|__ ___   _____ \n");
    printf(" | | | | '_ \\ / _` |/ _ \\ '__| |   / _` \\ \\ / / _ \\\n");
    printf(" | |_| | | | | (_| |  __/ |  | |__| (_| |\\ V /  __/\n");
    printf("  \\___/|_| |_|\\__,_|\\___|_|   \\____\\__,_| \\_/ \\___|\n");
    if (actions)
    {
        printf("\n");
        read_line(1, "actions");
        printf("\n");
    }
    printf("....................................................\n");
    printf("\n");
}

//====================================================================================================
// Actions : inventory, features
//====================================================================================================

int input_actions_question(int beginning_line, int ending_line, int choice_number)
// Return number chose by the player
// Used only for the different actions like inventory or features
{
    // Variable :
    int player_choice = -1;
    char temp_string[100];

    while (1 > player_choice || player_choice > choice_number)
    {
        // Write question and choices :
        for (beginning_line; beginning_line <= ending_line; beginning_line++)
        {
            read_line(beginning_line, "actions");
            printf("\n");
        }

        print_sword();
        scanf("%d", &player_choice);

        // If choice always -1, text in front is in temp variable
        if (player_choice == -1)
        {
            scanf("%s", temp_string);
        }
    }
    return player_choice;
}

void using_potion()
{
    // Variable :
    bool no_return = true;

    print_logo(false);
    while (no_return)
    {
        switch (input_actions_question(6, 9, 3))
        {
        case 1: // Healing Potion
            if (healing_potion_number > 0)
            {
                print_logo(false);
                read_line(11, "actions");
                printf("%d ", healing_potion_number);
                read_line(12, "actions");
                switch (input_actions_question(14, 16, 2))
                {
                case 1: // Yes
                    print_logo(false);
                    read_line(17, "actions");
                    read_line(18, "actions");
                    healing_potion_number -= 1;
                    if (hp + additionnal_hp > max_monster_hp)
                        hp = hp + (max_monster_hp - hp);
                    else
                        hp += additionnal_hp;
                    break;

                case 2: // No
                    print_logo(false);
                    break;
                }
            }
            else
            {
                print_logo(false);
                read_line(10, "actions");
            }
            break;

        case 2: // Power Potion
            if (power_potion_number > 0)
            {
                print_logo(false);
                read_line(11, "actions");
                printf("%d ", power_potion_number);
                read_line(13, "actions");
                switch (input_actions_question(14, 16, 2))
                {
                case 1: // Yes
                    print_logo(false);
                    read_line(17, "actions");
                    read_line(19, "actions");
                    power_potion_number -= 1;
                    potion_attack_number_lasting += using_potion_effects_number;
                    break;

                case 2: // No
                    print_logo(false);
                    break;
                }
            }
            else
            {
                print_logo(false);
                read_line(10, "actions");
            }
            break;

        case 3: // Return
            no_return = false;
            break;
        }
    }
}

void see_features()
{
    // Variable :
    bool no_return = true;
    while (no_return)
    {
        print_logo(false);
        read_line(20, "actions");
        printf("\n");

        // Name :
        read_line(21, "actions");
        printf("%s", name);
        printf("\n");

        // Hero class :
        read_line(22, "actions");
        read_line(22 + number_hero, "actions");
        printf("\n");

        // HP :
        read_line(27, "actions");
        printf("%d / %d", hp, max_monster_hp);
        printf("\n");

        // AP
        read_line(28, "actions");
        if (potion_attack_number_lasting > 0)
            printf("%d", ap + additionnal_attacks);
        else
            printf("%d", ap);
        printf("\n");

        // Effect Healing Potion :
        read_line(29, "actions");
        printf("+ %d ", additionnal_hp);
        read_line(30, "actions");
        printf("\n");

        // Effect Power Potion :
        read_line(31, "actions");
        printf("+ %d ", additionnal_attacks);
        read_line(32, "actions");
        printf("%d ", using_potion_effects_number);
        read_line(33, "actions");
        printf("\n");

        // Money
        read_line(34, "actions");
        printf("%d G", gold);
        printf("\n\n\n");

        // Return
        if (input_actions_question(35, 35, 1) == 1)
            no_return = false;
    }
}

void other_actions()
{
    // Variable :
    bool no_return = true;

    while (no_return)
    {
        print_logo(false);
        switch (input_actions_question(2, 5, 3))
        {
        case 1: // Potions
            using_potion();
            break;

        case 2: // Features
            see_features();
            break;

        case 3: // Return
            no_return = false;
            break;
        }
    }
}

//====================================================================================================
// Inputs
//====================================================================================================

void input_name()
// Ask the player his character name
{
    print_logo(false);
    read_line(4, filename);
    printf("\n");
    print_sword();
    scanf("%s", name);
}

int input_question(int beginning_line, int ending_line, int choice_number, char *filename, bool actions)
// Return number chosen by the player by the choices and language
{
    // Variable :
    int player_choice = -1, i;
    char temp_string[100];

    while (1 > player_choice || player_choice > choice_number)
    {
        // Write question and choices :
        for (i = beginning_line; i <= ending_line; i++)
        {
            read_line(i, filename);
            printf("\n");
        }
        print_sword();
        scanf("%d", &player_choice);

        // If choice always -1, text in front is in temp variable
        if (player_choice == -1)
        {
            scanf("%s", temp_string);
        }

        if (actions && player_choice == 0)
        {
            other_actions();
            print_logo(true);
        }
    }
    return player_choice;
}

void initiate_monster(int monster_number)
// Initiate monsters hp according to number (1.Cyclops / 2.Skeleton King / 3.Lord of Trolls)
{
    switch (monster_number)
    {
    case 1: // Cyclops
        max_monster_hp = 75;
        monster_hp = 75;
        monster_min = 10;
        monster_max = 15;
        break;

    case 2: // Skeleton King
        max_monster_hp = 100;
        monster_hp = 100;
        monster_min = 25;
        monster_max = 30;
        break;

    case 3: // Lord of Trolls
        max_monster_hp = 150;
        monster_hp = 150;
        monster_min = 30;
        monster_max = 60;
        break;
    }
}

int range_int_choose(int min, int max)
// Return an int between min and max
{
    return min + rand() % (max - min + 1);
}

void monster_attack_player(int monster_number)
// Monster attack the player with random damage between his interval of monster_number
{
    // Variable :
    int damage;

    damage = range_int_choose(monster_min, monster_max);
    printf("%d ", damage);
    hp -= damage;
}

bool input_combat(int monster_number, bool possible_actions)
// Do a fight between the monster and the hero turn-based
// Return True if player has beaten the monster
{
    // Variable :
    bool fight_in_process = true, monster_beaten = true;

    initiate_monster(monster_number);

    // print_logo(true);
    while (fight_in_process)
    {
        if (input_question(6, 8, 2, "combats", possible_actions) == 2) // Fuit
        {
            print_logo(true);
            if (range_int_choose(0, 100) > 50) // If he flee (50% chance)
            {
                fight_in_process = false;
                monster_beaten = false;
                read_line(9, "combats");
            }
            else
                read_line(10, "combats");
        }
        else // Fight
        {
            print_logo(true);

            // Player attack :
            read_line(1, "combats");
            read_line(10 + monster_number, "combats"); // Monster's name
            read_line(2, "combats");
            if (potion_attack_number_lasting > 0)
            {
                monster_hp = monster_hp - (ap + additionnal_attacks);
                potion_attack_number_lasting -= 1;
                printf("%d ", ap + additionnal_attacks);
            }
            else
            {
                monster_hp -= ap;
                printf("%d ", ap);
            }
            read_line(3, "combats"); // Healing Potion
        }
        // If monster not dead, monster attack :
        if (monster_hp > 0 && fight_in_process)
        {
            read_line(4, "combats");
            read_line(10 + monster_number, "combats"); // Name of monsters
            read_line(5, "combats");
            monster_attack_player(monster_number);
            read_line(3, "combats"); // Healing Potion

            // HP of monster :
            printf("\n");
            read_line(10 + monster_number, "combats"); // Name of monsters
            printf(": %d / %d\n", monster_hp, max_monster_hp);

            // HP of player  :
            printf("%s : %d / %d\n", name, hp, max_monster_hp);

            // If player is dead, Game over:
            if (hp < 0)
            {
                fight_in_process = false;
                monster_beaten = false;
                read_line(14, "combats");
            }
        }
        else // Fight done, monster beaten:
            fight_in_process = false;
    }

    return monster_beaten;
}

//====================================================================================================
// Introduction : Creation
//====================================================================================================

void initiate_hero_features()
// Initiate every features of hero base of his class.
{
    switch (number_hero)
    {
    case 1: // Priest (easy)
        // Healing Potion :
        max_monster_hp = 125;
        hp = 125;

        // AP :
        ap = 25;

        // Effect Healing Potion
        healing_potion_number = 3;
        additionnal_hp = 50;

        // Effect Power Potion (increase hero AP) :
        power_potion_number = 1;
        using_potion_effects_number = 3; /*Number of uses to increase*/
        additionnal_attacks = 25;        /*hp we remove to the enemy*/

        // Money :
        gold = 25; // Money (Gold)
        break;

    case 2: // Knight (intermediate)
        // Healing Potion :
        max_monster_hp = 125;
        hp = 125;

        // AP :
        ap = 40;

        // Effect Healing Potion
        healing_potion_number = 1;
        additionnal_hp = 25;

        // Effect Power Potion (increase hero AP) :
        power_potion_number = 1;
        using_potion_effects_number = 3; /*Utilisation number to increase*/
        additionnal_attacks = 40;        /*hp we remove to the enemy*/

        // Money :
        gold = 10; // Money (Gold)
        break;

    case 3: // Orc (Advanced)
        // Healing Potion :
        max_monster_hp = 100;
        hp = 100;

        // AP :
        ap = 50;

        // Effect Healing Potion
        healing_potion_number = 1;
        additionnal_hp = 25;

        // Effect Power Potion (increase hero AP) :
        power_potion_number = 0;
        using_potion_effects_number = 2; /*Utilisation number to increase*/
        additionnal_attacks = 20;        /*hp we remove to the enemy*/

        // Money :
        gold = 0; // Money (Gold)
        break;

    case 4: // Mage (Hard)
        // Healing Potion :
        max_monster_hp = 50;
        hp = 50;

        // AP :
        ap = 50;

        // Effect Healing Potion
        healing_potion_number = 0;
        additionnal_hp = 20;

        // Effect Power Potion (increase hero AP) :
        power_potion_number = 0;
        using_potion_effects_number = 2; /*Utilisation number to increase*/
        additionnal_attacks = 50;        /*hp we remove to the enemy*/

        // Money :
        gold = 0; // Money (Gold)
        break;
    }
}

void intro()
{
    // Variable :
    int i;

    // Game language :
    print_logo(false);
    switch (input_question(1, 3, 2, filename, false))
    {
    case 1:
        snprintf(language, sizeof(language), "%s", "fr");
        break;

    case 2:
        snprintf(language, sizeof(language), "%s", "en");
        break;
    }

    // Name du joueur :
    input_name();

    // Hero class :
    print_logo(false);
    read_line(5, filename);
    printf("%s", name);
    number_hero = input_question(6, 12, 4, filename, false);
    initiate_hero_features();
}

//====================================================================================================
// Chapitre 1 : Bases
//====================================================================================================

void stairs_slope(bool additionnal_sentence)
// Can use 2 times in chapter1.
// If additionnal_sentence is True, a sentence is added, False if No it's not added.
{
    print_logo(true);
    if (additionnal_sentence)
        read_line(8, filename);
    switch (input_question(9, 12, 2, filename, true))
    {
    case 1:
        print_logo(true);
        read_line(13, filename);
        hp -= 5;
        break;

    case 2:
        print_logo(true);
        read_line(14, filename);
        break;
    }
}

void chapter1()
{
    // Variables :
    bool stay = true, left_open = true, middle_open = true;

    // Change the overall variable "filename" :
    snprintf(filename, sizeof(filename), "%s", "chapter1");

    print_logo(true);
    switch (input_question(1, 3, 2, filename, true))
    {
    case 1:
        stairs_slope(false);
        break;

    case 2:
        print_logo(true);
        switch (input_question(4, 6, 2, filename, true))
        {
        case 1:
            print_logo(true);
            read_line(7, filename);
            hp = 0; // Game Over.
            break;

        case 2:
            stairs_slope(true);
            break;
        }
        break;
    }

    if (hp > 0)
    {
        switch (input_question(15, 22, 2, filename, true))
        {
        case 1:
            print_logo(true);
            read_line(23, filename);
            gold += 20;
            healing_potion_number += 1;
            break;

        case 2:
            print_logo(true);
            break;
        }

        while (stay && hp > 0)
        {
            switch (input_question(24, 27, 3, filename, true))
            {
            case 1: // Cyclops
                print_logo(true);
                read_line(28, filename);
                if (left_open)
                {
                    if (input_combat(1, true))
                    {
                        read_line(29, filename); // + Power Potion
                        power_potion_number += 1;
                    }
                    left_open = false;
                }
                else
                    read_line(41, filename);

                if (hp > 0)
                    read_line(30, filename);
                break;

            case 2: // Seller
                print_logo(true);
                if (middle_open)
                {
                    switch (input_question(31, 33, 2, filename, true))
                    {
                    case 1: // Yes
                        print_logo(true);
                        middle_open = false;
                        if (gold >= 20)
                        {
                            read_line(34, filename);
                            gold -= 20;
                            healing_potion_number += 1;
                        }
                        else
                            read_line(35, filename);
                        break;

                    case 2:
                        print_logo(true);
                        middle_open = false;
                        break;
                    }
                    read_line(40, filename);
                }
                else
                    read_line(41, filename);
                break;

            case 3: // Stairs
                print_logo(true);
                switch (input_question(36, 38, 2, filename, true))
                {
                case 1:
                    print_logo(true);
                    read_line(39, filename);
                    stay = false;
                    break;

                case 2:
                    print_logo(true);
                    read_line(40, filename);
                    break;
                }
            }
        }
    }
}

//====================================================================================================
// Chapitre 2 : Hell
//====================================================================================================

void chapter2()
{
    // Variable :
    bool possible_actions = true, throught_right_door = false, not_found_stairs = true, not_resolved_puzzle = true, not_resolved_code = true, middle_open = true;

    // Change overall variable "filename" :
    snprintf(filename, sizeof(filename), "%s", "chapter2");

    print_logo(possible_actions);
    switch (input_question(1, 9, 2, filename, possible_actions)) // Chest and sign
    {
    case 1:
        print_logo(possible_actions);
        read_line(10, filename);
        possible_actions = false; // pendant
        break;

    case 2:
        print_logo(possible_actions);
        read_line(11, filename);
        break;
    }

    while (not_found_stairs && hp > 0)
    {
        switch (input_question(12, 15, 3, filename, possible_actions)) // 3 doors room
        {
            // Left door
        case 1:
            print_logo(possible_actions);
            switch (input_question(16, 20, 2, filename, possible_actions)) // Ghostly mirror
            {
            case 1: // Yes
                print_logo(possible_actions);
                read_line(21, filename);
                hp = hp / 2;
                break;

            case 2: // No
                print_logo(possible_actions);
                read_line(22, filename);
                break;
            }
            read_line(23, filename);

            //(Still left door) Next room
            if (throught_right_door) // If the player already went to the right door, the room appears normally
            {
                while (not_resolved_code && hp > 0) // While the code isn't given, the player's stuck
                {
                    switch (input_question(24, 28, 4, filename, possible_actions)) // Giving the right code
                    {
                    case 1: // 3412
                        print_logo(possible_actions);
                        not_resolved_code = false;
                        switch (input_question(30, 37, 3, filename, possible_actions)) // Seller
                        {
                        case 1: // Healing Potion
                            print_logo(possible_actions);
                            read_line(38, filename);
                            gold -= 20;
                            break;

                        case 2: // Power Potion
                            print_logo(possible_actions);
                            read_line(39, filename);
                            gold -= 30;
                            break;

                        case 3: // Nothing bought
                            print_logo(possible_actions);
                            read_line(40, filename);
                            break;
                        }
                        break;

                    case 2: // 4231
                        print_logo(possible_actions);
                        read_line(29, filename);
                        hp -= 10;
                        break;

                    case 3: // 1432
                        print_logo(possible_actions);
                        read_line(29, filename);
                        hp -= 10;
                        break;

                    case 4: // 4123
                        print_logo(possible_actions);
                        read_line(29, filename);
                        hp -= 10;
                        break;
                    }
                }
                if (hp > 0)
                {
                    read_line(41, filename);
                    read_line(42, filename);
                    if (input_combat(2, possible_actions)) // fight Skeleton King
                    {
                        read_line(43, filename); // Skeleton King beaten
                    }
                    else if (hp > 0) // Alternate ending Game Over
                    {
                        read_line(4, "ends");
                        read_line(5, "ends");
                        read_line(6, "ends");
                        hp = 0;
                    }
                    else
                    {
                        read_line(74, filename);
                    }
                    not_found_stairs = false;
                }
            }
            else // If No, room is empty
            {
                read_line(44, filename);
            }
            break;

        case 2: // Middle
            print_logo(possible_actions);
            if (middle_open) // If door open
            {
                switch (input_question(45, 47, 2, filename, possible_actions))
                {
                case 1: // Open chest
                    print_logo(possible_actions);
                    read_line(48, filename);
                    gold += 30;
                    power_potion_number += 1;
                    break;
                case 2:
                    print_logo(possible_actions);
                    read_line(49, filename);
                    middle_open = false;
                }
            }
            else
                read_line(75, filename); // Locked door message
            break;

        case 3: // Right
            print_logo(possible_actions);
            if (!throught_right_door)
            {
                while (not_resolved_puzzle && hp > 0)
                {
                    switch (input_question(50, 55, 4, filename, possible_actions))
                    {
                    case 1: // Remove torches (remove 10 HP)
                        print_logo(possible_actions);
                        read_line(56, filename);
                        hp -= 10;
                        break;

                    case 2: // Tiles (do nothing)
                        print_logo(possible_actions);
                        read_line(57, filename);
                        break;

                    case 3: // Bricks (Open next room)
                        print_logo(possible_actions);
                        not_resolved_puzzle = false;
                        read_line(58, filename);
                        break;

                    case 4: // Shoe (Remove 5 HP)
                        print_logo(possible_actions);
                        read_line(72, filename);
                        hp -= 5;
                        break;
                    }
                }
                // Cyclops :
                read_line(59, filename);
                read_line(60, filename);
                read_line(61, filename);
                read_line(62, filename);
                if (input_combat(1, possible_actions))
                {
                    read_line(63, filename); // + 25G and + 2 Healing Potion
                    healing_potion_number += 2;
                    gold += 25;
                }
                // Code hint
                if (hp > 0)
                {
                    for (int i = 0; i <= 7; i++)
                    {
                        read_line(64 + i, filename);
                        printf("\n");
                    }
                    read_line(73, filename);
                    throught_right_door = true;
                }
            }
            else
                read_line(75, filename); // Closed door message
        }
    }
    if (hp < 0)
        read_line(74, filename);
}

//====================================================================================================
// Chapitre 3 : Ending scene
//====================================================================================================

void chapter3()
{
    // change overall variable "filename" :
    snprintf(filename, sizeof(filename), "%s", "chapter3");

    read_line(1, filename);
    read_line(2, filename);
    read_line(3, filename);
    if (input_combat(3, true)) // fight Lord of Trolls
    {
        read_line(1, "ends");
        read_line(2, "ends");
        read_line(3, "ends"); // Lord of Trolls beaten
    }
    else if (hp > 0) // Alternate ending Game Over
    {
        read_line(7, "ends");
        read_line(8, "ends");
        read_line(9, "ends");
        hp = 0;
    }
}

//====================================================================================================
// Main : Launching program
//====================================================================================================

void pause()
// Make a break at the end of the game, so the terminal doesn't close directly.
{
#ifdef _WIN32
    system("pause"); // for Windows
#else
    getchar(); // for Linux and autres OS
#endif
}

int main()
{
    // Initiating random numbers generator
    srand(time(NULL));

    intro();
    chapter1();
    if (hp > 0)
    {
        chapter2();
        if (hp > 0)
            chapter3();
    }
    pause();
    return 0;
}