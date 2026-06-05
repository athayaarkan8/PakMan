#include <cctype>
#include <iostream>
#include <conio.h>
#include <limits>
#include "game.h"

using namespace std;

void clearInput()
{
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void caraBermain()
{
    system("cls");
    cout << "\n======================================\n";
    cout << " CARA BERMAIN\n";
    cout << "======================================\n\n";
    cout << "W : Gerak ke atas\n";
    cout << "S : Gerak ke bawah\n";
    cout << "A : Gerak ke kiri\n";
    cout << "D : Gerak ke kanan\n";
    cout << "Z : Rewind \n";
    cout << "Q : Pause / Resume\n\n";

    cout << "Pulihkan energi rewind dengan berjalan 13 langkah.\n";
    cout << "Setiap kamu gerak, posisi sebelumnya akan disimpan. Kamu bisa rewind 3 langkah ke belakang.\n\n";

    cout << "Setiap player bergerkan, ghost juga akan bergerak. Ghost akan mengejar player jika berada dalam radius deteksinya.\n";
    cout << "Ambil paket ($), lalu antarkan ke titik delivery(!).\n";
    cout << "Hindari ghost yang ingin menghentikanmu (>).\n\n";
    cout << "Tekan Enter untuk Kembali";
    clearInput();
    cin.get();
    system("cls");
}

void difficultySelect()
{
}

void playGame(int difficulty)
{
    GameData game;
    initializeGame(game, difficulty);
    game.gameRunning = true;
    game.state = PLAYING;

    while (game.gameRunning)
    {
        renderGame(game);

        if (game.state == PAUSED)
        {
            cout << "\nInput : ";
        }
        else
        {
            cout << "\nInput (W/A/S/D, Z rewind, Q pause): ";
        }

        char input = _getch();
        input = static_cast<char>(
            tolower(
                static_cast<unsigned char>(input)));

        input = static_cast<char>(tolower(static_cast<unsigned char>(input)));

        if (input == 'q')
        {
            game.state = (game.state == PAUSED) ? PLAYING : PAUSED;

            if (game.state == PAUSED)
            {
                cout << "Game Dijeda.\n";
            }

            continue;
        }
        if (input == 'c')
        {
            caraBermain();
        }
        else if (input == 'x')
        {
            game.gameRunning = false;
            game.state = MENU;
            return;
        }

        handlePlayerInput(game, input);
        updateGameState(game);

        if (game.state == WIN)
        {
            renderGame(game);
            cout << "\n================================\n";
            cout << "Kamu menang! Paket berhasil diantar.\n";
            cout << "================================\n";
            game.gameRunning = false;
        }
        else if (game.state == GAME_OVER)
        {
            renderGame(game);
            cout << "\n================================\n";
            cout << "\nGame Over! Kamu tertangkap ghost.\n";
            cout << "================================\n";
            game.gameRunning = false;
        }
    }

    cout << "Tekan Enter untuk kembali ke Main Menu...";
    clearInput();
    cin.get();
}

int main()
{
    while (true)
    {
        system("cls");
        cout << "\n======================================\n";
        cout << "            PAKMAN GAMEBOY\n";
        cout << "======================================\n";
        cout << "[1] Mulai Game\n";
        cout << "[2] Cara Bermain\n";
        cout << "[3] Exit\n\n";
        cout << "Masukan Aksi: ";

        int aksi;
        cin >> aksi;

        if (cin.fail())
        {
            if (cin.eof())
            {
                return 0;
            }
            clearInput();
            cout << "Input harus angka!\n";
            continue;
        }

        switch (aksi)
        {
        case 1:
            system("cls");
            cout << "\n======================================\n";
            cout << " PILIH TINGKAT KESULITAN\n";
            cout << "======================================\n";
            cout << "[1] Mudah\n";
            cout << "[2] Sedang\n";
            cout << "[3] Sulit\n";
            cout << "[0] Kembali ke Menu\n\n";
            cout << "Masukan tingkat kesulitan: ";
            int level;
            cin >> level;
            if (cin.fail() || (level != 0 && (level < 1 || level > 3)))
            {
                clearInput();
                cout << "Tingkat kesulitan tidak valid!\n";
                continue;
            }
            if (level == 0)
            {
                continue;
            }

            playGame(level);
            break;
        case 2:
            caraBermain();
            break;
        case 3:
            return 0;
        default:
            cout << "Pilihan tidak valid!\n";
            break;
        }
    }
}
