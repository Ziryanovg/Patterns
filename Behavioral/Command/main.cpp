#include <iostream>
#include <list>
#include <memory>
using namespace std;

/******************************************************
 * Команда
 * ***************************************************/

class ICommand{
public:
    virtual void execute() = 0;
    virtual void unExecute() = 0;
};

class AddLetterCommand : public ICommand{
public:
    AddLetterCommand(string* data):m_data(data){}
    virtual ~AddLetterCommand() = default;

    // ICommand interface
    void execute() override{
        if(!m_data) return;
        m_data->push_back('L');
    }
    void unExecute() override{
        if(!m_data) return;
        m_data->resize(m_data->size()-1);
    }

private:
    string* m_data = nullptr;
};

class Invoker{
public:
    Invoker(){
        m_it = m_commands.begin();
    }

    void addString(string* str_ptr){
        m_data = str_ptr;
    }

    void addLetter(){
        if(!m_data) return;

        if(m_commands.size() > 9)
            m_commands.pop_front();
        m_commands.push_back(std::unique_ptr<ICommand>(new AddLetterCommand(m_data)));
        m_commands.back()->execute();
        m_it = --m_commands.end();
        cout << "string is " << *m_data << endl;
    }

    void Undo(){
        if(!m_data) return;
        if(m_it == m_commands.begin())
            return;
        cout << "Undo" << endl;
        m_it->get()->unExecute();
        m_it--;

        cout << "string is " << *m_data << endl;
    }

    void Redo(){
        if(!m_data) return;
        if(m_it == m_commands.end())
            return;

        cout << "Redo" << endl;
        ++m_it;
        m_it->get()->execute();

        cout << "string is " << *m_data << endl;
    }


private:
    list<std::shared_ptr<ICommand>>::iterator m_it;
    list<std::shared_ptr<ICommand>> m_commands;
    string* m_data = nullptr;
};

int main()
{
    auto s = new string;
    Invoker invoker;
    invoker.addString(s);
    invoker.addLetter();
    invoker.addLetter();
    invoker.Undo();
    invoker.Redo();

    delete s;

    return 0;
}
