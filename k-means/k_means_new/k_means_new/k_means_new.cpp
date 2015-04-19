#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>

double distance(const std::vector<double> &analysis, const std::vector<double> &centre) {
	double sum = 0;
	for (size_t k = 0; k != analysis.size(); ++k)
		sum += pow((analysis[k] - centre[k]), 2);
	return sqrt(sum);
}

std::vector<double> vec_sum(const std::vector<double> &vec1, const std::vector<double> &vec2) {
	std::vector<double> temp(vec1.size());
	for (size_t q = 0; q != vec1.size(); ++q)
		temp[q] = vec1[q] + vec2[q];
	return temp;
}

std::vector<std::pair<size_t, std::vector<size_t>>> k_means_new(const std::vector<std::vector<double>> &data, int &k) {
	std::vector< std::pair< size_t, std::vector< size_t > > > clusters;
	// «адаем первичные центры наших кластеров (их у нас k)

	std::vector<std::vector<double>> centres(k);
	std::vector<size_t> colors(data.size()); // каждому анализу - свой цвет (номер кластера)

	for (size_t i = 0; i != k; ++i)
		for (size_t j = 0; j != data[i].size(); ++j)
			centres[i].push_back(data[i][j]);

	//  расим первые k точек в массиве color: делаем ссылку #точки -> цвет
	for (size_t i = 0; i != k; ++i)
		colors[i] = i;
	for (size_t i = k; i != data.size(); ++i)
		colors[i] = -1; // ѕокраска точки в -1 означает, что точка еще не принадлежит ни одному кластеру

	// «апускаем основной цикл кластеризации
	double min = 0;
	double cur_dist = 0;
	int color = 0;
	bool flag = true;
	int count = 0;
	int exit_count = 0;

	while (flag) {
		exit_count = 0;
	    // распредел€ем точки по кластерам (центры пропускаем)
		for (size_t i = 0; i != data.size(); ++i) {
			if (colors[i] == -1 || data[i] != centres[colors[i]]) {
				min = distance(data[i], centres[0]);
				color = 0;
				for (size_t j = 1; j != k; ++j) {
					cur_dist = distance(data[i], centres[j]);
					if (cur_dist < min) {
						min = cur_dist;
						color = j;
					}
				}
				colors[i] = color;
			}
		}

		// ѕереопредел€ем центры кластеров
		for (size_t i = 0; i != centres.size(); ++i) {
			count = 0;
			std::vector<double> new_centre(data[0].size());
			for (size_t j = 0; j != colors.size(); ++j) {
				if (colors[j] == i) {
					new_centre = vec_sum(new_centre, data[j]);
					++count;
				}
			}
			for (size_t j = 0; j != new_centre.size(); ++j) {
				if (centres[i][j] == new_centre[j] / count)
					++exit_count;
				centres[i][j] = new_centre[j] / count;
			}
		}

		// ѕроверка на изменение центров
		if (exit_count == centres.size() * centres[0].size())
			flag = false;
	}

	// «апись данных в массив clusters
	std::vector<size_t> temp;
	for (size_t i = 0; i != k; ++i) {
		for (size_t j = 0; j != data.size(); ++j) {
			if (colors[j] == i)
				temp.push_back(j);
		}
		clusters.push_back(std::pair<size_t, std::vector<size_t>>(i, temp));
		temp.clear();
	}
	return clusters;
}

int main() {
	// Input k - a number of clusters, on which we need to divide the set of analyses
	int k;
	std::cin >> k;

	// Read data in matrix
	std::ifstream genes("output.txt");
	int m = 0, n = 0;
	genes >> n >> m;
	std::vector<std::vector<double>> data(m, std::vector<double>(n, 0));
	for (size_t i = 0; i != n; ++i)
		for (size_t j = 0; j != m; ++j)
			genes >> data[j][i];

	// Run k-means
	std::vector< std::pair< size_t, std::vector< size_t > > > clusters;
	clusters = k_means_new(data, k);
	for (auto it = clusters.begin(); it != clusters.end(); ++it) {
		std::cout << it->first << " : ";
		for (size_t i = 0; i != it->second.size(); ++i)
			std::cout << it->second[i] << " ";
		std::cout << "\n";
	}

	// Write data in finish.txt
	std::ofstream fin;
	fin.open("finish.txt");
	for (auto it = clusters.begin(); it != clusters.end(); ++it) {
		fin << it->first << " : " << "\n";
		for (size_t j = 0; j != data[0].size(); ++j) {
			for (size_t i = 0; i != it->second.size(); ++i) {
				fin << data[it->second[i]][j] << "\t";
			}
			fin << "\n";
		}
		fin << "\n" << "\n";
	}
	fin.close();
}
