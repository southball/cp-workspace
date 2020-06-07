#include <iostream>
#include <cstdlib>
#include <fstream>
#include <vector>
#include <map>
#include <set>
#include <sstream>
#include <cassert>
using namespace std;

// struct definitions

struct snippet {
	string id;
	vector<string> dependencies;
	string content;

	snippet() : id("NOT_INITED") {}
	snippet(string id) : id(id) {}
};

// global variables

map<string, snippet> snippets;
set<string> inserting_snippets;
set<string> inserted_snippets;
string source_file;
string snippet_buffer;
string result_buffer;

// functions

bool starts_with(string haystack, string needle) {
	return haystack.substr(0, needle.size()) == needle;
}

string lstrip(string str) {
	for (string::iterator it = str.begin(); it != str.end(); it++)
		if (*it != ' ')
			return string(it, str.end());
	return "";
}

string rstrip(string str) {
	while (str.size() && str.back() == ' ')
		str.pop_back();
	return str;
}

string strip(string str) {
	return lstrip(rstrip(str));
}

string remove_prefix(string str, string prefix) {
	assert(str.substr(0, prefix.length()) == prefix);
	return str.substr(prefix.length());
}

void read_file(string &file, string filename) {
	string line;
	file = "";
	ifstream fin(filename);
	while (getline(fin, line))
		file += line + '\n';
}

void read_snippets(string filename) {
	string content, line;
	read_file(content, filename);

	bool in_snip = false;
	snippet snip;

	stringstream content_ss(content);
	int line_count = 0;
	while (getline(content_ss, line)) {
		line_count++;

		if (starts_with(line, "//!")) {
			// process directive
			string directive = lstrip(remove_prefix(line, "//!"));
			if (starts_with(directive, "snippet")) {
				assert(!in_snip);
				in_snip = true;
				string id = strip(remove_prefix(directive, "snippet"));
				snip = snippet(id);
			} else if (starts_with(directive, "require")) {
				assert(in_snip);
				string dependency = strip(remove_prefix(directive, "require"));
				snip.dependencies.push_back(dependency);
			} else if (starts_with(directive, "end")) {
				assert(in_snip);
				in_snip = false;
				assert(snippets.find(snip.id) == snippets.end());
				snippets[snip.id] = snip;
			} else {
				cerr << "Unknown directive on line " << line_count << "." << endl;
				cerr << "Line content: " << line << endl;
				exit(1);
			}
		} else {
			if (!in_snip) {
				// ignore line
			} else {
				snip.content += line + '\n';
			}
		}
	}
}

void ensure_snippet(string id) {
	if (inserted_snippets.find(id) != inserted_snippets.end())
		return;

	assert(snippets.find(id) != snippets.end() && "Snippet not found.");
	assert(inserting_snippets.find(id) == inserting_snippets.end() && "Require cycle detected.");

	snippet snip = snippets[id];

	// For cycle detection.
	inserting_snippets.insert(id);

	// Fulfill all dependencies.
	for (string dependency : snip.dependencies)
		ensure_snippet(dependency);

	snippet_buffer += snip.content + '\n';

	// Successfully inserted snippet.
	inserting_snippets.erase(id);
	inserted_snippets.insert(id);
}

void print_snippets_info() {
	for (auto snippet_pair : snippets) {
		snippet snip = snippet_pair.second;
		cerr << snip.id;
		if (snip.dependencies.size()) {
			cerr << " (depends on: ";
			for (auto it = snip.dependencies.begin(); it != snip.dependencies.end(); it++) {
				if (it != snip.dependencies.begin())
					cerr << ", ";
				cerr << *it;
			}
			cerr << ")";
		}
		cerr << endl;
	}
}

string join(vector<string> tokens, string separator) {
	string result;
	for (auto it = tokens.begin(); it != tokens.end(); it++) {
		if (it != tokens.begin())
			result += separator;
		result += *it;
	}
	return result;
}

void process_snippets() {
	string line;
	stringstream source_ss(source_file);

	int line_count = 0;
	while (getline(source_ss, line)) {
		line_count++;

		if (starts_with(line, "//!")) {
			string directive = lstrip(remove_prefix(line, "//!"));
			if (starts_with(directive, "use")) {
				string requirement;
				stringstream requirements_ss(strip(remove_prefix(directive, "use")));
				vector<string> requirements;

				while (getline(requirements_ss, requirement, ','))
					requirements.push_back(requirement);
				for (string requirement : requirements)
					ensure_snippet(requirement);

				result_buffer += string("// Snippets inserted: ") + join(requirements, ", ") + '\n';
				result_buffer += snippet_buffer;
				snippet_buffer = "";
			}
		} else {
			result_buffer += line + '\n';
		}
	}
}

int main(int argc, char **argv) {
	if (argc < 2) {
		cerr << "Error: file name is not provided." << endl;
		exit(1);
	}

	read_file(source_file, argv[1]);
	read_snippets("snippets.cpp");
	//print_snippets_info();
	process_snippets();
	
	cout << result_buffer;
}
