#include <iostream>
#include <map>
using namespace std;

enum StateType{
    First,
    Second
};

class IState{
public:
    virtual ~IState() = default;
    virtual void handle() = 0;
};

class FirstState : public IState{
    // IState interface
public:
    void handle() override{
        cout << "Activated first state" << endl;
    }
};

class SecondState : public IState{
    // IState interface
public:
    void handle() override{
        cout << "Activated second state" << endl;
    }
};

class StateContext{
public:
    StateContext(){
        m_states.insert(std::make_pair(First, new FirstState));
        m_states.insert(std::make_pair(Second, new SecondState));
        setState(First);
    }

    ~StateContext(){
        for(auto [type, state] : m_states)
            delete state;
    }

    void setState(StateType type){
        for(auto [state_type, state] : m_states)
            if(state_type == type)
            {
                m_currentState = state;
                m_currentState->handle();
            }
    }
private:
    IState* m_currentState = nullptr;
    map<StateType, IState*> m_states;
};



int main()
{
    StateContext context;
    context.setState(Second);
    context.setState(First);
    return 0;
}
