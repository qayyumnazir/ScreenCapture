#include <string>
#include <cstdio>
#include <zmq.hpp>
#include "opencv2/opencv.hpp"
#pragma warning( disable : 4996 )

// configuration parameters
#define NUM_COMNMAND_LINE_ARGUMENTS 1
#define DISPLAY_WINDOW_NAME "ScreenCapturer Received Image"

void subscribe()
{
    //Initialize Sockets and contexts
    zmq::context_t ctx(1);
    zmq::socket_t socket(ctx, ZMQ_SUB);
    socket.connect("tcp://192.168.1.13:5555");
    socket.setsockopt(ZMQ_SUBSCRIBE, nullptr, 0); 


    std::cout << "subscribe" << std::endl;

    //Received and imshow image
    cv::Mat img_decode;
    while (true)
    {
        std::cout << "subscribe ..." << std::endl;
        zmq::message_t request;
        auto ok = socket.recv(&request);
        std::vector<uchar> data_reply;
        if (ok) 
        {
            data_reply.resize(request.size());
            memcpy(data_reply.data(), request.data(), request.size());

            img_decode = cv::imdecode(data_reply, cv::IMREAD_COLOR);
            cv::imshow("img_decode", img_decode);
            if ((char)cv::waitKey(1) == 'q') 
            {
                cv::imwrite("D://1.jpg", img_decode);
            };
        }
    }
}


int main()
{
    subscribe();
    return 0;
}