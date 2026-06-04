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
    cout << "\n======================================\n";
    cout << " CARA BERMAIN\n";
    cout << "======================================\n\n";
    cout << "W : Gerak ke atas\n";
    cout << "S : Gerak ke bawah\n";
    cout << "A : Gerak ke kiri\n";
    cout << "D : Gerak ke kanan\n";
    cout << "Z : Rewind posisi sebelumnya\n";
    cout << "Q : Pause / Resume\n\n";
    cout << "Ambil paket ($), lalu antarkan ke titik (!).\n";
    cout << "Hindari ghost (>).\n\n";
    cout << "Tekan Enter untuk kembali ke Main Menu...";
    clearInput();
    cin.get();
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

        cout << "Input (W/A/S/D, Z rewind, Q pause): ";

        char input = _getch();
        input = static_cast<char>(
            tolower(
                static_cast<unsigned char>(input)));

        // cout << input << endl; // optional biar keliatan tombol yang dipencet

        // if (cin.fail())
        // {
        //     if (cin.eof())
        //     {
        //         game.gameRunning = false;
        //         break;
        //     }
        //     clearInput();
        //     continue;
        // }

        input = static_cast<char>(tolower(static_cast<unsigned char>(input)));

        if (input == 'q')
        {
            game.state = (game.state == PAUSED) ? PLAYING : PAUSED;

            if (game.state == PAUSED)
            {
                cout << "Game Dijeda.\n";
                cout << "[Q] Lanjutkan.\n";
                cout << "[C] Cara Bermain.\n";
                cout << "[X] Keluar.\n";
            }

            continue;
        }

        if (game.state == PAUSED)
        {
            if (input == 'c')
            {
                caraBermain();
            }
            else if (input == 'x')
            {
                game.gameRunning = false;
            }
            continue;
        }

        if (game.state == PAUSED)
        {
            continue;
        }

        handlePlayerInput(game, input);
        updateGameState(game);

        if (game.state == WIN)
        {
            renderGame(game);
            cout << "\nKamu menang! Paket berhasil diantar.\n";
            game.gameRunning = false;
        }
        else if (game.state == GAME_OVER)
        {
            renderGame(game);
            cout << "\nGame Over! Kamu tertangkap ghost.\n";
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
        cout << "\n======================================\n";
        cout << "            PAKMAN GAMEBOY\n";
        cout << "======================================\n";
        cout << "[1] Mulai Game\n";
        cout << "[2] Cara Bermain\n";
        cout << "[3] Exit\n";
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
            cout << "\n======================================\n";
            cout << " PILIH TINGKAT KESULITAN\n";
            cout << "======================================\n\n";
            cout << "Pilih tingkat kesulitan:\n";
            cout << "[1] Mudah\n";
            cout << "[2] Sedang\n";
            cout << "[3] Sulit\n";
            cout << "Masukan tingkat kesulitan: ";
            int level;
            cin >> level;
            if (cin.fail() || level < 1 || level > 3)
            {
                clearInput();
                cout << "Tingkat kesulitan tidak valid!\n";
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
