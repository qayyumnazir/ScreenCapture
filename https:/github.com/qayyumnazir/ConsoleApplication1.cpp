#pragma once
#include <Windows.h>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <zmq.hpp>
#include <Windows.h>
#include <cstdio>
#pragma warning( disable : 4996 )

using namespace cv;
using namespace std;
int arr1[4]; //Holds coordinates of two positions
HWND hwnd = GetDesktopWindow();

//Draw a rectangle on screen
void drawRect(int x1,int y1,int x2,int y2) {
	HDC screenDC = ::GetDC(0);
	HWND hwnd = GetDesktopWindow();
	::SelectObject(screenDC, GetStockObject(NULL_BRUSH));
	::SelectObject(screenDC, GetStockObject(WHITE_PEN));
	::Rectangle(screenDC, x1,y1,x2,y2);
	::ReleaseDC(0, screenDC);
	UpdateWindow(hwnd);

}

//User Mouse and Confirmming the Crop
void CheckMouseButtonStatus()
{
	//Check the mouse left button is pressed or not
	boolean first = true;
	boolean second = true;
	POINT p1;
	p1.x = 0;
	p1.y = 0;
	POINT p2;
	p2.x = 0;
	p2.y = 0;
	cout << "Press W if youre ready.\n";
	while (true)
	{
		if (GetKeyState('W') & 0x80)
		{
			break;
		}
	}
	boolean gas = true;
	cout << "Ready to click\n";
	while (true)
	{

		if ((GetKeyState(VK_LBUTTON) & 0x80) != 0)
		{
			while ((GetKeyState(VK_LBUTTON) & 0x80) != 0)
			{
				while (first)
				{
					first = false;
					GetCursorPos(&p1);
					cout << p1.x;
					cout << " and ";
					cout << p1.y;
					cout << "\n";
					arr1[0] = p1.x;
					arr1[1] = p1.y;

				}
			}
			GetCursorPos(&p2);
			cout << p2.x;
			cout << " and ";
			cout << p2.y;
			arr1[2] = p2.x;
			arr1[3] = p2.y;
			cout << "To proceed with the shape, press A, to redo press S\n";
			bool Proceed = false;
			while (true)
			{
				drawRect(p1.x, p1.y, p2.x, p2.y);
				if (GetKeyState('A') & 0x8000)
				{
					Proceed=true;
					break;
				}
				else if (GetKeyState('S') & 0x8000)
				{
					first = true;
					second = true;
					cout << "Ready to click\n";
					UpdateWindow(hwnd);
					break;
				}
			}
			
			if (Proceed)
			{
				break;
			}
			
		}
		
	}
}
/**
 * Create a Bitmap file header..
 *
 * @param hwindowDC : window handle.
 * @param widht	    : image width.
 * @param height    : image height.
 *
 * @return Bitmap header.
 */
BITMAPINFOHEADER createBitmapHeader(int width, int height)
{
	BITMAPINFOHEADER  bi;

	// create a bitmap
	bi.biSize = sizeof(BITMAPINFOHEADER);
	bi.biWidth = width;
	bi.biHeight = -height;  //this is the line that makes it draw upside down or not
	bi.biPlanes = 1;
	bi.biBitCount = 32;
	bi.biCompression = BI_RGB;
	bi.biSizeImage = 0;
	bi.biXPelsPerMeter = 0;
	bi.biYPelsPerMeter = 0;
	bi.biClrUsed = 0;
	bi.biClrImportant = 0;

	return bi;
}
#define NUM_COMNMAND_LINE_ARGUMENTS 2
#define DISPLAY_WINDOW_NAME "Camera Image"

bool processFrame(const cv::Mat& imageIn, cv::Mat& imageOut);

bool processFrame(const cv::Mat& imageIn, cv::Mat& imageOut)
{
	// copy the input image frame to the ouput image
	imageIn.copyTo(imageOut);

	// return true on success
	return true;
}
/**
 * Capture a screen window as a matrix.
 *
 * @param hwnd : window handle.
 *
 * @return Mat (Mat of the captured image)
 */
Mat captureScreenMat(HWND hwnd)
{
	Mat src;

	// get handles to a device context (DC)
	HDC hwindowDC = GetDC(hwnd);
	HDC hwindowCompatibleDC = CreateCompatibleDC(hwindowDC);
	SetStretchBltMode(hwindowCompatibleDC, COLORONCOLOR);

	// define scale, height and width
	int scale = 1;
	int screenx = arr1[0];
	int screeny = arr1[1];
	int width = arr1[2]-arr1[0];
	int height = arr1[3] - arr1[1];

	// create mat object
	src.create(height, width, CV_8UC4);

	// create a bitmap
	HBITMAP hbwindow = CreateCompatibleBitmap(hwindowDC, width, height);
	BITMAPINFOHEADER bi = createBitmapHeader(width, height);

	// use the previously created device context with the bitmap
	SelectObject(hwindowCompatibleDC, hbwindow);

	// copy from the window device context to the bitmap device context
	StretchBlt(hwindowCompatibleDC, 0, 0, width, height, hwindowDC, screenx, screeny, width, height, SRCCOPY);  //change SRCCOPY to NOTSRCCOPY for wacky colors !
	GetDIBits(hwindowCompatibleDC, hbwindow, 0, height, src.data, (BITMAPINFO*)&bi, DIB_RGB_COLORS);            //copy from hwindowCompatibleDC to hbwindow

	// avoid memory leak
	DeleteObject(hbwindow);
	DeleteDC(hwindowCompatibleDC);
	ReleaseDC(hwnd, hwindowDC);

	return src;
}

int main()
{
	// initialize the zmq context and socket
	zmq::context_t context(1);
	zmq::socket_t socket(context, ZMQ_PUB);
	socket.bind("tcp://192.168.1.13:5555");   // here is the binding address
	cv::Mat frame;
	std::vector<uchar> data_encode;

	//Create the crop and show image
	CheckMouseButtonStatus();
	while (true) 
	{
		// capture image
		data_encode.clear();
		HWND hwnd = GetDesktopWindow();
		Mat src = captureScreenMat(hwnd);

		// encode result
		std::vector<uchar> buf;
		cv::imencode(".png", src, buf);

		// show img
		cv::imshow("Screenshot.png",src);
		zmq::message_t msg(buf.size());
		memcpy(msg.data(), buf.data(), buf.size());
		socket.send(msg);
		waitKey(1);

		if (GetKeyState('D') & 0x8000){
			break;
		}
		
		
		
	}
	return 0;
	

}