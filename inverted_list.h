#ifndef _INVERTED_LIST_H_
#define _INVERTED_LIST_H_

#include <vector>
#include <string>
using std::vector;
using std::string;

typedef struct {
	int doc, freq, pos_info_offset;
} index_unit;

typedef vector<index_unit> posting_list;

typedef struct {
	int termid, length;
} posting_meta;

class inverted_list : public vector<posting_list> {
public:
	inverted_list() {}
	inverted_list(const string& filename) :filename_(filename) {}
	void set_file_name(const string& filename) { filename_ = filename; }
	bool write_to_disk();
	bool load_from_disk();
	void new_posting_list() { resize(size() + 1); }
private:
	string filename_;
};

#endif
