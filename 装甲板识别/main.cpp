#include <opencv2/opencv.hpp>
#include "Armor.h"

using namespace cv;
using namespace std;

condition_variable cond;
queue<Mat> fpslist; // 线程安全的队列，存储待处理的帧
atomic<bool> finished = false;//显示任务是否完成

void frameReader(VideoCapture &cap);//帧提取函数的声明
void frameProcessor();//帧处理函数的声明

int main()
{


    // 视频测试

    VideoCapture cap("test.mp4");

    // 检查视频是否被正确加载
    if (!cap.isOpened())
    {
        std::cout << "读取视频失败" << std::endl;
        return -1;
    }
    thread readerThread(frameReader, ref(cap));

    // 创建处理帧的线程
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


    cap.release();//释放所有空间

    destroyAllWindows();
    return 0;
}



void frameReader(VideoCapture &cap)
{
    Mat frame;
    while (!finished)
    {
        
        cap >> frame;
        if (frame.empty())
        {
            finished = true;
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
    
    while (!finished || !fpslist.empty())
    {
        
        unique_lock<mutex> lock(mtx);
        cond.wait(lock, []
                  { return !fpslist.empty() || finished; });

        if (!fpslist.empty())
        {
            

            // unique_lock<mutex> lock(mtx);

            frame = fpslist.front();
            fpslist.pop();

            recognition(frame);//识别灯条
            
            matchArmors();//匹配装甲板
            
            drawArmor(frame);//画出装甲板
            
            // this_thread::sleep_for(std::chrono::milliseconds(1)); // 等待1毫秒，以便显示帧
            waitKey(20);
            reset();
        }
        else
        {
            cout<<"视频已结束"<<endl;
        }
    }
}