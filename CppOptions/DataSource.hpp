//
//  DataSource.hpp

#ifndef DataSource_hpp
#define DataSource_hpp

#include <string>

#include <map>

class DataSource {
private:
    DataSource(const std::string &name);
    DataSource(const DataSource &p);
    DataSource &operator=(const DataSource &p);
public:
    ~DataSource();  // must be public so clients can use delete

    static DataSource *createInstance();

    void readData();

private:
    std::string m_dataName;
};




#endif /* DataSource_hpp */
