#include <iostream>
#include <fstream>
#include <sstream>

#include <vector>

std::string read_text(std::string&& path){
    std::ifstream input_file(path);
    return std::string((std::istreambuf_iterator<char>(input_file)), std::istreambuf_iterator<char>());
}

std::vector<std::string> split_line_string(std::string&& str, std::string&& predicat){
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

int process_text(std::string&& s){
	auto lines = split_line_string(std::move(s), "\n");
	
	std::vector<std::vector<std::string>> tokens;

	int depth = 0;
	int horizontal = 0;
	int aim = 0;

	for(size_t i = 0; i < lines.size(); ++i){
		tokens.push_back(split_line_string(std::move(lines[i]), " "));
		//std::cout << tokens[i][0] << " " << tokens[i][1] << "\n";
		
		if(tokens[i][0] == "forward"){
			horizontal += std::stoi(tokens[i][1]);
			depth += (aim * std::stoi(tokens[i][1]));
		}

		if(tokens[i][0] == "up"){
			//depth -= std::stoi(tokens[i][1]);
			aim -= std::stoi(tokens[i][1]);
		}

		if(tokens[i][0] == "down"){
			//depth += std::stoi(tokens[i][1]);
			aim += std::stoi(tokens[i][1]);
			
		}

		std::cout << horizontal << " " << depth << " " << aim << " " << depth * horizontal << "\n";
	}
	std::cout << horizontal << " " << depth << " " << depth * horizontal << "\n";
	//process state


	return 0;
}

int main(){
	auto text = read_text("aoc_data2.txt");
	std::cout << process_text(std::move(text));
	return 0;
}