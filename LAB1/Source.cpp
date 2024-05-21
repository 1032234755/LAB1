#include <iostream>
#include <functional>
#include <stdexcept>

using namespace std;

// ��������� ��� ���� ������
template<typename T>
struct Node {
    T data;
    Node* next;
    Node(T data) : data(data), next(nullptr) {}
};

// ����� ������������ ������
template<typename T>
class SinglyLinkedList {
private:
    Node<T>* head;

public:
    SinglyLinkedList() : head(nullptr) {}

    // ����� ��� ���������� �������� � ������ ������
    void addFront(T data) {
        Node<T>* newNode = new Node<T>(data);
        newNode->next = head;
        head = newNode;
    }

    // ����� ��� ���������� �������� � ����� ������
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

    // ����� ��� ���������� �������� �� �������
    void addAtIndex(T data, int index) {
        if (index < 0) throw out_of_range("������ ��� ���������");
        if (index == 0) {
            addFront(data);
            return;
        }
        Node<T>* newNode = new Node<T>(data);
        Node<T>* temp = head;
        for (int i = 0; i < index - 1; ++i) {
            if (!temp) throw out_of_range("������ ��� ���������");
            temp = temp->next;
        }
        newNode->next = temp->next;
        temp->next = newNode;
    }

    // ����� ��� �������� ������� ��������
    void removeFront() {
        if (!head) return;
        Node<T>* temp = head;
        head = head->next;
        delete temp;
    }

    // ����� ��� �������� ���������� ��������
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

    // ����� ��� �������� �������� �� �������
    void removeAtIndex(int index) {
        if (index < 0 || !head) throw out_of_range("������ ��� ���������");
        if (index == 0) {
            removeFront();
            return;
        }
        Node<T>* temp = head;
        for (int i = 0; i < index - 1; ++i) {
            if (!temp->next) throw out_of_range("������ ��� ���������");
            temp = temp->next;
        }
        Node<T>* nodeToDelete = temp->next;
        temp->next = temp->next->next;
        delete nodeToDelete;
    }

    // ����� ��� ���������� �������� �� �������
    void updateAtIndex(T data, int index) {
        if (index < 0 || !head) throw out_of_range("������ ��� ���������");
        Node<T>* temp = head;
        for (int i = 0; i < index; ++i) {
            if (!temp) throw out_of_range("������ ��� ���������");
            temp = temp->next;
        }
        temp->data = data;
    }

    // ����� ��� ������ �������� �� �������
    T getAtIndex(int index) {
        if (index < 0 || !head) throw out_of_range("������ ��� ���������");
        Node<T>* temp = head;
        for (int i = 0; i < index; ++i) {
            if (!temp) throw out_of_range("������ ��� ���������");
            temp = temp->next;
        }
        return temp->data;
    }

    // ����� ��� ������ �������� �� ������� (�������)
    T find(std::function<bool(T)> filter) {
        Node<T>* temp = head;
        while (temp) {
            if (filter(temp->data)) {
                return temp->data;
            }
            temp = temp->next;
        }
        throw runtime_error("������� �� ������");
    }

    // ����� ��� ������ ������
    void printList() const {
        Node<T>* temp = head;
        while (temp) {
            cout << temp->data << " -> ";
            temp = temp->next;
        }
        cout << "nullptr" << endl;
    }

    // ���������� ��� ������� ������
    ~SinglyLinkedList() {
        while (head) {
            removeFront();
        }
    }
};

// ������ �������������
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
        cout << "������� �� ������� 0: " << list.getAtIndex(0) << endl; // 10
        cout << "������� �� �������: " << list.find([](int value) { return value == 10; }) << endl; // 10
    }
    catch (const std::exception& e) {
        cout << e.what() << endl;
    }

    return 0;
}
