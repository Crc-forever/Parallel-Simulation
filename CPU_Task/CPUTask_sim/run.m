% 1. 清理工作区和命令行（好习惯，防止旧数据干扰）
clear; 
clc;

% 2. 准备测试用例数据
% 如果你之前选了"工作区导入法"读 CSV，把读取代码写在这里：
% data = readtable('testcase.csv');
% myInputSignal = timeseries(data.Signal, data.Time);

% 3. 定义模型名称
modelName = 'CPUTask_Sim'; 

% 4. 在后台加载模型（非常重要！）
% 这样做可以把"打开模型文件"的时间剔除掉，让计时的全是"纯计算时间"
load_system(modelName); 

% 5. 开始计时与仿真
disp('模型已加载，开始仿真...');
tic;  % 🚀 按下秒表，开始计时

% 运行仿真，并把所有输出结果装进 'out' 这个变量里
out = sim(modelName); 

% 🛑 停止秒表，并把经过的真实时间（秒）存入 realTime 变量
realTime = toc; 

% 6. 打印统计结果
fprintf('\n====================================\n');
fprintf('仿真运行完毕！\n');
fprintf('电脑实际计算耗时: %.4f 秒\n', realTime);
fprintf('====================================\n');