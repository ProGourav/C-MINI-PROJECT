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

