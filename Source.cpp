#include <iostream> 
#include <vector> 
#include <algorithm> 

// ��������� ��� ������������� ��������� ������������
struct Participant {
    int id; // ������������� ���������
    int solved; // ���������� �������� �����
    int penalty; // ����� ����� ��������� (�����)
};

// ������� ��� ��������� ���������� ��� ����������
bool compareParticipants(const Participant& p1, const Participant& p2) {
    if (p1.solved != p2.solved) { // ���� ���������� �������� ����� ������
        return p1.solved > p2.solved; // ������� ��������� �� �������� ���������� �������� �����
    }
    else if (p1.penalty != p2.penalty) { // ���� ���������� �������� ����� ���������, �� ����� ����� ������
        return p1.penalty < p2.penalty; // ��������� �� ����������� ������ �������
    }
    else { // ���� ���������� �������� ����� � ����� ����� ���������
        return p1.id < p2.id; // ��������� �� ����������� ��������������
    }
}

int main() {
    setlocale(LC_ALL, "Russian"); // ��������� ������ ��� ������ �� ������� �����
    std::cout << "������� ���������� ������ ������������: ";
    int num_blocks;
    std::cin >> num_blocks;

    for (int b = 0; b < num_blocks; ++b) {
        std::vector<Participant> participants; // ������ ��� �������� ���������� �������� ����� ������������

        std::cout << "������� ���������� ���������� (�������������, ������, �����, ���������), ��� ���������� ������� 0: " << std::endl;
        while (true) {
            int participant, problem, time;
            char result;
            std::cin >> participant;

            if (participant == 0) { // ���� ������ 0, ��������� ���� ����������� �������� �����
                break;
            }

            std::cin >> problem >> time >> result;

            if (result == 'C') { // ���� ������ ������ �����
                bool found = false;
                for (auto& p : participants) {
                    if (p.id == participant) { // ���������, ���� �� �������� ��� � ������
                        p.solved++; // ����������� ���������� �������� �����
                        p.penalty += time; // ��������� ����� � ������ ������� ���������
                        found = true;
                        break;
                    }
                }
                if (!found) { // ���� ��������� ��� � ������, ��������� ���
                    participants.push_back({ participant, 1, time });
                }
            }
            else if (result == 'I') { // ���� ������ ������ �������
                for (auto& p : participants) {
                    if (p.id == participant) { // ������� ��������� � ������
                        p.penalty += 20; // ��������� ����� 20 ����� � ������ �������
                        break;
                    }
                }
            }
        }

        std::sort(participants.begin(), participants.end(), compareParticipants); // ��������� ���������� �������� �����

        for (const auto& participant : participants) { // ������� ��������������� ������ ����������
            if (participant.solved > 0) { // ���� �������� ����� ���� �� ���� ������
                std::cout << participant.id << " " << participant.solved << " " << participant.penalty << std::endl;
            }
        }

        if (b < num_blocks - 1) { // ���� ��� �� ��������� ���� ������������, ������� ������ ������
            std::cout << std::endl;
        }
    }

    return 0;
}
