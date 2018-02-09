#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>

#include <iostream>
#include <string>
#include <random>
#include <utility>
#include <vector>

using namespace cv;

using namespace std;

const int w = 1000;

int all = 1000000;
int N2 =   780840;
int O2 =   209460;
int Ar =     9340;
int Other =   360;

int main( int argc, char** argv )
{

	Mat atmosphere_image = Mat::ones( w, w, CV_8UC3 );
	const int channels = atmosphere_image.channels();
	cout << channels << endl;

	vector<pair<int, int>> vp;
	vp.push_back(make_pair(1, N2));
	vp.push_back(make_pair(N2 + 1, N2 + O2));
	vp.push_back(make_pair(N2 + O2 + 1, N2 + O2 + Ar));
	vp.push_back(make_pair(N2 + O2 + Ar + 1, all));

	default_random_engine e;

	MatIterator_<Vec3b> it, end;
	it = atmosphere_image.begin<Vec3b>();
	end = atmosphere_image.end<Vec3b>();

	int N2_test = 0;
	int O2_test = 0;
	int Ar_test = 0;
	int Other_test = 0;

	for (;it != end; it++)
	{
		uniform_int_distribution<int> distribution(1, all);
		int r = distribution(e);

		if (r >= vp[3].first && r <= vp[3].second)
		{
			(*it)[0] = 255;
			(*it)[1] = 1;
			(*it)[2] = 1;
			all -= 1;
			vp[3].second = all;
			Other_test ++;
		}
		else if (r >= vp[2].first && r <= vp[2].second)
		{
			(*it)[0] = 1;
			(*it)[1] = 255;
			(*it)[2] = 1;
			all -= 1;
			vp[3].second = all;
			vp[3].first -= 1;
			vp[2].second -= 1;
			Ar_test ++;
		}
		else if (r >= vp[1].first && r <= vp[1].second)
		{
			(*it)[0] = 1;
			(*it)[1] = 1;
			(*it)[2] = 255;

			all -= 1;
			vp[3].second = all;
			vp[3].first -= 1;
			vp[2].second -= 1;
			vp[2].first -= 1;
			vp[1].second -= 1;
			O2_test ++;
		}
		else // if (r >= vp[0].first && r <= vp[0].second)
		{
			(*it)[0] = 255;
			(*it)[1] = 255;
			(*it)[2] = 255;

			all -= 1;
			vp[3].second = all;
			vp[3].first -= 1;
			vp[2].second -= 1;
			vp[2].first -= 1;
			vp[1].second -= 1;
			vp[1].first -= 1;
			N2_test ++;
		}
	}

	cout << N2 << " -> " << N2_test << endl;
	cout << O2 << " -> " << O2_test << endl;
	cout << Ar << " -> " << Ar_test << endl;
	cout << Other << " -> " << Other_test << endl;

	imwrite("./atmoshpere.jpg", atmosphere_image);
	imshow("test window", atmosphere_image);
	waitKey(0);
	return 0;
}

