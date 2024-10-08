#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>
#include <cstdlib>

struct Tire {
    std::string model; // 轮胎型号
    int size;          // 轮胎尺寸
};

struct Chassis {
    std::string id;                    // 底盘编号
    std::string model;                 // 底盘型号
    int wheelbase;                     // 轴距
    int trackWidth;                    // 轮距
    int minGroundClearance;            // 最小离地间隙
    int minTurningRadius;              // 最小转弯半径
    std::string driveType;             // 驱动形式
    int maxRange;                      // 最大行程
    std::vector<Tire> tires;           // 轮胎信息
};

struct AGXModule {
    std::string model;    // AGX模块型号
    int aiPerformance;     // AI性能
    int cudaCores;        // CUDA核心数
    int tensorCores;      // Tensor CORE数
    int memory;           // 显存
    int storage;          // 存储
};

struct Camera {
    std::string model;      // 摄像头型号
    std::string cameraId;   // 摄像头ID
    std::string rgbResolution; // RGB分辨率
    int rgbFrameRate;       // RGB帧率
    std::string fov;        // 视场角
    int depthFrameRate;     // 深度帧率
};

struct Lidar {
    std::string model;       // 激光雷达型号
    int channels;            // 通道数
    int range;               // 测试范围
    int powerConsumption;    // 功耗
};

struct IMU {
    std::string model;      // 陀螺仪型号
    std::string manufacturer; // 厂家
};

struct Display {
    float size;            // 显示器尺寸
    std::string model;     // 显示器型号
};

struct Battery {
    std::string parameters; // 电池参数
    std::string externalPower; // 对外供电
    int chargeTime;        // 充电时长
};

struct SmartCar {
    std::string id;            // 编号
    Chassis chassis;          // 底盘信息
    AGXModule agxModule;      // AGX模块信息
    Camera camera;            // 摄像头信息
    Lidar lidar;              // 激光雷达信息
    IMU imu;                  // 陀螺仪信息
    Display display;          // 显示器信息
    Battery battery;          // 电池信息
};

struct Student {
    std::string studentId;  // 学号
    std::string name;        // 姓名
};

void saveCars(const std::string& filename, const std::vector<SmartCar>& cars, const std::vector<Student>& students) {
    std::ofstream outfile(filename);
    if (!outfile.is_open()) {
        std::cerr << "Error opening file for writing: " << filename << std::endl;
        return;
    }

    for (size_t i = 0; i < cars.size(); ++i) {
        const SmartCar& car = cars[i];
        const Student& student = students[i];

        outfile << car.id << "," 
                << student.studentId << "," 
                << student.name << "," 
                << car.chassis.id << "," 
                << car.chassis.model << "," 
                << car.chassis.wheelbase << "," 
                << car.chassis.trackWidth << "," 
                << car.chassis.minGroundClearance << "," 
                << car.chassis.minTurningRadius << "," 
                << car.chassis.driveType << "," 
                << car.chassis.maxRange << ",";

        for (const Tire& tire : car.chassis.tires) {
            outfile << tire.model << "," << tire.size << ";"; // 分隔轮胎信息
        }

        outfile << car.agxModule.model << "," 
                << car.agxModule.aiPerformance << "," 
                << car.agxModule.cudaCores << "," 
                << car.agxModule.tensorCores << "," 
                << car.agxModule.memory << "," 
                << car.agxModule.storage << "," 
                << car.camera.model << "," 
                << car.camera.cameraId << "," 
                << car.camera.rgbResolution << "," 
                << car.camera.rgbFrameRate << "," 
                << car.camera.fov << "," 
                << car.camera.depthFrameRate << "," 
                << car.lidar.model << "," 
                << car.lidar.channels << "," 
                << car.lidar.range << "," 
                << car.lidar.powerConsumption << "," 
                << car.imu.model << "," 
                << car.imu.manufacturer << "," 
                << car.display.size << "," 
                << car.display.model << "," 
                << car.battery.parameters << "," 
                << car.battery.externalPower << "," 
                << car.battery.chargeTime << "\n"; // 最后一行换行
    }

    outfile.close();
}

void loadCars(const std::string& filename, std::vector<SmartCar>& cars, std::vector<Student>& students) {
    std::ifstream infile(filename);
    if (!infile.is_open()) {
        std::cerr << "Error opening file for reading: " << filename << std::endl;
        return;
    }

    std::string line;
    while (std::getline(infile, line)) {
        std::istringstream iss(line);
        SmartCar car;
        Student student;

        std::string tiresInfo;
        std::getline(iss, car.id, ',');
        std::getline(iss, student.studentId, ',');
        std::getline(iss, student.name, ',');
        std::getline(iss, car.chassis.id, ',');
        std::getline(iss, car.chassis.model, ',');
        iss >> car.chassis.wheelbase; iss.ignore();
        iss >> car.chassis.trackWidth; iss.ignore();
        iss >> car.chassis.minGroundClearance; iss.ignore();
        iss >> car.chassis.minTurningRadius; iss.ignore();
        std::getline(iss, car.chassis.driveType, ',');
        iss >> car.chassis.maxRange; iss.ignore();
        
        std::getline(iss, tiresInfo, ',');
        std::istringstream tireStream(tiresInfo);
        std::string tire;
        while (std::getline(tireStream, tire, ';')) {
            Tire newTire;
            std::istringstream tireData(tire);
            std::string tireModel;
            int tireSize;
            std::getline(tireData, tireModel, ',');
            tireData >> tireSize; tireData.ignore();
            newTire.model = tireModel;
            newTire.size = tireSize;
            car.chassis.tires.push_back(newTire);
        }

        std::getline(iss, car.agxModule.model, ',');
        iss >> car.agxModule.aiPerformance; iss.ignore();
        iss >> car.agxModule.cudaCores; iss.ignore();
        iss >> car.agxModule.tensorCores; iss.ignore();
        iss >> car.agxModule.memory; iss.ignore();
        iss >> car.agxModule.storage; iss.ignore();
        std::getline(iss, car.camera.model, ',');
        std::getline(iss, car.camera.cameraId, ',');
        std::getline(iss, car.camera.rgbResolution, ',');
        iss >> car.camera.rgbFrameRate; iss.ignore();
        std::getline(iss, car.camera.fov, ',');
        iss >> car.camera.depthFrameRate; iss.ignore();
        std::getline(iss, car.lidar.model, ',');
        iss >> car.lidar.channels; iss.ignore();
        iss >> car.lidar.range; iss.ignore();
        iss >> car.lidar.powerConsumption; iss.ignore();
        std::getline(iss, car.imu.model, ',');
        std::getline(iss, car.imu.manufacturer, ',');
        iss >> car.display.size; iss.ignore();
        std::getline(iss, car.display.model, ',');
        std::getline(iss, car.battery.parameters, ',');
        std::getline(iss, car.battery.externalPower, ',');
        iss >> car.battery.chargeTime; iss.ignore();

        cars.push_back(car);
        students.push_back(student);
    }

    infile.close();
}

void displayCar(const SmartCar& car, const Student& student) {
    std::cout << "小车编号: " << car.id << "\n";
    std::cout << "分配学生: " << student.studentId << ", " << student.name << "\n";
    std::cout << "底盘编号: " << car.chassis.id << "\n";
    std::cout << "底盘型号: " << car.chassis.model << "\n";
    std::cout << "轴距: " << car.chassis.wheelbase << " mm\n";
    std::cout << "轮距: " << car.chassis.trackWidth << " mm\n";
    std::cout << "最小离地间隙: " << car.chassis.minGroundClearance << " mm\n";
    std::cout << "最小转弯半径: " << car.chassis.minTurningRadius << " m\n";
    std::cout << "驱动形式: " << car.chassis.driveType << "\n";
    std::cout << "最大行程: " << car.chassis.maxRange << " KM\n";

    std::cout << "轮胎信息:\n";
    for (const Tire& tire : car.chassis.tires) {
        std::cout << "  型号: " << tire.model << ", 尺寸: " << tire.size << " mm\n";
    }

    std::cout << "AGX模块型号: " << car.agxModule.model << "\n";
    std::cout << "AI性能: " << car.agxModule.aiPerformance << " TOPS\n";
    std::cout << "CUDA核心数: " << car.agxModule.cudaCores << "\n";
    std::cout << "Tensor核心数: " << car.agxModule.tensorCores << "\n";
    std::cout << "显存: " << car.agxModule.memory << " G\n";
    std::cout << "存储: " << car.agxModule.storage << " G\n";

    std::cout << "摄像头型号: " << car.camera.model << "\n";
    std::cout << "摄像头ID: " << car.camera.cameraId << "\n";
    std::cout << "RGB分辨率: " << car.camera.rgbResolution << "\n";
    std::cout << "RGB帧率: " << car.camera.rgbFrameRate << " FPS\n";
    std::cout << "视场角: " << car.camera.fov << "\n";
    std::cout << "深度帧率: " << car.camera.depthFrameRate << " FPS\n";

    std::cout << "激光雷达型号: " << car.lidar.model << "\n";
    std::cout << "通道数: " << car.lidar.channels << "\n";
    std::cout << "测试范围: " << car.lidar.range << " m\n";
    std::cout << "功耗: " << car.lidar.powerConsumption << " W\n";

    std::cout << "陀螺仪型号: " << car.imu.model << "\n";
    std::cout << "厂家: " << car.imu.manufacturer << "\n";

    std::cout << "显示器尺寸: " << car.display.size << " 英寸\n";
    std::cout << "显示器型号: " << car.display.model << "\n";

    std::cout << "电池参数: " << car.battery.parameters << "\n";
    std::cout << "对外供电: " << car.battery.externalPower << "\n";
    std::cout << "充电时长: " << car.battery.chargeTime << " 小时\n";
    std::cout << "------------------------------------\n";
}

int main() {
    std::vector<SmartCar> cars(10);  // 10台小车
    std::vector<Student> students(10); // 10个学生

    // 录入小车和学生信息
    for (int i = 0; i < 10; ++i) {
        cars[i].id = "cqusn" + std::to_string(100000 + i); // 生成编号
        students[i].studentId = "S" + std::to_string(1000 + i); // 学生编号
        students[i].name = "学生" + std::to_string(i + 1); // 学生姓名

        // 初始化小车的其他信息
        cars[i].chassis = {"dp" + std::to_string(100000 + i), "迷你侦察车", 450 + i * 5, 490 + i * 3, 120, 0, "四轮驱动", 12 + i, {}};
        cars[i].agxModule = {"AGX 赛维尔", 30 + i, 512 + i * 10, 64, 32, 64};
        cars[i].camera = {"超清摄像头", "D430", "1920*1080", 30 + i, "90度", 30};
        cars[i].lidar = {"激光雷达", 16 + i, 100 + i * 5, 10};
        cars[i].imu = {"IMU型号" + std::to_string(i), "制造商" + std::to_string(i)};
        cars[i].display = {11.6 + i * 0.2, "显示器" + std::to_string(i)};
        cars[i].battery = {"24V/20Ah", "24V", 1 + i};

        // 添加轮胎
        cars[i].chassis.tires.push_back({"公路轮", 175 + i});
        cars[i].chassis.tires.push_back({"麦克纳姆轮", 175 + i});
        cars[i].chassis.tires.push_back({"公路轮", 175 + i});
        cars[i].chassis.tires.push_back({"麦克纳姆轮", 175 + i});
    }

    // 保存信息到文件
    saveCars("SmartCars.txt", cars, students);

    // 读取并显示信息
    std::vector<SmartCar> loadedCars;
    std::vector<Student> loadedStudents;
    loadCars("SmartCars.txt", loadedCars, loadedStudents);

    int currentIndex = 0;
    char command;

    while (true) {
        displayCar(loadedCars[currentIndex], loadedStudents[currentIndex]);
        std::cout << "按 'n' 查看下一辆小车, 按 'p' 查看上一辆小车, 按 'q' 退出: ";
        std::cin >> command;

        if (command == 'n') {
            if (currentIndex < loadedCars.size() - 1) {
                currentIndex++;
            } else {
                std::cout << "这是最后一辆小车。\n";
            }
        } else if (command == 'p') {
            if (currentIndex > 0) {
                currentIndex--;
            } else {
                std::cout << "这是第一辆小车。\n";
            }
        } else if (command == 'q') {
            break;
        } else {
            std::cout << "无效命令，请重试。\n";
        }
    }

    return 0;
}
