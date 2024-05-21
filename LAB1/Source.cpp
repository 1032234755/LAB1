#include <iostream>
#include <functional>
#include <stdexcept>

using namespace std;

// Структура для узла списка
template<typename T>
struct Node {
    T data;
    Node* next;
    Node(T data) : data(data), next(nullptr) {}
};

// Класс односвязного списка
template<typename T>
class SinglyLinkedList {
private:
    Node<T>* head;

public:
    SinglyLinkedList() : head(nullptr) {}

    // Метод для добавления элемента в начало списка
    void addFront(T data) {
        Node<T>* newNode = new Node<T>(data);
        newNode->next = head;
        head = newNode;
    }

    // Метод для добавления элемента в конец списка
    void addBack(T data) {
        Node<T>* newNode = new Node<T>(data);
        if (!head) {
            head = newNode;
        }
        else {
            Node<T>* temp = head;
            while (temp->next) {
                temp = temp->next;
            }
            temp->next = newNode;
        }
    }

    // Метод для добавления элемента по индексу
    void addAtIndex(T data, int index) {
        if (index < 0) throw out_of_range("Индекс вне диапазона");
        if (index == 0) {
            addFront(data);
            return;
        }
        Node<T>* newNode = new Node<T>(data);
        Node<T>* temp = head;
        for (int i = 0; i < index - 1; ++i) {
            if (!temp) throw out_of_range("Индекс вне диапазона");
            temp = temp->next;
        }
        newNode->next = temp->next;
        temp->next = newNode;
    }

    // Метод для удаления первого элемента
    void removeFront() {
        if (!head) return;
        Node<T>* temp = head;
        head = head->next;
        delete temp;
    }

    // Метод для удаления последнего элемента
    void removeBack() {
        if (!head) return;
        if (!head->next) {
            delete head;
            head = nullptr;
            return;
        }
        Node<T>* temp = head;
        while (temp->next && temp->next->next) {
            temp = temp->next;
        }
        delete temp->next;
        temp->next = nullptr;
    }

    // Метод для удаления элемента по индексу
    void removeAtIndex(int index) {
        if (index < 0 || !head) throw out_of_range("Индекс вне диапазона");
        if (index == 0) {
            removeFront();
            return;
        }
        Node<T>* temp = head;
        for (int i = 0; i < index - 1; ++i) {
            if (!temp->next) throw out_of_range("Индекс вне диапазона");
            temp = temp->next;
        }
        Node<T>* nodeToDelete = temp->next;
        temp->next = temp->next->next;
        delete nodeToDelete;
    }

    // Метод для обновления элемента по индексу
    void updateAtIndex(T data, int index) {
        if (index < 0 || !head) throw out_of_range("Индекс вне диапазона");
        Node<T>* temp = head;
        for (int i = 0; i < index; ++i) {
            if (!temp) throw out_of_range("Индекс вне диапазона");
            temp = temp->next;
        }
        temp->data = data;
    }

    // Метод для поиска элемента по индексу
    T getAtIndex(int index) {
        if (index < 0 || !head) throw out_of_range("Индекс вне диапазона");
        Node<T>* temp = head;
        for (int i = 0; i < index; ++i) {
            if (!temp) throw out_of_range("Индекс вне диапазона");
            temp = temp->next;
        }
        return temp->data;
    }

    // Метод для поиска элемента по фильтру (функции)
    T find(std::function<bool(T)> filter) {
        Node<T>* temp = head;
        while (temp) {
            if (filter(temp->data)) {
                return temp->data;
            }
            temp = temp->next;
        }
        throw runtime_error("Элемент не найден");
    }

    // Метод для вывода списка
    void printList() const {
        Node<T>* temp = head;
        while (temp) {
            cout << temp->data << " -> ";
            temp = temp->next;
        }
        cout << "nullptr" << endl;
    }

    // Деструктор для очистки памяти
    ~SinglyLinkedList() {
        while (head) {
            removeFront();
        }
    }
};

// Пример использования
int main() {
    setlocale(LC_ALL, "ru");

    SinglyLinkedList<int> list;

    list.addFront(3);
    list.addBack(5);
    list.addAtIndex(4, 1);
    list.addAtIndex(2, 0);
    list.printList(); // 2 -> 3 -> 4 -> 5 -> nullptr

    list.removeFront();
    list.printList(); // 3 -> 4 -> 5 -> nullptr

    list.removeBack();
    list.printList(); // 3 -> 4 -> nullptr

    list.removeAtIndex(1);
    list.printList(); // 3 -> nullptr

    list.updateAtIndex(10, 0);
    list.printList(); // 10 -> nullptr

    try {
        cout << "Элемент по индексу 0: " << list.getAtIndex(0) << endl; // 10
        cout << "Элемент по фильтру: " << list.find([](int value) { return value == 10; }) << endl; // 10
    }
    catch (const std::exception& e) {
        cout << e.what() << endl;
    }

    return 0;
}
