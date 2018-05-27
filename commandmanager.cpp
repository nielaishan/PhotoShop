#include "commandmanager.h"

Mat CommandManager::Image;
Mat CommandManager::dealImg;
QString CommandManager::preOpStr="";
bool CommandManager::isInitImg = false;
QStack<Mat> *CommandManager::undoStack = new QStack<Mat>();
QStack<Mat> *CommandManager::redoStack = new QStack<Mat>();
const double kernRatio=0.01; //自适应核比例
const double wFactor=0.95; //w系数 用来调节
const double min_t =0.1; //最小透射率

CommandManager::CommandManager(){
   isInitImg = false;
}
/*
 * 选择不同接口
 */
void CommandManager::excute(QString styleName, Mat img) {
    qDebug()<<styleName<<endl;
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
    else if (styleName == "nostalgia")
        nostalgia();
    else if (styleName == "comic")
        comic();
    else if (styleName == "cast")
        cast();
    else if (styleName == "frozen")
        frozen();
    else if (styleName == "woolglass")
        woolGlass();
    else if (styleName == "vugue")
        vugue();
    else if (styleName == "bulge")
        bulge();
    else if (styleName == "sunken")
        sunken();
    else if (styleName == "mosaic")
        mosaic();
    else if (styleName == "light")
        light();
    else if (styleName == "fog")
        fog();
    else if (styleName == "gray")
        gray();
    else if (styleName == "pencil")
        pencil();
    else if (styleName == "BW")
        BW();
    else if (styleName == "negative")
        negative();
    else if (styleName == "wood")
        wood();
    else if (styleName == "autumn")
        colorTrans(1);
    else if (styleName == "bone")
        colorTrans(2);
    else if (styleName == "jet")
        colorTrans(3);
    else if (styleName == "winter")
        colorTrans(4);
    else if (styleName == "ocean")
        colorTrans(5);
    else if (styleName == "summer")
        colorTrans(6);
    else if (styleName == "spring")
        colorTrans(7);
    else if (styleName == "cool")
        colorTrans(8);
    else if (styleName == "hsv")
        colorTrans(9);
    else if (styleName == "pink")
        colorTrans(10);
    else if (styleName == "hot")
        colorTrans(11);
    else if (styleName.size() == 1)
        selectChannel(styleName);
    else
        saveImage(styleName);

    if (preOpStr != styleName && !dealImg.empty())
        undoStack->push(dealImg);
    preOpStr = styleName;
}
/*
 * 预处理
 */
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
    showImage(dst, true, QImage::Format_RGB32);
}
/*
 * 素描
 */
void CommandManager::sketch() {
    if (undoStack->size() == 0 ||  Image.empty())
        return ;
    int width=Image.cols;
    int heigh=Image.rows;
    Mat gray0,gray1;
    //去色
    gray0 = Image;
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
    showImage(Img, false, QImage::Format_Indexed8);
}
/*
 * 浮雕
 */
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
    showImage(img0, true, QImage::Format_RGB32);
}
/*
 * 雕刻
 */
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
    showImage(img0, true, QImage::Format_RGB32);
}
/*
 * 扩大
 */
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
    showImage(img1, true, QImage::Format_RGB32);
}
/*
 * 挤压
 */
void CommandManager::extrusion() {
    if (undoStack->size() == 0 || Image.empty())
        return ;
    Mat src = Image;
    int width = src.cols;
    int heigh = src.rows;
    Point center(width/2,heigh/2);
    Mat img2(src.size(),CV_8UC3);
    src.copyTo(img2);
    for (int y=0; y<heigh; y++)
    {
        uchar *img2_p = img2.ptr<uchar>(y);
        for (int x=0; x<width; x++)
        {
            int tX = x-center.x;
            int tY = y-center.y;
            double theta = atan2((double)tY,(double)tX);//使用atan出现问题~

            int R2 = sqrtf(norm(Point(x,y)-center))*32; //直接关系到挤压的力度，与R2成反比;

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
    showImage(img2, true, QImage::Format_RGB32);
}
/*
 * 怀旧
 */
void CommandManager::nostalgia() {
    if (undoStack->size() == 0 ||  Image.empty())
        return ;
    Mat src = Image;
    int width=src.cols;
    int heigh=src.rows;
    Mat img(src.size(),CV_8UC3);
    for (int y=0; y<heigh; y++)
    {
        uchar* P0  = src.ptr<uchar>(y);
        uchar* P1  = img.ptr<uchar>(y);
        for (int x=0; x<width; x++)
        {
            float B=P0[3*x];
            float G=P0[3*x+1];
            float R=P0[3*x+2];
            float newB=0.272*R+0.534*G+0.131*B;
            float newG=0.349*R+0.686*G+0.168*B;
            float newR=0.393*R+0.769*G+0.189*B;
            if(newB<0)
                newB=0;
            if(newB>255)
                newB=255;
            if(newG<0)
                newG=0;
            if(newG>255)
                newG=255;
            if(newR<0)
                newR=0;
            if(newR>255)
                newR=255;
            P1[3*x] = (uchar)newB;
            P1[3*x+1] = (uchar)newG;
            P1[3*x+2] = (uchar)newR;
        }
    }
    showImage(img, true, QImage::Format_RGB32);
}
/*
 * 连环画
 */
void CommandManager::comic() {
    if (undoStack->size() == 0 ||  Image.empty())
        return ;
    Mat src  = Image;
    int width=src.cols;
    int heigh=src.rows;
    Mat img(src.size(),CV_8UC3);
    for (int y=0; y<heigh; y++)
    {
        uchar* P0  = src.ptr<uchar>(y);
        uchar* P1  = img.ptr<uchar>(y);
        for (int x=0; x<width; x++)
        {
            float B=P0[3*x];
            float G=P0[3*x+1];
            float R=P0[3*x+2];
            float newB=abs(B-G+B+R)*G/256;
            float newG=abs(B-G+B+R)*R/256;
            float newR=abs(G-B+G+R)*R/256;
            if(newB<0)newB=0;
            if(newB>255)newB=255;
            if(newG<0)newG=0;
            if(newG>255)newG=255;
            if(newR<0)newR=0;
            if(newR>255)newR=255;
            P1[3*x] = (uchar)newB;
            P1[3*x+1] = (uchar)newG;
            P1[3*x+2] = (uchar)newR;
        }

    }
    Mat gray;
    cvtColor(img,gray,CV_BGR2GRAY);
    normalize(gray,gray,255,0,CV_MINMAX);
    showImage(img, true, QImage::Format_RGB32);
}

void CommandManager::InitMat(Mat &kernel)
{
    kernel.at<float>(1,1) = 5.0;
    kernel.at<float>(0,1) = -1.0;
    kernel.at<float>(1,0) = -1.0;
    kernel.at<float>(1,2) = -1.0;
    kernel.at<float>(2,1) = -1.0;
}
/*
 * 熔铸
 */
void CommandManager::cast() {
    if (undoStack->size() == 0 ||  Image.empty())
        return ;
    Mat src;
    Image.copyTo(src);
    int width=Image.cols;
    int heigh=Image.rows;
    Mat dst(src.size(),CV_8UC3);
    for (int y=0;y<heigh;y++)
    {
        uchar* imgP=src.ptr<uchar>(y);
        uchar* dstP=dst.ptr<uchar>(y);
        for (int x=0;x<width;x++)
        {
            float b0=imgP[3*x];
            float g0=imgP[3*x+1];
            float r0=imgP[3*x+2];

            float b = b0*255/(g0+r0+1);
            float g = g0*255/(b0+r0+1);
            float r = r0*255/(g0+b0+1);

            r = (r>255 ? 255 : (r<0? 0 : r));
            g = (g>255 ? 255 : (g<0? 0 : g));
            b = (b>255 ? 255 : (b<0? 0 : b));

            dstP[3*x] = (uchar)b;
            dstP[3*x+1] = (uchar)g;
            dstP[3*x+2] = (uchar)r;
        }
    }
    showImage(dst, true, QImage::Format_RGB32);
}
/*
 * 冰冻
 */
void CommandManager::frozen() {
    if (undoStack->size() == 0 ||  Image.empty())
        return ;
    Mat src;
    Image.copyTo(src);
    int width=Image.cols;
    int heigh=Image.rows;
    Mat dst(src.size(),CV_8UC3);
    for (int y=0;y<heigh;y++)
    {
        uchar* imgP=src.ptr<uchar>(y);
        uchar* dstP=dst.ptr<uchar>(y);
        for (int x=0;x<width;x++)
        {
            float b0=imgP[3*x];
            float g0=imgP[3*x+1];
            float r0=imgP[3*x+2];

            float b = (b0-g0-r0)*3/2;
            float g = (g0-b0-r0)*3/2;
            float r = (r0-g0-b0)*3/2;

            r = (r>255 ? 255 : (r<0? -r : r));
            g = (g>255 ? 255 : (g<0? -g : g));
            b = (b>255 ? 255 : (b<0? -b : b));
            dstP[3*x] = (uchar)b;
            dstP[3*x+1] = (uchar)g;
            dstP[3*x+2] = (uchar)r;
        }
    }
    showImage(dst, true, QImage::Format_RGB32);
}
/*
 * 毛玻璃
 */
void CommandManager::woolGlass() {
    if (undoStack->size() == 0 ||  Image.empty())
        return ;
    Mat imageSource = Image;
    Mat imageResult = imageSource.clone();
    RNG rng;
    int randomNum;
    int Number = max(imageSource.rows, imageSource.cols)/100*2;
    cout<<imageSource.rows<<' '<<imageSource.cols<<' '<<Number<<endl;
    for (int i = 0; i < imageSource.rows-5; i++)
        for (int j = 0; j < imageSource.cols-5; j++)
        {
            randomNum = rng.uniform(0, Number);
            imageResult.at<Vec3b>(i, j)[0] = imageSource.at<Vec3b>(i + randomNum, j + randomNum)[0];
            imageResult.at<Vec3b>(i, j)[1] = imageSource.at<Vec3b>(i + randomNum, j + randomNum)[1];
            imageResult.at<Vec3b>(i, j)[2] = imageSource.at<Vec3b>(i + randomNum, j + randomNum)[2];
        }
    showImage(imageResult, true, QImage::Format_RGB32);
}
/*
 * 模糊
 */
void CommandManager::vugue() {
    if (undoStack->size() == 0 ||  Image.empty())
        return ;
    Mat src = Image;
    Mat dst;
    GaussianBlur(src, dst, Size(45,45), 0);
    showImage(dst, true, QImage::Format_RGB32);
}
/*
 * 凸出
 */
void CommandManager::bulge() {
    if (undoStack->size() == 0 ||  Image.empty())
        return ;
    Mat Img;
    Img=Image;
    Mat Img_out(Img.size(), CV_8UC3);
    Img.copyTo(Img_out);
    int width=Img.cols;
    int height=Img.rows;
    float e;
    float a,b, a0, b0, a1,b1;
    float alpha=1.0;
    float K=pi/2;

    a=width/2; b=height/2;
    e=(float)width/(float)height;

    Point2i Center(width/2, height/2);

    float new_x, new_y;
    float p,q,x1,y1,x0,y0;
    float theta;

    for (int y=0; y<height; y++)
    {
        for (int x=0; x<width; x++)
        {
            y0=Center.y-y;
            x0=x-Center.x;


            theta=atan(y0*e/(x0+0.0001));
            if(x0<0)   theta=theta+pi;

            a0=x0/cos(theta);
            b0=y0/sin(theta+0.0001);

            if(a0/a>1 || b0/b>1)  continue;

            a1=asin(a0/a)*a/K;
            b1=asin(b0/b)*b/K;

            a1=(a0-a1)*(1-alpha)+a1;
            b1=(b0-b1)*(1-alpha)+b1;

            new_x=a1*cos(theta);
            new_y=b1*sin(theta);

            new_x=Center.x+new_x;
            new_y=Center.y-new_y;

            if(new_x<0)         new_x=0;
            if(new_x>=width-1)  new_x=width-2;
            if(new_y<0)         new_y=0;
            if(new_y>=height-1) new_y=height-2;

            x1=(int)new_x;
            y1=(int)new_y;

            p=new_x-x1;
            q=new_y-y1;


            for (int k=0; k<3; k++)
            {
                Img_out.at<Vec3b>(y, x)[k]=(1-p)*(1-q)*Img.at<Vec3b>(y1, x1)[k]+
                                            (p)*(1-q)*Img.at<Vec3b>(y1,x1+1)[k]+
                                            (1-p)*(q)*Img.at<Vec3b>(y1+1,x1)[k]+
                                            (p)*(q)*Img.at<Vec3b>(y1+1,x1+1)[k];

            }
        }
    }
    showImage(Img_out, true, QImage::Format_RGB32);
}
/*
 * 凹陷
 */
void CommandManager::sunken() {
    if (undoStack->size() == 0 ||  Image.empty())
        return ;
    Mat Img;
    Img=Image;

    Mat Img_out(Img.size(), CV_8UC3);
    Img.copyTo(Img_out);

    int width=Img.cols;
    int height=Img.rows;

    float e;
    float a,b, a0, b0, a1,b1;
    float alpha=1.0;
    float K=pi/2;

    a=width/2; b=height/2;
    e=(float)width/(float)height;

    Point2i Center(width/2, height/2);

    float new_x, new_y;
    float p,q,x1,y1,x0,y0;
    float theta;

    for (int y=0; y<height; y++)
    {
        for (int x=0; x<width; x++)
        {
            y0=Center.y-y;
            x0=x-Center.x;

            theta=atan(y0*e/(x0+0.0001));
            if(x0<0)   theta=theta+pi;

            a0=x0/cos(theta);
            b0=y0/sin(theta+0.0001);

            if(a0>a || b0>b)  continue;

            a1=a*sin(a0/a*K);
            b1=b*sin(b0/b*K);

            a1=(a1-a0)*(alpha)+a0;
            b1=(b1-b0)*(alpha)+b0;

            new_x=a1*cos(theta);
            new_y=b1*sin(theta);

            new_x=Center.x+new_x;
            new_y=Center.y-new_y;

            if(new_x<0)         new_x=0;
            if(new_x>=width-1)  new_x=width-2;
            if(new_y<0)         new_y=0;
            if(new_y>=height-1) new_y=height-2;

            x1=(int)new_x;
            y1=(int)new_y;

            p=new_x-x1;
            q=new_y-y1;

            for (int k=0; k<3; k++)
            {
                Img_out.at<Vec3b>(y, x)[k]=(1-p)*(1-q)*Img.at<Vec3b>(y1, x1)[k]+
                                            (p)*(1-q)*Img.at<Vec3b>(y1,x1+1)[k]+
                                            (1-p)*(q)*Img.at<Vec3b>(y1+1,x1)[k]+
                                            (p)*(q)*Img.at<Vec3b>(y1+1,x1+1)[k];

            }
        }
    }
    showImage(Img_out, true, QImage::Format_RGB32);
}
/*
 * 马赛克
 */
void CommandManager::mosaic() {
    if (undoStack->size() == 0 ||  Image.empty())
        return ;
    Mat mat_image_src=Image;

    //第二步：确定宽高
    int width = mat_image_src.cols;
    int height = mat_image_src.rows;
    cout<<width<<' '<<height<<endl;
    //图片类型->进行转换
    //在OpenCV里面只支持RGB处理将ARGB图片->RGB
    Mat mat_image_dst;
    cvtColor(mat_image_src, mat_image_dst, CV_RGBA2RGB, 3);

    //研究OpenCV时候，如何发现巨坑？
    //观察规律
    //看到了OpenCV官方网站->每次进行图像处理时候，规律->每一次都会调用cvtColor保持一致(RGB)
    //所以：每一次你在进行转换的时候，一定要记得转换类型

    //为了不影响原始图片
    Mat mat_image_clone = mat_image_dst.clone();

    //第三步：马赛克处理
    //分析马赛克算法原理
    //level = 3-> 3 * 3矩形
    //动态的处理
    int level = max(height, width)/100*2;
    int x = width-level;
    int y = height-level;
    cout<<width<<' '<<height<<endl;

    for (int i = 0; i < y; i += level) {
        for (int j = 0; j < x; j += level) {
            //创建一个矩形区域
            Rect2i mosaicRect = Rect2i(j, i, level, level);

            //给填Rect2i区域->填充数据->原始数据
            Mat roi = mat_image_dst(mosaicRect);
            Scalar scalar = Scalar(
                   mat_image_clone.at<Vec3b>(i, j)[0],
                   mat_image_clone.at<Vec3b>(i, j)[1],
                   mat_image_clone.at<Vec3b>(i, j)[2]);

            //将处理好矩形区域->数据->拷贝到图片上面去->修改后的数据
            //CV_8UC3解释一下->后面也会讲到
            //CV_:表示框架命名空间
            //8表示：32位色->ARGB->8位 = 1字节 -> 4个字节
            //U分析
            //两种类型：有符号类型(Sign->有正负->简写"S")、无符号类型(Unsign->正数->"U")
            //无符号类型：0-255(通常情况)
            //有符号类型：-128-127
            //C分析：char类型
            //3表示：3个通道->RGB
            Mat roiCopy = Mat(mosaicRect.size(), CV_8UC3, scalar);
            roiCopy.copyTo(roi);
        }
    }
    showImage(mat_image_dst, true, QImage::Format_RGB32);
}
/*
 * 强光
 */
void CommandManager::light() {
    if (undoStack->size() == 0 ||  Image.empty())
        return ;
    Mat img;
    Image.copyTo(img);
    int width=img.cols;
    int heigh=img.rows;
    Mat dst(img.size(),CV_8UC3);
    float tmp,r;
    for (int y=0;y<heigh;y++)
    {
        uchar* imgP=img.ptr<uchar>(y);
        uchar* dstP=dst.ptr<uchar>(y);
        for (int x=0;x<width;x++)
        {
            r = (float)imgP[3*x];
            if(r>127.5)
                tmp = r+(255-r)*(r-127.5)/127.5;
            else
                tmp = r*r/127.5;
            tmp=tmp>255?255:tmp;
            tmp=tmp<0?0:tmp;
            dstP[3*x]=(uchar)(tmp);

            r = (float)imgP[3*x+1];
            if(r>127.5)
                tmp = r+(255-r)*(r-127.5)/127.5;
            else
                tmp = r*r/127.5;
            tmp=tmp>255?255:tmp;
            tmp=tmp<0?0:tmp;
            dstP[3*x+1]=(uchar)(tmp);

            r = (float)imgP[3*x+2];
            if(r>127.5)
                tmp = r+(255-r)*(r-127.5)/127.5;
            else
                tmp = r*r/127.5;
            tmp=tmp>255?255:tmp;
            tmp=tmp<0?0:tmp;
            dstP[3*x+2]=(uchar)(tmp);
        }
    }
    showImage(dst, true, QImage::Format_RGB32);
}
/*
 * 去雾
 */
void CommandManager::fog() {
    if (undoStack->size() == 0 ||  Image.empty())
        return ;
    Mat src, m_tImage, m_dstImage;
    Image.copyTo(src);
    Mat tempImage=minRGB(src);
    int ksize=std::max(3,std::max((int)(src.cols*kernRatio),
                                (int)(src.rows*kernRatio))); //求取自适应核大小
    tempImage=minFilter(tempImage,ksize);
    //[3] --dark channel image
    m_tImage=Mat::zeros(src.rows,src.cols,CV_64FC1);
    for(int i=0;i<src.rows;i++)
      for(int j=0;j<src.cols;j++)
          m_tImage.at<double>(i,j)=((255.0-
                                     (double)tempImage.at<uchar>(i,j)*wFactor)/255)-0.005;

    double A[3];
    Point maxLoc;
    minMaxLoc(tempImage,0,0,0,&maxLoc);
    for(int c=0;c<src.channels();c++)
        A[c]=src.at<Vec3b>(maxLoc.y,maxLoc.x)[c];

    m_dstImage=Mat::zeros(src.rows,src.cols,CV_64FC3);
    for(int i=0;i<src.rows;i++)
        for(int j=0;j<src.cols;j++)
            for(int c=0;c<src.channels();c++)
                m_dstImage.at<Vec3d>(i,j)[c]=(src.at<Vec3b>(i,j)[c]-
                                              (1-m_tImage.at<double>(i,j))*A[c])/
                        std::max(m_tImage.at<double>(i,j),min_t);
    m_dstImage.convertTo(m_dstImage,CV_8UC3);

    Mat temp = Mat::zeros(m_tImage.rows,m_tImage.cols,CV_8UC1);
    for(int i=0;i<m_tImage.rows;i++)
        for( int j=0;j<m_tImage.cols;j++)
        {
            temp.at<uchar>(i,j) = (int)(m_tImage.at<double>(i,j)*255);
        }
    m_tImage.convertTo(m_tImage,CV_8UC1);
    m_tImage = temp;

    Mat dst;
    //[6] --自动色阶（rgb三通道灰度拉伸）
    Mat channels[3];
    split(src,channels);//不知道什么原因vector无法使用 只能用数组来表示
    for(int c=0;c<3;c++)
        channels[c]= grayStretch(channels[c],0.001,1); //根据实验 暗色像素的比例应该设置的较小效果会比较好
    merge(channels,3,dst);

    showImage(dst, true, QImage::Format_RGB32);
}

//图像灰度拉伸
//src 灰度图图
//lowcut、highcut为百分比的值 如lowcut=3表示3%
//lowcut表示暗色像素的最小比例，小于该比例均为黑色
//highcut为高亮像素的最小比例，大于该比例的均为白色
Mat CommandManager::grayStretch(const Mat src, double lowcut, double highcut)
{
    //[1]--统计各通道的直方图
    //参数
    const int bins = 256;
    int hist_size=bins;
    float range[]={0,255};
    const float* ranges[]={range};
    MatND desHist;
    int channels=0;
    //计算直方图
    calcHist(&src,1,&channels,Mat(),desHist,1,&hist_size,ranges,true,false);
    //[1]

    //[2] --计算上下阈值
    int pixelAmount=src.rows*src.cols; //像素总数
    float Sum=0;
    int minValue=0, maxValue=0;
    //求最小值
    for(int i=0;i<bins;i++)
    {
        Sum=Sum+desHist.at<float>(i);
        if(Sum>=pixelAmount*lowcut*0.01)
        {
            minValue=i;
            break;
        }
    }

    //求最大值
    Sum=0;
    for(int i=bins-1; i>=0; i--)
    {
        Sum=Sum+desHist.at<float>(i);
        if(Sum>=pixelAmount*highcut*0.01)
        {
            maxValue=i;
            break;
        }
    }
    //[2]

    //[3] --对各个通道进行线性拉伸
    Mat dst=src;
    //判定是否需要拉伸
    if(minValue>maxValue)
        return src;

    for(int i=0;i<src.rows;i++)
        for(int j=0;j<src.cols;j++)
        {
            if(src.at<uchar>(i,j)<minValue)
                dst.at<uchar>(i,j)=0;
            if(src.at<uchar>(i,j)>maxValue)
                dst.at<uchar>(i,j)=255;
            else
            {
                //注意这里做除法要使用double类型
                double pixelValue=((src.at<uchar>(i,j)-minValue)/
                                   (double)(maxValue-minValue))*255;
                dst.at<uchar>(i,j)=(int)pixelValue;
            }
        }
    //[3]
    return dst;
}

//最小值滤波
Mat CommandManager::minFilter(cv::Mat src, int ksize)
{
    Mat dst;
    //[1] --检测原始图像
    if(src.channels()!=1)
        return dst  ;  //返回空矩阵
    if(src.depth()>8)
        return dst;
    //[1]

    int r=(ksize-1)/2; //核半径

    //初始化目标图像
    dst=Mat::zeros(src.rows,src.cols,CV_8UC1);

    //[3] --最小值滤波
    for(int i=0;i<src.rows;i++)
        for(int j=0;j<src.cols;j++)
        {

            //[1] --初始化滤波核的上下左右边界
            int top=i-r;
            int bottom=i+r;
            int left=j-r;
            int right=j+r;
            //[1]

            //[2] --检查滤波核是否超出边界
            if(i-r<0)
                top=0;
            if(i+r>src.rows)
                bottom=src.rows;
            if(j-r<0)
                left=0;
            if(j+r>src.cols)
                right=src.cols;
            //[2]

            //[3] --求取模板下的最小值
            Mat ImROI=src(Range(top,bottom),Range(left,right));
            double min,max;
            minMaxLoc(ImROI,&min,&max,0,0);
            dst.at<uchar>(i,j)=min;
            //[3]
        }
    //[3]
    return dst;
}

Mat CommandManager::minRGB(Mat src)
{
    Mat minRgb;
    if(src.empty())
        return minRgb;

    minRgb= Mat::zeros(src.rows,src.cols,CV_8UC1);
    for(int i=0;i<src.rows;i++)
        for(int j=0;j<src.cols;j++)
        {
            uchar g_minvalue =255;
            for(int c=0;c<3;c++)
            {
                if(g_minvalue>src.at<Vec3b>(i,j)[c])
                    g_minvalue=src.at<Vec3b>(i,j)[c];
            }
            minRgb.at<uchar>(i,j)=g_minvalue;
        }
    return minRgb;
}
/*
 * 灰度
 */
void CommandManager::gray() {
    if (undoStack->size() == 0 ||  Image.empty())
        return ;
    Mat srcImage, srcGray;
    Image.copyTo(srcImage);
    cvtColor(srcImage, srcGray,CV_RGB2GRAY);
    showImage(srcGray, false, QImage::Format_Indexed8);
}
/*
 * 铅笔画
 */
void CommandManager::pencil() {
    if (undoStack->size() == 0 ||  Image.empty())
        return ;
    Mat srcImage;
    Image.copyTo(srcImage);
    Mat dst(Image.rows, Image.cols, CV_8UC1);
    Mat src;
    cvtColor(srcImage,src,CV_RGB2GRAY);
    for (int i=1; i<src.rows-1; i++)
    {
        uchar *current = src.ptr<uchar>(i);
        uchar *currentBefore = src.ptr<uchar>(i-1);
        uchar *currentNext = src.ptr<uchar>(i+1);
        //   uchar *currentNext = srcImage.ptr<uchar>(i+1);
        uchar *dstLine = dst.ptr<uchar>(i);
        for (int j=1; j<src.cols-1; j++)
        {
            int a,b,c,d,e,f,g,h;
            a=abs(current[j]-currentBefore[(j-1)]);
            b=abs(current[j]-currentBefore[j]);
            c=abs(current[j]-currentBefore[(j+1)]);
            d=abs(current[j]-currentNext[(j-1)]);
            e=abs(current[j]-currentNext[(j)]);
            f=abs(current[j]-currentNext[(j+1)]);
            g=abs(current[j]-current[(j-1)]);
            h=abs(current[j]-current[(j+1)]);

            if(a>30||b>30||c>30||d>30||e>30||f>30||g>30||h>30)
                dstLine[j]=0;
            else
                dstLine[j]=255;
        }
    }
    showImage(dst, false, QImage::Format_Indexed8);
}
/*
 * 反光
 */
void CommandManager::negative() {
    if (undoStack->size() == 0 ||  Image.empty())
        return ;
    Mat srcImage;
    Image.copyTo(srcImage);
    int rowNum = srcImage.rows;//要处理的行数
    int colNum = srcImage.cols * srcImage.channels();//要处理的列数

    for(int j = 0;j<rowNum;j++){
        uchar * row = srcImage.ptr<uchar>(j);
        for(int i = 0;i<colNum ;i++){
            row[i] = 255 - row[i];
        }
    }
    showImage(srcImage, true, QImage::Format_RGB32);
}
/*
 * 黑白
 */
void CommandManager::BW() {
    if (undoStack->size() == 0 ||  Image.empty())
        return ;
    Mat srcImage, srcGray;
    Image.copyTo(srcImage);
    cvtColor(srcImage, srcGray,CV_RGB2GRAY);
    showImage(srcGray, false, QImage::Format_Indexed8);
}
/*
 * 木雕
 */
void CommandManager::wood() {
    if (undoStack->size() == 0 ||  Image.empty())
        return ;
    Mat srcImage;
    Image.copyTo(srcImage);
    Mat dst(srcImage.rows,srcImage.cols,CV_8UC1);
    Mat src;
    cvtColor(srcImage,src,CV_RGB2GRAY);
    for (int i=1; i<src.rows-1; i++)
    {

        uchar *current = src.ptr<uchar>(i);
        uchar *currentBefore = src.ptr<uchar>(i-1);
        uchar *currentNext = src.ptr<uchar>(i+1);
        //   uchar *currentNext = src.ptr<uchar>(i+1);
        uchar *dstLine = dst.ptr<uchar>(i);
        for (int j=1; j<src.cols-1; j++)
        {
            int a,b,c,d,e,f,g,h;
            a=abs(current[j]-currentBefore[(j-1)]);
            b=abs(current[j]-currentBefore[j]);
            c=abs(current[j]-currentBefore[(j+1)]);
            d=abs(current[j]-currentNext[(j-1)]);
            e=abs(current[j]-currentNext[(j)]);
            f=abs(current[j]-currentNext[(j+1)]);
            g=abs(current[j]-current[(j-1)]);
            h=abs(current[j]-current[(j+1)]);
            if(a>30||b>30||c>30||d>30||e>30||f>30||g>30||h>30)
                dstLine[j]=255;
            else
                dstLine[j]=0;
        }
    }
    showImage(dst, false, QImage::Format_Indexed8);
}

void CommandManager::showImage(Mat image, bool styleColor, QImage::Format formatType) {
    if (styleColor)
        cvtColor(image, image, CV_BGR2BGRA);
    dealImg = image;
    QImage img = QImage((const unsigned char*)(dealImg.data),dealImg.cols,dealImg.rows,dealImg.cols*dealImg.channels(), formatType);
    ShowWidget::showImage(img);
    if (!isInitImg) {
        ShowWidget::showSrcImage();
        isInitImg = true;
    }
}
/*
 * 颜色转变
 */
void CommandManager::colorTrans(int c) {
    if (undoStack->size() == 0 ||  Image.empty())
        return ;
    Mat src;
    Image.copyTo(src);
    Mat gray, dst;
    cvtColor(src, gray, CV_BGR2GRAY);
    applyColorMap(gray, dst, c);
    showImage(dst, true, QImage::Format_RGB32);
}
/*
 * 通道
 */
void CommandManager::selectChannel(QString channel) {
    if (undoStack->size() == 0 ||  Image.empty())
        return ;
    Mat src;
    Image.copyTo(src);
    Mat dst[3];
    split(src, dst);
    Mat b = dst[0];
    Mat g = dst[1];
    Mat r = dst[2];
    if (channel == "R")
        showImage(r, false, QImage::Format_Indexed8);
    else if (channel == "G")
        showImage(g, false, QImage::Format_Indexed8);
    else
        showImage(b, false, QImage::Format_Indexed8);
}

void CommandManager::saveImage(QString filename) {
    string fileAsSave = filename.toStdString();
    imwrite(fileAsSave, dealImg);
}
