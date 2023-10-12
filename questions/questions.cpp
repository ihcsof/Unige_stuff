#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <ctime>
#include <cstdlib>
#include <algorithm>
#include <random>

using namespace std;

struct Question {
    string text;
    vector<string> answers;
    int correctAnswer;
};

vector<Question> readQuestionsFromFile(const string& fileName) {
    vector<Question> questions;
    ifstream inputFile(fileName);

    if (inputFile.is_open()) {
        string line;
        while (getline(inputFile, line)) {
            istringstream iss(line);
            string token;
            Question question;

            getline(iss, question.text, '*');

            for (int i = 0; i < 3; i++) {
                getline(iss, token, '*');
                question.answers.push_back(token);
            }

            getline(iss, token, '*');
            question.correctAnswer = stoi(token);

            questions.push_back(question);
        }
        inputFile.close();
    } else
        cout << "Can't open file: " << fileName << endl;

    return questions;
}

void saveIncorrects(const Question& question, ofstream& outputFile) {
    outputFile << question.text << '*';
    for (const string& answer : question.answers)
        outputFile << answer << '*';
    outputFile << question.correctAnswer << endl;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cout << "Usage: " << argv[0] << " <filename>" << endl;
        return 1;
    }

    string fileName = argv[1];
    vector<Question> questions = readQuestionsFromFile(fileName);

    if (questions.empty()) {
        cout << "No questions available" << endl;
        return 1;
    }

    srand(time(0));

    int correctAnswers = 0;
    int answeredQuestions = 0;
    vector<Question> incorrectQuestions;

    while (!questions.empty()) {
        random_device rd;
        mt19937 g(rd());
        shuffle(questions.begin(), questions.end(), g);

        const Question& currentQuestion = questions.back();

        cout << "Question: " << currentQuestion.text << endl;
        cout << "1. " << currentQuestion.answers[0] << endl;
        cout << "2. " << currentQuestion.answers[1] << endl;
        cout << "3. " << currentQuestion.answers[2] << endl;

        int userAnswer;
        cout << "Insert your answer (1, 2, or 3, 0 to leave): ";
        cin >> userAnswer;

        if (userAnswer == 0) break;

        answeredQuestions++;

        if (userAnswer >= 1 && userAnswer <= 3)
            if (userAnswer == currentQuestion.correctAnswer) {
                cout << "\nCorrect answer!\n" << endl;
                correctAnswers++;
            } else {
                cout << "\nWrong answer. The correct one is: " << currentQuestion.correctAnswer << ".\n\n";
                 incorrectQuestions.push_back(currentQuestion);
            }
        else
            cout << "Input not valid. Please insert 1, 2, or 3." << endl;

        // A question can appear only once.
        questions.pop_back();
    }

    // All questions answered or put 0
    double percentageCorrect = static_cast<double>(correctAnswers) / (answeredQuestions ? answeredQuestions : 1) * 100;
    cout << "---You answered " << percentageCorrect << "% of the questions correctly." << endl;

    string saveFile;
    cout << "\nDo you want to save incorrect questions to a file? (y/n): ";
    cin >> saveFile;

    if (saveFile == "y" || saveFile == "Y") {
        string outputFileName = "incorrect_questions.txt"; // default fname
        string aux;
        std::cout << "\nEnter a file name: ";
        std::cin >> aux;
    
        if (aux.length() < 4 || aux.substr(aux.length() - 4) != ".txt")
            std::cout << "File provided wasn't a txt file: appending to incorrect_questions.txt" << std::endl;
        else
            outputFileName = aux;

        ofstream outputFile("err/"+outputFileName, ios::app);

        if (outputFile.is_open()) {
            for (const Question& incorrectQuestion : incorrectQuestions)
                saveIncorrects(incorrectQuestion, outputFile);

            outputFile.close();
            cout << "Incorrect questions saved to " << outputFileName << endl;
        } else
            cout << "Unable to open the output file." << endl;
    }

    return 0;
}