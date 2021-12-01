#include <iostream>
#include <fstream>
#include <sstream>

#include <vector>

std::string read_text(std::string&& path){
    std::ifstream input_file(path);
    return std::string((std::istreambuf_iterator<char>(input_file)), std::istreambuf_iterator<char>());
}

int process_text(std::string&& s){
	std::string delimiter = "\n";

	size_t pos = 0;
	std::string token;

	std::vector<int> tokens;

	while ((pos = s.find(delimiter)) != std::string::npos) {
	    token = s.substr(0, pos);
	    tokens.push_back(std::stoi(token));
	    s.erase(0, pos + delimiter.length());
	}

	tokens.push_back(std::stoi(s));
	std::cout << tokens.size();
	int prev_token = 0;
	int curr_token = 0;
	int amount = 0;
	for(size_t i = 3; i < tokens.size(); ++i){
		prev_token = tokens[i-3];
		curr_token = tokens[i];
		if(curr_token > prev_token){
			amount++;
			//std::cout << curr_token << "- increased\n";
		}
		else{
			//std::cout << curr_token << "- decreased\n";
		}
	}

	return amount;
}

int main(){
	auto text = read_text("aoc_data1.txt");
	std::cout << process_text(std::move(text));
	return 0;
}