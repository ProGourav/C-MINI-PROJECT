/*
 * QuizMaster - C Language Quiz Application
 * BCA First Semester Mini Project
 *
 * Uses only: variables, operators, printf/scanf, if/switch, loops,
 * break/continue, 1D/2D arrays, strings, functions and basic pointers.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ---------- Constants ---------- */
#define WIDTH 64          /* inner width of every box              */
#define TOTAL_Q 40        /* 4 sets x 10 questions                 */
#define Q_PER_SET 10      /* questions asked in one quiz           */
#define NAME_SIZE 50      /* max characters for student name       */
#define USE_COLOR 1       /* set to 0 if colours look wrong        */

#if USE_COLOR
#define RESET  "\033[0m"
#define RED    "\033[91m"
#define GREEN  "\033[92m"
#define YELLOW "\033[93m"
#define CYAN   "\033[96m"
#define WHITE  "\033[97m"
#else
#define RESET  ""
#define RED    ""
#define GREEN  ""
#define YELLOW ""
#define CYAN   ""
#define WHITE  ""
#endif

/* ---------- Data: names ---------- */
char categoryNames[2][20] = {"C Programming", "Computer Basics"};
char levelNames[2][10]    = {"Easy", "Medium"};

/* ---------- Data: questions (2D char array = array of strings) ----------
 * Set 0 = C Programming  / Easy     -> questions 0-9
 * Set 1 = C Programming  / Medium   -> questions 10-19
 * Set 2 = Computer Basics / Easy    -> questions 20-29
 * Set 3 = Computer Basics / Medium  -> questions 30-39
 */
char questions[TOTAL_Q][100] = {
    /* ---- Set 0: C Programming - Easy ---- */
    "Which header file is needed for printf() and scanf()?",
    "Which symbol is used to end a statement in C?",
    "Which data type is used to store a whole number?",
    "Which format specifier is used to print an int value?",
    "Which operator gives the remainder of a division?",
    "In C, the index of an array starts from?",
    "Which loop always runs its body at least once?",
    "Which keyword is used to leave a loop immediately?",
    "Which is the correct way to start the main function?",
    "What is the output of printf(\"%d\", 5 + 3 * 2); ?",

    /* ---- Set 1: C Programming - Medium ---- */
    "What is printed by: int a = 10; printf(\"%d\", a++ + 5); ?",
    "What is the last valid index of the array int arr[6]; ?",
    "Which function is used to find the length of a string?",
    "Which character marks the end of every string in C?",
    "If int x = 7; int *p = &x; then what does *p give?",
    "What does strcmp(\"abc\", \"abc\") return?",
    "Which statement skips the rest of the current loop pass?",
    "In a switch, what happens if break is missing in a case?",
    "How many times does for(i = 0; i < 5; i++) run its body?",
    "Which is the correct way to declare a 3 x 4 two-D array?",

    /* ---- Set 2: Computer Basics - Easy ---- */
    "What does CPU stand for?",
    "Which of these is an input device?",
    "Which of these is an output device?",
    "How many bits are there in one byte?",
    "Which of these is an operating system?",
    "What type of memory is RAM?",
    "Which unit is used to measure the speed of a CPU?",
    "What does WWW stand for?",
    "Which of these is a web browser?",
    "What is a computer virus?",

    /* ---- Set 3: Computer Basics - Medium ---- */
    "Which number system does a computer use internally?",
    "What is the binary form of the decimal number 5?",
    "Which of these memories is the fastest?",
    "What is the full form of ROM?",
    "Which translator converts a whole program to machine code at once?",
    "Which of these is NOT an operating system?",
    "What does an IP address identify?",
    "How many bytes are there in 1 KB (kilobyte)?",
    "Which protocol is used to open web pages?",
    "What is the main job of a firewall?"
};

/* ---------- Data: options (4 options per question) ----------
 * Options of question n are stored at rows n*4, n*4+1, n*4+2, n*4+3
 */
char options[TOTAL_Q * 4][60] = {
    /* Set 0 */
    "stdlib.h", "stdio.h", "string.h", "math.h",
    ". (dot)", ": (colon)", "; (semicolon)", ", (comma)",
    "int", "float", "char", "double",
    "%f", "%c", "%s", "%d",
    "/", "%", "*", "&",
    "1", "-1", "0", "2",
    "for", "while", "do-while", "if",
    "continue", "stop", "exit", "break",
    "int main()", "main int()", "void int main", "function main()",
    "16", "11", "10", "13",

    /* Set 1 */
    "16", "14", "15", "11",
    "6", "5", "7", "0",
    "strcpy()", "strcmp()", "strlen()", "strcat()",
    "'\\n'", "'\\0'", "' ' (space)", "'.' (dot)",
    "The address of x", "The address of p", "Always zero", "The value of x (7)",
    "1", "-1", "0", "3",
    "continue", "break", "return", "exit",
    "Compile error", "Next cases also run", "Program stops", "Only default runs",
    "5", "4", "6", "Infinite times",
    "int a[4][3];", "int a[3,4];", "int a(3)(4);", "int a[3][4];",

    /* Set 2 */
    "Central Processing Unit", "Computer Personal Unit", "Central Program Utility", "Control Processing Unit",
    "Monitor", "Printer", "Speaker", "Keyboard",
    "Mouse", "Monitor", "Scanner", "Keyboard",
    "4", "16", "8", "2",
    "Windows", "Google Chrome", "MS Word", "Notepad",
    "Permanent memory", "Volatile (temporary) memory", "Read-only memory", "Optical memory",
    "Bytes", "Pixels", "Hertz (Hz / GHz)", "Watts",
    "World Web Wire", "Wide World Window", "Web World Wide", "World Wide Web",
    "Google Chrome", "Windows", "Linux", "Excel",
    "A type of monitor", "A harmful program that can damage data", "A printer driver", "A type of keyboard",

    /* Set 3 */
    "Decimal", "Octal", "Binary", "Hexadecimal",
    "101", "110", "111", "100",
    "Hard disk", "Pen drive", "RAM", "Cache memory",
    "Random Output Memory", "Read Only Memory", "Run Only Memory", "Read Output Module",
    "Interpreter", "Text editor", "Compiler", "Debugger",
    "Linux", "Windows", "Android", "Python",
    "A device on a network", "The colour of a website", "The size of a file", "The ink of a printer",
    "100", "512", "1024", "2048",
    "FTP", "HTTP", "SMTP", "POP",
    "Speed up the RAM", "Clean the keyboard", "Increase battery life", "Block unauthorized network access"
};

/* ---------- Data: correct answers (0=A, 1=B, 2=C, 3=D) ---------- */
int answers[TOTAL_Q] = {
    /* Set 0 */ 1, 2, 0, 3, 1, 2, 2, 3, 0, 1,
    /* Set 1 */ 2, 1, 2, 1, 3, 2, 0, 1, 0, 3,
    /* Set 2 */ 0, 3, 1, 2, 0, 1, 2, 3, 0, 1,
    /* Set 3 */ 2, 0, 3, 1, 2, 3, 0, 2, 1, 3
};

/* ---------- Function prototypes ---------- */
void clearScreen(void);
void printBorder(char ch);
void printBoxLine(const char *text, const char *color);
void printRowText(const char *label, const char *value);
void printRowNumber(const char *label, int value);
void printRowPercent(const char *label, float value);
void readToken(char *buf);
void readLine(char *buf);
int  readNumber(int min, int max);
int  readAnswer(void);
int  isValidName(char *p);
void getStudentName(char *name);
void pauseScreen(void);
void showWelcome(void);
void showMainMenu(const char *name);
void showInstructions(void);
int  chooseCategory(void);
int  chooseLevel(void);
int  runQuiz(int category, int level, const char *name);
void calculateResult(int correct, int total, int *wrong, float *percent);
const char *getPerformanceMessage(float percent);
void showResult(const char *name, int category, int level, int correct);
int  askPlayAgain(void);
void showGoodbye(const char *name);

/* ====================== MAIN ====================== */
int main(void)
{
    char name[NAME_SIZE];
    int choice, category, level, correct;
    int playAgain;

    showWelcome();
    getStudentName(name);

    do {
        playAgain = 0;
        showMainMenu(name);
        choice = readNumber(1, 3);

        switch (choice) {
            case 1:
                category = chooseCategory();
                level = chooseLevel();
                correct = runQuiz(category, level, name);
                showResult(name, category, level, correct);
                playAgain = askPlayAgain();
                break;
            case 2:
                showInstructions();
                playAgain = 1;      /* go back to the main menu */
                break;
            case 3:
                playAgain = 0;      /* exit */
                break;
        }
    } while (playAgain == 1);

    showGoodbye(name);
    return 0;
}

/* ====================== SCREEN HELPERS ====================== */

/* Clears the console (also switches on colour support on Windows 10/11) */
void clearScreen(void)
{
    system("cls");
}

/* Prints a border line like +=====...=====+ */
void printBorder(char ch)
{
    int i;
    printf("+");
    for (i = 0; i < WIDTH; i++) {
        printf("%c", ch);
    }
    printf("+\n");
}

/* Prints text centred inside | ... | with the given colour */
void printBoxLine(const char *text, const char *color)
{
    int len = (int)strlen(text);
    int left = (WIDTH - len) / 2;
    int right = WIDTH - len - left;
    int i;

    printf("|");
    for (i = 0; i < left; i++) {
        printf(" ");
    }
    printf("%s%s%s", color, text, RESET);
    for (i = 0; i < right; i++) {
        printf(" ");
    }
    printf("|\n");
}

/* Result-table rows: label : value */
void printRowText(const char *label, const char *value)
{
    printf("|  %-16s : %-42.42s |\n", label, value);
}

void printRowNumber(const char *label, int value)
{
    printf("|  %-16s : %-42d |\n", label, value);
}

void printRowPercent(const char *label, float value)
{
    int len = 4;                /* "80.0%" style text length (without %) */

    if (value >= 100) {
        len = 6;                /* 100.0% */
    } else if (value >= 10) {
        len = 5;                /* 80.0%  */
    }
    printf("|  %-16s : %.1f%%%*s |\n", label, value, 42 - len, "");
}

/* ====================== INPUT HELPERS ====================== */

/* Reads one word safely (max 49 characters). Exits if input is closed. */
void readToken(char *buf)
{
    if (scanf("%49s", buf) != 1) {
        printf("\n  Input closed. Exiting program.\n");
        exit(0);
    }
}

/* Reads a full line (spaces allowed) - used for the name */
void readLine(char *buf)
{
    if (scanf(" %49[^\n]", buf) != 1) {
        printf("\n  Input closed. Exiting program.\n");
        exit(0);
    }
}

/* Keeps asking until the user types ONE digit between min and max */
int readNumber(int min, int max)
{
    char input[NAME_SIZE];

    while (1) {
        printf("  Enter your choice (%d-%d): ", min, max);
        readToken(input);

        if (strlen(input) == 1 && input[0] >= '0' + min && input[0] <= '0' + max) {
            return input[0] - '0';
        }
        printf("%s  Invalid input! Please enter a number from %d to %d.%s\n",
               RED, min, max, RESET);
    }
}

/* Keeps asking until the user types A, B, C or D (small or capital).
   Returns 0 for A, 1 for B, 2 for C, 3 for D. */
int readAnswer(void)
{
    char input[NAME_SIZE];
    char ch;

    while (1) {
        printf("  Your answer (A/B/C/D): ");
        readToken(input);

        if (strlen(input) != 1) {
            printf("%s  Invalid input! Type only one letter: A, B, C or D.%s\n", RED, RESET);
            continue;
        }

        ch = input[0];
        if (ch >= 'a' && ch <= 'd') {
            ch = ch - 32;           /* small letter -> capital letter */
        }
        if (ch >= 'A' && ch <= 'D') {
            return ch - 'A';
        }
        printf("%s  Invalid input! Type only one letter: A, B, C or D.%s\n", RED, RESET);
    }
}

/* Uses a pointer to walk through the name; valid if it has a letter */
int isValidName(char *p)
{
    int found = 0;

    while (*p != '\0') {
        if ((*p >= 'A' && *p <= 'Z') || (*p >= 'a' && *p <= 'z')) {
            found = 1;
            break;
        }
        p++;
    }
    return found;
}

void getStudentName(char *name)
{
    while (1) {
        printf("  Enter your name: ");
        readLine(name);

        if (isValidName(name) == 1) {
            return;
        }
        printf("%s  Invalid name! The name must contain at least one letter.%s\n", RED, RESET);
    }
}

void pauseScreen(void)
{
    char tmp[NAME_SIZE];

    printf("\n  Type any word and press Enter to continue... ");
    readToken(tmp);
}

/* ====================== SCREENS ====================== */

void showWelcome(void)
{
    clearScreen();
    printf("\n");
    printBorder('=');
    printBoxLine("", WHITE);
    printBoxLine("*  *  *  *  *  *  *  *  *  *  *  *  *", CYAN);
    printBoxLine("", WHITE);
    printBoxLine("Q U I Z   M A S T E R", YELLOW);
    printBoxLine("The C Language Quiz Application", WHITE);
    printBoxLine("", WHITE);
    printBoxLine("*  *  *  *  *  *  *  *  *  *  *  *  *", CYAN);
    printBoxLine("", WHITE);
    printBoxLine("BCA First Semester Mini Project", WHITE);
    printBoxLine("", WHITE);
    printBorder('=');
    printf("\n");
}

void showMainMenu(const char *name)
{
    clearScreen();
    printf("\n");
    printBorder('=');
    printBoxLine("MAIN MENU", YELLOW);
    printBorder('=');
    printf("\n  Welcome, %s%s%s!\n\n", CYAN, name, RESET);
    printf("    [1]  Start Quiz\n");
    printf("    [2]  Instructions\n");
    printf("    [3]  Exit\n\n");
}

void showInstructions(void)
{
    clearScreen();
    printf("\n");
    printBorder('=');
    printBoxLine("INSTRUCTIONS", YELLOW);
    printBorder('=');
    printf("\n");
    printf("  1. Choose a category: C Programming or Computer Basics.\n");
    printf("  2. Choose a level: Easy or Medium.\n");
    printf("  3. Each quiz has %d multiple-choice questions.\n", Q_PER_SET);
    printf("  4. Type A, B, C or D and press Enter to answer.\n");
    printf("  5. Every correct answer gives 1 mark. No negative marking.\n");
    printf("  6. Your score and percentage are shown at the end.\n");
    pauseScreen();
}

int chooseCategory(void)
{
    clearScreen();
    printf("\n");
    printBorder('=');
    printBoxLine("SELECT CATEGORY", YELLOW);
    printBorder('=');
    printf("\n    [1]  C Programming\n");
    printf("    [2]  Computer Basics\n\n");
    return readNumber(1, 2) - 1;        /* 0 or 1 */
}

int chooseLevel(void)
{
    printf("\n");
    printBorder('=');
    printBoxLine("SELECT DIFFICULTY LEVEL", YELLOW);
    printBorder('=');
    printf("\n    [1]  Easy\n");
    printf("    [2]  Medium\n\n");
    return readNumber(1, 2) - 1;        /* 0 or 1 */
}

/* ====================== QUIZ ====================== */

/* Asks all questions of the chosen set and returns the number of correct answers */
int runQuiz(int category, int level, const char *name)
{
    int setIndex = category * 2 + level;    /* 0 to 3 */
    int start = setIndex * Q_PER_SET;       /* first question of this set */
    int q, j, qi, choice;
    int correct = 0;

    clearScreen();
    printf("\n");
    printBorder('=');
    printBoxLine("QUIZ STARTED - ALL THE BEST!", YELLOW);
    printBorder('=');
    printRowText("Student", name);
    printRowText("Category", categoryNames[category]);
    printRowText("Level", levelNames[level]);
    printBorder('=');

    for (q = 0; q < Q_PER_SET; q++) {
        qi = start + q;                     /* question number in the big array */

        printf("\n");
        printBorder('-');
        printf("  Question %d of %d                      Score so far: %d\n",
               q + 1, Q_PER_SET, correct);
        printBorder('-');
        printf("\n  Q%d. %s\n\n", q + 1, questions[qi]);

        for (j = 0; j < 4; j++) {
            printf("      %c)  %s\n", 'A' + j, options[qi * 4 + j]);
        }
        printf("\n");

        choice = readAnswer();

        if (choice == answers[qi]) {
            correct++;
            printf("%s  [OK] Correct! Well done. (+1 mark)%s\n", GREEN, RESET);
        } else {
            printf("%s  [X] Wrong! Correct answer: %c) %s%s\n",
                   RED, 'A' + answers[qi], options[qi * 4 + answers[qi]], RESET);
        }
    }
    return correct;
}

/* Pointers are used to send back two results (wrong and percent) */
void calculateResult(int correct, int total, int *wrong, float *percent)
{
    *wrong = total - correct;
    *percent = (float)correct * 100 / total;
}

const char *getPerformanceMessage(float percent)
{
    if (percent >= 90) {
        return "Outstanding! You are a true QuizMaster!";
    } else if (percent >= 70) {
        return "Very good! Keep up the great work.";
    } else if (percent >= 50) {
        return "Good effort! A little more practice will help.";
    } else if (percent >= 30) {
        return "Fair. Please revise the topics and try again.";
    } else {
        return "Needs improvement. Do not give up - practise more!";
    }
}

void showResult(const char *name, int category, int level, int correct)
{
    int wrong;
    float percent;
    const char *message;

    calculateResult(correct, Q_PER_SET, &wrong, &percent);
    message = getPerformanceMessage(percent);

    printf("\n\n");
    printBorder('=');
    printBoxLine("QUIZ RESULT", YELLOW);
    printBorder('=');
    printRowText("Student", name);
    printRowText("Category", categoryNames[category]);
    printRowText("Level", levelNames[level]);
    printBorder('-');
    printRowNumber("Total Questions", Q_PER_SET);
    printRowNumber("Correct Answers", correct);
    printRowNumber("Wrong Answers", wrong);
    printRowNumber("Score", correct);
    printRowPercent("Percentage", percent);
    printBorder('-');
    printBoxLine(message, CYAN);
    printBorder('=');
    printf("\n");
}

int askPlayAgain(void)
{
    char input[NAME_SIZE];

    while (1) {
        printf("  Do you want to play again? (Y/N): ");
        readToken(input);

        if (strlen(input) == 1) {
            if (input[0] == 'Y' || input[0] == 'y') {
                return 1;
            }
            if (input[0] == 'N' || input[0] == 'n') {
                return 0;
            }
        }
        printf("%s  Invalid input! Please type Y or N.%s\n", RED, RESET);
    }
}

void showGoodbye(const char *name)
{
    printf("\n");
    printBorder('=');
    printBoxLine("THANK YOU FOR PLAYING QUIZMASTER!", YELLOW);
    printBoxLine(name, CYAN);
    printBoxLine("Keep learning. Keep coding. Goodbye!", WHITE);
    printBorder('=');
    printf("\n");
}
