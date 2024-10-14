#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <limits>
#include <random>

class Question {
public:
    std::string text;
    std::vector<std::string> answers;
    int correctAnswer;

    Question(const std::string& text, const std::vector<std::string>& answers, int correctAnswer)
        : text(text), answers(answers), correctAnswer(correctAnswer) {}
};

class Quiz {
private:
    std::vector<Question> questions;

public:
    Quiz(const std::vector<Question>& questions) : questions(questions) {}

    void start() {
        std::srand(std::time(0));
        std::vector<Question> selectedQuestions = selectQuestions();
        int score = 0;

        for (auto& question : selectedQuestions) {
            displayQuestion(question);
            int answer;
            while (!(std::cin >> answer) || answer < 1 || answer > question.answers.size()) {
                std::cout << "Неверный ввод. Попробуйте снова: ";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
            // Проверяем правильный ответ по исходному индексу правильного ответа
            if (question.answers[question.correctAnswer] == question.answers[answer - 1]) {
                score++;
            }
        }
        displayResult(score);
    }

private:
    std::vector<Question> selectQuestions() {
        std::shuffle(questions.begin(), questions.end(), std::default_random_engine(std::time(0)));
        size_t numberOfQuestionsToSelect = std::min<size_t>(10, questions.size());
        return std::vector<Question>(questions.begin(), questions.begin() + numberOfQuestionsToSelect);
    }

    void displayQuestion(Question& question) {
        std::cout << question.text << std::endl;

        // Сохраняем индекс правильного ответа
        int correctIndex = question.correctAnswer-1;
        std::vector<std::string> shuffledAnswers = question.answers;

        // Перемешиваем ответы
        std::shuffle(shuffledAnswers.begin(), shuffledAnswers.end(), std::default_random_engine(std::time(0)));

        // Находим новый индекс правильного ответа
        int newCorrectIndex = std::find(shuffledAnswers.begin(), shuffledAnswers.end(), question.answers[correctIndex]) - shuffledAnswers.begin();

        for (size_t i = 0; i < shuffledAnswers.size(); i++) {
            std::cout << i + 1 << ". " << shuffledAnswers[i] << std::endl;
        }

        // Обновляем правильный ответ для вопроса
        question.correctAnswer = newCorrectIndex;
    }

    void displayResult(int score) {
        std::cout << "Ваш результат: " << score << std::endl;
        if (score >= 9) {
            std::cout << "Отлично!" << std::endl;
        }
        else if (score >= 7) {
            std::cout << "Хорошо!" << std::endl;
        }
        else if (score >= 5) {
            std::cout << "Удовлетворительно!" << std::endl;
        }
        else {
            std::cout << "Не удовлетворительно!" << std::endl;
        }
    }
};

int main() {
    setlocale(LC_ALL, "");
    std::vector<Question> questions = {
        Question("Какой язык программирования является объектно-ориентированным?", {"C", "C++", "Pascal"}, 2),
        Question("Какой из этих операторов используется для определения класса в C++?", {"class", "struct", "type"}, 1),
        Question("Что выводит данный код: std::cout << 5 + 10;", {"15", "510", "Ошибка"}, 1),
        Question("Какой язык программирования является объектно-ориентированным?", {"C", "C++", "Pascal"}, 2),
        Question("Какой оператор используется для присваивания значения переменной?", {"=", "==", "==="}, 1),
        Question("Что такое массив?", {"Структура данных для хранения элементов одного типа", "Тип данных", "Функция"}, 1),
        Question("Какой из следующих языков является функциональным?", {"Java", "Haskell", "Python"}, 2),
        Question("Что такое инкапсуляция?", {"Скрытие деталей реализации", "Наследование классов", "Полиморфизм"}, 1),
        Question("В каком языке используется ключевое слово 'async'?", {"Java", "C#", "Ruby"}, 2),
        Question("Что делает оператор 'break' в цикле?", {"Выходит из цикла", "Переходит к следующей итерации", "Стирает цикл"}, 1),
        Question("Какой из следующих типов данных является логическим?", {"int", "float", "bool"}, 3),
        Question("Какой метод используется для добавления элемента в список в Python?", {"append()", "add()", "insert()"}, 1),
        Question("Какой из этих протоколов используется для передачи веб-страниц?", {"HTTP", "FTP", "SMTP"}, 1),
        Question("Что такое Git?", {"Система управления версиями", "Язык программирования", "Система базы данных"}, 1),
        Question("Какой символ используется для комментариев в языке Python?", {"//", "#", "/* */"}, 2),
        Question("Что такое SQL?", {"Язык для работы с графикой", "Язык запросов к базе данных", "Язык программирования"}, 2),
        Question("Какой метод используется для преобразования строки в целое число в Python?", {"int()", "str()", "float()"}, 1),
        Question("Что такое AJAX?", {"Технология для асинхронных запросов", "Тип базы данных", "Язык программирования"}, 1),
        Question("Какой из следующих языков является интерпретируемым?", {"C++", "Python", "Java"}, 2),
        Question("Какой алгоритм используется для сортировки массива по возрастанию?", {"Сортировка выбором", "Сортировка вставками", "Сортировка пузырьком"}, 3),
        Question("Что такое сложность алгоритма?", {"Количество строк кода", "Количество операций, необходимых для выполнения", "Стоимость алгоритма"}, 2),
        Question("Какой оператор в C++ используется для указателя?", {"&", "*", "%"}, 2),
        Question("Какой метод используется для считывания данных из файла в Python?", {"read()", "write()", "input()"}, 1)
    };

    Quiz quiz(questions);
    quiz.start();

    return 0;
}