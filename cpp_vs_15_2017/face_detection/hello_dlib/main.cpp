#include <dlib\config.h>
#include <dlib\image_processing\frontal_face_detector.h>
#include <dlib\gui_widgets.h>
#include <dlib\image_io.h>
#include <iostream>

#define USE_CONSOLE

// How to convert cv::Mat to dlib::array2d<rgb_pixel>?
// https://stackoverflow.com/questions/29118317/how-to-convert-mat-to-array2drgb-pixel/40687888

//using namespace dlib;
using namespace std;
using namespace dlib;

int main(int argc, char** argv)
{
	try
	{
#ifdef USE_CONSOLE
		if (argc == 1)
		{
			std::cout << "Give some image files as arguments to this program." << endl;
			return -1;
		}
#endif


		frontal_face_detector detector = get_frontal_face_detector();
		image_window win;

		// Loop over all the images provided on the command line.
		for (int i = 1; i < argc; ++i)
		{
			std::cout << "processing image " << argv[i] << std::endl;
			array2d<unsigned char> img;
#ifdef USE_CONSOLE
			load_image(img, argv[i]);
#else
			load_image(img, "1.jpg");
#endif // USE_CONSOLE

			
			// Make the image bigger by a factor of two.  This is useful since
			// the face detector looks for faces that are about 80 by 80 pixels
			// or larger.  Therefore, if you want to find faces that are smaller
			// than that then you need to upsample the image as we do here by
			// calling pyramid_up().  So this will allow it to detect faces that
			// are at least 40 by 40 pixels in size.  We could call pyramid_up()
			// again to find even smaller faces, but note that every time we
			// upsample the image we make the detector run slower since it must
			// process a larger image.
			pyramid_up(img);

			// Now tell the face detector to give us a list of bounding boxes
			// around all the faces it can find in the image.
			std::vector<rectangle> dets = detector(img);

			std::cout << "Number of faces detected: " << dets.size() << endl;
			// Now we show the image on the screen and the face detections as
			// red overlay boxes.
			win.clear_overlay();
			win.set_image(img);
			win.add_overlay(dets, rgb_pixel(255, 0, 0));
			
			std::cout << "Hit enter to process the next image..." << std::endl;
			std::cin.get();
		}
	}
	catch (const std::exception& e)
	{
		std::cout << "\nexception thrown!" << std::endl;
		std::cout << e.what() << std::endl;
	}
	return 0;
}