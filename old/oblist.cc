#include <functional>
#include <utility>
#include <algorithm>
#include "oblist.h"
using namespace std;

typedef inverted_list::unit unit;
typedef inverted_list::positing positing;

vector<int> term_left;

void oblist::create_from(const inverted_list& list) {
	// TODO
	positing_list = list.load_from_disk();
	while (select_candidate())
		;
	positing_list.clear();
}

int goodness_score(int doc) {
	// TODO
}

bool oblist::select_candidate() {
	typedef pair<int, int> PII;
	vector<PII> wtpairs;
	// TODO calc vecotr<pair> wtpairs
	sort(wtpairs.begin(), wtpairs.end(), greater<PII>());
	int candinate_doc = next_doc();
	// TODO sort wtpairs with descendant order
	for (int i = 0; i < wtpairs.size(); ++i) {
		int upper = 0;
		for (int j = 0; j < avg_d; ++j)
			upper += wtpairs[i + j].first;
		int sigma = upper;
		for (iterator it(term[i]); it; ++it) {
			if (goodness_score(*it) > goodness_score(candinate_doc))
				candinate_doc = *it;
			for (int k = i + 1; i < i + avg_d; ++k)
				if (!seg_intersection(oid_lower[i], oid_upper[i], oid_lower[k], oid_upper[k])) {
					upper = max(sigma - wtpairs[k].first + wtpairs[k + avg_d].first, sigma - wtpairs[i].first + wtpairs[i + avg_d].first);
				}
		}
		if (goodness_score(candinate_doc) > upper)
			break;
	}
	// TODO post process
}

vector<unit> oblist::query_union_to(const vector<int>& q) {
	// TODO	
	Heap H; Set U;
	// initialize vbplist to term list here
	for (int i = 0; i < term_cc; ++i)
		H.push(make_pair(i, did[i]));
	while (H.size()) {
		int did = -1; eid = -1;
		Vector vec;
		while (H.size()) {
			(i, did_i) = H.top(); H.pop();
			if (did == -1) did = did_i, eid = eid_i;
			else if (did == did_i && (unsigned int)eid < (unsigned int)-1) eid |= eid_i;
			else if (did < did_i) {
				H.push(make_pair(i, did));
				break;
			}
			vec.push_back(make_pair(i, did_i));
		}
		if (did >= 0 && eid > 0) U.insert(make_pair(did, eid));
		for (int i = 0; i < vec.size(); ++i)
			H.push(vec[i]);
	}
	vector<unit> S; unit u;
	for (Set::iterator it = U.begin(); it != U.end(); ++it)
		for (int i = 0; i < B; ++i)
			if (it->second & (1 << i)) {
				u.doc = did + i;
				S.push_back(u);
			}
	return S;
}

vector<unit> oblist::query_intersection_to(const vector<int>& q) {
	// TODO
	Heap H; Set U;
	// initialize vbplist to term list here
	for (int i = 0; i < term_cc; ++i)
		H.push(make_pair(i, size(i)));
	while (H.size() != q.size()) {
		int did = -1; eid = -1;
		Vector vec;
		while (h.size()) {
			(i, Un_i) = H.top(); H.pop();
			vec.push_back(i);
			if (did == -1) did = did_i, eid = eid_i;
			else if (test_advance(did_i, i)) {
				eid &= eid_i;
				if (eid == 0)
					break;
			} else {
				eid = 0;
				break;
			}
		}
		if (did != -1 && eid != 0) U.insert(make_pair(did, eid));
		for (int i = 0; i < vec.size(); ++i) {
			do_advance(did, vec[i]);
			H.push_back(make_pair(i, size(i)));
		}
	}
	vector<unit> S; unit u;
	for (Set::iterator it = U.begin(); it != U.end(); ++it)
		for (int i = 0; i < B; ++i)
			if (it->second & (1 << i)) {
				u.doc = did + i;
				S.push_back(u);
			}
	return S;
}
