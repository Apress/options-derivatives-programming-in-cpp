//
//  Prototype.hpp

#ifndef Prototype_hpp
#define Prototype_hpp

class Prototype {
private:
    Prototype();
    Prototype(const Prototype &p);
    Prototype &operator=(const Prototype &p);

public:
    ~Prototype();
    Prototype *clone() const;
    void setVar1(int v);
    static const Prototype &getPrototype();

private:
    int m_var1;
    static Prototype *s_prototype;
    
};



#endif /* Prototype_hpp */
