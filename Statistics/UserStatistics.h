//---------------------------------------------------------------------------

#ifndef UserStatisticsH
#define UserStatisticsH

#include <vector>
#include <map>
#include <vcl.h>

#if EXPORTS
    #define DLL_EXPORT __declspec(dllexport)
#else
    #define DLL_EXPORT __declspec(dllimport)
#endif

//class IKeyStatistics;

class KeyStatistics;

class IUserStatistics {
	public:
        virtual wchar_t findMostAccurateChar() const = 0;
        virtual wchar_t findLeastAccurateChar() const = 0;
        virtual double calculateAvgPracticeTime() const = 0;
        virtual void Destroy() = 0;
// 		virtual ~IUserStatistics();
};

//class DLL_EXPORT UserStatistics {


class UserStatistics : public IUserStatistics {

	private:
		std::vector<TDateTime> practiceTime;
    	std::map<wchar_t, KeyStatistics> keyStatistics;

    public:
//    	UserStatistics(const std::vector<TDateTime> &_practiceTime, const std::map<wchar_t, IKeyStatistics*> &_keyStatistics);
//        UserStatistics(const std::map<wchar_t, IKeyStatistics*> &_keyStatistics);
        UserStatistics(const std::map<wchar_t, KeyStatistics> &_keyStatistics);

        const std::vector<TDateTime> &getPracticeTime() const;
        const std::map<wchar_t, KeyStatistics> &getKeyStatistics() const;
        wchar_t findMostAccurateChar() const;
        wchar_t findLeastAccurateChar() const;
        double calculateAvgPracticeTime() const;
        void Destroy();
};

extern "C" UserStatistics* DLL_EXPORT __stdcall CreateUserStatistics(const std::map<wchar_t, KeyStatistics> &keyStatistics);

#endif
