# C-MINI-PROJECT


# QuizMaster — Documentation

## 1. Folder Structure

```
QuizMaster/
├── quizmaster.c                 <- source code (only file needed)
├── quizmaster.exe               <- created after compiling
└── QuizMaster_Documentation.md  <- this file
```

## 2. Compile and Run (VS Code terminal, Windows)

1. Open the `QuizMaster` folder in VS Code (File → Open Folder).
2. Open the terminal: `Ctrl + ~`
3. Check GCC:
   ```
   gcc --version
   ```
4. Compile:
   ```
   gcc -std=c99 -Wall -Wextra quizmaster.c -o quizmaster.exe
   ```
5. Run:
   - PowerShell: `.\quizmaster.exe`
   - Command Prompt: `quizmaster.exe`

Notes:
- No warnings or errors should appear after step 4.
- If colours look like `←[92m` text, open `quizmaster.c` and change `#define USE_COLOR 1` to `0`, then compile again.

## 3. Code Explanation

### Global data (top of the file)
- `categoryNames`, `levelNames` — 2D char arrays holding the names shown on screen.
- `questions[40][100]` — 2D array. Each row is one question string.
- `options[160][60]` — 2D array. Each question has 4 options; question `n` uses rows `n*4` to `n*4+3`.
- `answers[40]` — 1D array of correct answers (0 = A, 1 = B, 2 = C, 3 = D).
- The 40 questions are split into 4 sets of 10: C-Easy, C-Medium, Computer-Easy, Computer-Medium.
- Set number = `category * 2 + level`. First question of the set = `set * 10`.

### Functions
| Function | What it does |
|---|---|
| `main()` | Shows welcome, reads name, then loops in a `do-while` showing the menu. A `switch` handles Start / Instructions / Exit. |
| `clearScreen()` | Clears the console with `system("cls")`. |
| `printBorder(ch)` | Prints a border line with `+`, 64 copies of `ch`, `+` using a `for` loop. |
| `printBoxLine(text, color)` | Prints text centred inside `\| \|`. Calculates left and right spaces from `strlen()`. |
| `printRowText / printRowNumber / printRowPercent` | Print one aligned row (label : value) of the result table. |
| `readToken(buf)` | Reads one word with `scanf("%49s")`. The 49 limit stops buffer overflow. |
| `readLine(buf)` | Reads a full line (name with spaces) with `scanf(" %49[^\n]")`. |
| `readNumber(min, max)` | Keeps asking until the user types one digit in range. Returns the number. |
| `readAnswer()` | Keeps asking until the user types A/B/C/D (capital or small). Returns 0–3. |
| `isValidName(p)` | Uses a **pointer** to walk through the name; valid if it has at least one letter. |
| `getStudentName(name)` | Asks for the name until it is valid. |
| `pauseScreen()` | Waits for the user before going back to the menu. |
| `showWelcome()`, `showMainMenu()`, `showInstructions()` | Draw the screens. |
| `chooseCategory()`, `chooseLevel()` | Show a menu, return 0 or 1. |
| `runQuiz()` | Loops over 10 questions: prints question and options, reads answer, compares with `answers[]`, prints feedback, counts correct answers. |
| `calculateResult(correct, total, *wrong, *percent)` | Uses **pointers** to return two values: wrong answers and percentage. |
| `getPerformanceMessage(percent)` | `if-else` ladder; returns a message string. |
| `showResult()` | Prints the result screen. |
| `askPlayAgain()` | Reads Y/N with validation. |
| `showGoodbye()` | Prints the exit screen. |

### Important code sections
- **Answer checking:** `if (choice == answers[qi])` — `qi` is the question's position in the big array.
- **Score:** `correct++` for every right answer. `wrong = total - correct`.
- **Percentage:** `(float)correct * 100 / total`. The `(float)` makes it a decimal division.
- **Input validation:** every `scanf` reads text (not numbers), so letters typed by mistake can never cause an endless loop. The text is then checked with `strlen()` and character comparisons.
- **Small → capital letter:** `ch = ch - 32` (ASCII difference between `'a'` and `'A'`).
- **Colours:** ANSI codes like `"\033[92m"` (green), stored in `#define` constants.

## 4. Sample Run (shortened)

```
+================================================================+
|                                                                |
|             *  *  *  *  *  *  *  *  *  *  *  *  *             |
|                                                                |
|                     Q U I Z   M A S T E R                      |
|                The C Language Quiz Application                 |
|                                                                |
|             *  *  *  *  *  *  *  *  *  *  *  *  *             |
|                                                                |
|                BCA First Semester Mini Project                 |
|                                                                |
+================================================================+

  Enter your name: Rahul Sharma
```
```
+================================================================+
|                           MAIN MENU                            |
+================================================================+

  Welcome, Rahul Sharma!

    [1]  Start Quiz
    [2]  Instructions
    [3]  Exit

  Enter your choice (1-3): 7
  Invalid input! Please enter a number from 1 to 3.
  Enter your choice (1-3): 1
```
```
+================================================================+
|                    QUIZ STARTED - ALL THE BEST!                |
+================================================================+
|  Student          : Rahul Sharma                               |
|  Category         : Computer Basics                            |
|  Level            : Medium                                     |
+================================================================+

+----------------------------------------------------------------+
  Question 3 of 10                      Score so far: 2
+----------------------------------------------------------------+

  Q3. Which of these memories is the fastest?

      A)  Hard disk
      B)  Pen drive
      C)  RAM
      D)  Cache memory

  Your answer (A/B/C/D): b
  [X] Wrong! Correct answer: D) Cache memory
```
```
+================================================================+
|                          QUIZ RESULT                           |
+================================================================+
|  Student          : Rahul Sharma                               |
|  Category         : Computer Basics                            |
|  Level            : Medium                                     |
+----------------------------------------------------------------+
|  Total Questions  : 10                                         |
|  Correct Answers  : 8                                          |
|  Wrong Answers    : 2                                          |
|  Score            : 8                                          |
|  Percentage       : 80.0%                                      |
+----------------------------------------------------------------+
|               Very good! Keep up the great work.               |
+================================================================+

  Do you want to play again? (Y/N): n
```

Performance messages: 90%+ Outstanding · 70%+ Very good · 50%+ Good effort · 30%+ Fair · below 30% Needs improvement.

## 5. Viva Questions and Answers

1. **What is QuizMaster?** A console quiz program in C with 40 multiple-choice questions in two categories and two levels.
2. **Which header files did you use and why?** `stdio.h` for printf/scanf, `string.h` for strlen, `stdlib.h` for system() and exit().
3. **How are questions stored?** In a 2D char array; each row is one question string.
4. **How are options stored?** In another 2D char array. Question `n` has options at rows `n*4` to `n*4+3`.
5. **How are correct answers stored?** In a 1D int array: 0 = A, 1 = B, 2 = C, 3 = D.
6. **How does the program find the right set of questions?** Set = `category * 2 + level`; first question = `set * 10`.
7. **How is the answer checked?** `if (choice == answers[qi])` compares the user's choice with the key.
8. **How is the percentage calculated?** `(float)correct * 100 / total`.
9. **Why `(float)` in the percentage formula?** Without it, int / int drops the decimal part.
10. **How do you validate input?** Input is read as text, its length is checked with `strlen()`, and the character is compared with the allowed range. Wrong input shows an error and asks again.
11. **Why read numbers as text instead of `%d`?** If a user types a letter into `scanf("%d")`, the letter stays in the buffer and the loop can repeat forever. Reading text avoids this.
12. **Which loops did you use?** `for` (printing, questions), `while` (validation), `do-while` (main menu / play again).
13. **Where did you use `switch`?** In `main()` for the menu choice (Start, Instructions, Exit).
14. **Where did you use `break` and `continue`?** `break` in switch cases and in `isValidName()`; `continue` in `readAnswer()` to ask again after wrong-length input.
15. **Where did you use pointers?** `char *` parameters for strings, `isValidName()` walks a string with `p++`, and `calculateResult()` uses `int *wrong` and `float *percent` to return two values.
16. **What does `const char *` mean?** A pointer to text that the function will not change.
17. **What is `'\0'`?** The null character; it marks the end of every string.
18. **What does `strlen()` do?** Returns the number of characters in a string (without `'\0'`).
19. **Why use functions?** To split the program into small parts that are easier to read, test and reuse.
20. **How are small letters converted to capital?** Subtract 32 (`'a' - 'A' = 32` in ASCII).
21. **What does `%-16s` mean in printf?** Print a string left-aligned in a field 16 characters wide.
22. **What does `system("cls")` do?** Runs the Windows command that clears the screen.
23. **How does the program exit?** The user picks Exit in the menu or answers N to "play again"; `main()` then prints the goodbye screen and returns 0.
24. **What are the limits of this project?** Fixed questions, same order every time, no saved scores (file handling is not in the syllabus).

## 6. Project Report

### Title
QuizMaster — C Language Quiz Application

### Introduction
QuizMaster is a console-based quiz program written in C. The student enters a name, chooses a category and a difficulty level, answers 10 multiple-choice questions, and receives an automatic score, percentage and performance message. It is built using only the concepts of the first-semester C syllabus.

### Objectives
- Apply arrays, strings, functions, loops, decisions and basic pointers in one working program.
- Build a menu-driven program with input validation.
- Give students a simple tool to practise C programming and computer basics.

### Features
- Welcome screen and main menu with ASCII borders and colours
- Student name input (validated)
- Categories: C Programming, Computer Basics
- Levels: Easy, Medium (10 questions each, 40 in total)
- Four options per question; answers accepted as A/B/C/D in capital or small letters
- Instant correct / wrong feedback with the right answer shown
- Final result: total, correct, wrong, score, percentage
- Performance message based on percentage
- Play again or exit
- Input validation for menu, answers, name and Y/N

### Algorithm
**Main program**
1. Show the welcome screen and read the student name (repeat until valid).
2. Show the main menu and read the choice (1–3).
3. If Instructions: show them and go to step 2.
4. If Exit: go to step 9.
5. If Start Quiz: read category (1–2) and level (1–2).
6. Compute `set = category * 2 + level` and `start = set * 10`.
7. For each of 10 questions: display the question and four options → read answer (A–D) → if it equals `answers[start + q]` then `correct++` and show "Correct", else show "Wrong" and the right answer.
8. Compute `wrong = 10 - correct` and `percent = correct * 100 / 10`; show the result and a message. Ask "play again?". If Y go to step 2.
9. Show the goodbye screen and stop.

**Input validation**
1. Read a word as text.
2. If its length is not 1, or the character is outside the allowed range, show an error and ask again.
3. Otherwise accept it.

### Concepts Used
Variables and constants (`#define`), data types (`int`, `float`, `char`), operators, `printf()`/`scanf()`, `if`, `if-else`, nested `if`, `switch`, `for`, `while`, `do-while`, `break`, `continue`, 1D and 2D arrays, strings and `strlen()`, user-defined functions with parameters and return values, basic pointers and pointers with arrays.

### Conclusion
QuizMaster meets all its objectives. It works correctly for every valid and invalid input tested, uses only syllabus concepts, and is divided into small functions that are easy to explain.

### Future Scope
- Random question order and more questions per category
- Timer for each question
- Saving high scores in a file (after learning file handling)
- Structures to store each question as one record
- More categories and a Hard level

## 7. Testing Checklist

| # | Test | Input | Expected result | Status |
|---|---|---|---|---|
| 1 | Name with no letters | `123` | Error, asks again | ☐ |
| 2 | Valid name with space | `Rahul Sharma` | Accepted, shown on menu | ☐ |
| 3 | Menu: out of range | `7` | Error, asks again | ☐ |
| 4 | Menu: letter / long text | `abc`, `12` | Error, asks again | ☐ |
| 5 | Instructions | `2`, then any word | Instructions shown, back to menu | ☐ |
| 6 | Category / level invalid | `0`, `3`, `x` | Error, asks again | ☐ |
| 7 | All four sets open | 1/1, 1/2, 2/1, 2/2 | Correct set of questions each time | ☐ |
| 8 | Correct answer | right letter | Green "Correct", score +1 | ☐ |
| 9 | Wrong answer | wrong letter | Red "Wrong", right answer shown, score unchanged | ☐ |
| 10 | Small letter answer | `b` | Treated as `B` | ☐ |
| 11 | Invalid answer | `E`, `5`, `ab`, `#` | Error, same question asked again | ☐ |
| 12 | Perfect score | all correct | 10 correct, 0 wrong, 100.0%, "Outstanding" | ☐ |
| 13 | All wrong | all wrong | 0 correct, 10 wrong, 0.0%, "Needs improvement" | ☐ |
| 14 | Mixed score | e.g. 7 correct | 7 / 3 / 70.0%, "Very good" | ☐ |
| 15 | Score arithmetic | any run | correct + wrong = 10 | ☐ |
| 16 | Play again invalid | `x`, `yes` | Error, asks again | ☐ |
| 17 | Play again = Y | `Y` | Returns to main menu, name remembered | ☐ |
| 18 | Play again = N | `N` | Goodbye screen, program ends | ☐ |
| 19 | Exit from menu | `3` | Goodbye screen, program ends | ☐ |

Answer key (set → correct options in order):
- C Easy: B C A D B C C D A B
- C Medium: C B C B D C A B A D
- Computer Easy: A D B C A B C D A B
- Computer Medium: C A D B C D A C B D
