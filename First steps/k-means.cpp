#include <iostream>
#include <vector>
#include <cmath>

double min_distance(const std::vector<double> &data, std::vector<double> centre) {
	double sum = 0;
	for (size_t k = 0; k != data.size(); ++k)
		sum += pow((data[k] - centre[k]), 2);
	return sqrt(sum);
}

int main() {
	// Очистка файла и запись готовых для обработки данных в вектор - Python
	std::vector<std::vector<double>> data;
	int k;
	std::cin >> k; // Задаем k
	std::vector<std::vector<double>> centres(k);
	// Задаем цетры кластеров (выбираем первые k анализов)
	for (size_t i = 0; i != k; ++i)
		for (size_t j = 0; j != data[i].size(); ++j)
			centres[i].push_back(data[i][j]);
	//
	bool flag = true;
	std::vector<std::vector<double>> empty;
	typedef std::pair<std::vector<double>, std::vector<std::vector<double>>> xxx;
	std::vector<std::pair<std::vector<double>, std::vector<std::vector<double>>>> clusters;
	for (size_t i = 0; i != k; ++i)
		clusters.push_back(xxx(centres[i], empty));
	double min;
	std::vector<double> save;
	while (flag) {
		for (size_t i = 0; i != data.size(); ++i) {
			auto it = clusters.begin();
			auto min_it = clusters.begin();
			min = min_distance(data[i], it->first);
			++it;
			for (; it != clusters.end(); ++it) {
				if (min_distance(data[i], it->first) < min) {
					min = min_distance(data[i], it->first);
					min_it = it;
					save = data[i];
				}
			}
			min_it->second.clear();
			for (size_t j = 0; j != data[i].size(); ++j)
				min_it->second.push_back(save);
		}
		size_t counter = 0;
		// Переопределяем евклидовые центры кластеров
		for (auto it = clusters.begin(); it != clusters.end(); ++it) {
			for (size_t z = 0; z != it->first.size(); ++z) {
				double sum = 0;
				for (size_t p = 0; p != it->second.size(); ++p) {
					sum += it->second[p][z];
				}
				if (it->first[z] == (sum / it->second.size()))
					++counter;
				it->first[z] = sum / it->second.size();
			}
		}
		// Проверяем, изменились ли центры. Если нет, то заканчиваем работу алгоритма
		auto ex = clusters.begin();
		if (counter == clusters.size()*(ex->first).size())
			flag = false;
	}
}
