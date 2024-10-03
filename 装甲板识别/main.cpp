#include <opencv2/opencv.hpp>
#include "Armor.h"

using namespace cv;
using namespace std;

condition_variable cond;
queue<Mat> fpslist; // 线程安全的队列，存储待处理的帧
atomic<bool> finished = false;

void frameReader(VideoCapture &cap);
void frameProcessor();
// void readVideo(VideoCapture &cap);
// void dueVideo();
int main()
{
    // // 图片测试
    //  cv::Mat img =cv::imread("test.jpg");
    //  cv::imshow("img",img);
    // recognition(img);
    //  cv::waitKey(0);
    //  return 0;

    // 视频测试
    VideoCapture cap("test.mp4");

    // 检查视频是否被正确加载
    if (!cap.isOpened())
    {
        std::cout << "读取视频失败" << std::endl;
        return -1;
    }
    cout << "视频打开成功" << endl;
    thread readerThread(frameReader, ref(cap));
    // thread dueThread(dueVideo);

    //创建处理帧的线程
    vector<thread> processorThreads;
    for (int i = 0; i < thread::hardware_concurrency(); ++i)
    {
        processorThreads.emplace_back(frameProcessor);
    }

    // 等待读取线程完成
    readerThread.join();
    // 等待所有处理线程完成

    // 设置finished标志，通知处理线程停止
    finished = true;
    cond.notify_all();
    for (auto &th : processorThreads)
    {
        th.join();
    }

    

    // readerThread.join();
    // dueThread.join();
    // readVideo(cap);
    // dueVideo();
    cap.release();
    
    destroyAllWindows();
    return 0;

}

// void readVideo(VideoCapture &cap)
// {
//     int i=1;
//     Mat fps;

//     if (!cap.isOpened())
//     {
//         cout << "打开视频失败" << endl;
//         return;
//     }
//     while (!finished)
//     {
//         cout << "视频提取运行成功" <<i<< endl;
//         cap >> fps;
//         if (fps.empty())
//         {

//             break;
//         }
//         mtx.lock();
//         fpslist.push(fps.clone());
//         mtx.unlock();
//         i++;
//     }
// }
// void dueVideo()
// {
//     mtx.lock();

//     Mat fps=fpslist.front();
//     mtx.unlock();

//     cout<<"开始处理"<<endl;
//     while (!finished||!fps.empty())
//     {

//         if (!fps.empty())
//         {
//             cout << "视频处理运行成功" << endl;
//             mtx.lock();
//             fpslist.pop();
//             fps = fpslist.front();
//             mtx.unlock();
//             recognition(fps);
//             waitKey(30);
//             reset();
//         }
//     }
// }

// while (true)
// {
//     Mat img;
//     cap >> img;
//     if (img.empty())
//     {
//         cout << "视频已结束" << endl;
//         break;
//     }
//     recognition(img);
//     reset();
//     if (cv::waitKey(30) >= 0)
//     {
//         break;
//     }

void frameReader(VideoCapture &cap)
{
    Mat frame;
    while (!finished)
    {
        cout<<"视频提取中"<<endl;
        cap >> frame;
        if (frame.empty())
        {
            // finished = true;
            break;
        }
        unique_lock<mutex> lock(mtx);
        fpslist.push(frame.clone());
        cond.notify_one();
    }
}

// 帧处理线程
void frameProcessor()
{
    Mat frame;
    cout<<"视频开始处理"<<endl;
    while (!finished || !fpslist.empty())
    {
        cout<<"视频处理中"<<endl;
        unique_lock<mutex> lock(mtx);
        cond.wait(lock, []
                  { return !fpslist.empty() || finished; });

        if (true)
        {
            cout<<"处理视频"<<endl; 
           
            // unique_lock<mutex> lock(mtx);
            
            frame = fpslist.front();
            fpslist.pop();
            
            recognition(frame);
            cout<<"帧提取成功"<<endl;
            waitKey(20); // 等待1毫秒，以便显示帧
            reset();

        }
    }
}