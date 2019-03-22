#pragma once
#include <vector>
#include <math.h>
#include <cstring>
#include <iostream>
#include <fstream>
#include "vec3.h"
using namespace std;

class PPM {
public:
	PPM(int height, int width, vector<vec3> data) : m_height(height),
		m_width(width),
		m_data(data) {};
	PPM() {}
	~PPM() {}


	bool save(string path);
	void addData(vec3 data);

	// Accesseurs
	int getWidth() { return m_width; }
	int getHeight() { return m_height; }
	vec3 getData(int i) { return m_data[i]; }

	// Accesseurs
	void setWidth(int _width) { m_width = _width; }
	void setHeight(int _height) { m_height = _height; }
	void setData(vector<vec3> _data) { m_data = _data; }


private:
	vector<vec3> m_data;
	int m_width;
	int m_height;
};
