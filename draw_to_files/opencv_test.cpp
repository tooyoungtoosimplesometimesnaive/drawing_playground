#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>

#include <iostream>
#include <string>

#define w 400

using namespace cv;

using namespace std;


void random_paint() {
}

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


    Mat atom_image = Mat::zeros( w, w, CV_8UC3 );
    const int channels = atom_image.channels();
    cout << channels << endl;
    MatIterator_<Vec3b> it;
    it = atom_image.begin<Vec3b>();

    it += 800;

    (*it)[0] = 255;
    (*it)[1] = 255;
    (*it)[2] = 255;

    it += 1600;
    
    (*it)[0] = 255;
    imshow("test window", atom_image);
    waitKey(0);
    return 0;
}
