#pragma once

class String {

private:
    char *str;
    
public:
    String();
    String(const char *str_);
    String(const String &obj);
    String& operator=(const String &obj);
    ~String();
    String operator+(const String &obj);
    bool operator==(const String &obj);
    int size() const;
    char* getStr() const;
    void setStr(const char *str_);
};
