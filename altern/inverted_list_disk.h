#ifndef _INVERTED_LIST_DISK_H_
#define _INVERTED_LIST_DISK_H_

#include <string>
#include <vector>

// intruded structure
class inverted_list_disk {
public:
	typedef struct {
		long pos, len;
	} positing;

	typedef struct {
		long doc, freq;
	} unit;

	inverted_list_disk() {}
	inverted_list_disk(std::string s): filename(s) {}

	std::vector<positing> load_from_disk() const;
	bool prepare_to_write_disk();
	bool write_positing_list(const std::vector<unit>&);
	void finish_writing_disk();
private:
	std::string filename;
};

#endif
