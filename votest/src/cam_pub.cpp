#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <opencv2/highgui/highgui.hpp>
#include <cv_bridge/cv_bridge.h>
#include <sstream>

int main(int argc, char** argv) {


    ros::init(argc, argv, "image_publisher");
    ros::NodeHandle nh;
    image_transport::ImageTransport it(nh);
    image_transport::Publisher pub = it.advertise("camera/image", 1);

    cv::VideoCapture cap(0);
    if (!cap.isOpened()) {
    ROS_INFO("cannot open video device\n");
    return 1;
    }

    cv::Mat frame;
    sensor_msgs::ImagePtr msg;

    ros::Rate loop_rate(50);//以10ms间隔发送图片
    while (nh.ok()) {
        cap >> frame;  

        if (!frame.empty()) {  
            msg = cv_bridge::CvImage(std_msgs::Header(), "bgr8", frame).toImageMsg();  
            pub.publish(msg);  
        }
            ROS_INFO("runnning!");
        ros::spinOnce();  
        loop_rate.sleep();//与ros::Rate loop_rate相对应,休息10ms
    }
}
