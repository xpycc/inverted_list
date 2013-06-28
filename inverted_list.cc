#include <cstdio>
#include "inverted_list.h"
using namespace std;

bool inverted_list::write_to_disk() {
	if (filename_.size() == 0) {
		fprintf(stderr, "%s\n", "Empty file name while writing inverted list!");
		return false;
	}
	FILE *f = fopen(filename_.c_str(), "wb");
	if (f == NULL) return false;
	for (size_t i = 0; i < size(); ++i) {
		posting_meta block = {(int)i, (int)(*this)[i].size()};
		if (
			fwrite(&block, sizeof block, 1, f) != 1 ||
			fwrite(&(*this)[i][0], sizeof(index_unit), block.length, f) != (size_t)block.length
		) {
			perror("An error occurred while writing inverted list!");
			return false;
		}
	}
	fclose(f);
	return true;
}

bool inverted_list::load_from_disk() {
	if (filename_.size() == 0) {
		fprintf(stderr, "%s\n", "Empty file name while reading inverted list!");
		return false;
	}
	FILE *f = fopen(filename_.c_str(), "rb");
	if (f == NULL) return false;
	posting_meta block;
	this->clear();
	while (fread(&block, sizeof block, 1, f) == 1) {
		resize(size() + 1);
		this->back().resize(block.length);
		if (fread(&this->back()[0], sizeof(index_unit), block.length, f) != (size_t)block.length) {
			perror("An error occurred while reading inverted list!");
			return false;
		}
	}
	fclose(f);
	return true;
}
