/* by CYB(cybcaoyibo@126.com) */

#include <vector>
#include <fstream>
#include <cstdint>
#include <iostream>

using namespace std;

vector<uint16_t> palette;
uint8_t tile[64 * 64];

int main(int, char**) {
	ifstream ifs("smfdog.bin", ios::in | ios::binary);
	for(int y = 0; y < 64; y++) {
		for(int x = 0; x < 64; x++) {
			uint8_t b, g, r, a;
			ifs.read((char*)&b, 1);
			ifs.read((char*)&g, 1);
			ifs.read((char*)&r, 1);
			ifs.read((char*)&a, 1);
			uint32_t R(r), G(g), B(b);
			R *= 0x1F;
			G *= 0x1F;
			B *= 0x1F;
			R /= 0xFF;
			G /= 0xFF;
			B /= 0xFF;
			uint16_t val = R | (G << 5) | (B << 10);
			int matched = -1;
			for(int i = 0; i < palette.size(); i++) {
				if(palette[i] == val) {
					matched = i;
					break;
				}
			}
			if(matched == -1) {
				tile[y * 64 + x] = palette.size();
				palette.push_back(val);
			} else {
				tile[y * 64 + x] = matched;
			}
		}
	}
	cout << "palette: " << palette.size() << endl;
	ofstream ofs("smfdog.c");
	ofs << "#include <stdint.h>" << endl;
	ofs << "uint8_t smfdog_palette[] = {";
	for(int i = 0; i < palette.size(); i++) {
		ofs << (palette[i] & 0x00FF) << ", ";
		ofs << ((palette[i] & 0xFF00) >> 8);
		if(i < palette.size() - 1)
			ofs << ", ";
	}
	ofs << "};" << endl;
	ofs << "uint8_t smfdog_tile[] = {";
	for(int i = 0; i < 64 * 64; i++) {
		ofs << (int)(tile[i] + 1);
		if(i < 64 * 64 - 1)
			ofs << ", ";
	}
	ofs << "};" << endl;
	ofs << "uint8_t smfdog_palette_size = " << palette.size() << ";" << endl;
	ofs << endl;
	return 0;
}
