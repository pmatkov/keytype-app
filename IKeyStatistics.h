//---------------------------------------------------------------------------

#ifndef IKeyStatisticsH
#define IKeyStatisticsH
//---------------------------------------------------------------------------

class IKeyStatistics {
public:
    virtual  wchar_t getKey() const = 0;
    virtual int getCorrect() const = 0;
    virtual void setCorrect(int _correct) = 0;
    virtual void increaseCorrect() = 0;

    virtual int getMistake() const = 0;
    virtual void setMistake(int _mistake) = 0;
    virtual void increaseMistake() = 0;

    virtual ~IKeyStatistics() {};
};

#endif
