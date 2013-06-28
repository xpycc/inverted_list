#ifndef _BITLIST_H_
#define _BITLIST_H_

#include <string>
#include <vector>
#include "inverted_list.h"

class oblist {
public:
	typedef inverted_list::unit unit;
	typedef inverted_list::positing positing;
	typedef struct {
		int doc[128], eid[128];
	} chunk_t;
	typedef struct {
		int term, chunk_cnt;
	} meta_t;
	typedef struct {
		meta_t meta;
		std::vector<chunk_t> vchunk;
	} bplist;
	
	oblist(const std::string& s): filename(s) {}
	void create_from(const inverted_list&);
	std::vector<unit> query_union_to(const std::vector<int>&);
	std::vector<unit> query_intersection_to(const std::vector<int>&);

private:
	bool write_to_disk();
	bool select_candidate();
	std::vector<int> doc_map;
	std::vector<bplist> vbplist;
	std::vector<positing> positing_list;
	std::string filename;
};

#endif
