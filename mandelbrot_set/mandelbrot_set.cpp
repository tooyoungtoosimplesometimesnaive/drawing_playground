#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>

#include <iostream>
#include <complex>
#include <vector>
#include <math.h>

using namespace cv;
using namespace std;

using c_d = complex<double>;

vector<Vec3b> vcolor = {Vec3b(66, 30, 15),Vec3b(25, 7, 26),Vec3b(9, 1, 47),Vec3b(4, 4, 73),Vec3b(0, 7, 100),Vec3b(12, 44, 138),Vec3b(24, 82, 177),Vec3b(57, 125, 209),Vec3b(134, 181, 229),Vec3b(211, 236, 248),Vec3b(241, 233, 191),Vec3b(248, 201, 95),Vec3b(255, 170, 0),Vec3b(204, 128, 0),Vec3b(153, 87, 0),Vec3b(106, 52, 3)};

pair<c_d, int> mandelbrot_iter_steps(c_d z, c_d c, int iter_num)
{
	for (int i = 0; i < iter_num; i++)
	{
		z = z * z + c;
		if (norm(z) > 4)
			return make_pair(z, i);
	}
	return make_pair(z, 0);

}

double smooth_color(pair<c_d, int> p)
{
	if (p.second == 0)
		return 0;
	else
	{
		auto z = p.first;
		int i = p.second;
		double log_z = log(norm(z));
		double nu = log(log_z) / log(2.0);
		return i - nu;
	}
}

Vec3b color(int i, int Max)
{
	// Vec3b: B G R
	// I = Max -> 255 255 255
	// I = 0 -> 0 0 0
	if (i == Max)
		return Vec3b(255, 255, 255);

	int step = 16777216 / Max;
	int c = step * i;
	int B = c % 65536;
	int G = (c - B * 65536) % 256;
	int R = (c - B * 65536 - G * 256);
	return Vec3b(B, G, R);
}

Vec3b paint_smooth_color(double i, double Max)
{
	if (i >= Max)
		return Vec3b(255, 255, 255);
	/*
	double step = 16777216.0 / Max;
	int c = floor(step * i);
	int B = c % 65536;
	int G = (c - B * 65536) % 256;
	int R = (c - B * 65536 - G * 256);
	return Vec3b(B, G, R);
	*/
	return vcolor[floor(i) % 16];
}

int main()
{
	const int w = 1000;

	Mat Im = Mat::zeros(w, w, CV_8UC3);
	Mat_<Vec3b> I = Im;
	for (int i = 0; i < I.rows; i++)
	{
		for (int j = 0; j < I.cols; j++)
		{
			c_d c(j/250.0 - 2.0, i/250.0 - 2.0);
			c_d z(0.0, 0.0);
			auto intensity = mandelbrot_iter_steps(z, c, 1000);
			double smoothed = smooth_color(intensity);
			I(i, j) = paint_smooth_color(smoothed, 1000.0);
		}

	}
	imshow("test window", Im);
	waitKey(0);

	return 0;
}

