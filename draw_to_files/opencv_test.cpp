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
    String imageName( "./ferrari_488.jpg" ); // by default

    Mat image;

    image = imread( imageName, IMREAD_COLOR ); // Read the file

    if( image.empty() )                      // Check for invalid input
    {
        cout <<  "Could not open or find the image" << std::endl ;
        return -1;
    }

    namedWindow( "Display window", WINDOW_AUTOSIZE ); // Create a window for display.

    imshow( "Display window", image );                // Show our image inside it.


    Mat atom_image = Mat::ones( w, w, CV_8UC3 );
    const int channels = atom_image.channels();
    cout << channels << endl;


    vector<pair<int, int>> vp;
    vp.push_back(make_pair(1, N2));
    vp.push_back(make_pair(N2 + 1, N2 + O2));
    vp.push_back(make_pair(N2 + O2 + 1, N2 + O2 + Ar));
    vp.push_back(make_pair(N2 + O2 + Ar + 1, all));

    default_random_engine e;

    MatIterator_<Vec3b> it, end;
    it = atom_image.begin<Vec3b>();
    end = atom_image.end<Vec3b>();

    for (;it != end; it++)
    {
    	uniform_int_distribution<int> distribution(1, all);
	int r = distribution(e);
	cout << r << endl;

	if (r >= vp[3].first && r <= vp[3].second)
	{
		(*it)[0] = 255;
		(*it)[1] = 1;
		(*it)[2] = 1;
		all -= 1;
		vp[3].second = all;
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
	}
    }

    imshow("test window", atom_image);
    waitKey(0);
    return 0;
}
