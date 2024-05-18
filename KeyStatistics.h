//---------------------------------------------------------------------------

#ifndef KeyStatisticsH
#define KeyStatisticsH

//---------------------------------------------------------------------------
class KeyStatistics {

	private:
        wchar_t key;
		int correct = 0;
		int mistake = 0;

    public:
    	KeyStatistics();
        KeyStatistics(wchar_t _key);
        KeyStatistics(wchar_t _key, int _correct, int _mistake);

        wchar_t getKey() const;

		int getCorrect() const;
		void setCorrect(int _correct);
		void increaseCorrect();

		int getMistake() const;
		void setMistake(int _mistake);
		void increaseMistake();
};

#endif
