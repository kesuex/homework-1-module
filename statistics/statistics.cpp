#include <iostream>
#include <limits>

class IStatistics {
public:
	virtual ~IStatistics() {}

	virtual void update(double next) = 0;
	virtual double eval() const = 0;
	virtual const char * name() const = 0;
};

class Min : public IStatistics {
public:
	Min() : m_min{std::numeric_limits<double>::max()} {
	}

	void update(double next) override {
		if (next < m_min) {
			m_min = next;
		}
	}

	double eval() const override {
		return m_min;
	}

	const char * name() const override {
		return "min";
	}

private:
	double m_min;
};

class Max : public IStatistics {
public:
	Max() : m_max{ std::numeric_limits<double>::min() } {
	}

	void update(double next) override {
		if (next > m_max) {
			m_max = next;
		}
	}

	double eval() const override {
		return m_max;
	}

	const char* name() const override {
		return "max";
	}

private:
	double m_max;
};

class Mean : public IStatistics {
public:
	Mean() : m_mean{ 0 } {
	}

	void update(double next) override {
		count++;
	    m_mean = m_mean + next;
	}

	double eval() const override {
		return m_mean/count;
	}

	const char* name() const override {
		return "mean";
	}

private:
	double m_mean;
	int count = 0;
};

class STD : public IStatistics {
public:
	STD() : sum{ 0 }, squaredSum{ 0 }, count{ 0 } {}

	void update(double next) override {
		sum += next;
		squaredSum += next * next;
		count++;
	}

	double eval() const override {
		if (count == 0) {
			return 0; 
		}

		double mean = sum / count;
		double variance = (squaredSum / count) - (mean * mean);
		return std::sqrt(variance);
	}

	const char* name() const override {
		return "std";
	}

private:
	double sum; 
	double squaredSum; 
	int count; 
};

int main() {

	const size_t statistics_count = 1;
	IStatistics* statistic_min[statistics_count];
	IStatistics* statistic_max[statistics_count];
	IStatistics* statistic_mean[statistics_count];
	IStatistics* statistic_std[statistics_count];

	statistic_min[0] = new Min{};
	statistic_max[0] = new Max{};
	statistic_mean[0] = new Mean{};
	statistic_std[0] = new STD{};

	double val = 0;
	
	while (std::cin >> val) {
		for (size_t i = 0; i < statistics_count; ++i) {
			statistic_min[i]->update(val);
			statistic_max[i]->update(val);
			statistic_mean[i]->update(val);
			statistic_std[i]->update(val);
		}
	}

	// Handle invalid input data
	if (!std::cin.eof() && !std::cin.good()) {
		std::cerr << "Invalid input data\n";
		return 1;
	}

	// Print results if any
	for (size_t i = 0; i < statistics_count; ++i) {
		std::cout << statistic_min[i]->name() << " = " << statistic_min[i]->eval() << std::endl;
	}
	for (size_t i = 0; i < statistics_count; ++i) {
		std::cout << statistic_max[i]->name() << " = " << statistic_max[i]->eval() << std::endl;
	}
	for (size_t i = 0; i < statistics_count; ++i) {
		std::cout << statistic_mean[i]->name() << " = " << statistic_mean[i]->eval() << std::endl;
	}
	for (size_t i = 0; i < statistics_count; ++i) {
		std::cout << statistic_std[i]->name() << " = " << statistic_std[i]->eval() << std::endl;
	}

	// Clear memory - delete all objects created by new
	for (size_t i = 0; i < statistics_count; ++i) {
		delete statistic_min[i];
	}
	for (size_t i = 0; i < statistics_count; ++i) {
		delete  statistic_max[i];
	}
	for (size_t i = 0; i < statistics_count; ++i) {
		delete  statistic_mean[i];
	}
	for (size_t i = 0; i < statistics_count; ++i) {
		delete  statistic_std[i];
	}

	return 0;
}