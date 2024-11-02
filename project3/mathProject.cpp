#include <iostream>
#include <cstdlib>
#include <string>
#include <ctime>
using namespace std;

/* Enum types for question levels and operation types */
enum QuestionLevels { easy = 1, medium = 2, hard = 3, mixedQuestions = 4 };
enum OperationTypes { add = 1, subtract = 2, multiply = 3, divide = 4, mixedOperations = 5 };

/* Converts selected operation type to string for display */
string displayOperationType(OperationTypes selectedOperation) {
    switch (selectedOperation) {
    case add:
        return "+";
    case subtract:
        return "-";
    case multiply:
        return "x";
    case divide:
        return "/";
    default:
        return "\nError in displayOperationType\n";
    }
}

/* Prompts the user to select an operation type */
OperationTypes selectOperationType() {
    short choice;
    do {
        cout << "Select operation type: add[1], subtract[2], multiply[3], divide[4], mixed[5]: ";
        cin >> choice;
    } while (choice < 1 || choice > 5);

    return (OperationTypes)choice;
}

/* Prompts the user to select a question difficulty level */
QuestionLevels selectQuestionLevel() {
    short choice;
    do {
        cout << "Select question level: easy[1], medium[2], hard[3], mixed[4]: ";
        cin >> choice;
    } while (choice < 1 || choice > 4);

    return (QuestionLevels)choice;
}

/* Generates a random number within the specified range */
int generateRandomNumber(int lowerBound, int upperBound) {
    return rand() % ((upperBound - lowerBound) + 1) + lowerBound;
}

/* Changes terminal color based on answer correctness */
void setTerminalColor(bool isCorrect) {
    if (isCorrect) {
        system("color 2F");
    }
    else {
        system("color 4F");
        cout << "\a";  // Sound alert for incorrect answer
    }
}

/* Gets the number of questions from the user */
int getNumberOfQuestions() {
    int numQuestions = 0;
    cout << "How many questions will the test have? ";
    cin >> numQuestions;
    return numQuestions;
}

/* Maps operation type to string for display in tables */
string mapOperationTypeForTable(OperationTypes operationType) {
    string operations[5] = { "add", "subtract", "multiply", "divide", "mixed" };
    return operations[operationType - 1];
}

/* Maps question level to string for display in tables */
string mapQuestionLevelForTable(QuestionLevels questionLevel) {
    string levels[4] = { "easy", "medium", "hard", "mixed" };
    return levels[questionLevel - 1];
}

/* Question structure to store question details */
struct Question {
    int number1;
    int number2;
    QuestionLevels level;
    OperationTypes operationType;
    int correctAnswer;
    int userAnswer;
    bool isAnswerCorrect = false;
};

/* Exam structure to store exam details */
struct Exam
{
    Question questions[100];
    short numQuestions;
    int correctAnswerCount = 0;
    int incorrectAnswerCount = 0;
    QuestionLevels selectedLevel;
    OperationTypes selectedOperationType;
    bool passed = false;
};

/* Calculates the result of an operation based on two numbers and the selected operation type */

int calculate(int number1, int number2, OperationTypes selectedOperation)
{
    switch (selectedOperation)
    {
    case add:
        return (number1 + number2);
    case subtract:
        return (number1 - number2);
    case divide:
        return (number1 / number2);
    case multiply:
        return (number1 * number2);
    default:
        return 999;  // Return a default error value if operation type is invalid
    }
}

/* Randomly selects a question level */
QuestionLevels getRandomQuestionLevel() {
    return (QuestionLevels)generateRandomNumber(1, 3);
}

/* Creates a question based on selected difficulty level and operation type */
Question createQuestion(QuestionLevels level, OperationTypes operationType) {
    Question newQuestion;
    if (level == mixedQuestions) {
        level = (QuestionLevels)generateRandomNumber(1, 3);
    }
    if (operationType == mixedOperations) {
        operationType = (OperationTypes)generateRandomNumber(1, 4);
    }
    newQuestion.operationType = operationType;

    switch (level) {
    case easy:
        newQuestion.number1 = generateRandomNumber(1, 10);
        newQuestion.number2 = generateRandomNumber(1, 10);
        newQuestion.level = level;
        newQuestion.correctAnswer = calculate(newQuestion.number1, newQuestion.number2, newQuestion.operationType);
        return newQuestion;

    case medium:
        newQuestion.number1 = generateRandomNumber(11, 50);
        newQuestion.number2 = generateRandomNumber(11, 50);
        newQuestion.level = level;
        newQuestion.correctAnswer = calculate(newQuestion.number1, newQuestion.number2, newQuestion.operationType);
        return newQuestion;

    case hard:
        newQuestion.number1 = generateRandomNumber(51, 99);
        newQuestion.number2 = generateRandomNumber(51, 99);
        newQuestion.level = level;
        newQuestion.correctAnswer = calculate(newQuestion.number1, newQuestion.number2, newQuestion.operationType);
        return newQuestion;
    }
}

/* Populates exam with questions based on selected level and operation type */
void createExam(Exam& exam) {
    for (int i = 0; i < exam.numQuestions; i++) {
        exam.questions[i] = createQuestion(exam.selectedLevel, exam.selectedOperationType);
    }
}

/* Gets user's answer for a question */
int getAnswerFromUser() {
    int answer = 0;
    cin >> answer;
    return answer;
}

/* Displays a question */
void displayQuestion(Exam& exam, short questionIndex) {
    cout << "\nQuestion [" << questionIndex + 1 << "/" << exam.numQuestions << "]\n\n";
    cout << exam.questions[questionIndex].number1 << endl;
    cout << exam.questions[questionIndex].number2 << " ";
    cout << displayOperationType(exam.questions[questionIndex].operationType);
    cout << "\n______________" << endl;
}

/* Compares the user's answer with the correct answer and updates the result */
void compareAnswer(Exam& exam, short questionIndex) {
    if (exam.questions[questionIndex].userAnswer != exam.questions[questionIndex].correctAnswer) {
        exam.questions[questionIndex].isAnswerCorrect = false;
        exam.incorrectAnswerCount++;
        cout << "Incorrect answer\n";
        cout << "Correct answer: " << exam.questions[questionIndex].correctAnswer << "\n";
    }
    else {
        exam.questions[questionIndex].isAnswerCorrect = true;
        exam.correctAnswerCount++;
        cout << "Correct answer :-)\n";
    }
    setTerminalColor(exam.questions[questionIndex].isAnswerCorrect);
}

/* Presents questions to the user and checks answers */
void askQuestionsAndCheckAnswers(Exam& exam) {
    for (short i = 0; i < exam.numQuestions; i++) {
        displayQuestion(exam, i);
        exam.questions[i].userAnswer = getAnswerFromUser();
        compareAnswer(exam, i);
    }
    exam.passed = (exam.correctAnswerCount >= exam.incorrectAnswerCount);
}

/* Returns result message based on exam passing status */
string getResultMessage(bool passed) {
    return passed ? "Passed :-)" : "Failed :-)";
}

/* Displays summary table of exam results */
void displayResultTable(Exam exam) {
    cout << "\n__________________________\n\n";
    cout << getResultMessage(exam.passed) << endl;
    cout << "__________________________\n\n";
    cout << "Summary:\n";
    cout << "Number of questions: " << exam.numQuestions << endl;
    cout << "Question level: " << mapQuestionLevelForTable(exam.selectedLevel) << endl;
    cout << "Operation type: " << mapOperationTypeForTable(exam.selectedOperationType) << endl;
    cout << "Correct answers: " << exam.correctAnswerCount << endl;
    cout << "Incorrect answers: " << exam.incorrectAnswerCount << endl;
    cout << "___________________________\n\n";
}

/* Main game loop function */
void gameLoop() {
    Exam exam;
    exam.numQuestions = getNumberOfQuestions();
    exam.selectedLevel = selectQuestionLevel();
    exam.selectedOperationType = selectOperationType();
    createExam(exam);
    askQuestionsAndCheckAnswers(exam);
    displayResultTable(exam);
}

/* Resets terminal to default state */
void resetTerminal() {
    system("cls");
    system("color 0F");
}

/* Starts the quiz program */
void start() {
    char playAgain = 'y';
    do {
        resetTerminal();
        gameLoop();
        cout << "Play again? Y/N\n";
        cin >> playAgain;
    } while (playAgain == 'y' || playAgain == 'Y');
}

int main() {
    srand((unsigned)time(NULL));
    start();
    return 0;
}
