namespace mpr{
  enum PassType {MAIN, PREMAIN, FILTER};
  class Pass{
    public:
      std::string name;
      PassType type;
    public:
      Pass():name("main"),type(MAIN){};
      Pass(Pass const &p){
        this->name =p.name;
        this->type =p.type;
      }
      Pass(std::string n, PassType tp):name(n),type(tp){}
      ~Pass(){}
  };
}
