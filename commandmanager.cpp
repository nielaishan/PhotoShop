#include "commandmanager.h"
Mat CommandManager::Image;
Mat CommandManager::dealImg;
QStack<Mat> *CommandManager::undoStack = new QStack<Mat>();
QStack<Mat> *CommandManager::redoStack = new QStack<Mat>();
QString CommandManager::preOpStr="";
CommandManager::CommandManager()
{
}

void CommandManager::excute(QString styleName, Mat img) {
    qDebug()<<undoStack->size()<<endl;

    if (styleName == "preprocessing") {
        Image = img;
        undoStack->clear();
        preprocessing();
    }
    else if (styleName == "sketch")
        sketch();
    else if (styleName == "carve")
        carve();
    else if (styleName == "relief")
        relief();
    else if (styleName == "expand")
        expand();
    else if (styleName == "extrusion")
        extrusion();

    if (preOpStr != styleName && !dealImg.empty())
        undoStack->push(dealImg);
    preOpStr = styleName;
}

void CommandManager::preprocessing() {
    //cvtColor是Opencv里的颜色空间转换函数，可以实现RGB颜色向HSV，HSI等颜色空间的转换，也可以转换成灰度图像。
    Mat tmp, dst;
    dst = Image;
    cvtColor(dst, tmp, CV_RGB2RGBA);
    // 先用使用 3x3内核来降噪 中值滤波器去噪
    medianBlur(tmp, dst, 3);
    //锐化
    Mat kernel(3,3,CV_32F,cv::Scalar(0));
    InitMat(kernel);
    cv::filter2D(tmp, dst, tmp.depth(), kernel);
    dealImg = dst;
    QImage img = QImage((const unsigned char*)(dst.data),dst.cols,dst.rows,dst.cols*dst.channels(), QImage::Format_ARGB32);
    ShowWidget::showImage(img);
}

void CommandManager::sketch() {
    if (undoStack->size() == 0 ||  Image.empty())
        return ;
    int width=Image.cols;
    int heigh=Image.rows;
    Mat gray0,gray1;
    //去色
    cvtColor(Image, gray0,CV_BGR2GRAY);
    //反色
    addWeighted(gray0, -1, NULL, 0, 255, gray1);
    //高斯模糊,高斯核的Size与最后的效果有关
    GaussianBlur(gray1,gray1,Size(11,11),0);
    //融合：颜色减淡
    Mat Img(gray1.size(),CV_8UC1);
    for (int y=0; y<heigh; y++)
    {
        uchar* P0  = gray0.ptr<uchar>(y);
        uchar* P1  = gray1.ptr<uchar>(y);
        uchar* P  = Img.ptr<uchar>(y);
        for (int x=0; x<width; x++)
        {
            int tmp0=P0[x];
            int tmp1=P1[x];
            P[x] =(uchar) min((tmp0+(tmp0*tmp1)/(256-tmp1)),255);
        }
    }
    dealImg = Img;
    QImage img = QImage((const unsigned char*)(dealImg.data),dealImg.cols,dealImg.rows,dealImg.cols*dealImg.channels(), QImage::Format_Indexed8);
    ShowWidget::showImage(img);
}

void CommandManager::relief() {
    if (undoStack->size() == 0 ||  Image.empty())
        return ;
    Mat src = Image;
    Mat img0(src.size(),CV_8UC3);
    for (int y=1; y<src.rows-1; y++)
    {
        uchar *p0 = src.ptr<uchar>(y);
        uchar *p1 = src.ptr<uchar>(y+1);

        uchar *q0 = img0.ptr<uchar>(y);
        for (int x=1; x<Image.cols-1; x++)
        {
            for (int i=0; i<3; i++)
            {
                int tmp0 = p1[3*(x+1)+i]-p0[3*(x-1)+i]+128;//浮雕
                if (tmp0<0)
                    q0[3*x+i]=0;
                else if(tmp0>255)
                    q0[3*x+i]=255;
                else
                    q0[3*x+i]=tmp0;
            }
        }
    }
    dealImg = img0;
    QImage img = QImage((const unsigned char*)(dealImg.data),dealImg.cols,dealImg.rows,dealImg.cols*dealImg.channels(), QImage::Format_RGB888);
    ShowWidget::showImage(img);
}

void CommandManager::carve() {
    if (undoStack->size() == 0 ||  Image.empty())
        return ;
    Mat src = Image;
    Mat img0(src.size(),CV_8UC3);
    for (int y=1; y<src.rows-1; y++)
    {
        uchar *p0 = src.ptr<uchar>(y);
        uchar *p1 = src.ptr<uchar>(y+1);
        uchar *q1 = img0.ptr<uchar>(y);
        for (int x=1; x<Image.cols-1; x++)
        {
            for (int i=0; i<3; i++)
            {
                int tmp1 = p0[3*(x-1)+i]-p1[3*(x+1)+i]+128;//雕刻
                if (tmp1<0)
                    q1[3*x+i]=0;
                else if(tmp1>255)
                    q1[3*x+i]=255;
                else
                    q1[3*x+i]=tmp1;
            }
        }
    }
    dealImg = img0;
    QImage img = QImage((const unsigned char*)(dealImg.data),dealImg.cols,dealImg.rows,dealImg.cols*dealImg.channels(), QImage::Format_RGB888);
    ShowWidget::showImage(img);
}

void CommandManager::expand() {
    if (undoStack->size() == 0 ||  Image.empty())
        return ;
    Mat src = Image;
    int width = src.cols;
    int heigh = src.rows;
    Point center(width/2,heigh/2);
    Mat img1(src.size(),CV_8UC3);
    src.copyTo(img1);

    //【1】放大
    int R1 = sqrtf(width*width+heigh*heigh)/2; //直接关系到放大的力度,与R1成正比;

    for (int y=0; y<heigh; y++)
    {
        uchar *img1_p = img1.ptr<uchar>(y);
        for (int x=0; x<width; x++)
        {
            int dis = norm(Point(x,y)-center);
            if (dis<R1)
            {
                int newX = (x-center.x)*dis/R1+center.x;
                int newY = (y-center.y)*dis/R1+center.y;

                img1_p[3*x]=src.at<uchar>(newY,newX*3);
                img1_p[3*x+1]=src.at<uchar>(newY,newX*3+1);
                img1_p[3*x+2]=src.at<uchar>(newY,newX*3+2);
            }
        }
    }
    dealImg = img1;
    QImage img = QImage((const unsigned char*)(dealImg.data),dealImg.cols,dealImg.rows,dealImg.cols*dealImg.channels(), QImage::Format_RGB888);
    ShowWidget::showImage(img);
}

void CommandManager::extrusion() {
    if (undoStack->size() == 0 ||  Image.empty())
        return ;
    Mat src = Image;
    int width = src.cols;
    int heigh = src.rows;
    Point center(width/2,heigh/2);
    Mat img1(src.size(),CV_8UC3);
    src.copyTo(img1);

    for (int y=0; y<heigh; y++)
    {
        uchar *img2_p = img1.ptr<uchar>(y);
        for (int x=0; x<width; x++)
        {
            double theta = atan2((double)(y-center.y),(double)(x-center.x));//使用atan出现问题~

            int R2 = sqrtf(norm(Point(x,y)-center))*8; //直接关系到挤压的力度，与R2成反比;

            int newX = center.x+(int)(R2*cos(theta));

            int newY = center.y+(int)(R2*sin(theta));

            if(newX<0) newX=0;
            else if(newX>=width) newX=width-1;
            if(newY<0) newY=0;
            else if(newY>=heigh) newY=heigh-1;

            img2_p[3*x]=src.at<uchar>(newY,newX*3);
            img2_p[3*x+1]=src.at<uchar>(newY,newX*3+1);
            img2_p[3*x+2]=src.at<uchar>(newY,newX*3+2);
        }
    }
    dealImg = img1;
    QImage img = QImage((const unsigned char*)(dealImg.data),dealImg.cols,dealImg.rows,dealImg.cols*dealImg.channels(), QImage::Format_RGB888);
    ShowWidget::showImage(img);
}
void CommandManager::InitMat(Mat &kernel)
{
    kernel.at<float>(1,1) = 5.0;
    kernel.at<float>(0,1) = -1.0;
    kernel.at<float>(1,0) = -1.0;
    kernel.at<float>(1,2) = -1.0;
    kernel.at<float>(2,1) = -1.0;
}
