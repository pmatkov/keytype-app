//---------------------------------------------------------------------------

#ifndef KeyStatisticsH
#define KeyStatisticsH
//---------------------------------------------------------------------------
class KeyStatistics {

	private:
		int totalCount = 0;
		int correctCount = 0;
		int mistakesCount = 0;

    public:
    	const int& getTotalCount() const;
		void setTotalCount(int _totalCount);
		void incTotalCount();

		const int& getCorrectCount() const;
		void setCorrectCount(int _correctCount);
		void incCorrectCount();

		const int& getMistakesCount() const;
		void setMistakesCount(int _mistakesCount);
		void incMistakesCount();
};

#endif
