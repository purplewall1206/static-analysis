struct Base {
    virtual void foo() {};
};

struct Derived: public Base {
    void foo() override {};
};

void StaticDispatch() {
  Base B;
  Derived D;

  B.foo();
  D.foo();
}

void DynamicDispatch() {
  Base *B = new Base();
  Derived *D = new Derived();

  B->foo();
  D->foo();
}