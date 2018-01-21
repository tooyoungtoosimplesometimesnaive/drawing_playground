#include<iostream>
#include<vector>

using std::vector;


template <typename Func>
void draw(Func f, int h = 20, int w = 20) {
	int x, y;
	for (y = 0; y < h; y++) {
		for (x = 0; x < w; x++) {
			if (f(x,y))
				std::cout<< "* ";
			else
				std::cout<< "  ";
		}
		std::cout << std::endl;
	}
}

template <typename Func, typename T>
void draw(Func f, T h, T w, T x_start, T y_start, T increment) {
	for (T y = y_start; y < h; y += increment) {
		for (T x = x_start; x < w; x += increment) {
			if (f(x,y))
				std::cout<< "* ";
			else
				std::cout<< "  ";
		}
		std::cout << std::endl;
	}
}

int triangle(int x, int y) {
	return abs(x) <= y;
}

int w, h;
void put_v(vector<char> & v, int x, int y, char c) {
	char cc = v[y * w + x];
	if (cc == ' ' || cc == '_')
		v[y * w + x] = c;
}

void koch_curve(vector<char>& v, int n, int dir, int & x, int & y) {
	if (n == 0) {
		switch (dir % 6) {
		case 0: put_v(v, x++, y, '_');
			put_v(v, x++, y, '_');
			break;
		case 1: put_v(v, x++, y--, '/');
			break;
		case 2: put_v(v, --x, y--, '\\');
			break;
		case 3: put_v(v, --x, y, '_');
			put_v(v, --x, y, '_');
			break;
		case 4: put_v(v, --x, ++y, '/');
			break;
		case 5: put_v(v, x++, ++y, '\\');
			break;
		}
	}
	else {
		koch_curve(v, n - 1, dir, x, y);
		koch_curve(v, n - 1, dir + 1, x, y);
		koch_curve(v, n - 1, dir + 5, x, y);
		koch_curve(v, n - 1, dir, x, y);
	}
}

void draw_koch_curve() {

	w = 2, h = 1;
 
	for (int n = 0; n < 4; n++) {
		vector<char> v;
		for (int i = 0; i < w * h; i++)
			v.push_back(' ');
	
		int x = 0, y = h - 1;
		koch_curve(v, n, 0, x, y);
		std::cout << "\n\nn=" << n << "\n";
		for (int j = 0; j < h; j++) {
			for (int i = 0; i < w; i++) {
				std::cout << v[j * w + i];
			}
			std::cout << std::endl;
		}
		w *= 3;
		h = n == 0 ? 1 : h * 3;
	}	
}

void draw_koch_snowflake() {
	w = 2, h = 4;
 
	for (int n = 0; n < 4; n++) {
		vector<char> v;
		for (int i = 0; i < w * h; i++)
			v.push_back(' ');

		int x = 0, y = h/4 - 1;
		koch_curve(v, n, 0, x, y);
		koch_curve(v, n, 4, x, y);
		koch_curve(v, n, 2, x, y);

		std::cout << "\n\nn=" << n << "\n";
		for (int j = 0; j < h; j++) {
			for (int i = 0; i < w; i++) {
				std::cout << v[j * w + i];
			}
			std::cout << std::endl;
		}
		w *= 3;
		h = n == 0 ? 4 : h * 3;
	}	
}

int main() {
	draw([] (int x, int y) {return (x - 10) * (x - 10) + (y - 10) * (y - 10) <= 8 * 8;});
	draw([] (int x, int y) {return abs(x - 11) <= y;}, 12, 23);
	draw([] (int x, int y) {return x <= y;}, 12, 23);
	draw([] (int x, int y) {return triangle(x % 6 - 2, y % 3);}, 12, 23);
	draw([] (int x, int y) {return triangle((x + y / 3 * 3 + 3) % 6 - 2, y % 3);}, 12, 23);
	draw([] (int x, int y) {return triangle(x - 11, y) && triangle((x + y / 3 * 3 + 3) % 6 - 2, y % 3);}, 12, 23);
	draw([] (float x, float y) { float a = x * x + y * y - 1;
		return (a * a * a + x * x * y * y * y) <= 0.0f;
	}, 1.5f, 1.5f, -1.5f, -1.5f, 0.1f);

	draw_koch_curve();
	draw_koch_snowflake();

	// Double Folium : (x^2 + y^2)^2 = 4axy^2
	draw([] (float x, float y) {
		float a = x * x + y * y;
		return (a * a - 4.0f * x * y * y) <= 0.0f;
	}, 1.5f, 1.5f, -1.5f, -1.5f, 0.05f);

	// Pear-shaped quartic
	draw([] (float x, float y) {
		return (0.25f * y * y - x * x * x * (1.0f - x)) <= 0.0f;
	}, 1.5f, 1.5f, -1.5f, -1.5f, 0.05f);

	return 0;
}
