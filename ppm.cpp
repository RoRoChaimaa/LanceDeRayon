#include "pch.h"

#include "ppm.h"

// ecriture
bool PPM::save(string path) {
	cout << "Save commence..." << endl;
	ofstream file(path);

	if (!file.is_open()) {
		cout << "Can't creat the pgm image!" << endl;
		return false;
	}

	// écriture du fichier...

	file << "P3\n" << this->m_height << " " << this->m_width << "\n255\n";

	for (int i = 0; i <= (m_data.size() - 1); i++) {
	//for (int i = 0; i <= ((m_height*m_width)-1); i++) {
		file << m_data[i].r() << " " << m_data[i].g() << " " << m_data[i].b();

		file << '\n';

	}
	file.close();
	cout << "Saved!!!" << endl;
	return true;
}

void PPM::addData(vec3 data) {
	this->m_data.push_back(data);
}
