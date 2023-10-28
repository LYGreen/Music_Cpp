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
    //���ټ�
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
    //����
    if (_kbhit())
    {
        //�л�����
        if (GetAsyncKeyState(VK_LEFT))
        {
            Sleep(30);
            ins--;
            midiOutShortMsg(hMidiOut, (ins << 8) + 0xC0);
            system("cls");
            cout << "����:" << ins << endl;
            cout << "�˶�:" << octave << endl;
        }
        if (GetAsyncKeyState(VK_RIGHT))
        {
            Sleep(30);
            ins++;
            midiOutShortMsg(hMidiOut, (ins << 8) + 0xC0);
            system("cls");
            cout << "����:" << ins << endl;
            cout << "�˶�:" << octave << endl;
        }
        //���ð˶�
        if (GetAsyncKeyState(VK_UP))
        {
            while (GetAsyncKeyState(VK_UP));
            octave++;
            system("cls");
            cout << "����:" << ins << endl;
            cout << "�˶�:" << octave << endl;
        }
        if (GetAsyncKeyState(VK_DOWN))
        {
            while (GetAsyncKeyState(VK_DOWN));
            octave--;
            system("cls");
            cout << "����:" << ins << endl;
            cout << "�˶�:" << octave << endl;
        }
    }
}

int main(int argc, char* argv[])
{
    //˵��
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
    cout << "����:" << endl;
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
    cout << "�л�����:������" << endl;
    cout << "�����˶�:������" << endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    system("Pause");

    //MIDI
    midiOutOpen(&hMidiOut, 0, 0, 0, CALLBACK_NULL);
    midiOutShortMsg(hMidiOut, (0 << 8) + 0xC0);
    system("cls");
    cout << "����:" << ins << endl;
    cout << "�˶�:" << octave << endl;
    while (1)
    {
        Sleep(1);
        if (GetAsyncKeyState(VK_ESCAPE))//�˳�
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
    //midi�������
    Acoustic_Grand_Piano = 0,                    //����٣���ѧ���٣�
    Bright_Acoustic_Piano,                       //�����ĸ���
    Electric_Grand_Piano,                        //�����
    Honky__tonk_Piano,                           //�ưɸ���
    Rhodes_Piano,                                //��͵ĵ����
    Chorused_Piano,                              //�Ӻϳ�Ч���ĵ����
    Harpsichord,                                 //��ܼ��٣����ҹŸ��٣�
    Clavichord,                                  //����ά�����٣����ҹŸ��٣�

    //ɫ�ʴ������
    Celesta,                                     //��Ƭ��
    Glockenspiel,                                //����
    Music_box,                                   //������
    Vibraphone,                                  //������
    Marimba,                                     //���ְ�
    Xylophone,                                   //ľ��
    Tubular_Bells,                               //����
    Dulcimer,                                    //������

    //����
    Hammond_Organ,                               //���˷���
    Percussive_Organ,                            //���ʽ����
    Rock_Organ,                                  //ҡ������
    Church_Organ,                                //���÷���
    Reed_Organ,                                  //�ɹܷ���
    Accordian,                                   //�ַ���
    Harmonica,                                   //����
    Tango_Accordian,                             //̽���ַ���

    //����
    Acoustic_Guitar_nylon,                       //�����Ҽ���
    Acoustic_Guitar_steel,                       //���Ҽ���
    Electric_Guitar_jazz,                        //��ʿ�缪��
    Electric_Guitar_clean,                       //�����缪��
    Electric_Guitar_muted,                       //�����缪��
    Overdriven_Guitar,                           //������Ч���ĵ缪��
    Distortion_Guitar,                           //��ʧ��Ч���ĵ缪��
    Guitar_Harmonics,                            //��������

    //��˾
    Acoustic_Bass,                               //��˾����ѧ��˾��
    Electric_Bass_finger,                        //�籴˾��ָ����
    Electric_Bass_pick,                          //�籴˾����Ƭ��
    Fretless_Bass,                               //��Ʒ��˾
    Slap_Bass_1,                                 //�ƻ�Bass 1
    Slap_Bass_2,                                 //�ƻ�Bass 2
    Synth_Bass_1,                                //���Ӻϳ�Bass 1
    Synth_Bass_2,                                //���Ӻϳ�Bass 2

    //����
    Violin,                                       //С����
    Viola,                                        //������
    Cello,                                        //������
    Contrabass,                                   //����������
    Tremolo_Strings,                              //����Ⱥ������ɫ
    Pizzicato_Strings,                            //����Ⱥ������ɫ
    Orchestral_Harp,                              //����
    Timpani,                                      //������

    //���� / �ϳ�
    String_Ensemble_1,                            //���ֺ�����ɫ1
    String_Ensemble_2,                            //���ֺ�����ɫ2
    Synth_Strings_1,                              //�ϳ����ֺ�����ɫ1
    Synth_Strings_2,                              //�ϳ����ֺ�����ɫ2
    Choir_Aahs,                                   //�����ϳ�������
    Voice_Oohs,                                   //������ཡ�
    Synth_Voice,                                  //�ϳ�����
    Orchestra_Hit,                                //�������û�����

    //ͭ��
    Trumpet,                                      //С��
    Trombone,                                     //����
    Tuba,                                         //���
    Muted_Trumpet,                                //��������С��
    French_Horn,                                  //�����ţ�Բ�ţ�
    Brass_Section,                                //ͭ���飨ͭ������������ɫ��
    Synth_Brass_1,                                //�ϳ�ͭ����ɫ1
    Synth_Brass_2,                                //�ϳ�ͭ����ɫ2

    //�ɹ�
    Soprano_Sax,                                  //��������˹��
    Alto_Sax,                                     //����������˹��
    Tenor_Sax,                                    //��������˹��
    Baritone_Sax,                                 //��������˹��
    Oboe,                                         //˫�ɹ�
    English_Horn,                                 //Ӣ����
    Bassoon,                                      //���ɣ���ܣ�
    Clarinet,                                     //���ɹܣ��ڹܣ�

    //��
    Piccolo,                                      //�̵�
    Flute,                                        //����
    Recorder,                                     //����
    Pan_Flute,                                    //����
    Bottle_Blow,                                  //[����������ȱ]
    Shakuhachi,                                   //�ձ��߰�
    Whistle,                                      //������
    Ocarina,                                      //�¿�����

    //�ϳ�����
    Lead_1,                                       //(square)�ϳ�����1��������
    Lead_2,                                       //(sawtooth)�ϳ�����2����ݲ���
    Lead_3,                                       //(caliope lead)                 �ϳ�����3
    Lead_4,                                       //(chiff lead)                     �ϳ�����4
    Lead_5,                                       //(charang)�ϳ�����5
    Lead_6,                                       //(voice)�ϳ�����6��������
    Lead_7,                                       //(fifths)�ϳ�����7��ƽ����ȣ�
    Lead_8,                                       //(bass + lead)�ϳ�����8����˾��������

    //�ϳ���ɫ
    Pad_1,                                        //(new age)           �ϳ���ɫ1�������ͣ�
    Pad_2,                                        //(warm)�ϳ���ɫ2 ����ů��
    Pad_3,                                        //(polysynth)�ϳ���ɫ3
    Pad_4,                                        //(choir)�ϳ���ɫ4 ���ϳ���
    Pad_5,                                        //(bowed)�ϳ���ɫ5
    Pad_6,                                        //(metallic)�ϳ���ɫ6 ����������
    Pad_7,                                        //(halo)�ϳ���ɫ7 ���⻷��
    Pad_8,                                        //(sweep)�ϳ���ɫ8

    //�ϳ�Ч��
    FX_1,                                        //(rain)�ϳ�Ч�� 1 ����
    FX_2,                                        //(soundtrack)�ϳ�Ч�� 2 ����
    FX_3,                                        //(crystal)�ϳ�Ч�� 3 ˮ��
    FX_4,                                        //(atmosphere)�ϳ�Ч�� 4 ����
    FX_5,                                        //(brightness)�ϳ�Ч�� 5 ����
    FX_6,                                        //(goblins)�ϳ�Ч�� 6 ���
    FX_7,                                        //(echoes)�ϳ�Ч�� 7 ����
    FX_8,                                        //(sci - fi)�ϳ�Ч�� 8 �ƻ�

    //�������
    Sitar,                                       //��������ӡ�ȣ�
    Banjo,                                       //��׿�٣����ޣ�
    Shamisen,                                    //�����ߣ��ձ���
    Koto,                                        //ʮ�����ݣ��ձ���
    Kalimba,                                     //���ְ�
    Bagpipe,                                     //���
    Fiddle,                                      //��������
    Shanai,                                      //ɽ��

    //�������
    Tinkle_Bell,                                 //������
    Agogo,                                       //[����������ȱ]
    Steel_Drums,                                 //�ֹ�
    Woodblock,                                   //ľ��
    Taiko_Drum,                                  //̫��
    Melodic_Tom,                                 //ͨͨ��
    Synth_Drum,                                  //�ϳɹ�
    Reverse_Cymbal,                              //ͭ��

    //Sound Effects ����Ч��
    Guitar_Fret_Noise,                           //������������
    Breath_Noise,                                //������
    Seashore,                                    //������
    Bird_Tweet,                                  //����
    Telephone_Ring,                              //�绰��
    Helicopter,                                  //ֱ����
    Applause,                                    //������
    Gunshot,                                     //ǹ����
};
*/
