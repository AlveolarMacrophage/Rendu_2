#include "network.h"
#include "random.h"
#include <algorithm>
#include <iostream>

using namespace std;

	void Network::resize(const size_t& n){
		values.clear();
		values.resize(n);
		RNG.normal(values, 0, 1);
	}



	bool Network::add_link(const size_t& node_a, const size_t& node_b){
		
		if ((values.size() <= node_a) or (values.size() <= node_b) or (node_a == node_b)) {
			return false;
		}
		
		for (auto i : neighbors(node_a)) {
			if (i == node_b) {
				return false;
			}
		}
		
		links.emplace(node_a, node_b);
		links.emplace(node_b, node_a);
		
		return true;
	
	}




	size_t Network::random_connect(const double& mean_deg){
		
		vector<size_t> vec;
		vector<size_t> vec_shuffled;
		size_t nb_links(0);
		int sum(0);
		
		for (size_t i(0); i <= values.size() ; ++i) {
			vec.push_back(i);
			vec_shuffled.push_back(i);
		}
		
		for (auto t : vec) {
			RNG.shuffle(vec_shuffled);
			nb_links = RNG.poisson(mean_deg);
			sum += nb_links;
			
			for (size_t j(0) ; j <= nb_links ; ++j) {
				add_link(vec[t], vec_shuffled[j]);
			}
			
		}
		
		return sum;
	}

	size_t Network::set_values(const std::vector<double>& new_values){
		values.clear();
		values = new_values;
		return values.size();
	}
		
	size_t Network::size() const{
		return values.size();
	}
		
	size_t Network::degree(const size_t &_n) const{
		return links.count(_n);
	}
	
	double Network::value(const size_t &_n) const{
		return values[_n];
	}
	
	std::vector<double> Network::sorted_values() const{
		vector<double> table;
		table = values; 
		sort(table.begin(), table.end());
		reverse(table.begin(), table.end());
		return table;
	}
	
	std::vector<size_t> Network::neighbors(const size_t&_n) const{
		vector<size_t> mapped_values;
		for (auto itr = links.begin(); itr != links.end(); itr++)     
			if (itr->first == _n){
			mapped_values.push_back(itr->second);
		}
		return mapped_values;
	}
