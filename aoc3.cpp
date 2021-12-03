#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <vector>

inline std::string read_text(std::string&& path){
    std::ifstream input_file(path);
    return std::string((std::istreambuf_iterator<char>(input_file)), std::istreambuf_iterator<char>());
}

inline std::vector<std::string> split_line_string(std::string&& str, std::string&& predicat){
	size_t pos = 0;
	std::vector<std::string> tokens;
	std::string token;
	while((pos = str.find(predicat)) != std::string::npos){
		token = str.substr(0, pos);
		tokens.push_back(token);
	    str.erase(0, pos + predicat.length());
	}
	tokens.push_back(str);
	
	return tokens;
}

inline std::vector<std::string> split_string_by_symbol(std::string&& str){
	std::vector<std::string> symbols;

	for(size_t i = 0; i < str.size(); ++i){
		std::string symb;
		symb += str[i];
		symbols.push_back(symb);
	}

	return symbols;
}

//101010010
int get_numeric(std::string&& number_binary){
	std::cout << "INPUT: " << number_binary << "\n";
	int power = number_binary.size();
	int res = 0;

	for(size_t i = 0; i < number_binary.size(); ++i){
		std::string tok;
		tok += number_binary[i];
		res += (std::stoi(tok) * pow(2, power-1));

		std::cout << tok << " " << power << " " << res << "\n";
		power--;	
	}

	return res;

}

int process_text(std::string&& s){
	auto lines = split_line_string(std::move(s), "\n");
	#define INPUT_NUMBER_LEN 12
	std::vector<std::vector<std::string>> tokens;
	std::vector<int> res_counter;
	res_counter.resize(INPUT_NUMBER_LEN);

	for(size_t i = 0; i < lines.size(); ++i){
		auto token = split_string_by_symbol(std::move(lines[i]));
		tokens.push_back(token);
		
		for(size_t j = 0; j < tokens[i].size(); ++j){
			if(tokens[i][j] == "1"){
				res_counter[j]++;
			}

			if(tokens[i][j] == "0"){
				res_counter[j]--;
			}
		}
		//std::cout << "\n";
	}

	std::string gamma;
	std::string epsilon;

	for(size_t i = 0; i < INPUT_NUMBER_LEN; ++i){
		gamma += (res_counter[i] > 0 ? "1" : "0");
	}
	
	for(size_t i = 0; i < INPUT_NUMBER_LEN; ++i){
		epsilon += (res_counter[i] < 0 ? "1" : "0");
	}

	return get_numeric(std::move(gamma)) * get_numeric(std::move(epsilon));
}

int main(){
	auto text = read_text("aoc_data3.txt");
	std::cout << process_text(std::move(text));
	return 0;
}