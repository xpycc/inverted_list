#include <cstdio>
#include <cstring>
#include "inverted_list_disk.h"
using namespace std;

vector<inverted_list_disk::positing> inverted_list_disk::load_from_disk() const {
	FILE *f = fopen(filename.c_str(), "rb");
	vector<positing> res;
	if (f == NULL)
		return res;
	positing block;
	while (fread(&block, sizeof block, 1, f) == 1) {
		res.push_back(block);
		if (fseek(f, block.len * sizeof(unit), SEEK_CUR)) {
			perror("An error occurred while reading inverted list!");
			res.clear();
			fclose(f);
			return res;
		}
	}
	fclose(f);
	return res;
}

static FILE* wf;

bool inverted_list_disk::prepare_to_write_disk() {
	return (wf = fopen(filename.c_str(), "wb")) != NULL;
}

bool inverted_list_disk::write_positing_list(const vector<unit>& v) {
	positing block = {ftell(wf), v.size()};
	if (fwrite(&block, sizeof block, 1, wf) != 1) {
		perror("An error occurred while writing inverted list!");
		return false;
	}
	if (fwrite(&v[0], sizeof block, v.size(), wf) != v.size()) {
		perror("An error occurred while writing inverted list!");
		return false;
	}
	return true;
}

void inverted_list_disk::finish_writing_disk() {
	fclose(wf);
}
