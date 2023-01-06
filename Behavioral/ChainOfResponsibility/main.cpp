#include <iostream>

using namespace std;

/*************************************************
*  Цепочка обязанностей
*************************************************/

//Некий объект который обрабатывается в цепочку
class Event{
public:
    Event(int complexity) : m_complexity(complexity){}
    void processEvent(const std::string& handler) const{
        cout << "Event processed by " << handler << endl;
    }
    int getСomplexity() const { return m_complexity; }

private:
    int m_complexity = 0;
};

//Интерфейс обработчиков
class Handler{
public:
    virtual void process(const Event& event) {
        cout << m_description << " start to process" << endl;
        if(event.getСomplexity() > m_complexity)
        {
            cout << "Events complexity > handler complexity ";
            if(!m_nextHandler)
            {
                cout << "but no next handler, process finished" << endl;
            }
            else
            {
                cout << ", send to next handler" << endl;
                m_nextHandler->process(event);
            }
        }
        else
        {
            event.processEvent(m_description);
        }
    }
    virtual void setNextHandler(Handler* handler){ m_nextHandler = handler; }
protected:
    int m_complexity = 0;
    std::string m_description;
    Handler* m_nextHandler = nullptr;
};

class Handler1 : public Handler{
public:
    Handler1(int complexity, const std::string& description){
        m_complexity = complexity;
        m_description = description;
    };
};

class Handler2 : public Handler{
public:
    Handler2(int complexity, const std::string& description){
        m_complexity = complexity;
        m_description = description;
    };
};

int main()
{
    auto hndl1 = new Handler1(1, "Handler 1");
    if(!hndl1)
        return 5;

    auto hndl2 = new Handler2(2, "Handler 2");
    if(!hndl2)
        return 5;
    hndl1->setNextHandler(hndl2);

    cout << "Event1:" << endl;
    Event event1(1);
    hndl1->process(event1);

    cout << "Event2:" << endl;
    Event event2(2);
    hndl1->process(event2);

    cout << "Event3:" << endl;
    Event event3(5);
    hndl1->process(event3);

    return 0;
}
