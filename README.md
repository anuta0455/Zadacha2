# Zadacha2
#include <iostream> 
#include <vector> 
#include <algorithm> 

// Структура для представления участника соревнования
struct Participant {
    int id; // Идентификатор участника
    int solved; // Количество решенных задач
    int penalty; // Общее время участника (штраф)
};

// Функция для сравнения участников при сортировке
bool compareParticipants(const Participant& p1, const Participant& p2) {
    if (p1.solved != p2.solved) { // Если количество решенных задач разное
        return p1.solved > p2.solved; // Сначала сортируем по убыванию количества решенных задач
    }
    else if (p1.penalty != p2.penalty) { // Если количество решенных задач одинаково, но общее время разное
        return p1.penalty < p2.penalty; // Сортируем по возрастанию общего времени
    }
    else { // Если количество решенных задач и общее время одинаковы
        return p1.id < p2.id; // Сортируем по возрастанию идентификатора
    }
}

int main() {
    setlocale(LC_ALL, "Russian"); // Установка локали для вывода на русском языке
    std::cout << "Введите количество блоков соревнований: ";
    int num_blocks;
    std::cin >> num_blocks;

    for (int b = 0; b < num_blocks; ++b) {
        std::vector<Participant> participants; // Вектор для хранения участников текущего блока соревнований

        std::cout << "Введите результаты участников (идентификатор, задача, время, результат), для завершения введите 0: " << std::endl;
        while (true) {
            int participant, problem, time;
            char result;
            std::cin >> participant;

            if (participant == 0) { // Если введен 0, завершаем ввод результатов текущего блока
                break;
            }

            std::cin >> problem >> time >> result;

            if (result == 'C') { // Если задача решена верно
                bool found = false;
                for (auto& p : participants) {
                    if (p.id == participant) { // Проверяем, есть ли участник уже в списке
                        p.solved++; // Увеличиваем количество решенных задач
                        p.penalty += time; // Добавляем время к общему времени участника
                        found = true;
                        break;
                    }
                }
                if (!found) { // Если участника нет в списке, добавляем его
                    participants.push_back({ participant, 1, time });
                }
            }
            else if (result == 'I') { // Если задача решена неверно
                for (auto& p : participants) {
                    if (p.id == participant) { // Находим участника в списке
                        p.penalty += 20; // Добавляем штраф 20 минут к общему времени
                        break;
                    }
                }
            }
        }

        std::sort(participants.begin(), participants.end(), compareParticipants); // Сортируем участников текущего блока

        for (const auto& participant : participants) { // Выводим отсортированный список участников
            if (participant.solved > 0) { // Если участник решил хотя бы одну задачу
                std::cout << participant.id << " " << participant.solved << " " << participant.penalty << std::endl;
            }
        }

        if (b < num_blocks - 1) { // Если это не последний блок соревнований, выводим пустую строку
            std::cout << std::endl;
        }
    }

    return 0;
}
