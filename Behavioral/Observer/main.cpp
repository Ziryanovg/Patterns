#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

/*************************************
 * Наблюдатель
 * **********************************/

class IObserver{
public:
    virtual void handle(const string& data) = 0;
};

class FirstObserver : public IObserver{
    // IObserver interface
public:
    virtual ~FirstObserver() = default;
    void handle(const string &data) override {
        cout << "First observer notified with data:" << data << endl;
    }
};

class SecondObserver : public IObserver{
    // IObserver interface
public:
    virtual ~SecondObserver() = default;
    void handle(const string &data) override {
        cout << "Second observer notified with data:" << data << endl;
    }
};

class SupervisedObject{
public:
    void setData(const string& data){
        for(auto observer : m_observers)
        {
            if(observer)
                observer->handle(data);
        }

    }

    void addObserver(IObserver* observer) {
        if(!observer)
            return;
        cout << "Observer added" << endl;
        m_observers.push_back(observer);
    }
    void removeObserver(IObserver* observer) {
        cout << "Observer removed" << endl;
        m_observers.erase(find_if(m_observers.begin(), m_observers.end(), [&](IObserver* obs){return obs == observer;}));
    }
private:
    vector<IObserver*> m_observers;
};

int main()
{
    SupervisedObject object;

    auto firstObs = new FirstObserver();
    auto secondObs = new SecondObserver();

    object.addObserver(firstObs);
    object.addObserver(secondObs);

    object.setData("First new data");

    object.removeObserver(secondObs);

    object.setData("Second new data");

    if(firstObs)
        delete firstObs;

    if(secondObs)
        delete secondObs;

    return 0;
}
