// Header Files
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <thread>
#include <conio.h>
#include <string>
#include <iomanip>
using namespace std;

// Global constants and variables
// ANSI color codes
const char* reset_color = "\x1B[0m";
const char* bold = "\x1B[1m";
const char* underline = "\x1B[4m";
const char* invert_color = "\x1B[7m";
const char* color[] = {
    "\x1B[31m",  // red
    "\x1B[32m",  // green
    "\x1B[33m",  // yellow
    "\x1B[34m",  // blue
    "\x1B[35m",  // magenta
    "\x1B[36m",  // cyan
    "\x1B[37m"   // white
};

// Player Stats
string player_name = "Aiden";
int player_health = 100;
int lightning_spells = 2;
int healing_spells = 0;
int rage_spells = 0;
int player_rage_power = 35;
int player_attack_power = 20;
int player_healing_power = 15;
int player_lightning_power = 30;
int player_level_health[] = { 100, 110, 120, 130, 140 };
int level_counter = 1;
int spear_cooldown = 0;
int player_attack_power_with_spear = 45;

// Minotaur Stats (Final Boss Level 01)
string harpy_name = "Harpy";
int harpy_health = 60;
int harpy_attack_power_talon = 20;
int harpy_attack_power_wind_gust = 20;

// Minotaur Stats (Final Boss Level 01)
string monster_name = "Minotaur";
int minotaur_attack_power = 20;
int minotaur_health = 200;

// Minotaur Stats (Final Boss Level 01)
string griffin_name = "Griffin";
int griffin_health = 90;
int griffin_attack_power_claw = 20;
int griffin_attack_power_screech = 20;
// Calliope Stats (Final Boss Level 05)
bool second_chance = false;
bool alive = true;
bool win = false;

// Reward Items
int fury_scroll = 0;
int griffin_claw = 0;
int harpy_feather = 0;
int lykomalos_coins = 0;
int minotaur_horn = 0;
int puck_token = 0;
int calliope_fabric = 0;
int chimera_fire_jar = 0;
int tyson_drawing = 0;
int mnemosyne_jar = 0;

// Lykomalos
const int ROCK = 1;
const int PAPER = 2;
const int SCISSORS = 3;

// Chimera's Stats ]
int chimera_attack_power_claws = 40;
int chimera_attack_power_fire = 45;
int chimera_health = 120;
bool chimera_fire_mode = false;

bool flag_hangman = false;

// Voicelines
const string aiden_battle_voice_lines[] = {
    "Aiden braces himself for battle",
    "Aiden shouts \"Behold Monster, your reckoning has come!\"",
    "Aiden looks into the eyes of his enemy, and prepares to strike",
    "Aiden readies his sword, and prepares to fight",
    "Aiden channels his inner strength, ready to face the unknown",
    "Aiden's determination shines brighter than the blade he wields",
    "Aiden whispers to himself, a silent oath to conquer the impending darkness",
    "Aiden stands firm, a solitary figure against the tide of adversaries",
    "Aiden's heartbeat syncs with the rhythm of impending battle",
    "Aiden, with unwavering resolve, steps into the crucible of combat"
};

const string aiden_victory_voice_lines[] = {
    "Aiden triumphs over the fallen foe, a testament to his skill and courage!",
    "The echoes of battle subside as Aiden stands victorious on the battlefield.",
    "With the monster defeated, Aiden's resolve shines brighter than ever before.",
    "The vanquished monster's roars are replaced by the silence of Aiden's triumph.",
    "Aiden, the indomitable warrior, emerges victorious from the crucible of combat!",
    "As the dust settles, Aiden stands as the sole conqueror of the once-daunting foe.",
    "Aiden's blade, now stained with victory, reflects the resilience of a true hero.",
    "In the aftermath of battle, Aiden's name will be whispered with awe and respect.",
    "With the monster's defeat, Aiden's legend grows, destined to be told in tales of valor.",
    "Aiden, the slayer of beasts, leaves the battlefield with head held high."
};

const string aiden_defeat_voice_lines[] = {
    "Aiden falls to the relentless onslaught of the monster, defeated but not broken.",
    "In the face of overwhelming odds, Aiden succumbs to the might of the monstrous foe.",
    "The battlefield echoes with the lament of Aiden, defeated in the struggle against the monster.",
    "Aiden's valiant effort is met with the cruel reality of defeat at the hands of the monster.",
    "As the monster stands triumphant, Aiden acknowledges the bitter taste of defeat.",
    "The once indomitable Aiden bows to the superior strength of the fearsome monster.",
    "Defeated but undaunted, Aiden retreats, vowing to return stronger in the face of adversity.",
    "The roar of the monster drowns out the echoes of Aiden's defeat on the battlefield.",
    "Aiden's defeat is a somber melody, harmonizing with the ruthless symphony of the monster.",
    "In the aftermath of the battle, Aiden reflects on the lessons learned in the crucible of defeat."
};

void lines_tabs(int lines, int tabs = 0) {
    for (int i = 0; i < lines; ++i) {
        cout << endl;
    }

    for (int i = 0; i < tabs; ++i) {
        cout << "\t";
    }
}

// Design Function definitions
void set_text_attributes(bool is_inverted = false, bool is_bold = false, bool is_underlined = false, const char* color_code = color[6]) {
    if (is_inverted) cout << invert_color;
    if (is_bold) cout << bold;
    if (is_underlined) cout << underline;
    cout << color_code;
}

// Fight modes functions prototypes
int perform_attack(int attack_power) {
    return (rand() % (attack_power - 15 + 1)) + 15; // Range of Damage = [ 15 , attack_power ] 
}

int perform_healing_spell(int healing_power) {
    return (rand() % (healing_power - 10 + 1)) + 10; // Range of Healing =  [ 10 , healing_power ]
}

int perform_lightning_spell(int lightning_power) {
    return (rand() % (player_lightning_power - 15 + 1)) + 15; // Range of Damage = [ 15 , lightning_power ]
}

void reset_text_attributes() {
    cout << reset_color;
}

void print_text_with_attributes(const string& text, bool is_inverted = false, bool is_bold = false, bool is_underlined = false, const char* color_code = color[6], int delay = 50) {
    set_text_attributes(is_inverted, is_bold, is_underlined, color_code);
    for (char c : text) {
        cout << c << flush;
        this_thread::sleep_for(chrono::milliseconds(delay));
    }
    reset_text_attributes();
}

void print_text_without_delay(const string& text, bool is_inverted = false, bool is_bold = false, bool is_underlined = false, const char* color_code = color[6]) {
    set_text_attributes(is_inverted, is_bold, is_underlined, color_code);
    cout << text << flush;
    reset_text_attributes();
}

int perform_spear_throw() {
    spear_cooldown = 2;
    return (rand() % (player_attack_power_with_spear - 30 + 1)) + 30; // Range of Damage = [ 30 , player_attack_power ]
}

bool is_spear_available() {
    return spear_cooldown <= 0;
}

void reduce_spear_cooldown() {
    if (spear_cooldown > 0) {
        spear_cooldown--;
    }
}

void perform_roll_away() {
    int damage_taken_roll_away = 15;
    player_health -= (rand() % (damage_taken_roll_away - 5 + 1)) + 5;             // Range = [ 5 , 15 ]
    lines_tabs(1, 1);
    print_text_with_attributes(player_name + " rolls away from the Chimera's fire breath but takes " + to_string(damage_taken_roll_away) + " damage", true, false, false, color[0]);
}

void getRandomLykomalosVoiceLine() {
    const int numVoiceLines = 5;
    const char* voiceLines[numVoiceLines] = {
        "\x1B[31mLykomalos whispers: 'You think you can outsmart me, traveler?'\n",
        "\x1B[31mLykomalos chuckles: 'Let's see if you can predict my move.'\n",
        "\x1B[31mLykomalos teases: 'Are you feeling lucky, Aiden?'\n",
        "\x1B[31mLykomalos laughs: 'This game is more than meets the eye.'\n",
        "\x1B[31mLykomalos warns: 'Your choices have consequences, my friend.'\n"
    };

    int randomIndex = rand() % numVoiceLines;
    print_text_with_attributes(voiceLines[randomIndex], true);
}

void getRandomAidenVoiceLine() {
    const int numVoiceLines = 5;
    const char* voiceLines[numVoiceLines] = {
        "\x1B[32mAiden triumphs: 'Looks like I've got the upper hand!'\n",
        "\x1B[32mAiden cheers: 'Victory tastes sweet, doesn't it?'\n",
        "\x1B[32mAiden boasts: 'Part-lion, part-fox, yet your losing to me'\n",
        "\x1B[32mAiden exclaims: 'I thought foxes were known for their cunning'\n",
        "\x1B[32mAiden laughs: 'Better luck next time, Lykomalos!'\n"
    };

    int randomIndex = rand() % numVoiceLines;
    print_text_with_attributes(voiceLines[randomIndex], true);
}

// Voiceline function definitions
void random_battle_voicelines(bool is_aiden, bool is_victory)
{
    int random_voice_line = (rand() % 10);              // Range = [ 0 , 9 ]
    if (is_aiden)
        print_text_with_attributes(aiden_battle_voice_lines[random_voice_line], true, false, color[(rand() % 6) + 1]);
    else if (is_victory)
        print_text_with_attributes(aiden_victory_voice_lines[random_voice_line], true, false, color[5]);
    else
        print_text_with_attributes(aiden_defeat_voice_lines[random_voice_line], true, false, color[0]);
}

void clear_screen()
{
    system("cls");
}

void loading_screen() {
    // Choose a random color for the entire text
    int random_color = rand() % 7;

    clear_screen();
    // Center the text on the screen
    cout << "\n\n\n\n\n\n";
    cout << setw((80 - 7) / 2) << ""; // Adjust the width as needed
    print_text_with_attributes(" L O A D I N G", true, false, color[random_color]);
    this_thread::sleep_for(chrono::seconds(1));
    print_text_with_attributes(" .", true, false, color[random_color]);
    this_thread::sleep_for(chrono::seconds(1));
    print_text_with_attributes(" .", true, false, color[random_color]);
    this_thread::sleep_for(chrono::seconds(1));
    print_text_with_attributes(" .", true, false, color[random_color]);
    this_thread::sleep_for(chrono::seconds(1));

    // Final clear screen
    clear_screen();
}

void display_weapon_inventory() {
    // Display header
    lines_tabs(4, 4);
    print_text_with_attributes("Weapons Inventory", true, false, false, color[6]);
    lines_tabs(1, 0);
    lines_tabs(1, 2);
    cout << "+--------------------------+------------------+" << endl;
    lines_tabs(0, 2);
    cout << "|        " << invert_color << bold << color[5] << "Weapons" << reset_color << "        |    " << invert_color << "Attack Power" << reset_color << "     |" << endl;
    lines_tabs(0, 2);
    cout << "+--------------------------+------------------+" << endl;
    lines_tabs(0, 2);
    cout << "|       " << invert_color << bold << color[5] << " Sword " << reset_color << "         |    " << "   " << invert_color << "   " << player_attack_power << "   " << reset_color << "      |" << endl;
    lines_tabs(0, 2);
    cout << "|       " << invert_color << bold << color[5] << " Spear " << reset_color << "         |    " << "   " << invert_color << "   " << player_attack_power_with_spear << "   " << reset_color << "      |" << endl;
    lines_tabs(0, 2);
    cout << "+--------------------------+------------------+" << endl;
    lines_tabs(0, 2);
}

void display_spell_inventory() {
    // Display header
    lines_tabs(4, 3);
    print_text_with_attributes("Spells Inventory", true, false, false, color[6]);
    lines_tabs(1, 0);

    lines_tabs(1, 1);
    cout << "+--------------------------+------------------+------------------+" << endl;
    lines_tabs(0, 1);
    cout << "|        " << invert_color << bold << color[2] << "Spells" << reset_color << "          |    " << invert_color << bold << color[1] << "Attack Power" << reset_color << "    |     " << invert_color << bold << color[5] << " Amount " << reset_color << "     |" << endl;
    lines_tabs(0, 1);
    cout << "+--------------------------+------------------+------------------+" << endl;
    lines_tabs(0, 1);
    cout << "|    " << invert_color << bold << color[2] << "Lightning Spell" << reset_color << "     |    " << invert_color << bold << color[1] << "      " << player_lightning_power << "      " << reset_color << "  |      " << invert_color << bold << color[5] << "  " << lightning_spells << "  " << reset_color << "       |" << endl;
    lines_tabs(0, 1);
    cout << "|    " << invert_color << bold << color[2] << "Healing Spell" << reset_color << "       |    " << invert_color << bold << color[1] << "      " << player_healing_power << "      " << reset_color << "  |      " << invert_color << bold << color[5] << "  " << healing_spells << "  " << reset_color << "       |" << endl;
    lines_tabs(0, 1);
    cout << "|    " << invert_color << bold << color[2] << "Rage Spell" << reset_color << "          |    " << invert_color << bold << color[1] << "      " << player_rage_power << "      " << reset_color << "  |      " << invert_color << bold << color[5] << "  " << rage_spells << "  " << reset_color << "       |" << endl;
    lines_tabs(0, 1);
    cout << "+--------------------------+------------------+------------------+" << endl;
    lines_tabs(0, 1);
}

void damage_report(string attackMode, int damageInflicted, int playerHealth, int enemy_health, bool is_monster = false, string name = "monster") {
    lines_tabs(1, 5);
    if (!is_monster)
    {
        print_text_with_attributes("Aiden's Turn", true, false, false, color[5]);
        lines_tabs(1, 1);
        cout << "+------------------+------------------+------------------+------------------+" << endl;
        lines_tabs(0, 1);
        cout << "| " << bold << color[2] << "Attack Mode      | Damage Inflicted | Player Health    | Monster Health   | " << reset_color << endl;
        lines_tabs(0, 1);
        cout << "+------------------+------------------+------------------+------------------+" << endl;
        lines_tabs(0, 1);
        cout << "   " << attackMode << "                " << damageInflicted << "                    " << playerHealth << "                 " << enemy_health << "                " << endl;
        lines_tabs(0, 1);
        cout << "+------------------+------------------+------------------+------------------+" << endl;
    }
    else {
        print_text_with_attributes(harpy_name + "'s Turn", true, false, false, color[0]);
        lines_tabs(1, 1);
        cout << "+------------------+------------------+------------------+------------------+" << endl;
        lines_tabs(0, 1);
        cout << "| " << bold << color[1] << "Attack Mode      | Damage Inflicted | Player Health    | Monster Health   | " << reset_color << endl;
        lines_tabs(0, 1);
        cout << "+------------------+------------------+------------------+------------------+" << endl;
        lines_tabs(0, 1);
        cout << "   " << attackMode << "                " << damageInflicted << "                    " << playerHealth << "                 " << enemy_health << "                " << endl;
        lines_tabs(0, 1);
        cout << "+------------------+------------------+------------------+------------------+" << endl;
    }
}

void display_rewards_inventory()
{
    lines_tabs(4, 3);
    print_text_with_attributes("Rewards Inventory", true, false, false, color[6]);
    lines_tabs(1, 2);
    cout << "+--------------------------+------------------+" << endl;
    lines_tabs(0, 2);
    cout << "|     " << invert_color << "Rewards" << reset_color << "              |   " << invert_color << "Quantity  " << reset_color << "     |" << endl;
    lines_tabs(0, 2);
    cout << "+--------------------------+------------------+" << endl;
    lines_tabs(0, 2);
    cout << "|    " << invert_color << " Minotaur Horn " << reset_color << "       |    " << "   " << invert_color << "   " << minotaur_horn << "   " << reset_color << "    |" << endl;
    lines_tabs(0, 2);
    cout << "|    " << invert_color << " Harpy Feather " << reset_color << "       |    " << "   " << invert_color << "   " << harpy_feather << "   " << reset_color << "    |" << endl;
    lines_tabs(0, 2);
    cout << "|    " << invert_color << " Fury Scroll " << reset_color << "         |    " << "   " << invert_color << "   " << fury_scroll << "   " << reset_color << "    |" << endl;
    lines_tabs(0, 2);
    cout << "|    " << invert_color << " Griffin Claw " << reset_color << "        |    " << "   " << invert_color << "   " << griffin_claw << "   " << reset_color << "    |" << endl;
    lines_tabs(0, 2);
    cout << "|    " << invert_color << " Lykomalos Coins " << reset_color << "     |    " << "   " << invert_color << "   " << lykomalos_coins << "   " << reset_color << "    |" << endl;
    lines_tabs(0, 2);
    cout << "|    " << invert_color << " Puck Token      " << reset_color << "     |    " << "   " << invert_color << "   " << puck_token << "   " << reset_color << "    |" << endl;
    lines_tabs(0, 2);
    cout << "|    " << invert_color << " Calliope Fabric " << reset_color << "     |    " << "   " << invert_color << "   " << calliope_fabric << "   " << reset_color << "    |" << endl;
    lines_tabs(0, 2);
    cout << "|    " << invert_color << " Tyson Drawing   " << reset_color << "     |    " << "   " << invert_color << "   " << tyson_drawing << "   " << reset_color << "    |" << endl;
    lines_tabs(0, 2);
    cout << "+--------------------------+------------------+" << endl;
    lines_tabs(0, 2);
}

void player_turn() {
    lines_tabs(2, 1);
    print_text_with_attributes("Aiden's Turn: ", true, false, false, color[1]);
    lines_tabs(1, 1);
    print_text_with_attributes("Aiden braces himself for the harpy's attack ", true);
    lines_tabs(2, 1);

    cout << "Choose your action:";
    cout << "\n\t1. Attack With Sword"
        << "\n\t2. Cast A Spell";
    cout << "\n\tEnter your choice: ";
    int choice;
    cin >> choice;
    bool valid_choice = false;

    switch (choice) {
    case 1: {
        int player_damage = perform_attack(player_attack_power);
        /*lines_tabs(1, 1);
        print_text_with_attributes("Aiden has attacked the Harpy for: ", true);
        cout << invert_color << " " << player_damage << " damage " << reset_color;
        */
        harpy_health -= player_damage;
        damage_report("Sword", player_damage, player_health, harpy_health);
        break;
    }
    case 2: {
        display_spell_inventory();
        cout << "\n\tChoose a spell:";
        lines_tabs(1, 1);
        cout << color[2] << "1. Cast a healing spell";
        reset_text_attributes();
        lines_tabs(1, 1);
        cout << color[5] << "2. Cast a lightning spell";
        reset_text_attributes();
        cout << "\n\tEnter your choice: ";
        int spell_choice;
        cin >> spell_choice;

        switch (spell_choice)
        {
        case 1:
        {
            if (healing_spells > 0)
            {
                int player_healing_amount = perform_healing_spell(player_healing_power);
                player_health += player_healing_amount;
                lines_tabs(1, 1);
                damage_report("Spell", 0, player_health, harpy_health);
                /*print_text_without_delay("Aiden casts a healing spell and gains ", true, false, false, color[2]);
                cout << invert_color << color[2] << player_healing_amount << " health!" << reset_color;
                */
                valid_choice = true;
                healing_spells--;
            }
            else
                print_text_with_attributes("\n\t" + player_name + " is out of healing spells. Choose other options", true, false, false, color[4]);
            break;
        }
        case 2:
        {
            if (lightning_spells > 0)
            {
                int player_lightning_damage = perform_lightning_spell(player_lightning_power);
                harpy_health -= player_lightning_damage;
                damage_report("Spell", player_lightning_damage, player_health, harpy_health);
                /*print_text_with_attributes(player_name + " casts a lightning spell on the harpy for " + to_string(player_lightning_damage) + " damage", true, false, false, color[5]);
                cout << "\n\t" << player_name << " casts a lightning spell on the harpy for " << player_lightning_damage << " damage.";
                */
                valid_choice = true;
                lightning_spells--;
            }
            else
            {
                print_text_with_attributes("\n\t" + player_name + " is out of lightning spells. Choose other options", true, false, false, color[4]);
            }
            break;
        }
        default:
        {
            print_text_with_attributes("\n\tMagic is not in the tools but in the hands of the one who wields them. \n\tMistakes illuminate the path to mastery.", true, false, false, color[4]);
            break;
        }
        break;
        }
        break;
    default: {
        print_text_with_attributes("\n\tLike a misdirected incantation or an ill - fated swing of the sword, \n\ta wrong choice echoes lessons to heed and paths to reconsider in the journey of wisdom.", true, false, false, color[4]);
        break;
    }
    }
    }

}

bool skip_dialogues()
{
    string r;
    bool flag = false;
    do {
        lines_tabs(1, 1);
        print_text_with_attributes("Skip Dialogues?", true);
        cin >> r;
        lines_tabs(0, 1);
        clear_screen();
        if (r == "yes" || r == "Yes" || r == "YES")
        {
            flag = true;
            return true;
        }
        else if (r == "NO" || r == "no" || r == "No")
        {
            flag = true;
            return false;
        }
    } while (!flag);
}

void harpy_turn() {
    // Randomize the harpy's attack mode
    int attack_choice = rand() % 2;

    if (attack_choice == 0) {
        int harpy_damage = perform_attack(harpy_attack_power_talon);
        player_health -= harpy_damage;
        damage_report("Talons", harpy_damage, player_health, harpy_health, true, harpy_name);
        //lines_tabs(1, 1);
        //print_text_with_attributes("The Harpy strikes Aiden with its talons, dealing " + to_string(harpy_damage) + " damage", true, false, false, color[0]);
        //cout << invert_color << " " << harpy_damage << " damage " << reset_color;
    }
    else {
        int harpy_damage = perform_attack(harpy_attack_power_wind_gust);
        player_health -= harpy_damage;
        damage_report("Wind Gust", harpy_damage, player_health, harpy_health, true, harpy_name);
        //lines_tabs(1, 1);
        //print_text_with_attributes("The Harpy unleashes a gust of wind, dealing " + to_string(harpy_damage) + " damage", true, false, false, color[0]);
        //cout << invert_color << " " << harpy_damage << " damage " << reset_color;
    }
}

bool i_make_and_display_riddles() {
    const int numRiddles = 7;

    print_text_without_delay("\n\n\n\t                                                                                 ", true);
    print_text_with_attributes("\n\t  You are confronted by a Fury. A winged creature having serpents for hair       ", true);
    print_text_with_attributes("\n\t Furies have terrifying and fearful appearence, representing the vengeful aspect ", true);
    print_text_with_attributes("\n\t                        of justice                                               ", true);
    print_text_without_delay("\n\t                                                                              \n", true);


    const char* greek_riddles[numRiddles][2] = {
        {"\tI am the king of the gods, ruling from \n\t\tMount Olympus.", "Zeus"},
        {"\tI am a monster with snakes for hair. \n\t\tOne look at me turns people to stone.", "Medusa"},
        {"\tI am the goddess of wisdom, warfare, and crafts. \n\t\tI sprang fully grown and armored from \n\t\t\tthe head of Zeus.", "Athena"},
        {"\tI am a hero with exceptional strength. \n\t\tMy only weakness is my heel.", "Achilles"},
        {"\tI am the goddess of love and beauty, \n\t\tborn from the sea foam.", "Aphrodite"},
        {"\tI am a three-headed dog guarding the \n\t\tentrance to the Underworld.", "Cerberus"},
        {"\tI am the titan who stole fire from the \n\t\tgods and gave it to humanity.", "Prometheus"}
    };

    const char* second_greek_riddles[numRiddles][2] = {
        {"\tI am the god of lightning.\n\t\tMy Roman counterpart is Jupiter.", "Zeus"},
        {"\tI am a gorgon. My name starts with an M", "Medusa"},
        {"\tMy symbol is an owl", "Athena"},
        {"\tAlthough I was a hero in Trojan War, \n\t\tthey only remember me because of my heel", "Achilles"},
        {"\tMy Roman counterpart is Venus, a celestial body \n\t\tthat shines so bright, just like me", "Aphrodite"},
        {"\tHeracles brought me to the surface\n\t\tas one of his Twelve Labors", "Cerberus"},
        {"\t p-om-e-theus", "Prometheus"}
    };

    const char* riddles_to_ask[][2] = {
        {"\tI have cities but no houses, \n\t\tForests but no trees, \n\t\tRivers but no water,\n\t\tWhat am I, a puzzle to tease ?", "map"},
        {"\tI fly without wings, cry without eyes,\n\t\tDarkness follows wherever I rise.\n\t\tWhat am I, a meteorological sprite,\n\t\tDraped in mist, a captivating sight ?", "cloud"},
        {"\tWith keys but no locks, \n\t\tI hold secrets untold,\n\t\tLetters and numbers within me unfold.\n\t\tTap my surface with fingers light,\n\t\tWhat am I, a modern-day sight ?", "keyboard"},
        {"\tI'm a feline of mystery, sleek and black,\n\t\tCross my path and you may turn back.\n\t\tSuperstitions swirl, tales are spun,\n\t\tWhat am I under the moonlit sun?", "black cat"},
        {"\tIn the morning, I wake, a ball of light,\n\t\tAt night, I rest, out of sight.\n\t\tReflecting the sun, I glow and gleam,\n\t\tWhat am I, a celestial dream?", "moon"},
        {"\tI have a face, two hands, but no arms,\n\t\tI tick and tock with rhythmic charms.\n\t\tWhat am I, a keeper of time,\n\t\tIn every chime?", "clock"},
        {"\tI'm always in front of you, but can't be seen,\n\t\tI follow you home, yet remain unseen.\n\t\tWhat am I, a shadowy guide,\n\t\tWalking beside?", "shadow"},
        {"\tI speak without a mouth, hear without ears,\n\t\tNo body to hold, yet I calm your fears.\n\t\tWhat am I, an elusive sound,\n\t\tEchoing around?", "echo"},
        {"\tI'm tall when I'm young, short when I'm old,\n\t\tI can be thin or wide, hot or cold.\n\t\tI dance in the sky, a celestial spree,\n\t\tWhat am I, a natural beauty?", "candle"},
        {"\tI'm a vessel of knowledge, filled with words,\n\t\tPages upon pages, stories unheard.\n\t\tWhat am I, a treasure of tales,\n\t\tIn libraries and bookshelves, my sails?", "book"}
    };

    // Seed the random number generator
    srand(time(0));

    int random_index = rand() % 11;

    cout << invert_color << bold << color[2] << "\n\n\t+---------------------------+-----------------------------+" << reset_color << endl << endl;
    cout << "\t" << invert_color << bold << color[5] << riddles_to_ask[random_index][0] << reset_color << endl;
    cout << invert_color << bold << color[5] << "\t\tWho am I?" << endl;
    cout << invert_color << bold << color[2] << "\n\t+---------------------------+-----------------------------+" << reset_color << endl;

    string userAnswer;
    print_text_with_attributes("\n\n\n\t\t\tWhat do you say, traveler? ", true, true, false, color[0]);
    getline(cin, userAnswer);

    if (userAnswer == riddles_to_ask[random_index][1]) {
        print_text_with_attributes("\n\t\t\tCorrect, you may proceed", true, true);
        print_text_with_attributes("\n\t\tThe fury places a mark on Aiden. This mark allows \n\t\tAiden to retaliate against enemies with increased power and health", true, true);
        player_attack_power += 5;
        player_healing_power += 5;
        player_lightning_power += 5;
        print_text_with_attributes("\n\t\tAiden feels stronger as his attack power is increased", true, true);
        clear_screen();
        display_weapon_inventory();
        display_spell_inventory();
    }
    else {
        int random_index_1 = rand() % 7;
        print_text_with_attributes("\t\tIncorrect. The correct answer is ", true, true, false);
        cout << invert_color << bold << riddles_to_ask[random_index][1] << reset_color;
        print_text_with_attributes("\n\tI'll give you another chance, traveler. But beware, no help comes for free\n", true, true, false);
        _getch();
        clear_screen();
        cout << invert_color << bold << color[2] << "\t+---------------------------+-----------------------------+" << reset_color << endl << endl;
        cout << "\t" << invert_color << bold << color[5] << greek_riddles[random_index][0] << reset_color << endl;
        cout << invert_color << bold << color[5] << "\t\tWho am I?" << endl;
        cout << invert_color << bold << color[2] << "\n\t+---------------------------+-----------------------------+" << reset_color << endl;

        string userAnswer;
        print_text_with_attributes("\n\n\n\t\t\tWhat do you say, traveler? ", true, true, false, color[0]);
        getline(cin, userAnswer);

        if (userAnswer == greek_riddles[random_index][1]) {
            print_text_with_attributes("\n\t\t\tCorrect, you may proceed", true, true);
            print_text_with_attributes("\n\t\tThe fury places a mark on Aiden. This mark allows \n\t\tAiden to retaliate against enemies with increased power and health", true, true);
            player_attack_power += 5;
            player_healing_power += 5;
            player_lightning_power += 5;
            print_text_with_attributes("\n\t\tAiden feels stronger as his attack power is increased", true, true);
            clear_screen();
            display_weapon_inventory();
            display_spell_inventory();
        }
        else {
            //cout << "\tIncorrect. The correct answer is: " << greek_riddles[random_index_1][1] << endl;
            print_text_with_attributes("\n\n\tI'll give you a hint. But traveler, beware, no help comes for free\n", true, true);
            cout << invert_color << bold << color[2] << "\n\n\t+---------------------------+-----------------------------+" << reset_color << endl << endl;
            cout << "\t" << invert_color << bold << color[5] << second_greek_riddles[random_index][0] << reset_color << endl;
            cout << invert_color << bold << color[5] << "\t\tWho am I?" << endl;
            cout << invert_color << bold << color[2] << "\n\t+---------------------------+-----------------------------+" << reset_color << endl;

            string userAnswer;
            print_text_with_attributes("\n\n\n\t\t\tWhat do you say, traveler? ", true, true, false, color[0]);
            getline(cin, userAnswer);

            if (userAnswer == second_greek_riddles[random_index][1]) {
                print_text_with_attributes("\n\t\t\tCorrect, you may proceed", true, true);
                print_text_with_attributes("\n\t\tThe fury places a mark on Aiden. This mark allows \n\t\tAiden to retaliate against enemies with increased power and health", true, true);
                player_attack_power += 5;
                player_healing_power += 5;
                player_lightning_power += 5;
                print_text_with_attributes("\n\t\tAiden feels stronger as his attack power is increased", true, true);
                clear_screen();
                display_weapon_inventory();
                display_spell_inventory();
            }

            else {
                print_text_with_attributes("\t\t\tYou lose. The correct answer was ", true, false, false, color[0]);
                cout << invert_color << color[0] << second_greek_riddles[random_index][1] << reset_color;
                return false;
            }
        }
    }
    return true;
}

void GG() {
    system("cls");  // Clear the console screen
    cout << "\n\n\n\n\n\n";
    cout << "\t\t\t  GGGGGGGG      GGGGGGGG   \n" << reset_color;
    cout << "\t\t\t G             G           \n" << reset_color;
    cout << "\t\t\t G             G           \n" << reset_color;
    cout << "\t\t\t G    GGGGG    G    GGGGG  \n" << reset_color;
    cout << "\t\t\t G        G    G        G  \n" << reset_color;
    cout << "\t\t\t  GGGGGGGG      GGGGGGGG  \n\n" << reset_color;
}


void display_battle_status_harpy() {
    lines_tabs(1, 1);
    cout << invert_color << player_name << "'s Health: " << player_health << " ";
    lines_tabs(1, 1);
    cout << harpy_name << "'s Health: " << harpy_health << " " << reset_color;
}

void display_inventory_harpy() {
    // Display header
    lines_tabs(4, 2);
    print_text_with_attributes("Current Inventory and Status", true, false, false, color[6]);
    lines_tabs(1, 0);

    // Display player and harpy health in a table
    lines_tabs(0, 1);
    cout << "+--------------------------+------------------+" << endl;
    lines_tabs(0, 1);
    cout << "| " << bold << color[2] << "Player Health" << reset_color << "        | " << bold << color[1] << "Harpy Health" << reset_color << "         |" << endl;
    lines_tabs(0, 1);
    cout << "+--------------------------+------------------+" << endl;
    lines_tabs(0, 1);
    cout << "| " << invert_color << color[2] << player_health << "                 " << reset_color << " | " << invert_color << color[1] << harpy_health << "                 " << reset_color << "  |" << endl;
    lines_tabs(0, 1);
    cout << "+--------------------------+------------------+" << endl;

    // Display attack modes in a table
    lines_tabs(1, 1);
    cout << "+--------------------------+------------------+" << endl;
    lines_tabs(0, 1);
    cout << "| " << bold << color[2] << "Player Attack Modes" << reset_color << "  | " << bold << color[1] << "Harpy Attack Modes" << reset_color << "   |" << endl;
    lines_tabs(0, 1);
    cout << "+--------------------------+------------------+" << endl;
    lines_tabs(0, 1);
    cout << "|    " << color[2] << "Attack With Sword" << reset_color << " |    " << color[1] << "Talon" << reset_color << "             |" << endl;
    lines_tabs(0, 1);
    cout << "|    " << color[2] << "Roll Away" << reset_color << "         |    " << color[1] << "Wind Gust" << reset_color << "         |" << endl;
    lines_tabs(0, 1);
    cout << "|    " << color[2] << "Cast A Spell" << reset_color << "      |                      |" << endl;
    lines_tabs(0, 1);
    cout << "+--------------------------+------------------+" << endl;
    lines_tabs(0, 1);
}

bool fight_harpy()
{
    srand(time(0));

    lines_tabs(2, 1);
    print_text_without_delay("                                                                             ", true);
    lines_tabs(1, 1);
    print_text_with_attributes("  As Aiden wanders through the enchanted forest, he hears a flutter of wings  ", true);
    lines_tabs(1, 1);
    print_text_with_attributes("  A fierce harpy, a creature with the head of a woman and the body of a bird  ", true);
    lines_tabs(1, 1);
    print_text_with_attributes("  from the sky. Without warning, she attacks Aiden. Aiden prepares himself    ", true);
    lines_tabs(1, 1);
    print_text_without_delay("                       for battle                                             ", true);
    lines_tabs(1, 1);
    print_text_without_delay("                                                                              ", true);

    display_inventory_harpy();

    _getch();
    loading_screen();
    // Aiden's turn is first
    while (player_health > 0 && harpy_health > 0) {
        player_turn();
        if (harpy_health <= 0) {
            cout << "\t";
            random_battle_voicelines(false, true);
            return true;
            break;
        }
        //display_battle_status();
        lines_tabs(1, 0);
        harpy_turn();
        if (player_health <= 0) {
            cout << "\t";
            random_battle_voicelines(false, false);
            return false;
            break;
        }
        display_battle_status_harpy();
        _getch();
        system("cls");
    }
}

void display_rps_menu(const string& playerName) {

    cout << invert_color << bold << color[2] << "\n--- Choose Wisely, traveler ---\n" << reset_color;
    cout << invert_color << bold << color[5] << "\t1. Rock" << endl;
    cout << invert_color << bold << color[5] << "\t2. Paper" << endl;
    cout << invert_color << bold << color[5] << "\t3. Scissors" << endl;
    cout << invert_color << bold << color[2] << "---------------------------------\n";
}

void determine_winner(const string& playerName, int player, int computer, int& aidenScore, int& lykomalosScore) {
    cout << playerName << " chose ";
    this_thread::sleep_for(chrono::milliseconds(250));
    switch (player) {
    case ROCK:
        cout << "Rock." << endl;
        break;
    case PAPER:
        cout << "Paper." << endl;
        break;
    case SCISSORS:
        cout << "Scissors." << endl;
        break;
    }
    cout << "Lykomalos chose ";
    this_thread::sleep_for(chrono::milliseconds(1500));
    switch (computer) {
    case ROCK:
        cout << "Rock." << endl;
        break;
    case PAPER:
        cout << "Paper." << endl;
        break;
    case SCISSORS:
        cout << "Scissors." << endl;
        break;
    }
    cout << "-------------------------------" << endl;

    if (player == computer) {
        this_thread::sleep_for(chrono::milliseconds(500));
        cout << "It's a tie!" << endl;
    }
    else if ((player == ROCK && computer == SCISSORS) ||
        (player == PAPER && computer == ROCK) ||
        (player == SCISSORS && computer == PAPER)) {
        this_thread::sleep_for(chrono::milliseconds(500));
        cout << playerName << " wins this round!" << endl;
        aidenScore++;
    }
    else {
        this_thread::sleep_for(chrono::milliseconds(500));
        cout << "Lykomalos wins this round!" << endl;
        lykomalosScore++;
    }

    // Pause for a moment
    this_thread::sleep_for(chrono::seconds(1));
}

int getPlayerChoice()
{
    int choice;
    print_text_with_attributes("\tEnter your move: ", true);
    cin >> choice;

    // Validate the input
    while (choice < 1 || choice > 3) {
        cout << "\tInvalid move. Please enter 1 for Rock, 2 for Paper, or 3 for Scissors: ";
        cin >> choice;
    }

    return choice;
}

bool flag_lykomalos = false;

void play_rps_game()
{
    srand(time(0));

    string playerName = "Aiden";
    int aidenScore = 0;
    int lykomalosScore = 0;

    //skip_dialogues();

    if (!skip_dialogues()) {
        lines_tabs(2, 1);
        print_text_without_delay("                                                                                               ", true);
        lines_tabs(1, 1);
        print_text_with_attributes("  Aiden walks through the eerie woods. Suddenly, the trees rustle behind him.                  ", true);
        lines_tabs(1, 1);
        print_text_with_attributes("  Aiden, feeling a bit uneasy, turns back and stammers, 'Who's there? Show yourself!'          ", true);
        lines_tabs(1, 1);
        print_text_with_attributes("  A whimsical creature emerges from the tree under which Aiden is standing.                    ", true);
        lines_tabs(1, 1);
        print_text_with_attributes("  It's Lykomalos, the part fox, part lion wanderer in the forest.                              ", true);
        lines_tabs(1, 1);
        print_text_with_attributes("  Aiden, still jittery, mutters, 'You nearly gave me a heart attack!'                          ", true);
        lines_tabs(1, 1);
        print_text_with_attributes("                                                                                               ", true);
        lines_tabs(1, 1);
        print_text_with_attributes("  'Arent you a sight for sore eyes. I'm Lykomalos. Traveler, you've stumbled                   ", true);
        lines_tabs(1, 1);
        print_text_with_attributes("  into my terrain of the forest. I challenge you to a game of rock, paper, scissors.           ", true);
        lines_tabs(1, 1);
        print_text_with_attributes("  Best of five. What do you say?' Aiden, with a nervous smile, agrees to the challenge.        ", true);
        lines_tabs(1, 1);
        print_text_without_delay("                                                                                             ", true);
        lines_tabs(1, 1);
        print_text_with_attributes("  Lykomalos adds, 'Just a heads up, loser buys the dinner. And by dinner, I mean...            ", true);
        lines_tabs(1, 1);
        print_text_with_attributes("  uh... you might be on the menu.' Aiden gulps, 'Wait, what?....'                              ", true);
        lines_tabs(1, 1);
        print_text_without_delay("                                                                                               ", true);
        _getch();

    }
    else {
        lines_tabs(2, 1);
        print_text_without_delay("                                                                                         ", true);
        lines_tabs(1, 1);
        print_text_without_delay("  Aiden walks through the eerie woods. Suddenly, the trees rustle behind him.            ", true);
        lines_tabs(1, 1);
        print_text_without_delay("  Aiden, feeling a bit uneasy, turns back and stammers, 'Who's there? Show yourself!'    ", true);
        lines_tabs(1, 1);
        print_text_without_delay("  A whimsical creature emerges from the tree under which Aiden is standing.              ", true);
        lines_tabs(1, 1);
        print_text_without_delay("  It's Lykomalos, the part fox, part lion wanderer in the forest.                        ", true);
        lines_tabs(1, 1);
        print_text_without_delay("  Aiden, still jittery, mutters, 'You nearly gave me a heart attack!'                    ", true);
        lines_tabs(1, 1);
        print_text_without_delay("                                                                                         ", true);
        lines_tabs(1, 1);
        print_text_without_delay("  'Arent you a sight for sore eyes. I'm Lykomalos. Traveler, you've stumbled             ", true);
        lines_tabs(1, 1);
        print_text_without_delay("  into my terrain of the forest. I challenge you to a game of rock, paper, scissors.     ", true);
        lines_tabs(1, 1);
        print_text_without_delay("  Best of five. What do you say?' Aiden, with a nervous smile, agrees to the challenge.  ", true);
        lines_tabs(1, 1);
        print_text_without_delay("                                                                                         ", true);
        lines_tabs(1, 1);
        print_text_without_delay("  Lykomalos adds, 'Just a heads up, loser buys the dinner. And by dinner, I mean...      ", true);
        lines_tabs(1, 1);
        print_text_without_delay("  uh... you might be on the menu.' Aiden gulps, 'Wait, what?....'                        ", true);
        lines_tabs(1, 1);
        print_text_without_delay("                                                                                         ", true);
        _getch();
    }
    loading_screen();

    while (aidenScore < 3 && lykomalosScore < 3) {
        clear_screen();

        display_rps_menu(playerName);

        if (aidenScore <= lykomalosScore)
            getRandomLykomalosVoiceLine();
        else
            getRandomAidenVoiceLine();

        // Player's turn
        int playerChoice = getPlayerChoice();

        // Lykomalos's turn
        int lykomalosChoice = rand() % 3 + 1; // Random choice for Lykomalos

        clear_screen();
        display_rps_menu(playerName);

        // Determine the winner for the RPS game
        determine_winner(playerName, playerChoice, lykomalosChoice, aidenScore, lykomalosScore);

        // Pause for a moment
        this_thread::sleep_for(chrono::seconds(1));

        if (aidenScore <= 3 && lykomalosScore <= 3) {
            cout << invert_color << "\n\n\nCurrent Score" << reset_color << " -                   " << invert_color << bold << color[5] << " " << playerName << " " << reset_color << ": " << color[5] << " " << aidenScore << " " << reset_color
                << " | " << invert_color << bold << color[0] << " Lykomalos: " << reset_color << " " << color[0] << lykomalosScore << reset_color << endl;

            _getch();
        }
    }

    if (aidenScore == 3) {
        cout << invert_color << bold << color[5] << playerName << " wins the game!" << reset_color << endl;
        flag_lykomalos = true;
    }
    else {
        cout << invert_color << bold << color[0] << "Lykomalos wins the game!" << reset_color << endl;
        print_text_with_attributes("\n\tLykomalos gives a haughty look to Aiden", true, true, false, color[2]);
        print_text_with_attributes("\n\t\"I will let you pass traveler, no one has managed to beat me\"", true, true, false, color[2]);
        print_text_with_attributes("\n\t\"I didnt expect you to beat me either. Here are 10 coins for playing with me", true, true, false, color[2]);
    }
}

void update_player_stats(bool level_end)
{
    if (level_end)
    {
        player_health += 10;
        healing_spells += 2;
        lightning_spells += 4;
        if (level_counter >= 3)
        {
            rage_spells++;
        }
        player_attack_power += 10;
        player_healing_power += 5;
        player_lightning_power += 10;
    }
}

void damage_report_griffin(string attackMode, int damageInflicted, int playerHealth, int monsterHealth, bool is_monster = false, string name = "monster") {
    lines_tabs(1, 5);
    if (!is_monster)
    {
        print_text_with_attributes("Aiden's Turn", true, false, false, color[5]);
        lines_tabs(1, 1);
        cout << "+------------------+------------------+------------------+------------------+" << endl;
        lines_tabs(0, 1);
        cout << "| " << bold << color[2] << "Attack Mode      | Damage Inflicted | Player Health    | Monster Health   | " << reset_color << endl;
        lines_tabs(0, 1);
        cout << "+------------------+------------------+------------------+------------------+" << endl;
        lines_tabs(0, 1);
        cout << "   " << attackMode << "                " << damageInflicted << "                    " << playerHealth << "                 " << griffin_health << "                " << endl;
        lines_tabs(0, 1);
        cout << "+------------------+------------------+------------------+------------------+" << endl;
    }
    else {
        print_text_with_attributes(griffin_name + "'s Turn", true, false, false, color[4]);
        lines_tabs(1, 1);
        cout << "+------------------+------------------+------------------+------------------+" << endl;
        lines_tabs(0, 1);
        cout << "| " << bold << color[4] << "Attack Mode      | Damage Inflicted | Player Health    | Monster Health   | " << reset_color << endl;
        lines_tabs(0, 1);
        cout << "+------------------+------------------+------------------+------------------+" << endl;
        lines_tabs(0, 1);
        cout << "   " << attackMode << "                " << damageInflicted << "                    " << playerHealth << "                 " << monsterHealth << "                " << endl;
        lines_tabs(0, 1);
        cout << "+------------------+------------------+------------------+------------------+" << endl;
    }
}

void display_inventory_griffin() {
    // Display header
    lines_tabs(4, 2);
    print_text_with_attributes("Current Inventory and Status", true, false, false, color[6]);
    lines_tabs(1, 0);

    // Display player and harpy health in a table
    lines_tabs(0, 1);
    cout << "+--------------------------+------------------+" << endl;
    lines_tabs(0, 1);
    cout << "| " << bold << color[2] << "Player Health" << reset_color << "        | " << bold << color[4] << "Griffin Health" << reset_color << "       |" << endl;
    lines_tabs(0, 1);
    cout << "+--------------------------+------------------+" << endl;
    lines_tabs(0, 1);
    cout << "| " << invert_color << color[2] << player_health << "                 " << reset_color << " | " << invert_color << color[4] << griffin_health << "                 " << reset_color << "  |" << endl;
    lines_tabs(0, 1);
    cout << "+--------------------------+------------------+" << endl;
    // Display attack modes in a table
    lines_tabs(1, 1);
    cout << "+--------------------------+------------------+" << endl;
    lines_tabs(0, 1);
    cout << "| " << bold << color[2] << "Player Attack Modes" << reset_color << "  | " << bold << color[4] << "Griffin Attack Modes" << reset_color << " |" << endl;
    lines_tabs(0, 1);
    cout << "+--------------------------+------------------+" << endl;
    lines_tabs(0, 1);
    cout << "|    " << color[2] << "Attack With Sword" << reset_color << " |    " << color[4] << "Power Claw" << reset_color << "        |" << endl;
    lines_tabs(0, 1);
    cout << "|    " << color[2] << "Roll Away" << reset_color << "         |    " << color[4] << "Screech" << reset_color << "           |" << endl;
    lines_tabs(0, 1);
    cout << "|    " << color[2] << "Cast A Spell" << reset_color << "      |                      |" << endl;
    lines_tabs(0, 1);
    cout << "+--------------------------+------------------+" << endl;
    lines_tabs(0, 1);
}

void replenish_health()
{
    player_health = player_level_health[level_counter - 1];
}

void display_level_end_inventory()
{
    replenish_health();
    update_player_stats(true);
    display_rewards_inventory();
    display_spell_inventory();
    display_weapon_inventory();
}

bool play_level_1()
{
    loading_screen();

    if (!i_make_and_display_riddles())
    {
        // Player failed the riddles, go back to the start of the level
        _getch();
        print_text_with_attributes("\n\n\tYou failed to answer the riddles. Returning to the start of the level.\n", true, false, false, color[0]);
        return false;
    }

    _getch();
    clear_screen();
    print_text_with_attributes("\n\n\n\n\n\n\tCongratulations. You answered the riddles correctly.\n\tYou have been rewarded by the fury with a magical scroll", true, true, false, color[2]);
    fury_scroll++;
    print_text_with_attributes("\n\tPrepare for your next challenge", true, true, false, color[2]);
    _getch();

    loading_screen();

    if (!fight_harpy())
    {
        // Player failed to defeat the harpy, go back to the start of the level
        print_text_with_attributes("\n\n\tYou were defeated by the Harpy. Returning to the start of the level.\n", true, false, false, color[0]);
        return false;
    }

    print_text_with_attributes("\n\tYou have been rewarded with a Harpy Feather", true, true);
    harpy_feather++;
    _getch();
    clear_screen();

    loading_screen();

    play_rps_game();

    _getch();
    clear_screen();

    if (flag_lykomalos)
    {
        print_text_with_attributes("\n\n\n\tYou have been awarded 30 coins by a gruesome looking Lykomalos, \n\twho congratulates your victory and walks off", true, true, false, color[5]);
        lykomalos_coins += 30;
    }
    else
    {
        lykomalos_coins += 10;
    }
    //display_rewards_inventory();
    _getch();
    return true;
}

void display_battle_status_griffin() {
    lines_tabs(1, 1);
    cout << invert_color << player_name << "'s Health: " << player_health << " ";
    lines_tabs(1, 1);
    cout << griffin_name << "'s Health: " << griffin_health << " " << reset_color;
}



void player_turn_griffin() {
    lines_tabs(2, 1);
    print_text_with_attributes("Aiden's Turn: ", true, false, false, color[1]);
    lines_tabs(1, 1);
    print_text_with_attributes("Aiden braces himself for the griffin's attack ", true);
    lines_tabs(2, 1);

    cout << "Choose your action:";
    cout << "\n\t1. Attack With Sword"
        << "\n\t2. Cast A Spell";
    cout << "\n\tEnter your choice: ";
    int choice;
    cin >> choice;
    bool valid_choice = false;

    switch (choice) {
    case 1: {
        int player_damage = perform_attack(player_attack_power);
        /*lines_tabs(1, 1);
        print_text_with_attributes("Aiden has attacked the Harpy for: ", true);
        cout << invert_color << " " << player_damage << " damage " << reset_color;
        */
        griffin_health -= player_damage;
        damage_report_griffin("Sword", player_damage, player_health, griffin_health);
        break;
    }
    case 2: {
        display_spell_inventory();
        cout << "\n\tChoose a spell:";
        lines_tabs(1, 1);
        cout << color[2] << "1. Cast a healing spell";
        reset_text_attributes();
        lines_tabs(1, 1);
        cout << color[5] << "2. Cast a lightning spell";
        reset_text_attributes();
        cout << "\n\tEnter your choice: ";
        int spell_choice;
        cin >> spell_choice;

        switch (spell_choice)
        {
        case 1:
        {
            if (healing_spells > 0)
            {
                int player_healing_amount = perform_healing_spell(player_healing_power);
                player_health += player_healing_amount;
                lines_tabs(1, 1);
                damage_report_griffin("Spell", 0, player_health, griffin_health);
                /*print_text_without_delay("Aiden casts a healing spell and gains ", true, false, false, color[2]);
                cout << invert_color << color[2] << player_healing_amount << " health!" << reset_color;
                */
                valid_choice = true;
                healing_spells--;
            }
            else
                print_text_with_attributes("\n\t" + player_name + " is out of healing spells. Choose other options", true, false, false, color[4]);
            break;
        }
        case 2:
        {
            if (lightning_spells > 0)
            {
                int player_lightning_damage = perform_lightning_spell(player_lightning_power);
                griffin_health -= player_lightning_damage;
                damage_report_griffin("Spell", player_lightning_damage, player_health, griffin_health);
                /*print_text_with_attributes(player_name + " casts a lightning spell on the harpy for " + to_string(player_lightning_damage) + " damage", true, false, false, color[5]);
                cout << "\n\t" << player_name << " casts a lightning spell on the harpy for " << player_lightning_damage << " damage.";
                */
                valid_choice = true;
                lightning_spells--;
            }
            else
            {
                print_text_with_attributes("\n\t" + player_name + " is out of lightning spells. Choose other options", true, false, false, color[4]);
            }
            break;
        }
        default:
        {
            print_text_with_attributes("\n\tMagic is not in the tools but in the hands of the one who wields them. \n\tMistakes illuminate the path to mastery.", true, false, false, color[4]);
            break;
        }
        break;
        }
        break;
    default: {
        print_text_with_attributes("\n\tLike a misdirected incantation or an ill - fated swing of the sword, \n\ta wrong choice echoes lessons to heed and paths to reconsider in the journey of wisdom.", true, false, false, color[4]);
        break;
    }
    }
    }

}

void griffin_turn() {
    // Randomize the griffin's attack mode
    int attack_choice = rand() % 2;

    if (attack_choice == 0) {
        int griffin_damage = perform_attack(griffin_attack_power_claw);
        player_health -= griffin_damage;
        damage_report_griffin("Power Claw", griffin_damage, player_health, griffin_health, true, griffin_name);
        //lines_tabs(1, 1);
        //print_text_with_attributes("The Harpy strikes Aiden with its talons, dealing " + to_string(harpy_damage) + " damage", true, false, false, color[0]);
        //cout << invert_color << " " << harpy_damage << " damage " << reset_color;
    }
    else {
        int griffin_damage = perform_attack(griffin_attack_power_screech);
        player_health -= griffin_damage;
        damage_report_griffin("Screech", griffin_damage, player_health, griffin_health, true, griffin_name);
        //lines_tabs(1, 1);
        //print_text_with_attributes("The Harpy unleashes a gust of wind, dealing " + to_string(harpy_damage) + " damage", true, false, false, color[0]);
        //cout << invert_color << " " << harpy_damage << " damage " << reset_color;
    }
}

bool fight_griffin()
{
    srand(time(0));

    lines_tabs(2, 1);
    print_text_without_delay("                                                                                 ", true);
    lines_tabs(1, 1);
    print_text_with_attributes("  As Aiden ventures further into the enchanted forest, a mighty griffin appears  ", true);
    lines_tabs(1, 1);
    print_text_with_attributes("  with the body of a lion and the head of an eagle. The Griffin locks eyes with  ", true);
    lines_tabs(1, 1);
    print_text_with_attributes("  Aiden, ready to engage in a fierce battle. Aiden readies his weapon.           ", true);
    lines_tabs(1, 1);
    print_text_without_delay("                     Prepare for the clash of mythical beings!                   ", true);
    lines_tabs(1, 1);
    print_text_without_delay("                                                                                 ", true);

    //display_spell_inventory();
    //display_weapon_inventory();
    display_inventory_griffin();
    _getch();
    loading_screen();
    // Aiden's turn is first
    while (player_health > 0 && griffin_health > 0) {
        player_turn_griffin();
        if (griffin_health <= 0) {
            cout << "\t";
            random_battle_voicelines(false, true);
            return true;
            break;
        }
        //display_battle_status();
        lines_tabs(1, 0);
        griffin_turn();
        if (player_health <= 0) {
            cout << "\t";
            random_battle_voicelines(false, false);
            return false;
            break;
        }
        display_battle_status_griffin();
        _getch();
        system("cls");
    }
}

void displaying_maze(int position_x, int position_y) {
    system("cls");
    cout << "#######" << endl;
    cout << "#";
    if (position_x == 1 && position_y == 3)
        cout << "P";
    else
        cout << " ";
    cout << "#";
    if (position_x == 3 && position_y == 3)
        cout << "P";
    else
        cout << " ";
    cout << "#";
    if (position_x == 5 && position_y == 3)
        cout << "P";
    else
        cout << "E";
    cout << "#";
    cout << endl;
    cout << "#";
    if (position_x == 1 && position_y == 2)
        cout << "P";
    else
        cout << " ";
    cout << "#";
    if (position_x == 3 && position_y == 2)
        cout << "P";
    else
        cout << " ";
    cout << "#";
    if (position_x == 5 && position_y == 2)
        cout << "P";
    else
        cout << " ";
    cout << "#";
    cout << endl;
    cout << "#";
    if (position_x == 1 && position_y == 1)
        cout << "P";
    else
        cout << " ";
    if (position_x == 2 && position_y == 1)
        cout << "P";
    else
        cout << " ";
    if (position_x == 3 && position_y == 1)
        cout << "P";
    else
        cout << " ";
    if (position_x == 4 && position_y == 1)
        cout << "P";
    else
        cout << " ";
    if (position_x == 5 && position_y == 1)
        cout << "P";
    else
        cout << " ";
    cout << "#";
    cout << endl;
    cout << "#######" << endl;
}

//Checking if the player hit a wall

bool checking_alive(int position_x, int position_y) {
    bool alive = true;
    if (position_y == 0 || position_y == 4)
        alive = false;
    if (position_x == 0 || position_x == 6)
        alive = false;
    if ((position_y == 2 || position_y == 3) && (position_x == 2 || position_x == 4))
        alive = false;

    return alive;
}

//Checking if the player won!

bool checking_win(int position_x, int position_y) {
    bool win = false;
    if (position_x == 5 && position_y == 3)
        win = true;
    return win;
}

bool check_answer(const string& player_answer, const string& correct_answer) {
    // Convert both answers to lowercase for case-insensitive comparison
    string lowercase_player_answer = player_answer;
    string lowercase_correct_answer = correct_answer;

    for (char& c : lowercase_player_answer)
        c = tolower(c);

    for (char& c : lowercase_correct_answer)
        c = tolower(c);

    return lowercase_player_answer == lowercase_correct_answer;
}

void provide_riddle()
{
    int tries = 1;
    bool answered_correctly = false;
    const string correct_answer = "gaia";
    string player_response;

    while (!answered_correctly)
    {
        if (tries == 1)
        {
            print_text_with_attributes("\n\n\n\t\tPuck's Riddle: ", true);
            print_text_with_attributes("\t\tMy name means 'Earth,' \n\t\tand I am the personification of the Earth itself", true);
            print_text_with_attributes("\n\t\tWho am I?", true);
            string response;
            cout << "Your answer: ";
            cin >> response;  // Allowing spaces in the response
            player_response = response;
            if (check_answer(player_response, correct_answer))
            {
                print_text_with_attributes("\n\n\t\tPuck: Well done, adventurer! You have wisdom as vast as the ancient seas. Continue your journey!", true);
                answered_correctly = true;  // Player answered correctly
                puck_token++;
            }
            else {
                print_text_with_attributes("\n\n\t\tPuck: Oh, not quite right!. Let me offer you another chance.", true);
                tries++;
            }
        }
        else if (tries == 2)
        {
            print_text_with_attributes("\n\n\t\tPuck's Riddle: ", true);
            print_text_with_attributes("\t\tMany gods and goddesses, including Zeus, \n\t\ttrace their lineage back to me.", true);
            print_text_with_attributes("\n\t\tWho am I?", true);
            string response;
            cout << "Your answer: ";
            cin >> response;  // Allowing spaces in the response
            player_response = response;

            if (check_answer(player_response, correct_answer))
            {
                print_text_with_attributes("\n\n\t\tPuck: Well done, adventurer! You have wisdom as vast as the ancient seas. \n\t\tContinue your journey!\n\t\tPuck gives Aiden a token of appreciation", true);
                answered_correctly = true;  // Player answered correctly
                puck_token;
            }
            else {
                print_text_with_attributes("\n\n\t\tPuck: Oh, not quite right!", true);
                return;
            }
        }
    }
    win = true;
}

void play_maze_game()
{
    int chance = 1;
    int initial_x = 1;
    int initial_y = 3;

    lines_tabs(3, 1);
    print_text_without_delay("                                                                      ", true, true);
    lines_tabs(1, 1);
    print_text_with_attributes("  Beaming at his victory, Aiden made his way further into the forest  ", true, true);
    lines_tabs(1, 1);
    print_text_with_attributes("   He was really excited at his prospects of finding his home         ", true, true);
    lines_tabs(1, 1);
    print_text_with_attributes("      Suddenly the ground below him gave way and he fell down         ", true, true);
    lines_tabs(1, 1);
    print_text_with_attributes("  After what seemed like an eternity, Aiden landed on the cold stone  ", true, true);
    lines_tabs(1, 1);
    print_text_with_attributes("            floor. He got up, bruised and injured                     ", true, true);
    lines_tabs(1, 1);
    print_text_with_attributes("  Infront of him a bright light appears and makes its way to Aiden    ", true, true);
    lines_tabs(1, 1);
    print_text_with_attributes("   Its a nymph. She tells Aiden that he has to venture into a maze    ", true, true);
    lines_tabs(1, 1);
    print_text_with_attributes("  and find his way out, in order to survive or he will be trapped     ", true, true);
    lines_tabs(1, 1);
    print_text_without_delay("                                                                      ", true, true);
    lines_tabs(3, 1);
    print_text_without_delay("    Due to the fall, Aiden has lost 20 health points    ", true, true, false, color[2]);
    player_health -= 20;
    lines_tabs(3, 1);
    _getch();

    displaying_maze(initial_x, initial_y);

    while (alive && win == false) {
        char op;
        cout << "Move (W/A/D/S for up/left/down/right): ";
        cin >> op;

        switch (op) {

        case 'W':
            initial_y += 1;
            displaying_maze(initial_x, initial_y);
            alive = checking_alive(initial_x, initial_y);
            win = checking_win(initial_x, initial_y);
            break;
        case 'D':
            initial_y -= 1;
            displaying_maze(initial_x, initial_y);
            alive = checking_alive(initial_x, initial_y);
            win = checking_win(initial_x, initial_y);
            break;
        case 'S':
            initial_x += 1;
            displaying_maze(initial_x, initial_y);
            alive = checking_alive(initial_x, initial_y);
            win = checking_win(initial_x, initial_y);
            break;
        case 'A':
            initial_x -= 1;
            displaying_maze(initial_x, initial_y);
            alive = checking_alive(initial_x, initial_y);
            win = checking_win(initial_x, initial_y);
            break;
        case 'w':
            initial_y += 1;
            displaying_maze(initial_x, initial_y);
            alive = checking_alive(initial_x, initial_y);
            win = checking_win(initial_x, initial_y);
            break;
        case 'd':
            initial_y -= 1;
            displaying_maze(initial_x, initial_y);
            alive = checking_alive(initial_x, initial_y);
            win = checking_win(initial_x, initial_y);
            break;
        case 's':
            initial_x += 1;
            displaying_maze(initial_x, initial_y);
            alive = checking_alive(initial_x, initial_y);
            win = checking_win(initial_x, initial_y);
            break;
        case 'a':
            initial_x -= 1;
            displaying_maze(initial_x, initial_y);
            alive = checking_alive(initial_x, initial_y);
            win = checking_win(initial_x, initial_y);
            break;
        default:
            cout << "Wrong input!" << endl;

        }
    }

    if (!alive)
    {
        // Scenario when Aiden crashes into a wall and Puck appears
        print_text_with_attributes("\n\n\tAs Aiden took a wrong turn, he crashed into a solid wall with a thud!", true, false, false, "\033[1;31m");
        cout << endl;
        print_text_with_attributes("\n\tSuddenly, a mischievous voice echoed through the maze:", false, true, false, "\033[1;35m");
        cout << endl;
        print_text_with_attributes("\n\tPuck: Oh dear adventurer, lost in the maze! Fear not, for Puck is here to play!", false, false, false, "\033[1;35m");
        cout << endl;
        print_text_with_attributes("\n\tPuck: A riddle I give, a path you shall find. Answer true, and leave this maze behind!", false, false, false, "\033[1;35m");
        cout << endl;
        _getch();
        clear_screen();
        provide_riddle();
    }
    if (win == true) {
        print_text_with_attributes("Aiden has successfully escaped the maze", true);
        calliope_fabric++;
    }
    else
    {
        print_text_with_attributes("Aiden is trapped in the maze for eternity", true);
    }
}

bool play_level_2()
{
    loading_screen();

    play_maze_game();

    loading_screen();

    if (!i_make_and_display_riddles())
    {
        // Player failed the riddles, go back to the start of the level
        _getch();
        print_text_with_attributes("\n\n\tYou failed to answer the riddles. Returning to the start of the level.\n", true, false, false, color[0]);
        return false;
    }

    _getch();
    clear_screen();
    print_text_with_attributes("\n\n\n\n\n\n\tCongratulations. You answered the riddles correctly.\n\tYou have been rewarded by the fury with a magical scroll", true, true, false, color[2]);
    fury_scroll++;
    print_text_with_attributes("\n\tPrepare for your next challenge", true, true, false, color[2]);
    _getch();

    loading_screen();

    if (!fight_griffin())
    {
        // Player failed to defeat the griffin, go back to the start of the level
        print_text_with_attributes("\n\n\tYou were defeated by the Griffin. Returning to the start of the level.\n", true, false, false, color[0]);
        return false;
    }

    print_text_with_attributes("\n\tYou have been rewarded with a Griffin Claw", true, true);
    griffin_claw++;
    return true;
}

void display_inventory_chimera() {
    // Display header
    lines_tabs(4, 2);
    print_text_with_attributes("Current Inventory and Status", true, false, false, color[6]);
    lines_tabs(1, 0);

    // Display player and chimera health in a table
    lines_tabs(0, 1);
    cout << "+--------------------------+------------------+" << endl;
    lines_tabs(0, 1);
    cout << "| " << bold << color[2] << "Player Health" << reset_color << "        | " << bold << color[5] << "Chimera Health" << reset_color << "       |" << endl;
    lines_tabs(0, 1);
    cout << "+--------------------------+------------------+" << endl;
    lines_tabs(0, 1);
    cout << "| " << invert_color << color[2] << player_health << "                 " << reset_color << " | " << invert_color << color[5] << chimera_health << "                 " << reset_color << "  |" << endl;
    lines_tabs(0, 1);
    cout << "+--------------------------+------------------+" << endl;
    // Display attack modes in a table
    lines_tabs(1, 1);
    cout << "+--------------------------+------------------+" << endl;
    lines_tabs(0, 1);
    cout << "| " << bold << color[2] << "Player Attack Modes" << reset_color << "  | " << bold << color[5] << "Chimera Attack Modes" << reset_color << " |" << endl;
    lines_tabs(0, 1);
    cout << "+--------------------------+------------------+" << endl;
    lines_tabs(0, 1);
    cout << "|    " << color[2] << "Attack With Sword" << reset_color << " |    " << color[5] << "Power Claw" << reset_color << "        |" << endl;
    lines_tabs(0, 1);
    cout << "|    " << color[2] << "Roll Away" << reset_color << "         |    " << color[5] << "Fire Breath" << reset_color << "        |" << endl;
    lines_tabs(0, 1);
    cout << "|    " << color[2] << "Cast A Spell" << reset_color << "      |                      |" << endl;
    lines_tabs(0, 1);
    cout << "+--------------------------+------------------+" << endl;
    lines_tabs(0, 1);
}

void damage_report_chimera(string attackMode, int damageInflicted, int playerHealth, int enemy_health, bool is_monster = false, string name = "monster") {
    lines_tabs(1, 5);
    if (!is_monster)
    {
        print_text_with_attributes("Aiden's Turn", true, false, false, color[6]);
        lines_tabs(1, 1);
        cout << "+------------------+------------------+------------------+------------------+" << endl;
        lines_tabs(0, 1);
        cout << "| " << bold << color[2] << "Attack Mode      | Damage Inflicted | Player Health    | Monster Health   | " << reset_color << endl;
        lines_tabs(0, 1);
        cout << "+------------------+------------------+------------------+------------------+" << endl;
        lines_tabs(0, 1);
        cout << "   " << attackMode << "                " << damageInflicted << "                    " << playerHealth << "                 " << enemy_health << "                " << endl;
        lines_tabs(0, 1);
        cout << "+------------------+------------------+------------------+------------------+" << endl;
    }
    else {
        print_text_with_attributes("Chimera's Turn", true, false, false, color[5]);
        lines_tabs(1, 1);
        cout << "+------------------+------------------+------------------+------------------+" << endl;
        lines_tabs(0, 1);
        cout << "| " << bold << color[5] << "Attack Mode      | Damage Inflicted | Player Health    | Monster Health   | " << reset_color << endl;
        lines_tabs(0, 1);
        cout << "+------------------+------------------+------------------+------------------+" << endl;
        lines_tabs(0, 1);
        cout << "   " << attackMode << "                " << damageInflicted << "                    " << playerHealth << "                 " << enemy_health << "                " << endl;
        lines_tabs(0, 1);
        cout << "+------------------+------------------+------------------+------------------+" << endl;
    }
}

void player_turn_chimera() {
    lines_tabs(2, 1);
    print_text_with_attributes("Aiden's Turn: ", true, false, false, color[1]);
    lines_tabs(1, 1);
    print_text_with_attributes("Aiden braces himself for battle ", true);
    lines_tabs(2, 1);
    cout << "Choose your action:";
    cout << "\n\t1. Attack With Sword"
        << "\n\t2. Cast A Spell"
        << "\n\t3. Roll Away";
    if (is_spear_available())
        cout << "\n\t4. Throw Spear";
    cout << "\n\t. Enter your choice: ";
    int choice;
    cin >> choice;

    switch (choice) {
    case 1: {
        int player_damage = perform_attack(player_attack_power);
        lines_tabs(1, 1);
        chimera_health = chimera_health - player_damage;
        damage_report_chimera("Sword", player_damage, player_health, chimera_health);
        break;
    }
    case 2: {
        display_spell_inventory();
        cout << "\n\tChoose a spell:";
        lines_tabs(1, 1);
        cout << color[2] << "1. Cast a healing spell";
        reset_text_attributes();
        lines_tabs(1, 1);
        cout << color[5] << "2. Cast a lightning spell";
        reset_text_attributes();
        cout << "\n\tEnter your choice: ";
        int spell_choice;
        cin >> spell_choice;

        switch (spell_choice) {
        case 1: {
            int player_healing_amount = perform_healing_spell(player_healing_power);
            player_health += player_healing_amount;
            lines_tabs(1, 1);
            damage_report_chimera("Spell", 0, player_health, chimera_health);
            break;
        }
        case 2: {
            int player_lightning_damage = perform_lightning_spell(player_lightning_power);
            chimera_health -= player_lightning_damage;
            damage_report_chimera("Spell", player_lightning_damage, player_health, chimera_health);
            break;
        }
        default: {
            cout << "\n\tMagic is not in the tools but in the hands of the one who wields them. \n\tMistakes illuminate the path to mastery.";
            break;
        }
        }
        break;
    }
    case 3:
        perform_roll_away();
        damage_report_chimera("Roll Away", 0, player_health, chimera_health);
        return; // Skip Chimera's turn if Aiden rolls away
    case 4: {
        if (is_spear_available()) {
            // Aiden throws a spear
            int damage_inflicted = perform_spear_throw();
            chimera_health -= damage_inflicted;
            lines_tabs(1, 1);
            damage_report_chimera("Spear", damage_inflicted, player_health, chimera_health);
        }
        else {
            cout << "\n\tThe spear is not ready. Choose another action.";
        }
        break;
    }
    default: {
        cout << "\n\tLike a misdirected incantation or an ill-fated swing of the sword, \n\ta wrong choice echoes lessons to heed and paths to reconsider in the journey of wisdom.";
        break;
    }
    }
    reduce_spear_cooldown();
}

void chimera_turn() {
    if (chimera_fire_mode) {
        int chimera_fire_damage = (rand() % (chimera_attack_power_fire - 15 + 1)) + 15;
        player_health -= chimera_fire_damage;
        lines_tabs(1, 1);
        damage_report_chimera("Fire Damage", chimera_fire_damage, player_health, chimera_health, true, "chimera");
    }
    else {
        int chimera_damage = perform_attack(chimera_attack_power_claws);
        player_health -= chimera_damage;
        lines_tabs(1, 1);
        damage_report_chimera("Claw Damage", chimera_damage, player_health, chimera_health, true, "chimera");
    }

    // Toggle to the other mode for the next turn
    chimera_fire_mode = !chimera_fire_mode;
}

bool fight_chimera()
{
    srand(time(0));

    lines_tabs(4, 1);
    print_text_without_delay("                                                                                                        ", true, true);
    lines_tabs(1, 1);
    print_text_with_attributes("  Ahead of Aiden is a creature with the body of a lion, the head of a goat, and the tail of a serpent.  ", true, true);
    lines_tabs(1, 1);
    print_text_with_attributes("                              It's the mighty Chimera!                                                  ", true, true);
    lines_tabs(1, 1);
    print_text_with_attributes("             The Chimera eyes Aiden with a menacing glare and prepares to strike.                       ", true, true);
    lines_tabs(1, 1);
    print_text_without_delay("                                                                                                        ", true, true);

    display_inventory_chimera();
    _getch();
    clear_screen();

    while (player_health > 0 && chimera_health > 0) {
        // Aiden's turn
        player_turn_chimera();
        if (chimera_health <= 0) {
            cout << "\t";
            random_battle_voicelines(false, true);
            _getch();
            return true;
            break;
        }
        lines_tabs(1, 0);

        // Chimera's turn
        chimera_turn();
        if (player_health <= 0) {
            cout << "\t";
            random_battle_voicelines(false, false);
            _getch();
            return false;
            break;
        }
        lines_tabs(1, 0);

        _getch();
        clear_screen();
    }
}

string words[] = {
       "hephaestus",
       "uranus",
       "gaia"
};

const string hints_hangman_word_1[] = {
    "I am a god associated with craftsmanship and technology.",
    "My Roman counterpart is Vulcan.",
    "I am one of the twelve Olympian gods.",
    "I am often depicted as a blacksmith.",
    "My symbols include a hammer and anvil.",
    "I am the son of Zeus and Hera.",
    "I forged powerful weapons for the gods, including Zeus' thunderbolt.",
    "I am married to Aphrodite, the goddess of love and beauty."
};

const string hints_hangman_word_2[] = {
    "I am a primordial goddess, one of the first beings in existence.",
    "My name means 'Earth,' and I am the personification of the Earth itself.",
    "I am the mother of the Titans, the Cyclopes, and the Hecatoncheires.",
    "I am often depicted as a maternal figure, nurturing and protective.",
    "My Roman counterpart is Terra.",
    "I played a crucial role in the creation of the universe and its natural order.",
    "I am connected to the cycles of life, growth, and fertility.",
    "Many gods and goddesses, including Zeus, trace their lineage back to me."
};

const string hints_hangman_word_3[] = {
    "I am a primordial god, one of the first beings in existence.",
    "My name means 'Sky,' and I am the personification of the sky itself.",
    "I am the father of the Titans, the Cyclopes, and the Hecatoncheires.",
    "I am the husband and son of Gaia, the Earth.",
    "I played a crucial role in the creation of the universe and its cosmic order.",
    "My Roman counterpart is Caelus.",
    "I am associated with the celestial and the infinite expanse above.",
    "The planets in our solar system are named after me."
};

string get_word() {
    return words[rand() % 3];
}

void draw_hangman(int lives) {
    cout << "   + - - - +" << endl;
    cout << "   |       |" << endl;
    if (lives < 6) {
        cout << "   O       |" << endl;
    }
    else {
        cout << "           |" << endl;
    }
    if (lives == 4) {
        cout << "   |       |" << endl;
    }
    else if (lives == 3) {
        cout << " / |       |" << endl;
    }
    else if (lives < 3) {
        cout << " / | \\     |" << endl;
    }
    else {
        cout << "           |" << endl;
    }
    if (lives == 1) {
        cout << "  /        |" << endl;
    }
    else if (lives == 0) {
        cout << "  / \\      |" << endl;
    }
    else {
        cout << "           |" << endl;
    }

    cout << "=============" << endl;
}

void hints_for_chosen_word()
{
    print_text_with_attributes("\n\n\tALRIGHTYY HUMAN, YOU BEE' SO STOOPID. YUUU STOOPIDER' THAN ME", true, false, false, color[5]);
    print_text_with_attributes("\n\tMee give u hints, but me no spek word. Nauuu Yu listen' carfulleee", true, false, false, color[5]);
    print_text_with_attributes("\n\tAlrightyy, me think: ", true, false, false, color[5]);
    print_text_with_attributes("\n\t.", true, false, false, color[5], 200);
    print_text_with_attributes("\n\t.", true, false, false, color[5], 200);
    print_text_with_attributes("\n\t.", true, false, false, color[5], 200);
    print_text_with_attributes("\n\t.\n\n\n\t", true, false, false, color[5], 200);
    if (get_word() == words[0])
        print_text_with_attributes(hints_hangman_word_1[rand() % 8], true, true, false, color[2]);
    else if (get_word() == words[1])
        print_text_with_attributes(hints_hangman_word_2[rand() % 8], true, true, false, color[2]);
    else
        print_text_with_attributes(hints_hangman_word_1[rand() % 8], true, true, false, color[2]);
    print_text_with_attributes("\n\n\tYASSSS, THEE SHUD DO. NAUUU BE LESS STOOPID", true, false, false, color[5]);
    cin.get();
}

void initial_dialogues()
{
    lines_tabs(2, 1);
    print_text_without_delay("                                                                              ", true);
    print_text_without_delay("\n\t    As night falls, Aiden stumbles into an unusual discovery.                 \n\tHe looks for a source of water to replenish his thirst and heal his wounds.    ", true);
    print_text_without_delay("\n\tAiden notices the bright gold hue in the air. \n\tHe searches some more and finally collapses to the ground due to fatigue. \n\n\n\tHe crawls a few feet ahead in desperation and finds the huge footstep of a cyclops", true);
    print_text_without_delay("\n\tThe footstep is so huge that Aiden could hardly believe his eyes.", true);
    print_text_without_delay("\n\tIn desperation, Aiden follows the trail of footsteps, in his struggle to find a way to survive.", true);
    cin.get();
    clear_screen();

    //this_thread::sleep_for(chrono::milliseconds(1000));
    lines_tabs(2, 1);
    print_text_without_delay("\n\n\n\tAs Aiden continued his journey, his heartbeat echoed in his ears, \n\ta rhythm of both fear and determination. \n\tThe forest seemed to close in around him, \n\tand the air shimmered with an otherworldly golden glow, \n\tintensifying his sense of vulnerability", true);
    print_text_without_delay("\n\tA feeling of sheer terror grips Aiden, he had no idea of what challenge lied in front of him. \n\tAll he wanted was to survive, and to find his identity", true);
    print_text_without_delay("\n\tThe gold glow in the air seemed to intensify.", true);
    print_text_without_delay("\n\tIn the quiet of the enchanted forest, Aiden strained to hear the gentle sounds of water. \n\tFollowing the cyclops's footsteps, the noise became clearer, \n\tleading him to a hidden creek at last. \n\n\tThe moonlit clearing revealed a peaceful scene, \n\twith the water glistening in the soft light.", true);
    print_text_without_delay("\n\tAiden gulps down some water and cleans his wounds", true);
    cin.get();
    clear_screen();

    //this_thread::sleep_for(chrono::milliseconds(1000));
    lines_tabs(2, 1);
    print_text_without_delay("\n\t\"Well, looky here! What's this little human doin' in our neck of the woods ? \"", true);
    print_text_without_delay(" A voice behind Aiden boomed.\n\tAiden looked behind him, startled and before he could brace himself, \n\the was punched to the ground. ", true);
    print_text_without_delay("\"Looks like dinner wandered to us, this time.\"", true);
    print_text_without_delay("\n\tAiden could hear other cyclops laughing around him", true);

    // Cyclops camp dialogue
    lines_tabs(2, 1);
    print_text_without_delay("\n\tCyclops Leader: 'Well, well, well... Look what we have here. A puny human!'", true);
    print_text_without_delay(" *laughs*", true);
    print_text_without_delay("\n\tCyclops Leader: 'You thought you could wander into our territory unnoticed? Stupid human!'", true);
    print_text_without_delay("\n\t *others laugh*", true);
    print_text_without_delay("\n\tAiden is grabbed by the Cyclops and taken to their camp. \n\n\tThe smell of roasting meat fills the air, and Aiden sees a huge bull being cooked on a spit.", true);
    print_text_without_delay("\n\tCyclops Leader: 'Throw him into the dungeon! We'll decide what to do with him later.'", true);
    print_text_without_delay("\n\n\t *Aiden is thrown into a dark dungeon*", true);
    print_text_without_delay("\n\tIn the dungeon, Aiden notices a young Cyclops sitting in a corner. \n\tThe Cyclops seems different, perhaps friendlier than the others.", true);
    cin.get();
    clear_screen();

    // Dialogue with Tyson
    lines_tabs(4, 1);
    print_text_with_attributes("\n\tYoung Cyclops (Tyson): 'Hello, small human. I'm Tyson. What's your name?'", true, true, false, color[5]);
    lines_tabs(2, 1);
    print_text_with_attributes("'Aiden, Where are we?', Aiden exclaims in pain", true, true, false, color[2]);
    lines_tabs(2, 1);
    print_text_with_attributes("'tWe r in dee duneegons. Can't tuu see?', Tyson laughs", true, true, false, color[5]);
    lines_tabs(2, 1);
    print_text_with_attributes("'I need to find a way to escape. Help me and ill give you whatever I have", true, true, false, color[2]);
    lines_tabs(2, 1);
    print_text_with_attributes("'Fineee, play hangman with me. If yuu win, Tyson help yuu escape dis dunegon", true, true, false, color[5]);
    lines_tabs(2, 1);
    cin.get();
    clear_screen();
}

bool game_play(char name[]) {
    initial_dialogues();

    string word = get_word();
    int length = word.length() - 1;
    cout << length << endl;
    int lives = 6;
    bool guessed[] = { false,false,false,false,false };
    int correct = 0;
    while (true) {
        char ch;
        system("cls");
        draw_hangman(lives);

        for (int i = 0; i <= length; i++) {
            if (guessed[i] == true) {
                cout << word[i] << " ";
            }
            else {
                cout << "  ";
            }
        }
        cout << endl;
        for (int i = 0; i <= length; i++) {
            cout << "_ ";
        }
        cout << endl;
        if (correct == length + 1 || lives == 0) {
            break;
        }
        cout << "Enter guess: ";
        cin >> ch;

        if (ch >= 65 && ch <= 90) {
            ch += 32;
        }
        bool doesExist = false;
        for (int i = 0; i <= length; i++) {
            if (word[i] == ch && guessed[i] != true) {
                doesExist = true;
                guessed[i] = true;
                correct++;
                for (int j = 0; name[j] != '\0'; j++) {
                    char nameChar = name[j];
                    if (nameChar >= 65 && nameChar <= 90)
                        nameChar += 32;
                    if (nameChar == word[i] && lives < 6) {
                        cout << "Extra Life!" << endl;
                        lives++;
                        break;
                    }
                }
            }
        }
        if (doesExist == false)
            lives--;
        if (lives == 2 || lives == 1)
            hints_for_chosen_word();
    }
    flag_hangman = true;
    if (lives == 0)
    {
        cout << "Word was: " << word << endl;
        return false;
    }
    else
        return true;
}

bool play_hangman()
{
    srand(time(0));
    print_text_with_attributes("\n\tYoung Cyclops (Tyson): 'Hello, small human. I'm Tyson. What's your name?'\n\t", true, true, false, color[5]);
    char name[50];
    cout << invert_color << bold << color[2] << "\n\n\n\n\t\t\t\tEnter Your Name: " << reset_color;
    cin.getline(name, 50);
    clear_screen();
    char choice = 'y';
    //play_hangman();

    while (choice == 'y') {
        bool correct = game_play(name);

        if (correct && flag_hangman)
        {
            choice = 'n';
            return true;
        }
        else {
            clear_screen();
            return false;
        }

    }
}

bool play_level_3()
{
    loading_screen();

    if (!i_make_and_display_riddles())
    {
        // Player failed the riddles, go back to the start of the level
        _getch();
        print_text_with_attributes("\n\n\tYou failed to answer the riddles. Returning to the start of the level.\n", true, false, false, color[0]);
        return false;
    }

    _getch();
    clear_screen();
    print_text_with_attributes("\n\n\n\n\n\n\tCongratulations. You answered the riddles correctly.\n\tYou have been rewarded by the fury with a magical scroll", true, true, false, color[2]);
    fury_scroll++;
    print_text_with_attributes("\n\tPrepare for your next challenge", true, true, false, color[2]);
    _getch();

    loading_screen();

    if (!fight_chimera())
    {
        // Player failed to defeat the griffin, go back to the start of the level
        print_text_with_attributes("\n\n\tYou were defeated by the Chimera. Returning to the start of the level.\n", true, false, false, color[0]);
        return false;
    }

    print_text_with_attributes("\n\tYou have been rewarded with a Chimera Fire Jar", true, true);
    chimera_fire_jar++;
    print_text_with_attributes("\n\tPrepare for your next challenge", true, true, false, color[2]);
    _getch();

    loading_screen();

    if (!play_hangman())
    {
        // Player failed to control Tyson anger, go to start of level
        print_text_with_attributes("\n\n\tTyson got angry and smashed a rock into your head. Returning to the start of the level.\n", true, false, false, color[0]);
        return false;
    }

    print_text_with_attributes("\n\tTyson helped you escape the dungeon and gave you a drawing as a token \n\t of appreciation\n", true, true, false, color[5]);
    tyson_drawing++;
    return true;
}

void display_board(int board[], bool revealed[], int size) {
    // Calculate the number of spaces to center the board
    int spaces = (50 - (size * 4)) / 2;  // Increased the multiplier for better spacing

    // Display the board with revealed and unrevealed cards
    for (int i = 0; i < size; ++i) {
        cout << setw(4) << " ";

        for (int j = 0; j < spaces; ++j) {
            cout << " ";
        }

        if (revealed[i]) {
            set_text_attributes(true);  // Set invert color attribute
            cout << board[i] << " ";
            reset_text_attributes();  // Reset color attributes
        }
        else {
            cout << "* ";
        }

        if ((i + 1) % 4 == 0) {
            cout << "\n";
        }
    }
}

bool is_mmg_game_won(bool revealed[], int size) {
    for (int i = 0; i < size; ++i) {
        if (!revealed[i]) {
            return false;
        }
    }
    return true;
}

void play_memory_match_game() {
    const int boardSize = 8;
    int board[boardSize] = { 1, 1, 2, 2, 3, 3, 4, 4 };
    bool revealed[boardSize] = { false };

    srand(time(0));

    // Shuffle the cards
    for (int i = 0; i < boardSize; ++i) {
        int randomIndex = rand() % boardSize;
        swap(board[i], board[randomIndex]);
    }

    int first_card_index = -1;
    int second_card_index = -1;

    if (!skip_dialogues())
    {
        lines_tabs(2, 1);
        print_text_with_attributes("In the heart of the enchanted forest, Aiden stumbles into a secluded glade\n\twhere a majestic creature stood ", true);
        print_text_with_attributes(" The creature had the upper body of a noble man\n\tand the lower body of a powerful horse \n\t'Fear Not, young traveler' the centaur spoke in a quiet and majestic voice", true);
        print_text_with_attributes("\n\t'I am no illusion. I am Chiron, a protector of these enchanted woods'", true);
        print_text_with_attributes("\n\n\tAiden observed that the forest was echoing with strange whispers", true);
        print_text_with_attributes("\n\tChiron seemed to have read Aiden's thoughts. The centaur looked at Aiden pitifully \n\tas the wind rustled through the leaves", true);
        print_text_with_attributes("\n\t'These winds' he said 'carry the whispers of Mnemosyne, the Titaness of Memory. \n\tThey hold the echoes of ages past, tales untold, and the weight of countless memories", true);
        _getch();
        clear_screen();

        print_text_with_attributes("\n\tHis voice took a more somber note 'But beware, young traveler, for as enchanting as these whispers may be, \n\tthey have the power to stir the deepest recesses of one's mind \n\tThey'll beckon you to recall moments long forgotten and secrets buried in the sands of time \n\tIn their relentless pursuit, they may even threaten to unravel the threads of your sanity, as if the \n\tvery fabric of Mnemosyne's tapestry wishes to consume you ", true);
        print_text_with_attributes("\n\tCountless before you have perished in their pursuit.'", true);
        print_text_with_attributes("\n\tChiron's eyes, reflecting both wisdom and sorrow met Aiden's eyes \n\t'Embrace the magic cautiously, for the winds of Mnemosyne can be both a blessing and a curse. \n\tShould you choose to wander these enchanted woods, let your memory be your guide, \n\tbut tread lightly, and remember that not all secrets are meant to be unearthed' ", true);
        _getch();
        clear_screen();

        print_text_with_attributes("\n\tAiden gathered his bearings 'I wish to remember'", true);
        print_text_with_attributes("\n\tAiden's mind, shrouded in a mysterious fog, struggled to grasp the fragments of his past.", true);
        print_text_with_attributes("\n\t'I can't remember,' Aiden confessed, a hint of frustration in his voice. 'It's as if a veil has been drawn over my memories.'", true);
        print_text_with_attributes("\n\tThe forest whispered in sympathy, its ancient trees bearing witness to Aiden's inner turmoil.", true);
        print_text_with_attributes("\n\tChiron, sensing Aiden's plight, spoke softly, \n\t'Amnesia is a formidable adversary, young one. \n\tThe threads of your memories, though elusive, may yet be rewoven.'", true);
        print_text_with_attributes("\n\tAiden's eyes sparkled with a mix of determination and yearning. \n\t'I must remember. There are pieces of myself lost in \n\tthe shadows, and I need to find them.'", true);
        _getch();
        clear_screen();

        print_text_with_attributes("\n\tChiron looked down, his face seemed to be clouded with sorrow, \n\t'Very well, traveler, make your way into these enchanted woods,'", true);
        print_text_with_attributes("\n\tAs Aiden ventured deeper, Chiron's gaze lingered upon a \n\tweathered tree stump adorned with ancient markings.", true);
        print_text_with_attributes("\n\t'Behold the Memory Grove,' Chiron whispered, his voice \n\tcarrying the weight of countless tales. \n\t'Each mark etched upon this stump is a remnant of stories, memories, \n\tand the timeless dance of existence.'", true);
        print_text_with_attributes("\n\n\tAiden noticed symbols, runes, and names engraved upon the stump, each telling a fragment of the enchanted woods' rich history.", true);
        print_text_with_attributes("\n\n\n\tChiron spoke again, 'The Memory Grove bears witness to the ebb and flow of time. \n\tExplore its secrets, and you may find echoes of your own story \n\tamidst the whispers of those who came before.'", true);
        _getch();
        clear_screen();
    }

    else
    {
        lines_tabs(2, 1);
        print_text_without_delay("In the heart of the enchanted forest, Aiden stumbles into a secluded glade\n\twhere a majestic creature stood ", true);
        print_text_without_delay(" The creature had the upper body of a noble man\n\tand the lower body of a powerful horse \n\t'Fear Not, young traveler' the centaur spoke in a quiet and majestic voice", true);
        print_text_without_delay("\n\t'I am no illusion. I am Chiron, a protector of these enchanted woods'", true);
        print_text_without_delay("\n\n\tAiden observed that the forest was echoing with strange whispers", true);
        print_text_without_delay("\n\tChiron seemed to have read Aiden's thoughts. The centaur looked at Aiden pitifully \n\tas the wind rustled through the leaves", true);
        print_text_without_delay("\n\t'These winds' he said 'carry the whispers of Mnemosyne, the Titaness of Memory. \n\tThey hold the echoes of ages past, tales untold, and the weight of countless memories", true);
        _getch();
        clear_screen();

        print_text_without_delay("\n\tHis voice took a more somber note 'But beware, young traveler, for \n\tas enchanting as these whispers may be, \n\tthey have the power to stir the deepest recesses of one's mind \n\tThey'll beckon you to recall moments long forgotten and secrets buried in the sands of time \n\tIn their relentless pursuit, they may even threaten to unravel the threads of your sanity, as if the \n\tvery fabric of Mnemosyne's tapestry wishes to consume you ", true);
        print_text_without_delay("\n\tCountless before you have perished in their pursuit.'", true);
        print_text_without_delay("\n\tChiron's eyes, reflecting both wisdom and sorrow met Aiden's eyes \n\n\t'Embrace the magic cautiously, for the winds of Mnemosyne can be both a blessing and a curse. \n\tShould you choose to wander these enchanted woods, let your memory be your guide, \n\tbut tread lightly, and remember that not all secrets are meant to be unearthed' ", true);
        _getch();
        clear_screen();

        print_text_without_delay("\n\tAiden gathered his bearings 'I wish to remember'", true);
        print_text_without_delay("\n\tAiden's mind, shrouded in a mysterious fog, struggled to grasp the fragments of his past.", true);
        print_text_without_delay("\n\t'I can't remember,' Aiden confessed, a hint of frustration in his voice. \n\t'It's as if a veil has been drawn over my memories.'", true);
        print_text_without_delay("\n\n\tThe forest whispered in sympathy, its ancient trees bearing witness to Aiden's inner turmoil.", true);
        print_text_without_delay("\n\tChiron, sensing Aiden's plight, spoke softly, \n\t'Amnesia is a formidable adversary, young one. The threads of \n\tyour memories, though elusive, may yet be rewoven.'", true);
        print_text_without_delay("\n\tAiden's eyes sparkled with a mix of determination and yearning \n\t'I must remember. There are pieces of myself lost in the shadows, and I need to find them.'", true);
        _getch();
        clear_screen();

        print_text_without_delay("\n\tChiron looked down, his face seemed to be clouded with sorrow, \n\t'Very well, traveler, make your way into these enchanted woods,'", true);
        print_text_without_delay("\n\tAs Aiden ventured deeper, Chiron's gaze lingered upon a weathered tree \n\tstump adorned with ancient markings.", true);
        print_text_without_delay("\n\n\t'Behold the Memory Grove,' Chiron whispered, \n\this voice carrying the weight of countless tales. 'Each mark etched upon this \n\tstump is a remnant of stories, memories, and the timeless dance of existence.'", true);
        print_text_without_delay("\n\tAiden noticed symbols, runes, and names engraved upon the stump, each telling a fragment \n\tof the enchanted woods' rich history.", true);
        print_text_without_delay("\n\tChiron spoke again, 'The Memory Grove bears witness to the ebb and flow of time. \n\tExplore its secrets, and you may find echoes of your own story amidst the whispers \n\tof those who came before.'", true);
        _getch();
        clear_screen();
    }

    loading_screen();

    while (!is_mmg_game_won(revealed, boardSize)) {
        clear_screen();

        display_board(board, revealed, boardSize);

        // Get user input for card selection
        cin >> first_card_index;

        // Check if the input is valid
        if (first_card_index < 0 || first_card_index >= boardSize || revealed[first_card_index]) {
            print_text_with_attributes("\n\tDon't get carried away, young traveler. Seek Reason. Act With Reason. Try again.");
            continue;
        }

        revealed[first_card_index] = true;
        clear_screen();
        display_board(board, revealed, boardSize);

        cin >> second_card_index;

        // Check if the input is valid
        if (second_card_index < 0 || second_card_index >= boardSize || revealed[second_card_index]) {
            print_text_with_attributes("\n\tChiron, exasperated, implored Aiden to focus, 'Come on, young traveler, try valid input.'", true);
            revealed[first_card_index] = false;
            continue;
        }

        revealed[second_card_index] = true;
        clear_screen();
        display_board(board, revealed, boardSize);
        this_thread::sleep_for(chrono::milliseconds(250));

        if (board[first_card_index] != board[second_card_index])
        {
            clear_screen();
            print_text_with_attributes("\n\t'Not a match. Try again,' Chiron sighed, and the winds whispered a \n\tgentle reminder through the enchanted woods.", true);
            revealed[first_card_index] = false;
            revealed[second_card_index] = false;
        }
        else
        {
            clear_screen();
            print_text_with_attributes("\n\t'Match found!' Chiron exclaimed, and the enchanted woods echoed \n\twith a harmonious melody, celebrating the discovery alongside Aiden.", true);
        }

        // Reset card indices
        second_card_index = -1;
        second_card_index = -1;
    }

    print_text_without_delay("\n\tAs Aiden uncovered the final pair, a radiant light seemed to envelop him.", true, true);
    print_text_without_delay("\n\tOverwhelmed by the winds' ethereal dance, Aiden succumbed to their gentle embrace and fainted.", true);
    print_text_without_delay("\n\tWhen he awoke, a renewed vigor coursed through his veins, and a sense of well-being washed over him.", true);
    print_text_without_delay("\n\tAiden realized that the haze of forgotten memories had lifted, and the fragments of his past had seamlessly woven themselves back into the fabric of his consciousness.", true);
    print_text_without_delay("\n\tBeside him, Chiron spoke, 'You have been graced with Mnemosyne's blessing, young traveler. The winds carry not only whispers but also the essence of rejuvenation and remembrance.'", true);
    print_text_without_delay("\n\tAiden, now awakened to a restored self, cradled his regained memories with gratitude, a testament to the enchantment of the woods and the Titaness' benevolence.", true);
    print_text_without_delay("\n\tAs a reward for overcoming the challenges within the enchanted woods, Aiden discovered a mystical jar adorned with symbols related to Mnemosyne.", true);
    print_text_without_delay("\n\tChiron explained, 'This jar, a sacred vessel linked to Mnemosyne herself, holds the essence of memories - a tangible manifestation of the blessings you've earned.'", true);
    print_text_without_delay("\n\tAs Aiden held the jar, he felt the subtle pulse of ancient memories echoing within, a reservoir of wisdom and experiences carefully preserved by the Titaness.", true);
    print_text_without_delay("\n\t'Guard it well, Aiden,' Chiron advised. 'For within this jar lies not just your memories but a connection to the eternal wellspring of Mnemosyne's timeless knowledge.'", true);
    print_text_without_delay("\n\tWith the jar in hand, Aiden ventured forth, the whispers of Mnemosyne and the enchanted woods guiding his newfound journey.", true);
}

void damage_report_minotaur(string attackMode, int damageInflicted, int playerHealth, int enemy_health, bool is_monster = false, string name = "monster") {
    lines_tabs(1, 5);
    if (!is_monster)
    {
        print_text_with_attributes("Aiden's Turn", true, false, false, color[6]);
        lines_tabs(1, 1);
        cout << "+------------------+------------------+------------------+------------------+" << endl;
        lines_tabs(0, 1);
        cout << "| " << bold << color[2] << "Attack Mode      | Damage Inflicted | Player Health    | Monster Health   | " << reset_color << endl;
        lines_tabs(0, 1);
        cout << "+------------------+------------------+------------------+------------------+" << endl;
        lines_tabs(0, 1);
        cout << "   " << attackMode << "                " << damageInflicted << "                    " << playerHealth << "                 " << enemy_health << "                " << endl;
        lines_tabs(0, 1);
        cout << "+------------------+------------------+------------------+------------------+" << endl;
    }
    else {
        print_text_with_attributes("Minotaur's Turn", true, false, false, color[5]);
        lines_tabs(1, 1);
        cout << "+------------------+------------------+------------------+------------------+" << endl;
        lines_tabs(0, 1);
        cout << "| " << bold << color[5] << "Attack Mode      | Damage Inflicted | Player Health    | Monster Health   | " << reset_color << endl;
        lines_tabs(0, 1);
        cout << "+------------------+------------------+------------------+------------------+" << endl;
        lines_tabs(0, 1);
        cout << "   " << attackMode << "                " << damageInflicted << "                    " << playerHealth << "                 " << enemy_health << "                " << endl;
        lines_tabs(0, 1);
        cout << "+------------------+------------------+------------------+------------------+" << endl;
    }
}

void display_inventory_minotaur() {
    // Display header
    lines_tabs(4, 2);
    print_text_with_attributes("Current Inventory and Status", true, false, false, color[6]);
    lines_tabs(1, 0);

    // Display player and chimera health in a table
    lines_tabs(0, 1);
    cout << "+--------------------------+------------------+" << endl;
    lines_tabs(0, 1);
    cout << "| " << bold << color[2] << "Player Health" << reset_color << "        | " << bold << color[0] << "Minotaur Health" << reset_color << "      |" << endl;
    lines_tabs(0, 1);
    cout << "+--------------------------+------------------+" << endl;
    lines_tabs(0, 1);
    cout << "| " << invert_color << color[2] << player_health << "                 " << reset_color << " | " << invert_color << color[0] << minotaur_health << "                " << reset_color << "  |" << endl;
    lines_tabs(0, 1);
    cout << "+--------------------------+------------------+" << endl;
    // Display attack modes in a table
    lines_tabs(1, 1);
    cout << "+--------------------------+------------------+" << endl;
    lines_tabs(0, 1);
    cout << "| " << bold << color[2] << "Player Attack Modes" << reset_color << "  | " << bold << color[0] << "Minotaur Attack Modes" << reset_color << "|" << endl;
    lines_tabs(0, 1);
    cout << "+--------------------------+------------------+" << endl;
    lines_tabs(0, 1);
    cout << "|    " << color[2] << "Attack With Sword" << reset_color << " |    " << color[0] << "Super Strength" << reset_color << "    |" << endl;
    lines_tabs(0, 1);
    cout << "|    " << color[2] << "Roll Away" << reset_color << "         |    " << color[0] << "High Health" << reset_color << "       |" << endl;
    lines_tabs(0, 1);
    cout << "|    " << color[2] << "Cast A Spell" << reset_color << "      |                      |" << endl;
    lines_tabs(0, 1);
    cout << "+--------------------------+------------------+" << endl;
    lines_tabs(0, 1);
}

void player_turn_minotaur()
{
    bool validChoice = false;

    while (!validChoice)
    {
        lines_tabs(2, 1);
        print_text_with_attributes("Aiden's Turn: ", true, false, false, color[1]);
        lines_tabs(1, 1);
        random_battle_voicelines(true, false);
        lines_tabs(2, 1);
        cout << "Choose your action:";
        cout << "\n\t1. Attack";
        cout << "\n\t2. Cast a spell";
        cout << "\n\tEnter your choice: ";
        int choice;
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            int player_damage = perform_attack(player_attack_power);
            lines_tabs(1, 1);
            minotaur_health = minotaur_health - player_damage;
            damage_report_minotaur("Sword", player_damage, player_health, minotaur_health);
            validChoice = true;
            break;
        }
        case 2:
        {
            display_spell_inventory();
            cout << "\n\tChoose a spell:";
            lines_tabs(1, 1);
            cout << color[2] << "1. Cast a healing spell";
            reset_text_attributes();
            lines_tabs(1, 1);
            cout << color[5] << "2. Cast a lightning spell";
            reset_text_attributes();
            lines_tabs(1, 1);
            cout << color[4] << "3. Cast a rage spell";
            reset_text_attributes();
            cout << "\n\tEnter your choice: ";
            int spell_choice;
            cin >> spell_choice;

            switch (spell_choice)
            {
            case 1:
            {
                if (healing_spells > 0)
                {
                    int player_healing_amount = perform_healing_spell(player_healing_power);
                    player_health += player_healing_amount;
                    lines_tabs(1, 1);
                    damage_report_minotaur("Spell", 0, player_health, minotaur_health);
                    validChoice = true;
                    healing_spells--;
                }
                else
                    print_text_without_delay("Aiden is out of healing spells. Choose other options", true);
                break;
            }
            case 2:
            {
                if (lightning_spells > 0)
                {
                    int player_lightning_damage = perform_lightning_spell(player_lightning_power);
                    minotaur_health -= player_lightning_damage;
                    lines_tabs(1, 1);
                    damage_report_minotaur("Spell", player_lightning_damage, player_health, minotaur_health);
                    validChoice = true;
                    lightning_spells--;
                }
                else
                {
                    cout << "\n\t" << player_name << " is out of lightning spells. Choose other options";
                }
                break;
            case 3:
            {
                if (rage_spells > 0)
                {
                    int player_rage_damage = perform_lightning_spell(player_rage_power);
                    minotaur_health -= player_rage_damage;
                    lines_tabs(1, 1);
                    damage_report_minotaur("Spell", player_rage_damage, player_health, minotaur_health);
                    rage_spells--;
                }
            }
            }
            default:
            {
                cout << "\n\tMagic is not in the tools but in the hands of the one who wields them. \n\tMistakes illuminate the path to mastery.";
                break;
            }
            }
            break;
        }
        default:
        {
            cout << "\n\tLike a misdirected incantation or an ill-fated swing of the sword, \n\ta wrong choice echoes lessons to heed and paths to reconsider in the journey of wisdom.";
            break;
        }
        }
    }
}

void minotaur_turn() {
    int minotaur_damage = perform_attack(minotaur_attack_power);
    lines_tabs(2, 1);
    damage_report_minotaur("Power Claw", minotaur_damage, player_health, minotaur_health, true, monster_name);
    player_health = player_health - minotaur_damage;
}

void display_status() {
    lines_tabs(1, 1);
    cout << invert_color << player_name << "'s Health: " << player_health << " ";
    lines_tabs(1, 1);
    cout << monster_name << "'s Health: " << minotaur_health << " " << reset_color;
}

bool fight_minotaur()
{
    srand(time(0));

    lines_tabs(2, 1);
    print_text_without_delay("                                                                                        ", true, true);
    lines_tabs(1, 1);
    print_text_with_attributes("  Having regained his memory, Aiden walked with purpose towards his homeland, Aldora    ", true, true);
    lines_tabs(1, 1);
    print_text_with_attributes("                       He has to face one final challenge.                              ", true, true);
    lines_tabs(1, 1);
    print_text_with_attributes("  Ahead of Aiden is a creature with the body of a muscular man and the head of a bull   ", true, true);
    lines_tabs(1, 1);
    print_text_with_attributes("                      The minotaur looks at Aiden and charges                           ", true, true);
    lines_tabs(1, 1);
    print_text_without_delay("                                                                                        ", true, true);

    display_inventory_minotaur();
    _getch();

    loading_screen();

    while (player_health > 0 && minotaur_health > 0) {
        player_turn_minotaur();
        if (minotaur_health <= 0) {
            cout << "\t";
            random_battle_voicelines(false, true);
            return true;
            break;
        }

        lines_tabs(1, 0);
        minotaur_turn();
        _getch();
        clear_screen();
        if (player_health <= 0) {
            cout << "\t";
            random_battle_voicelines(false, false);
            return false;
            break;
        }

        _getch();
        clear_screen();
    }
}

bool play_level_4()
{
    loading_screen();

    if (!i_make_and_display_riddles())
    {
        // Player failed the riddles, go back to the start of the level
        _getch();
        print_text_with_attributes("\n\n\tYou failed to answer the riddles. Returning to the start of the level.\n", true, false, false, color[0]);
        return false;
    }

    _getch();
    clear_screen();
    print_text_with_attributes("\n\n\n\n\n\n\tCongratulations. You answered the riddles correctly.\n\tYou have been rewarded by the fury with a magical scroll", true, true, false, color[2]);
    fury_scroll++;
    print_text_with_attributes("\n\tPrepare for your next challenge", true, true, false, color[2]);
    _getch();

    loading_screen();

    play_memory_match_game();
    mnemosyne_jar++;


    loading_screen();
    if (!fight_minotaur())
    {
        // Player failed to defeat the minotaur, go back to the start of the level
        print_text_with_attributes("\n\n\tYou were defeated by the Minotaur. Returning to the start of the level.\n", true, false, false, color[0]);
        return false;
    }

    print_text_with_attributes("\n\tYou have been rewarded with a Minotaur Horn", true, true);
    minotaur_horn++;
    _getch();

    return true;
}

void credits()
{
    cout << "\t\t ==========================================================" << endl;
    cout << "\t\t|               MADE BY BANPHANTOMX STUDIOS                |" << endl;
    cout << "\t\t ==========================================================" << endl;
    cout << "\t\t|                     GAME DEVELOPERS                      |" << endl;
    cout << "\t\t ----------------------------------------------------------" << endl;
    cout << "\t\t|    DAUD SHAFI KHAN                (BAN Shafi)            |" << endl;
    cout << "\t\t|    MUHAMMAD HASSAN IRFAN          (phantompainx21)       |" << endl;
    cout << "\t\t ----------------------------------------------------------" << endl;
}

int final_score()
{
    int final_score = 0;
    final_score += player_health * 30;
    final_score += lightning_spells * 30;
    final_score += healing_spells * 50;
    final_score += rage_spells * 50;
    final_score += tyson_drawing * 1000;
    final_score += griffin_claw * 1000;
    final_score += harpy_feather * 1000;
    final_score += minotaur_horn * 1000;
    final_score += calliope_fabric * 1000;
    final_score -= puck_token * 2000;
    final_score += chimera_fire_jar * 1000;
    final_score += mnemosyne_jar * 1000;
    final_score -= fury_scroll * 100;
    return final_score;
}

void game_intro()
{
    clear_screen();

    //print_text_without_delay("\n\n\n\n\t\t\t\t==============================================", false, true, false, color[4]);
    //print_text_without_delay("\n\n\n\n\n\t\t\t\t\t\t WELCOME TO ", true, true, false, color[6]);
    //print_text_without_delay("\n\t\t\t\t==============================================", false, true, false, color[4]);
    cout << "\n\n\n\n\n\n\n\n\n\t\t";

    print_text_with_attributes(" T  H  E  ", true, true, false, color[6]);
    this_thread::sleep_for(chrono::milliseconds(1000));
    print_text_with_attributes("   A  D  V  E  N  T  U  R  E  S  ", true, true, false, color[2]);
    this_thread::sleep_for(chrono::milliseconds(1000));
    print_text_with_attributes("   O  F   ", true, true, false, color[5]);
    this_thread::sleep_for(chrono::milliseconds(1000));
    print_text_with_attributes("   A  I  D  E  N   ", true, true, false, color[3]);
    this_thread::sleep_for(chrono::milliseconds(2000));

    lines_tabs(3, 3);
    print_text_with_attributes("    A   R O L E   P L A Y I N G   G A M E  ( R P G )  ", true, false, false, color[6], 25);
    //print_text_with_attributes("\n\n\n\n\n\n\t\t\t   ( Press any key to begin your journey...... )", false, true, false, color[5], 15);

    _getch();
    clear_screen();

    lines_tabs(2, 5);
    print_text_without_delay("  DEVELOPER'S SCROLL  ", true, true);
    lines_tabs(2, 2);
    print_text_without_delay("****************************************************************************", false, true);
    cout << "\n\n";
    lines_tabs(1, 2);
    print_text_without_delay("\tDarkness envelops the enchanted forest, where mystery and danger\n");
    lines_tabs(1, 2);
    print_text_without_delay("\t lurk in every shadow. Aiden a lone wandered has stubled upon a \n");
    lines_tabs(1, 2);
    print_text_without_delay("\trealm of magic and peril. Aiden has lost his memory and is miles\n");
    lines_tabs(1, 2);
    print_text_without_delay("\t             away from his homeland Aldora.\n\n");

    lines_tabs(1, 2);
    print_text_without_delay("\t Embark on a journey with Aiden as destiny unfolds and secrets  \n");
    lines_tabs(1, 2);
    print_text_without_delay("\treveal themselves. Your choices will shape the fate of Aiden and\n");
    lines_tabs(1, 2);
    print_text_without_delay("\t                the enchanted world that awaits\n");
    lines_tabs(1, 2);

    print_text_without_delay("\tHelp Aiden find his homeland. You wil recieve rewards along the \n");
    lines_tabs(1, 2);
    print_text_without_delay("\t  way. Beware of the mysterious creatures hiding in the forest  \n");
    lines_tabs(1, 2);
    print_text_without_delay("\t                         Good luck\n\n");
    lines_tabs(1, 2);

    print_text_without_delay("****************************************************************************", false, true);

    lines_tabs(4, 3);
    print_text_without_delay(" Press any key to begin your adventure! ", true, true, false, color[6]);

    _getch();
    clear_screen();
}


void display_game_over()
{
    print_text_without_delay("\n\n\t\tCongratulations. You have successfully completed the game", true, true, false, color[6]);
    print_text_without_delay("\n\n\t\t+----------------------------+-------------------------+", true, true, false, color[2]);
    cout << "\n\n\t\t              ";
    print_text_without_delay(" Your final score was ", true, true, false, color[5]);
    cout << "\n\n\t\t                   ";
    print_text_without_delay(" " + to_string(final_score()) + " points", true, true, false, color[5]);
    cout << "\n\n\t\t                    ";
    print_text_without_delay(" Well Done!", true, true, false, color[5]);
    cout << "\n\n\t\t           ";
    print_text_without_delay(" Thank You for Playing. Goodbye!   ", true, true, false, color[5]);
    print_text_without_delay("\n\n\t\t+----------------------------+-------------------------+", true, true, false, color[2]);
    _getch();
    clear_screen();
    cout << "\n\n\n";
    credits();
}

int main()
{
    game_intro();

    loading_screen();

    while (!play_level_1())
    {
        if (play_level_1())
        {
            clear_screen();
        }
    }
    display_level_end_inventory();
    _getch();
    clear_screen();

    while (!play_level_2())
    {
        if (play_level_2())
        {
            clear_screen();
        }
    }
    display_level_end_inventory();
    _getch();
    clear_screen();

    while (!play_level_3())
    {
        if (play_level_3())
        {
            clear_screen();
        }
    }
    display_level_end_inventory();
    _getch();
    clear_screen();

    while (!play_level_4())
    {
        if (play_level_4())
        {
            clear_screen();
        }
    }
    display_level_end_inventory();

    loading_screen();
    clear_screen();

    display_game_over();
    _getch();
    GG();
    _getch();
    clear_screen();

    return 0;
}