#include <iostream>
#include <limits>
#include "ghost/ghost.h"
#include "ghost/bfs.h"
using namespace std;

bool gameRunning = false;
int score = 0;
int lamaBermain = 0;

int maze[SIZE][SIZE] = {

    {0, 0, 0, 1, 0},
    {1, 0, 0, 1, 0},
    {0, 0, 0, 0, 0},
    {0, 1, 1, 0, 1},
    {0, 0, 0, 0, 0}};

Ghost ghost(0, 0);

int playerX = 2;
int playerY = 2;

enum GameState
{
    MENU,
    PLAYING,
    GAME_OVER,
    WIN
};

void clearInput()
{
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void caraBermain()
{
    system("cls");
    cout << endl;
    cout << "======================================" << endl;
    cout << " CARA BERMAIN " << endl;
    cout << "======================================" << endl;
    cout << endl;
    cout << "Tujuan Game :" << endl;
    cout << "Antarkan seluruh paket ke titik tujuan" << endl;
    cout << "sebelum waktu habis." << endl;
    cout << endl;
    cout << "Hindari Penganggu!" << endl;
    cout << "Jika tertangkap Antek-Antek maka permainan selesai." << endl;
    cout << endl;
    cout << "============== KONTROL ===============" << endl;
    cout << "W : Gerak Ke Atas" << endl;
    cout << "A : Gerak Ke Kiri" << endl;
    cout << "S : Gerak Ke Bawah" << endl;
    cout << "D : Gerak Ke Kanan" << endl;
    cout << "Z : Gunakan Time Rewind" << endl;
    cout << "Q : Jeda Game" << endl;
    cout << endl;
    cout << "======== KEKUATAN TIME REWIND ========" << endl;
    cout << "Time Rewind digunakan untuk kembali" << endl;
    cout << "ke posisi sebelumnya." << endl;
    cout << "Gunakan dengan bijak karena energi rewind" << endl;
    cout << "terbatas." << endl;
    cout << endl;
    cout << "============= ARTI SIMBOL ============" << endl;
    cout << "C : Pemain" << endl;
    cout << "> : Antek-Antek" << endl;
    cout << "$ : Paket" << endl;
    cout << "! : Titik Delivery" << endl;
    cout << "# : Tembok" << endl;
    cout << ". : Jalan" << endl;
    cout << endl;
    cout << "Tekan Enter untuk kembali ke menu...";
    cin.ignore();
    cin.get();
}

void chooseGameTime()
{
    int aksi;

    while (true)
    {
        system("cls");

        cout << "============ DURASI GAME ============" << endl;
        cout << "1. Regular (1 Menit)" << endl;
        cout << "2. Mid (2 Menit)" << endl;
        cout << "3. Long (3 Menit)" << endl;
        cout << "4. Kembali ke Menu" << endl;
        cout << endl;
        cout << "Pilih Waktu Main: ";

        cin >> aksi;

        if (cin.fail())
        {
            clearInput();

            cout << "\nInput harus angka!" << endl;
            system("pause");
            continue;
        }

        switch (aksi)
        {
        case 1:
            lamaBermain = 60;
            return;

        case 2:
            lamaBermain = 120;
            return;

        case 3:
            lamaBermain = 180;
            return;

        case 4:
            return;

        default:
            cout << "\nPilihan tidak valid!" << endl;
            system("pause");
        }
    }
}

void mainMenu()
{
    int aksi;

    while (true)
    {
        system("cls");

        cout << "======================================" << endl;
        cout << "            PAKMAN GAMEBOY            " << endl;
        cout << "======================================" << endl;
        cout << endl;

        cout << "[1] Mulai Game" << endl;
        cout << "[2] Cara Bermain" << endl;
        cout << "[3] Exit" << endl;
        cout << endl;

        cout << "Masukan Aksi: ";

        cin >> aksi;

        switch (aksi)
        {
        case 1:
            chooseGameTime();

            if (lamaBermain > 0)
            {
                gameRunning = true;
                return;
            }
            break;

        case 2:
            caraBermain();

        case 3:
            exit(0);

        default:
            cout << "Pilihan tidak valid!" << endl;
            system("pause");
        }
    }
}

void renderGame()
{
    cout << "████████████████" << endl;
    cout << "█ C · · X · · !█" << endl;
    cout << "█ . . . . # . .█" << endl;
    cout << "█ . # # . . . #█" << endl;
    cout << "████████████████" << endl;
    cout << endl;
}

void updateGame()
{
    ghost.setDifficulty(2);

    ghost.update(
        maze,
        playerX,
        playerY);
}

int main()
{
    while (true)
    {
        mainMenu();

        while (gameRunning)
        {
            system("cls");

            renderGame();

            updateGame();

            system("pause");

            gameRunning = false;
        }
    }

    return 0;
}