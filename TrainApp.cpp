#include <iostream>
#include <vector>
#include <iomanip>

class Train {
public:
    Train(int id, int numCars, int seatsPerCar) : id(id), numCars(numCars), seatsPerCar(seatsPerCar) {
        for (int i = 0; i < numCars; ++i) {
            for (int j = 0; j < seatsPerCar; ++j) {
                availableSeats.push_back(std::make_pair(i + 1, j + 1));
            }
        }
    }

    int getId() const {
        return id;
    }

    void displayAvailableSeats() const {
        std::cout << "Доступные места в поезде " << id << ":" << std::endl;
        for (const auto& seat : availableSeats) {
            std::cout << "Вагон " << seat.first << ", Место " << seat.second << std::endl;
        }
    }

    bool bookSeat() {
        if (!availableSeats.empty()) {
            std::pair<int, int> seat = availableSeats.back();
            availableSeats.pop_back();
            std::cout << "Место забронировано: Вагон " << seat.first << ", Место " << seat.second << std::endl;
            return true;
        }
        else {
            std::cout << "Нет доступных мест." << std::endl;
            return false;
        }
    }

    void cancelBooking(int car, int seat) {
        if (car >= 1 && car <= numCars && seat >= 1 && seat <= seatsPerCar) {
            availableSeats.push_back(std::make_pair(car, seat));
            std::cout << "Бронирование отменено: Вагон " << car << ", Место " << seat << std::endl;
        }
        else {
            std::cout << "Некорректный номер вагона или места." << std::endl;
        }
    }

private:
    int id;
    int numCars;
    int seatsPerCar;
    std::vector<std::pair<int, int>> availableSeats; // вектор пар (номер вагона, номер места)
};

class ReservationSystem {
public:
    void initializeTrains() {
        for (int i = 1; i <= 8; ++i) {
            Train train(i, 7, 20);
            trains.push_back(train);
        }
    }

    void displayTrains() const {
        for (const Train& train : trains) {
            std::cout << "Поезд " << train.getId() << std::endl;
            train.displayAvailableSeats();
            std::cout << std::endl;
        }
    }

    void bookSeat(int trainId) {
        if (trainId >= 1 && trainId <= 8) {
            trains[trainId - 1].bookSeat();
        }
        else {
            std::cout << "Некорректный номер поезда." << std::endl;
        }
    }

    void cancelBooking(int trainId, int car, int seat) {
        if (trainId >= 1 && trainId <= 8) {
            trains[trainId - 1].cancelBooking(car, seat);
        }
        else {
            std::cout << "Некорректный номер поезда." << std::endl;
        }
    }

private:
    std::vector<Train> trains;
};

int main() {
    ReservationSystem reservationSystem;
    reservationSystem.initializeTrains();

    int choice;
    do {
        std::cout << "Выберите действие:" << std::endl;
        std::cout << "1. Показать доступные поезда и места" << std::endl;
        std::cout << "2. Забронировать место" << std::endl;
        std::cout << "3. Отменить бронирование" << std::endl;
        std::cout << "0. Выйти" << std::endl;

        std::cin >> choice;

        switch (choice) {
        case 1:
            reservationSystem.displayTrains();
            break;
        case 2:
            int bookTrainId;
            std::cout << "Введите номер поезда для бронирования: ";
            std::cin >> bookTrainId;
            reservationSystem.bookSeat(bookTrainId);
            break;
        case 3:
            int cancelTrainId, cancelCar, cancelSeat;
            std::cout << "Введите номер поезда для отмены бронирования: ";
            std::cin >> cancelTrainId;
            std::cout << "Введите номер вагона: ";
            std::cin >> cancelCar;
            std::cout << "Введите номер места: ";
            std::cin >> cancelSeat;
            reservationSystem.cancelBooking(cancelTrainId, cancelCar, cancelSeat);
            break;
        case 0:
            std::cout << "Программа завершена." << std::endl;
            break;
        default:
            std::cout << "Некорректный ввод. Пожалуйста, повторите попытку." << std::endl;
        }

    } while (choice != 0);

    return 0;
}
