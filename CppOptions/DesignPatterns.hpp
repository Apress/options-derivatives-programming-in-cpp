//
//  DesignPatterns.hpp
//  CppOptions

#ifndef DesignPatterns_hpp
#define DesignPatterns_hpp

class Trade {
    //  ....
};

class ClearingHouse {
private:                   // these are all private because this is a singleton
    ClearingHouse();
    // the copy constructor is not implemented
    ClearingHouse(const ClearingHouse &p);
    ~ClearingHouse();
    // assignment operator is not implemented
    ClearingHouse &operator=(const ClearingHouse &p);

public:
    static ClearingHouse &getClearingHouse();

    void clearTrade(const Trade &);

private:
    static ClearingHouse *s_clearingHouse;
};



#endif /* DesignPatterns_hpp */
