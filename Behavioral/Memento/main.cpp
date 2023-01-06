#include <iostream>

//Паттерн хранитель
//Объект с состоянием
class Memento{
public:
    const std::string& getState() const { return m_state;}
private:
    friend class Originator;
    void setState(const std::string& state) {m_state = state;}
    std::string m_state;
};

//Чье состояние берем
class Originator{
public:
    Memento createMemento(){
        Memento memento;
        memento.setState(m_state);
        std::cout << "Memento saved: " << m_state << std::endl;
        return memento;
    }
    void setMemento(const Memento& memento){
        m_state = memento.getState();
        std::cout << "Memento restored: " << m_state << std::endl;
    }
    void setState(const std::string& state){
        m_state = state;
        std::cout << "Memento set: " << m_state << std::endl;
    }
private:
    std::string m_state = "Start";
};

int main(int argc, char *argv[])
{
    (void) argc;
    (void) argv;
    Originator originator;
    Memento mem = originator.createMemento();
    originator.setState("Hello");
    originator.setMemento(mem);
}
