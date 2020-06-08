#include <iostream>
#include <cctype>
#include <cstdlib>
#include <fstream>
#include <vector>
#include <map>
#include <set>
#include <sstream>
#include <cassert>
#define eprintf(args...) fprintf(stderr, args)
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
string join(vector<string> tokens, string separator) {
	string result;
	for (auto it = tokens.begin(); it != tokens.end(); it++) {
		if (it != tokens.begin())
			result += separator;
		result += *it;
	}
	return result;
}

string lstrip(string str) {
	for (string::iterator it = str.begin(); it != str.end(); it++)
		if (!isspace(*it))
			return string(it, str.end());
	return "";
}

string rstrip(string str) {
	while (str.size() && isspace(str.back()))
		str.pop_back();
	return str;
}

string strip(string str) {
	return lstrip(rstrip(str));
}

bool starts_with_lstrip(string haystack, string needle) {
	return lstrip(haystack).substr(0, needle.size()) == needle;
}

string remove_prefix(string str, string prefix) {
	assert(starts_with_lstrip(str, prefix));
	return lstrip(str).substr(prefix.size());
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

		if (starts_with_lstrip(line, "//!")) {
			// process directive
			string directive = lstrip(remove_prefix(line, "//!"));
			if (starts_with_lstrip(directive, "snippet")) {
				assert(!in_snip);
				in_snip = true;
				string id = strip(remove_prefix(directive, "snippet"));
				assert(snippets.find(id) == snippets.end());
				snip = snippet(id);
				
				eprintf("[LOG  ] Start reading snippet %s\n", id.c_str());
			} else if (starts_with_lstrip(directive, "use")) {
				assert(in_snip);
				string dependency = strip(remove_prefix(directive, "use"));
				snip.dependencies.push_back(strip(dependency));
			} else if (starts_with_lstrip(directive, "end")) {
				assert(in_snip);
				in_snip = false;
				string id = strip(remove_prefix(directive, "end"));
				snippets[snip.id] = snip;
				assert(id == snip.id);

				eprintf("[LOG  ] Finish reading snippet %s\n", snip.id.c_str());
			} else {
				eprintf("[ERROR] Unknown directive on line %d\n", line_count);
				eprintf("[ERROR] Line content: %s\n", line.c_str());
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
	//eprintf("[LOG  ] Ensure snippet %s is loaded.\n", id.c_str());

	if (inserted_snippets.find(id) != inserted_snippets.end())
		return;

	eprintf("[LOG  ] Loading snippet %s\n", id.c_str());

	assert(snippets.find(id) != snippets.end() && "Snippet not found.");
	assert(inserting_snippets.find(id) == inserting_snippets.end() && "Require cycle detected.");

	snippet snip = snippets[id];

	// For cycle detection.
	inserting_snippets.insert(id);

	// Fulfill all dependencies.
	for (string dependency : snip.dependencies)
		ensure_snippet(dependency);

	snippet_buffer += snip.content;

	// Successfully inserted snippet.
	inserting_snippets.erase(id);
	inserted_snippets.insert(id);
}

void print_snippets_info() {
	eprintf("[INFO ] Snippets:\n");
	for (auto snippet_pair : snippets) {
		snippet snip = snippet_pair.second;
		
		if (!snip.dependencies.size()) {
			eprintf("[INFO ] - %s\n", snip.id.c_str());
		} else {
			eprintf("[INFO ] - %s (depends on: %s)\n", snip.id.c_str(), join(snip.dependencies, ", ").c_str());
		}
	}
}

void process_snippets() {
	string line;
	stringstream source_ss(source_file);

	int line_count = 0;
	while (getline(source_ss, line)) {
		line_count++;

		if (starts_with_lstrip(line, "//!")) {
			string directive = lstrip(remove_prefix(line, "//!"));
			
			eprintf("[LOG  ] Processing directive in source file: %s\n", directive.c_str());
			
			if (starts_with_lstrip(directive, "use")) {
				string requirement;
				stringstream requirements_ss(strip(remove_prefix(directive, "use")));
				vector<string> requirements;

				//eprintf("[LOG  ] Requirements: %s\n", directive.c_str());
				while (getline(requirements_ss, requirement, ','))
					requirements.push_back(strip(requirement));
				for (string requirement : requirements)
					ensure_snippet(requirement);
			} else if (starts_with_lstrip(directive, "snippet-holder")) {
				// This is to be handled in the second pass.
				result_buffer += line + '\n';
			} else {
				eprintf("[ERROR] Unknown directive on line %d.\n", line_count);
				eprintf("[ERROR] Line content: %s\n", line.c_str());
				exit(1);
			}
		} else {
			result_buffer += line + '\n';
		}
	}
}

void insert_snippets() {
	string source = result_buffer;
	string line;
	stringstream source_ss(source);

	result_buffer.clear();

	int line_count = 0;
	bool snippets_inserted = false;

	while (getline(source_ss, line)) {
		line_count++;

		if (starts_with_lstrip(line, "//!")) {
			string directive = strip(line.substr(3));
			if (starts_with_lstrip(directive, "snippet-holder")) {
				if (!snippets_inserted) {
					if (inserted_snippets.size()) {
						vector<string> snippets_list(inserted_snippets.begin(), inserted_snippets.end());
						result_buffer += string("// Inserted snippets: ") + join(snippets_list, ", ") + '\n';
						result_buffer += snippet_buffer;
						result_buffer += "// End snippets\n";
					} else {
						result_buffer += "// No snippets inserted.\n";
					}
					snippets_inserted = true;
				} else {
					eprintf("[ERROR] Multiple snippet holders defined.\n");
					exit(1);
				}
			}
		} else {
			result_buffer += line + '\n';
		}
	}

	if (!inserted_snippets.empty() && !snippets_inserted) {
		eprintf("[ERROR] No snippet holders defined but snippets requested.\n");
		exit(1);
	}
}

int main(int argc, char **argv) {
	if (argc < 2) {
		eprintf("[ERROR] File name is not provided.\n");
		exit(1);
	}

	read_file(source_file, argv[1]);
	read_snippets("snippets.cpp");
	//print_snippets_info();
	process_snippets();
	insert_snippets();

	cout << result_buffer;
}
