#include <cctype>
#include <iostream>
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
    cout << "W/A/S/D : Gerak\n";
    cout << "Z       : Rewind posisi sebelumnya\n";
    cout << "Q       : Pause / Resume\n\n";
    cout << "Ambil paket ($), lalu antarkan ke titik (!).\n";
    cout << "Hindari ghost (>).\n\n";
    cout << "Tekan Enter untuk kembali ke menu...";
    clearInput();
    cin.get();
}

void playGame()
{
    GameData game;
    initializeGame(game);
    game.gameRunning = true;
    game.state = PLAYING;

    while (game.gameRunning)
    {
        renderGame(game);

        cout << "Input (W/A/S/D, Z rewind, Q pause): ";
        char input;
        cin >> input;

        if (cin.fail())
        {
            if (cin.eof())
            {
                game.gameRunning = false;
                break;
            }
            clearInput();
            continue;
        }

        input = static_cast<char>(tolower(static_cast<unsigned char>(input)));

        if (input == 'q')
        {
            game.state = (game.state == PAUSED) ? PLAYING : PAUSED;

            if (game.state == PAUSED)
            {
                cout << "Game dijeda. Tekan Q lagi untuk lanjut.\n";
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

    cout << "Tekan Enter untuk kembali ke menu...";
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
            playGame();
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
