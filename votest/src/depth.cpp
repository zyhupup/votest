#include "opencv2/calib3d/calib3d.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/core/utility.hpp"
#include <ros/ros.h>  
#include <image_transport/image_transport.h>  
#include <cv_bridge/cv_bridge.h>
#include <stdio.h>
#include <iostream>
#define ture 1
#define false 0
using namespace cv;
using namespace std;
cv::Mat caml,camr,cameye0,cameye1;
bool camflag=ture;
void imageCallbackl(const sensor_msgs::ImageConstPtr& msg)  
{  

  cv_bridge::CvImagePtr cv_ptr;  
  try  
  {  
     cv_ptr = cv_bridge::toCvCopy(msg, "mono8");  
  }  
  catch (cv_bridge::Exception& e)  
  {  
     ROS_ERROR("cv_bridge exception: %s", e.what());  
     return;  
  }  

  // cv::Mat caml;
  caml = cv_ptr->image;  
//imshow("1",caml);
  // fail if don't have waitKey(3).
 // cv::waitKey(3);
}  
void imageCallbackr(const sensor_msgs::ImageConstPtr& msg)  
{  

  cv_bridge::CvImagePtr cv_ptr;  
  try  
  {  
     cv_ptr = cv_bridge::toCvCopy(msg, "mono8");  
  }  
  catch (cv_bridge::Exception& e)  
  {  
     ROS_ERROR("cv_bridge exception: %s", e.what());  
     return;  
  }  

  // cv::Mat camr;
  camr = cv_ptr->image;  
//imshow("2",camr);
  // fail if don't have waitKey(3).
  //cv::waitKey(3);
}  

void imageCallbackfisheye(const sensor_msgs::ImageConstPtr& msg)  
{  
  cv_bridge::CvImagePtr cv_ptr;  
  try  
  {  
     cv_ptr = cv_bridge::toCvCopy(msg, "bgr8");  
  }  
  catch (cv_bridge::Exception& e)  
  {  
     ROS_ERROR("cv_bridge exception: %s", e.what());  
     return;  
  }  
  if(camflag)
  {
    cameye1 = cv_ptr->image;  
    cameye0.size()=cv_ptr->image.size();
    camflag=false;
  }

  if(!camflag);
  {
    cameye0=cameye1;
    cameye1=cv_ptr->image;
  }


}  

int main(int argc, char** argv)
{    
    ros::init(argc, argv, "zr300_subscriber");  
    ros::NodeHandle nh;  
    image_transport::ImageTransport it(nh);  
  //  image_transport::Subscriber subl = it.subscribe("/zr300_node/ir_1/image_raw", 1, imageCallbackl);
  //  image_transport::Subscriber subr = it.subscribe("/zr300_node/ir_2/image_raw", 1, imageCallbackr);
    // image_transport::Subscriber  subfisheye =it.subscribe("/zr300_node/fisheye/image_raw",1,imageCallbackfisheye);
    image_transport::Subscriber  subfisheye =it.subscribe("/zr300_node/fisheye/image_raw",1,imageCallbackfisheye);
     image_transport::Publisher pub0 = it.advertise("camera/fisheye0", 1);
     image_transport::Publisher pub1 = it.advertise("camera/fisheye1", 1);
    ros::Rate loop_rate(30); 
    sensor_msgs::ImagePtr msg0;
    sensor_msgs::ImagePtr msg1;
    while(ros::ok){
    //show(caml,camr);
   
   // fail if don't have waitKey(3).
   //std::cout<<"ss"<<std::endl;
   ros::spinOnce(); 
   if(!cameye0.empty()&!cameye1.empty()){
    msg0 = cv_bridge::CvImage(std_msgs::Header(), "bgr8", cameye0).toImageMsg();  
    msg1 = cv_bridge::CvImage(std_msgs::Header(), "bgr8", cameye1).toImageMsg();  
    pub0.publish(msg0);  
    pub1.publish(msg1);  
   imshow("1",cameye0);
   imshow("2",cameye1);
    
   // fail if don't have waitKey(3).
    cv::waitKey(3);
   }
   loop_rate.sleep();
  }
    // ros::spinOnce(); 
    // loop_rate.sleep();
    
    return 0;
}