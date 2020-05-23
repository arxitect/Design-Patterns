#include <iostream>
#include <string>

using std::string;
using std::cout;

class BaseComponent;

class Mediator {
public:
    virtual void Notify(BaseComponent *sender, string event) const = 0;
};

class BaseComponent{
protected:
    Mediator *mediator_;
public:
    BaseComponent(Mediator *mediator = nullptr) : mediator_(mediator){}
    void setMediator(Mediator *mediator) {
        this->mediator_ = mediator;
    }
};

class Component1 : public BaseComponent {
public:
    void doA() {
        cout << "Component 1 does A.\n";
        this->mediator_->Notify(this, "A");
    }
    void doB() {
        cout << "Component 1 does B.\n";
        this->mediator_->Notify(this, "B");
    }
};

class Component2 : public BaseComponent {
public:
    void doC() {
        cout << "Component 2 does C.\n";
        this->mediator_->Notify(this, "C");
    }
    void doD() {
        cout << "Component 2 does D.\n";
        this->mediator_->Notify(this, "D");
    }
};

class ConcreteMediator : public Mediator {
private:
    Component1 *component1_;
    Component2 *component2_;
public:
    ConcreteMediator(Component1 *c1, Component2 *c2) : component1_(c1), component2_(c2){
        this->component1_->setMediator(this);
        this->component2_->setMediator(this);
    }
    void Notify(BaseComponent *sender, string event) const override {
        if (event == "A") {
            cout << "Mediator reacts on A and triggers following operations:\n";
            this->component2_->doC();
        }
        if (event == "D") {
            cout << "Mediator reacts on D and triggers following operations:\n";
            this->component1_->doB();
            this->component2_->doC();
        }
    }
};

void ClientCode() {
    Component1 *c1 = new Component1;
    Component2 *c2 = new Component2;
    ConcreteMediator *mediator = new ConcreteMediator(c1, c2);
    cout << "Client triggers operation A.\n";
    c1->doA();
    cout << "\n";
    cout << "Client triggers operation D.\n";
    c2->doD();

    delete c1;
    delete c2;
    delete mediator;
}

int main() {
    ClientCode();
    return 0;
}