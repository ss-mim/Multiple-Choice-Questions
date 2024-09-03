#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <cctype>

using namespace std;

class Question {
    string questionText;
    vector<string> options;
    char correctAnswer;

public:
    Question(const string& q, const vector<string>& opts, char ans)
        : questionText(q), options(opts), correctAnswer(ans) {}

    void display() const {
        cout << questionText << endl;
        for (size_t i = 0; i < options.size(); ++i)
            cout << char('A' + i) << ": " << options[i] << endl;
    }

    bool checkAnswer(char answer) const {
        return toupper(answer) == toupper(correctAnswer);
    }

    void showCorrectAnswer() const {
        cout << "The correct answer is " << correctAnswer << ": " << options[toupper(correctAnswer) - 'A'] << endl;
    }
};

class ScoredQuiz {
    vector<Question> questions;
    int score;

public:
    ScoredQuiz() : score(0) {}

    void loadQuestions(const string& filename) {
        ifstream file(filename);
        if (!file) {
            cerr << "Error: Could not open file " << filename << endl;
            return;
        }

        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            string questionText, correctAnswerStr;
            vector<string> options(4);

            getline(ss, questionText, ',');
            for (string& opt : options) getline(ss, opt, ',');
            getline(ss, correctAnswerStr, ',');

            if (!questionText.empty() && !correctAnswerStr.empty())
                questions.emplace_back(questionText, options, correctAnswerStr[0]);
        }
    }

    void startQuiz(int numQuestions) {
        cout << "Starting scored quiz..." << endl;
        for (int i = 0; i < numQuestions && i < questions.size(); ++i) {
            questions[i].display();
            char answer;
            
            cout << "Your answer (A/B/C/D): ";
            while (true) {
                cin >> answer;
                if (toupper(answer) >= 'A' && toupper(answer) <= 'D') break;
                cout << "Invalid answer. Please enter A, B, C, or D: ";
            }

            if (questions[i].checkAnswer(answer)) {
                score++;
            } else {
                score--;
                cout << "Wrong answer! You lost 1 point." << endl;
                questions[i].showCorrectAnswer();
            }
        }

        cout << "Quiz finished. Your total score is: " << score << endl;
    }
};

int main() {

    cout << "***************************************************************" << endl;
    cout << "*                  Know Computer Basic                        *" << endl;
    cout << "***************************************************************" << endl;

    int numQuestions;
    cout << "How many questions would you like to answer?(Maximum 50): ";
    cin >> numQuestions;

    ScoredQuiz quiz;
    quiz.loadQuestions("questions.csv");
    quiz.startQuiz(numQuestions);

    return 0;
}