#include<iostream>


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

int main() {
	draw([] (int x, int y) {return (x - 10) * (x - 10) + (y - 10) * (y - 10) <= 8 * 8;});
	draw([] (int x, int y) {return abs(x - 11) <= y;}, 12, 23);
	draw([] (int x, int y) {return x <= y;}, 12, 23);
	draw([] (int x, int y) {return triangle(x % 6 - 2, y % 3);}, 12, 23);
	draw([] (int x, int y) {return triangle((x + y / 3 * 3 + 3) % 6 - 2, y % 3);}, 12, 23);
	draw([] (int x, int y) {return triangle(x - 11, y) && triangle((x + y / 3 * 3 + 3) % 6 - 2, y % 3);}, 12, 23);
	draw([] (float x, float y) { float a = x * x + y * y - 1;
		return (a * a * a - x * x * y * y * y) <= 0.0f;
	}, 1.5f, 1.5f, -1.5f, -1.5f, 0.1f);

	return 0;
}
