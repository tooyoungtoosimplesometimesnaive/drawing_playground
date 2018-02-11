#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>

#include <iostream>
#include <math.h>

using namespace cv;
using namespace std;

double f(double x, double y, double z)
{
	double a = x * x + 9.0 / 4.0 * y * y + z * z - 1;
	return a * a * a - x * x * z * z * z - 9.0 / 80.0 * y * y * z * z * z;
}

double h(double x, double z)
{
	for (double y = 1.0; y >= 0.0; y -= 0.001)
		if (f(x, y, z) <= 0.0)
			return y;
	return 0.0;
}

int main()
{
	int sw = 512, sh = 512;
	Mat Im = Mat::zeros(sw, sh, CV_8UC3);
	Mat_<Vec3b> I = Im;
	for (int sy = 0; sy < sh; sy++)
	{
		double z = 1.5 - sy * 3.0 / sh;
		for (int sx = 0; sx < sw; sx++)
		{
			double x = sx * 3.0 / sw - 1.5;
			double v = f(x, 0.0, z);
			int r = 0;
			if (v <= 0.0)
			{
				double y0 = h(x, z);
				double ny = 0.001;
				double nx = h(x + ny, z) - y0;
				double nz = h(x, z + ny) - y0;
				double nd = 1.0 / sqrt(nx * nx + ny * ny + nz * nz);
				double d = (nx + ny - nz) / sqrt(3.0) * nd * 0.5 + 0.5;
				// cout << d << endl;
				// cout << ".:-=+*#%@"[(int)(d * 5.0f)];
				r = (int)(d * 255.0);
			}
			I(sy, sx)[2] = r;
		}
	}

	imwrite("heart_shape.jpg", Im);
	imshow("Heart Window", Im);
	waitKey(0);

	return 0;
}