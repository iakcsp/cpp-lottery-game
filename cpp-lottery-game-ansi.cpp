#include<iostream>
#include<windows.h>
#include<fstream>
#include<string>
#include<ctime>
using namespace std;

// 颜色定义
enum Color {
    BLACK = 0,
    BLUE = 1,
    GREEN = 2,
    CYAN = 3,
    RED = 4,
    MAGENTA = 5,
    BROWN = 6,
    LIGHTGRAY = 7,
    DARKGRAY = 8,
    LIGHTBLUE = 9,
    LIGHTGREEN = 10,
    LIGHTCYAN = 11,
    LIGHTRED = 12,
    LIGHTMAGENTA = 13,
    YELLOW = 14,
    WHITE = 15
};

// 设置控制台文本颜色
void SetColor(int textColor, int bgColor) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (bgColor << 4) | textColor);
}

// 光标定位
void GotoXY(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

// 绘制分隔线
void DrawLine(int length) {
    SetColor(CYAN, BLACK);
    for (int i = 0; i < length; i++) {
        cout << "=";
    }
    cout << endl;
    SetColor(WHITE, BLACK);
}

// 清屏并保持光标在顶部
void ClearScreen() {
    system("cls");
    GotoXY(0, 0);
}

enum LotteryType {
    GGL,//刮刮乐
    DDL,//洞洞乐
    MQL //摸球乐
};

int money = 1000; //余额

//获取随机数
int GetRandom(int min, int max) {
    if (min > max) swap(min, max); // 确保范围正确
    return rand() % (max - min + 1) + min;
}

//获取随机概率
bool GetRandomProbability(int totalProbability) {
    int a = GetRandom(1, 100);
    return a <= totalProbability;
}

void PrintMenu();

//刮刮乐
void LotteryA() {
    RESET:
    ClearScreen();
    int width = 50;
    DrawLine(width);
    SetColor(YELLOW, BLACK);
    cout << "|";
    for (int i = 0; i < (width - 6)/2; i++) cout << " ";
    cout << "刮刮乐";
    for (int i = 0; i < (width - 6 - (width - 6)/2); i++) cout << " ";
    cout << "|" << endl;
    SetColor(WHITE, BLACK);
    DrawLine(width);
    
    SetColor(LIGHTGREEN, BLACK);
    cout << "当前余额：" << money << "元" << endl << endl;
    SetColor(WHITE, BLACK);
    
    cout << "请选择刮刮乐类型：" << endl << endl;
    
    SetColor(LIGHTCYAN, BLACK);
    cout << "1. 15元刮刮乐" << endl;
    SetColor(WHITE, BLACK);
    cout << "   概率：50%谢谢惠顾 | 30%奖励10元 | 15%奖励50元 | 5%奖励100元" << endl << endl;
    
    SetColor(LIGHTCYAN, BLACK);
    cout << "2. 20元刮刮乐" << endl;
    SetColor(WHITE, BLACK);
    cout << "   概率：20%谢谢惠顾 | 50%奖励10元 | 20%奖励50元 | 10%奖励100元" << endl << endl;
    
    SetColor(LIGHTCYAN, BLACK);
    cout << "3. 50元刮刮乐" << endl;
    SetColor(WHITE, BLACK);
    cout << "   概率：10%谢谢惠顾 | 60%奖励10元 | 20%奖励50元 | 10%奖励100元" << endl << endl;
    
    DrawLine(width);
    cout << "请输入选择(1-3，输入0返回菜单)：";
    char choice;
    cin >> choice;
    
    // 处理输入缓冲区，防止错误输入导致死循环
    if (cin.fail()) {
        cin.clear();
        cin.ignore(1000, '\n');
        SetColor(RED, BLACK);
        cout << "输入格式错误，请重新输入！" << endl;
        system("pause>nul");
        goto RESET;
    }
    
    cout << endl;
    
    if (choice == '0') {
        PrintMenu();
        return;
    }
    
    int tmp = GetRandom(1, 100);
    bool valid = true;
    
    switch (choice) {
        case '1':
            if (money < 15) {
                SetColor(RED, BLACK);
                cout << "余额不足！需要15元" << endl;
                valid = false;
                break;
            }
            money -= 15;
            if (tmp <= 50) {
                SetColor(RED, BLACK);
                cout << "很遗憾，谢谢惠顾！" << endl;
            } else if (tmp <= 80) { // 50+30
                SetColor(GREEN, BLACK);
                cout << "恭喜你，获得10元奖励！" << endl;
                money += 10;
            } else if (tmp <= 95) { // 80+15
                SetColor(GREEN, BLACK);
                cout << "恭喜你，获得50元奖励！" << endl;
                money += 50;
            } else { // 95+5
                SetColor(YELLOW, BLACK);
                cout << "恭喜你，获得100元大奖！你的运气真好！" << endl;
                money += 100;
            }
            break;
            
        case '2':
            if (money < 20) {
                SetColor(RED, BLACK);
                cout << "余额不足！需要20元" << endl;
                valid = false;
                break;
            }
            money -= 20;
            if (tmp <= 20) {
                SetColor(RED, BLACK);
                cout << "很遗憾，谢谢惠顾！" << endl;
            } else if (tmp <= 70) { // 20+50
                SetColor(GREEN, BLACK);
                cout << "恭喜你，获得10元奖励！" << endl;
                money += 10;
            } else if (tmp <= 90) { // 70+20
                SetColor(GREEN, BLACK);
                cout << "恭喜你，获得50元奖励！" << endl;
                money += 50;
            } else { // 90+10
                SetColor(YELLOW, BLACK);
                cout << "恭喜你，获得100元大奖！你的运气真好！" << endl;
                money += 100;
            }
            break;
            
        case '3':
            if (money < 50) {
                SetColor(RED, BLACK);
                cout << "余额不足！需要50元" << endl;
                valid = false;
                break;
            }
            money -= 50;
            if (tmp <= 10) {
                SetColor(RED, BLACK);
                cout << "很遗憾，谢谢惠顾！" << endl;
            } else if (tmp <= 70) { // 10+60
                SetColor(GREEN, BLACK);
                cout << "恭喜你，获得10元奖励！" << endl;
                money += 10;
            } else if (tmp <= 90) { // 70+20
                SetColor(GREEN, BLACK);
                cout << "恭喜你，获得50元奖励！" << endl;
                money += 50;
            } else { // 90+10
                SetColor(YELLOW, BLACK);
                cout << "恭喜你，获得100元大奖！你的运气真好！" << endl;
                money += 100;
            }
            break;
            
        default:
            SetColor(RED, BLACK);
            cout << "输入错误，请输入1-3之间的数字！" << endl;
            valid = false;
            break;
    }
    
    SetColor(WHITE, BLACK);
    cout << endl << "当前余额：" << money << "元" << endl;
    DrawLine(width);
    cout << "按任意键" << (valid ? "继续刮奖或返回菜单..." : "重新选择...");
    system("pause>nul");
    
    // 如果操作有效，询问是否继续
    if (valid) {
        ClearScreen();
        cout << "是否继续刮奖？(y/n)：";
        char cont;
        cin >> cont;
        if (cont == 'y' || cont == 'Y') {
            LotteryA();
        } else {
            PrintMenu();
        }
    } else {
        goto RESET;
    }
}

//生成随机洞洞乐奖池
int jc[10][10] = {0};
void GenerateJiangChi() {
    // 初始化奖池为5元
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            jc[i][j] = 5;
        }
    }
    
    // 生成5个50元奖项（修复原代码逻辑错误）
    int count50 = 0;
    while (count50 < 5) {
        int tmpx = GetRandom(0, 9);
        int tmpy = GetRandom(0, 9);
        if (jc[tmpx][tmpy] == 5) {  // 确保只替换5元格子
            jc[tmpx][tmpy] = 50;
            count50++;
        }
    }
    
    // 生成10个20元奖项（修复原代码数量错误）
    int count20 = 0;
    while (count20 < 10) {
        int tmpx = GetRandom(0, 9);
        int tmpy = GetRandom(0, 9);
        if (jc[tmpx][tmpy] == 5) {  // 确保只替换5元格子
            jc[tmpx][tmpy] = 20;
            count20++;
        }
    }
}

//洞洞乐
void LotteryB() {
    GenerateJiangChi();
    ClearScreen();
    int width = 60;
    DrawLine(width);
    SetColor(YELLOW, BLACK);
    cout << "|";
    for (int i = 0; i < (width - 6)/2; i++) cout << " ";
    cout << "洞洞乐";
    for (int i = 0; i < (width - 6 - (width - 6)/2); i++) cout << " ";
    cout << "|" << endl;
    SetColor(WHITE, BLACK);
    DrawLine(width);
    
    SetColor(LIGHTGREEN, BLACK);
    cout << "当前余额：" << money << "元" << endl << endl;
    SetColor(WHITE, BLACK);
    
    cout << "游戏说明：选择1-10行和1-10列的格子，每次10元" << endl;
    cout << "奖项设置：大部分为5元，10个20元，5个50元大奖" << endl << endl;
    
    // 显示格子布局
    SetColor(CYAN, BLACK);
    cout << "   ";
    for (int i = 1; i <= 10; i++) {
        printf("%2d ", i);  // 格式化输出，确保对齐
    }
    cout << endl;
    
    for (int i = 0; i < 10; i++) {
        printf("%2d ", i + 1);  // 格式化输出，确保对齐
        for (int j = 0; j < 10; j++) {
            cout << "■ ";
        }
        cout << endl;
    }
    SetColor(WHITE, BLACK);
    cout << endl;
    DrawLine(width);
    
    cout << "请输入行号(1-10)和列号(1-10)，用空格隔开（输入0 0返回菜单）：";
    int a, b;
    cin >> a >> b;
    
    // 处理输入错误
    if (cin.fail()) {
        cin.clear();
        cin.ignore(1000, '\n');
        SetColor(RED, BLACK);
        cout << "输入格式错误，请输入两个数字！" << endl;
        system("pause>nul");
        LotteryB();
        return;
    }
    
    // 返回菜单
    if (a == 0 && b == 0) {
        PrintMenu();
        return;
    }
    
    if (a < 1 || a > 10 || b < 1 || b > 10) {
        SetColor(RED, BLACK);
        cout << "输入错误，行列号必须在1-10之间！" << endl;
        cout << "按任意键重新选择...";
        system("pause>nul");
        LotteryB();
        return;
    }
    
    if (money < 10) {
        SetColor(RED, BLACK);
        cout << "余额不足，无法参与！需要10元" << endl;
        cout << "按任意键返回菜单...";
        system("pause>nul");
        PrintMenu();
        return;
    }
    
    money -= 10;
    a--; b--;
    int reward = jc[a][b];
    money += reward;
    
    cout << endl;
    SetColor(GREEN, BLACK);
    cout << "你选择了" << a + 1 << "行" << b + 1 << "列" << endl;
    cout << "恭喜你获得了" << reward << "元奖励！" << endl;
    SetColor(WHITE, BLACK);
    cout << "当前余额：" << money << "元" << endl;
    DrawLine(width);
    
    cout << "是否继续游戏？(y/n)：";
    char choice;
    cin >> choice;
    if (choice == 'y' || choice == 'Y') {
        LotteryB();
    } else {
        PrintMenu();
    }
}

//摸球乐
void LotteryC() {
    ClearScreen();
    int width = 50;
    DrawLine(width);
    SetColor(YELLOW, BLACK);
    cout << "|";
    for (int i = 0; i < (width - 6)/2; i++) cout << " ";
    cout << "摸球乐";
    for (int i = 0; i < (width - 6 - (width - 6)/2); i++) cout << " ";
    cout << "|" << endl;
    SetColor(WHITE, BLACK);
    DrawLine(width);
    
    SetColor(LIGHTGREEN, BLACK);
    cout << "当前余额：" << money << "元" << endl << endl;
    SetColor(WHITE, BLACK);
    
    cout << "游戏说明：每次花费10元，随机获得1-100元奖励" << endl << endl;
    
    if (money < 10) {
        SetColor(RED, BLACK);
        cout << "余额不足，无法参与！需要10元" << endl;
        DrawLine(width);
        cout << "按任意键返回菜单...";
        system("pause>nul");
        PrintMenu();
        return;
    }
    
    cout << "是否开始抽奖？(y/n，n返回菜单)：";
    char choice;
    cin >> choice;
    
    if (choice != 'y' && choice != 'Y') {
        PrintMenu();
        return;
    }
    
    money -= 10;
    int reward = GetRandom(1, 100);
    money += reward;
    
    cout << endl << "正在摸球...";
    for (int i = 0; i < 3; i++) {
        Sleep(500);
        cout << ".";
    }
    cout << endl;
    
    cout << "恭喜你摸到了";
    if (reward > 70) {
        SetColor(YELLOW, BLACK);
    } else if (reward > 30) {
        SetColor(GREEN, BLACK);
    } else {
        SetColor(LIGHTBLUE, BLACK);
    }
    cout << reward << "元";
    SetColor(WHITE, BLACK);
    cout << "奖励！" << endl << endl;
    
    cout << "当前余额：" << money << "元" << endl;
    DrawLine(width);
    
    cout << "是否继续抽奖？(y/n)：";
    cin >> choice;
    if (choice == 'y' || choice == 'Y') {
        LotteryC();
    } else {
        PrintMenu();
    }
}

void Lottery(LotteryType type) {
    switch (type) {
        case GGL:
            LotteryA();
            break;
        case DDL:
            LotteryB();
            break;
        case MQL:
            LotteryC();
            break;
        default:
            break;
    }
}

string Author = "Lin114514";
string Version = "1.1";  // 版本更新
string GameName = "C++抽奖游戏";
string GameIntroduction = "C++纯控制台抽奖游戏，支持刮刮乐、洞洞乐、摸球乐，欢迎各位玩家来体验！";

void PrintStart() {
    ClearScreen();
    int width = 60;
    DrawLine(width);
    
    // 居中显示游戏名称
    GotoXY((width - GameName.length()) / 2, 1);
    SetColor(YELLOW, BLACK);
    cout << GameName << endl;
    
    // 居中显示游戏介绍
    GotoXY(2, 3);
    SetColor(LIGHTCYAN, BLACK);
    cout << GameIntroduction << endl;
    
    GotoXY(2, 5);
    SetColor(LIGHTGRAY, BLACK);
    cout << "作者：" << Author << endl;
    cout << "版本：" << Version << endl;
    
    DrawLine(width);
    
    GotoXY((width - 20) / 2, 8);
    SetColor(WHITE, BLACK);
    cout << "按任意键开始游戏...";
    system("pause>nul");
    ClearScreen();
}

void Save() {
    ofstream ofs("save.dat", ios::binary);
    if (ofs.is_open()) {  // 检查文件是否成功打开
        ofs.write((char*)&money, sizeof(int));
        ofs.close();
    } else {
        // 保存失败时的提示（不影响游戏运行）
        SetColor(RED, BLACK);
        cout << "警告：保存数据失败！" << endl;
        SetColor(WHITE, BLACK);
    }
}

void Load() {
    ifstream ifs("save.dat", ios::binary);
    if (ifs.is_open()) {  // 检查文件是否存在且可打开
        ifs.read((char*)&money, sizeof(int));
        // 确保加载的余额为正数
        if (money < 0) money = 1000;
        ifs.close();
    } else {
        // 首次运行或文件不存在时使用初始余额
        money = 1000;
    }
}

void PrintMenu() {
    Save();
    ClearScreen();
    int width = 50;
    DrawLine(width);
    
    SetColor(YELLOW, BLACK);
    cout << "|";
    for (int i = 0; i < (width - 6)/2; i++) cout << " ";
    cout << "主菜单";
    for (int i = 0; i < (width - 6 - (width - 6)/2); i++) cout << " ";
    cout << "|" << endl;
    SetColor(WHITE, BLACK);
    
    DrawLine(width);
    SetColor(LIGHTGREEN, BLACK);
    cout << "当前余额：" << money << "元" << endl << endl;
    SetColor(WHITE, BLACK);
    
    SetColor(LIGHTCYAN, BLACK);
    cout << "1. 刮刮乐" << endl;
    SetColor(WHITE, BLACK);
    cout << "   多种价位选择，不同中奖概率" << endl << endl;
    
    SetColor(LIGHTCYAN, BLACK);
    cout << "2. 洞洞乐" << endl;
    SetColor(WHITE, BLACK);
    cout << "   10x10格子矩阵，惊喜等你来" << endl << endl;
    
    SetColor(LIGHTCYAN, BLACK);
    cout << "3. 摸球乐" << endl;
    SetColor(WHITE, BLACK);
    cout << "   简单刺激，随机获得1-100元" << endl << endl;
    
    SetColor(RED, BLACK);
    cout << "4. 退出游戏" << endl << endl;
    SetColor(WHITE, BLACK);
    
    DrawLine(width);
    cout << "请输入选择(1-4)：";
    char choice;
    cin >> choice;
    
    // 处理输入错误
    if (cin.fail()) {
        cin.clear();
        cin.ignore(1000, '\n');
        SetColor(RED, BLACK);
        cout << "输入格式错误，请重新输入！" << endl;
        system("pause>nul");
        PrintMenu();
        return;
    }
    
    switch (choice) {
        case '1':
            Lottery(GGL);
            break;
        case '2':
            Lottery(DDL);
            break;
        case '3':
            Lottery(MQL);
            break;
        case '4':
            SetColor(YELLOW, BLACK);
            cout << endl << "感谢游玩，再见！" << endl;
            SetColor(WHITE, BLACK);
            exit(0);
        default:
            SetColor(RED, BLACK);
            cout << "输入错误，请输入1-4之间的数字！" << endl;
            SetColor(WHITE, BLACK);
            system("pause>nul");
            PrintMenu();
            break;
    }
}

int main() {
//    SetConsoleOutputCP(65001);
    SetConsoleTitle(GameName.c_str());
    Load();
    srand((unsigned int)time(0));  // 确保随机数种子正确
    PrintStart();
    PrintMenu();
    return 0;
}
