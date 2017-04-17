#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

class GeoHash {
public:
	GeoHash(string& hash);
	GeoHash(double lng, double lat);
	void display_hash();
	void display_gpspoint();
	static void set_hash_length(int l) { hash_length = l; }
private:
	string hash;
	double lng;
	double lat;
	static int hash_length;
	static const double max_lng;
	static const double min_lng;
	static const double max_lat;
	static const double min_lat;
	static const string hash_table;
	void check(double &s, double &t, int& v, double& k);
	void revert(double &s, double &t, int index);
};

int GeoHash::hash_length = 10;
const string GeoHash::hash_table = "0123456789bcdefghjkmnpqrstuvwxyz";
const double GeoHash::max_lng = 180;
const double GeoHash::min_lng = -180;
const double GeoHash::max_lat = 90;
const double GeoHash::min_lat = -90;

void GeoHash::check(double &s, double &t, int& v, double &k)
{
	double m = (s+t)/2;
	if (k < m) {
		v = v*2;
		t = m;
	} else {
		v = v*2 + 1;
		s = m;
	}
}

void GeoHash::revert(double& s, double& t, int index)
{
	double m = (s + t)/2;
	if (index & 1) {
		s = m;
	} else {
		t = m;
	}
}

GeoHash::GeoHash(string& hash)
{
	double s1 = min_lng, t1 = max_lng;
	double s2 = min_lat, t2 = max_lat;
	bool odd = true;

	this->hash = hash;
	for (string::size_type i=0; i < hash.length(); ++i) {
		int v = hash_table.find(hash.at(i));
		for (int k = 4; k >= 0; --k) {
			if (odd) {
				revert(s1, t1, (v >> k) & 1);
			} else {
				revert(s2, t2, (v >> k) & 1);
			}
			odd = !odd;
		}
	}

	this->lng = (s1 + t1)/2;
	this->lat = (s2 + t2)/2;
}

GeoHash::GeoHash(double lat, double lng)
{
	int v = 0;
	double s1 = min_lng, t1 = max_lng;
	double s2 = min_lat, t2 = max_lat;

	this->lng = lng;
	this->lat = lat;

	for (int i = 1; i <= hash_length*5; ++i) {
		if (i & 1) {	// odd - lng
			check(s1, t1, v, lng);
		} else {		// even - lat
			check(s2, t2, v, lat);
		}
		if (i % 5 == 0) {
			hash = hash + hash_table.at(v);
			v = 0;
		}
	}
}

void GeoHash::display_hash()
{
	cout << hash << endl;
}

void GeoHash::display_gpspoint()
{
	cout.setf(ios::fixed);
	cout << setprecision(6) << lat;
	cout << ' ';
	cout << setprecision(6) << lng;
	cout << endl;
}

int main()
{
	int n, m;
	cin >> n >> m;
	for (int i = 0; i < n; ++i) {
		double lat, lng;
		cin >> lat >> lng;
		GeoHash(lat, lng).display_hash();
	}

	for (int i=0; i<m; ++i) {
		string hash;
		cin >> hash;
		GeoHash(hash).display_gpspoint();
	}
	return 0;
}
