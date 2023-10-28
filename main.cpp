#include <iostream>
#include <conio.h>
#include <Windows.h>

#pragma comment(lib,"winmm.lib")

using namespace std;

const int CHANNEL = 0;
const int VOLUME = 100;

int ins = 0;
int octave = 0;
//int channel = 0;
bool keys[1024] = { false };
HMIDIOUT hMidiOut;

enum Tone
{
    Rest = 0, 

    C8 = 108, 

    B7 = 107, 
    A7s = 106, 
    A7 = 105, 
    G7s = 104, 
    G7 = 103, 
    F7s = 102, 
    F7 = 101, 
    E7 = 100,
    D7s = 99, 
    D7 = 98, 
    C7s = 97, 
    C7 = 96, 

    B6 = 95, 
    A6s = 94, 
    A6 = 93, 
    G6s = 92, 
    G6 = 91, 
    F6s = 90, 
    F6 = 89,
    E6 = 88, 
    D6s = 87, 
    D6 = 86, 
    C6s = 85, 
    C6 = 84, 

    B5 = 83, 
    A5s = 82, 
    A5 = 81, 
    G5s = 80, 
    G5 = 79, 
    F5s = 78,
    F5 = 77, 
    E5 = 76, 
    D5s = 75, 
    D5 = 74, 
    C5s = 73, 
    C5 = 72, 

    B4 = 71, 
    A4s = 70, 
    A4 = 69, 
    G4s = 68, 
    G4 = 67,
    F4s = 66, 
    F4 = 65, 
    E4 = 64, 
    D4s = 63, 
    D4 = 62, 
    C4s = 61, 
    C4 = 60, 

    B3 = 59, 
    A3s = 58, 
    A3 = 57, 
    G3s = 56,
    G3 = 55, 
    F3s = 54, 
    F3 = 53, 
    E3 = 52, 
    D3s = 51, 
    D3 = 50, 
    C3s = 49, 
    C3 = 48, 

    B2 = 47, 
    A2s = 46, 
    A2 = 45,
    G2s = 44, 
    G2 = 43, 
    F2s = 42, 
    F2 = 41, 
    E2 = 40, 
    D2s = 39, 
    D2 = 38, 
    C2s = 37, 
    C2 = 36, 

    B1 = 35, 
    A1s = 34,
    A1 = 33, 
    G1s = 32, 
    G1 = 31, 
    F1s = 30, 
    F1 = 29, 
    E1 = 28, 
    D1s = 27, 
    D1 = 26, 
    C1s = 25, 
    C1 = 24, 

    B0 = 23,
    A0s = 22, 
    A0 = 21

};

void PianoKey(int kbKey, int tone)
{
    //钢琴键
    if (GetAsyncKeyState(kbKey))
    {
        if (keys[kbKey] == false)
        {
            midiOutShortMsg(hMidiOut, 0x90 + ((tone + octave * 12) << 8) + (VOLUME << 16) + CHANNEL);
            keys[kbKey] = true;
        }
    }
    else
    {
        keys[kbKey] = false;
    }
}
void SetInstrumentValue()
{
    //设置
    if (_kbhit())
    {
        //切换乐器
        if (GetAsyncKeyState(VK_LEFT))
        {
            Sleep(30);
            ins--;
            midiOutShortMsg(hMidiOut, (ins << 8) + 0xC0);
            system("cls");
            cout << "乐器:" << ins << endl;
            cout << "八度:" << octave << endl;
        }
        if (GetAsyncKeyState(VK_RIGHT))
        {
            Sleep(30);
            ins++;
            midiOutShortMsg(hMidiOut, (ins << 8) + 0xC0);
            system("cls");
            cout << "乐器:" << ins << endl;
            cout << "八度:" << octave << endl;
        }
        //设置八度
        if (GetAsyncKeyState(VK_UP))
        {
            while (GetAsyncKeyState(VK_UP));
            octave++;
            system("cls");
            cout << "乐器:" << ins << endl;
            cout << "八度:" << octave << endl;
        }
        if (GetAsyncKeyState(VK_DOWN))
        {
            while (GetAsyncKeyState(VK_DOWN));
            octave--;
            system("cls");
            cout << "乐器:" << ins << endl;
            cout << "八度:" << octave << endl;
        }
    }
}

int main(int argc, char* argv[])
{
    //说明
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
    cout << "按键:" << endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
    cout << " C4s  D4s    F4s G4s A4s   C5s  D5s   F5s  G5s A5s   C6s  D6s   F6s  " << endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
    cout << "C4  D4  E4 F4  G4  A4  B4 C5  D5  E5 F5  G5  A5  B5 C6  D6  E6 F6  G6" << endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
    cout << "                             2   3     5    6   7     9    0     =   " << endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
    cout << "                           Q   W   E  R   T   Y  U  I    O   P [    ]" << endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
    cout << "  S    D      G   H   J     L    ;                                   " << endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
    cout << " Z   X   C  V  B   N   M   ,   .   /                                 " << endl;
    cout << "                                                                     " << endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
    cout << "切换乐器:←，→" << endl;
    cout << "调整八度:↑，↓" << endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    system("Pause");

    //MIDI
    midiOutOpen(&hMidiOut, 0, 0, 0, CALLBACK_NULL);
    midiOutShortMsg(hMidiOut, (0 << 8) + 0xC0);
    system("cls");
    cout << "乐器:" << ins << endl;
    cout << "八度:" << octave << endl;
    while (1)
    {
        Sleep(1);
        if (GetAsyncKeyState(VK_ESCAPE))//退出
        {
            break;
        }
        SetInstrumentValue();
        PianoKey('Q', C5);
        PianoKey('2', C5s);
        PianoKey('W', D5);
        PianoKey('3', D5s);
        PianoKey('E', E5);
        PianoKey('R', F5);
        PianoKey('5', F5s);
        PianoKey('T', G5);
        PianoKey('6', G5s);
        PianoKey('Y', A5);
        PianoKey('7', A5s);
        PianoKey('U', B5);
        PianoKey('I', C6);
        PianoKey('9', C6s);
        PianoKey('O', D6);
        PianoKey('0', D6s);
        PianoKey('P', E6);
        PianoKey(219, F6);//[
        PianoKey(187, F6s);//=
        PianoKey(221, G6);//]

        PianoKey('Z', C4);
        PianoKey('S', C4s);
        PianoKey('X', D4);
        PianoKey('D', D4s);
        PianoKey('C', E4);
        PianoKey('V', F4);
        PianoKey('G', F4s);
        PianoKey('B', G4);
        PianoKey('H', G4s);
        PianoKey('N', A4);
        PianoKey('J', A4s);
        PianoKey('M', B4);
        PianoKey(188, C5);//,
        PianoKey('L', C5s);
        PianoKey(190, D5);//.
        PianoKey(186, D5s);//;
        PianoKey(191, E5);///
    }

    midiOutClose(hMidiOut);
	return 0;
}

/*
enum Instrument
{
    //midi乐器编号
    Acoustic_Grand_Piano = 0,                    //大钢琴（声学钢琴）
    Bright_Acoustic_Piano,                       //明亮的钢琴
    Electric_Grand_Piano,                        //电钢琴
    Honky__tonk_Piano,                           //酒吧钢琴
    Rhodes_Piano,                                //柔和的电钢琴
    Chorused_Piano,                              //加合唱效果的电钢琴
    Harpsichord,                                 //羽管键琴（拨弦古钢琴）
    Clavichord,                                  //科拉维科特琴（击弦古钢琴）

    //色彩打击乐器
    Celesta,                                     //钢片琴
    Glockenspiel,                                //钟琴
    Music_box,                                   //八音盒
    Vibraphone,                                  //颤音琴
    Marimba,                                     //马林巴
    Xylophone,                                   //木琴
    Tubular_Bells,                               //管钟
    Dulcimer,                                    //大扬琴

    //风琴
    Hammond_Organ,                               //击杆风琴
    Percussive_Organ,                            //打击式风琴
    Rock_Organ,                                  //摇滚风琴
    Church_Organ,                                //教堂风琴
    Reed_Organ,                                  //簧管风琴
    Accordian,                                   //手风琴
    Harmonica,                                   //口琴
    Tango_Accordian,                             //探戈手风琴

    //吉他
    Acoustic_Guitar_nylon,                       //尼龙弦吉他
    Acoustic_Guitar_steel,                       //钢弦吉他
    Electric_Guitar_jazz,                        //爵士电吉他
    Electric_Guitar_clean,                       //清音电吉他
    Electric_Guitar_muted,                       //闷音电吉他
    Overdriven_Guitar,                           //加驱动效果的电吉他
    Distortion_Guitar,                           //加失真效果的电吉他
    Guitar_Harmonics,                            //吉他和音

    //贝司
    Acoustic_Bass,                               //大贝司（声学贝司）
    Electric_Bass_finger,                        //电贝司（指弹）
    Electric_Bass_pick,                          //电贝司（拨片）
    Fretless_Bass,                               //无品贝司
    Slap_Bass_1,                                 //掌击Bass 1
    Slap_Bass_2,                                 //掌击Bass 2
    Synth_Bass_1,                                //电子合成Bass 1
    Synth_Bass_2,                                //电子合成Bass 2

    //弦乐
    Violin,                                       //小提琴
    Viola,                                        //中提琴
    Cello,                                        //大提琴
    Contrabass,                                   //低音大提琴
    Tremolo_Strings,                              //弦乐群颤音音色
    Pizzicato_Strings,                            //弦乐群拨弦音色
    Orchestral_Harp,                              //竖琴
    Timpani,                                      //定音鼓

    //合奏 / 合唱
    String_Ensemble_1,                            //弦乐合奏音色1
    String_Ensemble_2,                            //弦乐合奏音色2
    Synth_Strings_1,                              //合成弦乐合奏音色1
    Synth_Strings_2,                              //合成弦乐合奏音色2
    Choir_Aahs,                                   //人声合唱“啊”
    Voice_Oohs,                                   //人声“嘟”
    Synth_Voice,                                  //合成人声
    Orchestra_Hit,                                //管弦乐敲击齐奏

    //铜管
    Trumpet,                                      //小号
    Trombone,                                     //长号
    Tuba,                                         //大号
    Muted_Trumpet,                                //加弱音器小号
    French_Horn,                                  //法国号（圆号）
    Brass_Section,                                //铜管组（铜管乐器合奏音色）
    Synth_Brass_1,                                //合成铜管音色1
    Synth_Brass_2,                                //合成铜管音色2

    //簧管
    Soprano_Sax,                                  //高音萨克斯风
    Alto_Sax,                                     //次中音萨克斯风
    Tenor_Sax,                                    //中音萨克斯风
    Baritone_Sax,                                 //低音萨克斯风
    Oboe,                                         //双簧管
    English_Horn,                                 //英国管
    Bassoon,                                      //巴松（大管）
    Clarinet,                                     //单簧管（黑管）

    //笛
    Piccolo,                                      //短笛
    Flute,                                        //长笛
    Recorder,                                     //竖笛
    Pan_Flute,                                    //排箫
    Bottle_Blow,                                  //[中文名称暂缺]
    Shakuhachi,                                   //日本尺八
    Whistle,                                      //口哨声
    Ocarina,                                      //奥卡雷那

    //合成主音
    Lead_1,                                       //(square)合成主音1（方波）
    Lead_2,                                       //(sawtooth)合成主音2（锯齿波）
    Lead_3,                                       //(caliope lead)                 合成主音3
    Lead_4,                                       //(chiff lead)                     合成主音4
    Lead_5,                                       //(charang)合成主音5
    Lead_6,                                       //(voice)合成主音6（人声）
    Lead_7,                                       //(fifths)合成主音7（平行五度）
    Lead_8,                                       //(bass + lead)合成主音8（贝司加主音）

    //合成音色
    Pad_1,                                        //(new age)           合成音色1（新世纪）
    Pad_2,                                        //(warm)合成音色2 （温暖）
    Pad_3,                                        //(polysynth)合成音色3
    Pad_4,                                        //(choir)合成音色4 （合唱）
    Pad_5,                                        //(bowed)合成音色5
    Pad_6,                                        //(metallic)合成音色6 （金属声）
    Pad_7,                                        //(halo)合成音色7 （光环）
    Pad_8,                                        //(sweep)合成音色8

    //合成效果
    FX_1,                                        //(rain)合成效果 1 雨声
    FX_2,                                        //(soundtrack)合成效果 2 音轨
    FX_3,                                        //(crystal)合成效果 3 水晶
    FX_4,                                        //(atmosphere)合成效果 4 大气
    FX_5,                                        //(brightness)合成效果 5 明亮
    FX_6,                                        //(goblins)合成效果 6 鬼怪
    FX_7,                                        //(echoes)合成效果 7 回声
    FX_8,                                        //(sci - fi)合成效果 8 科幻

    //民间乐器
    Sitar,                                       //西塔尔（印度）
    Banjo,                                       //班卓琴（美洲）
    Shamisen,                                    //三昧线（日本）
    Koto,                                        //十三弦筝（日本）
    Kalimba,                                     //卡林巴
    Bagpipe,                                     //风笛
    Fiddle,                                      //民族提琴
    Shanai,                                      //山奈

    //打击乐器
    Tinkle_Bell,                                 //叮当铃
    Agogo,                                       //[中文名称暂缺]
    Steel_Drums,                                 //钢鼓
    Woodblock,                                   //木鱼
    Taiko_Drum,                                  //太鼓
    Melodic_Tom,                                 //通通鼓
    Synth_Drum,                                  //合成鼓
    Reverse_Cymbal,                              //铜钹

    //Sound Effects 声音效果
    Guitar_Fret_Noise,                           //吉他换把杂音
    Breath_Noise,                                //呼吸声
    Seashore,                                    //海浪声
    Bird_Tweet,                                  //鸟鸣
    Telephone_Ring,                              //电话铃
    Helicopter,                                  //直升机
    Applause,                                    //鼓掌声
    Gunshot,                                     //枪击声
};
*/
