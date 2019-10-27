class TestA{
  private:
  int privateFunc();

  public:
  int getNumInCpp();

  int getNumInH() {
    return 42;
  }

  int getNumCallCpp(){
    return privateFunc() + getNumInH();
  }

  int getNumInline();

  //int getNumNormal();
};

inline int TestA::getNumInline(){return 321;}

// そもそも定義できない
// int TestA::getNumNormal(){return 111;}
