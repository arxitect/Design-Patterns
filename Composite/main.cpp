#include <algorithm>
#include <iostream>
#include <list>
#include <string>

using std::string;
using std::list;
using std::cout;

class Component {
protected:
    Component *parent_;
public:
    virtual ~Component() = default;
    void SetParent(Component *parent) {
        this->parent_ = parent;
    }
    [[nodiscard]] Component *GetParent() const {
        return this->parent_;
    }
    virtual void Add(Component *component) {}
    virtual void Remove(Component *component) {}
    [[nodiscard]] virtual bool isComposite() const {
        return false;
    }

    [[nodiscard]] virtual string Operation() const = 0;
};

class Leaf : public Component {
public:
    [[nodiscard]] string Operation() const override {
        return "Leaf";
    }
};

class Composite : public Component {
protected:
    list<Component *> children_;
public:
    void Add(Component *component) override {
        this->children_.push_back(component);
        component->SetParent(this);
    }

    void Remove(Component *component) override {
        children_.remove(component);
        component->SetParent(nullptr);
    }
    [[nodiscard]] bool isComposite() const override {
        return true;
    }

    [[nodiscard]] string Operation() const override {
        string result;
        for(const Component *c : children_) {
            if(c == children_.back())
                result += c->Operation();
            else
                result += c->Operation() + "+";
        }

        return "Branch(" + result + ")";
    }
};

void ClientCode(Component *component) {
    cout << "RESULT: " << component->Operation();
}

void ClientCode2(Component *component1, Component *component2) {
    if (component1->isComposite()) {
        component1->Add(component2);
    }
    cout << "RESULT: " << component1->Operation();
}

int main()
{
    Component *simple = new Leaf;
    cout << "Client: I've got a simple component:\n";
    ClientCode(simple);
    cout << "\n\n";

    Component *tree = new Composite;
    Component *branch1 = new Composite;

    Component *leaf_1 = new Leaf;
    Component *leaf_2 = new Leaf;
    Component *leaf_3 = new Leaf;
    branch1->Add(leaf_1);
    branch1->Add(leaf_2);
    Component *branch2 = new Composite;
    branch2->Add(leaf_3);
    tree->Add(branch1);
    tree->Add(branch2);
    cout << "Client: Now I've got a composite tree:\n";
    ClientCode(tree);
    cout << "\n\n";

    cout << "Client: I don't need to check the components classes even when managing the tree:\n";
    ClientCode2(tree, simple);
    cout << "\n";

    delete simple;
    delete tree;
    delete branch1;
    delete branch2;
    delete leaf_1;
    delete leaf_2;
    delete leaf_3;
    return 0;
}