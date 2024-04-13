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
            try {
                question.correctAnswer = stoi(token);
            } catch (const std::invalid_argument& e) {
                std::cerr << "Invalid argument: " << e.what() << std::endl;
                cout << "Skipping question: " << question.text << endl;
            } catch (const std::out_of_range& e) {
                std::cerr << "Out of range: " << e.what() << std::endl;
            } catch (const std::exception& e) {
                std::cerr << "General std::exception: " << e.what() << std::endl;
            }

            questions.push_back(question);
        }
        inputFile.close();
    } else
        cout << "Can't open file: " << fileName << endl;

    return questions;
}

int getValidAnswer() {
    int userAnswer;
    while (true) {
        cout << "Insert your answer (1, 2, or 3, 0 to leave): ";
        if (cin >> userAnswer) {
            if (userAnswer >= 0 && userAnswer <= 3)
                break;
            else
                cout << "Input not valid. Please insert 0, 1, 2, or 3." << endl;
        } else {
            cout << "Invalid input. Please enter a valid integer." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
         cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    return userAnswer;
}

void toFile(const Question& question, ofstream& outputFile) {
    outputFile << question.text << '*';
    for (const string& answer : question.answers)
        outputFile << answer << '*';
    outputFile << question.correctAnswer << endl;
}

void saveQuestions(const string& fileName, const vector<Question>& qs) {
    string outputFileName = fileName; // default fname
    string aux;
    std::cout << "\nEnter a file name: ";
    std::cin >> aux;

    if (aux.length() < 4 || aux.substr(aux.length() - 4) != ".txt")
        std::cout << "File provided wasn't a txt file: appending to " << fileName << std::endl;
    else
        outputFileName = aux;

    ofstream outputFile(outputFileName, ios::app);

    if (outputFile.is_open()) {
        for (const Question& q : qs)
            toFile(q, outputFile);

        outputFile.close();
        cout << "Questions saved to " << outputFileName << endl;
    } else
        cout << "Unable to open the output file." << endl;
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

        int userAnswer = getValidAnswer();

        if (userAnswer == 0) {
            string saveFile;
            cout << "\nDo you want to save missing questions to a file? (y/n): ";
            cin >> saveFile;

            if (saveFile == "y" || saveFile == "Y")
                saveQuestions("missing_questions.txt", questions);
            break;
        }

        answeredQuestions++;
   
        if (userAnswer == currentQuestion.correctAnswer) {
            cout << "\nCorrect answer!\n" << endl;
            correctAnswers++;
        } else {
            cout << "\nWrong answer. The correct one is: " << currentQuestion.correctAnswer << ".\n\n";
            incorrectQuestions.push_back(currentQuestion);
        }

        // A question can appear only once.
        questions.pop_back();
    }

    // All questions answered or put 0
    double percentageCorrect = static_cast<double>(correctAnswers) / (answeredQuestions ? answeredQuestions : 1) * 100;
    cout << "---You answered " << percentageCorrect << "% of the questions correctly." << endl;

    string saveFile;
    cout << "\nDo you want to save incorrect questions to a file? (y/n): ";
    cin >> saveFile;

    if (saveFile == "y" || saveFile == "Y")
        saveQuestions("incorrect_questions.txt", incorrectQuestions);

    return 0;
}
