//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit8.h"
#include <Math.hpp>
#include <cmath>
#include <vector>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <random>
#include <System.SysUtils.hpp>

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm8 *Form8;
//---------------------------------------------------------------------------
	int k;
	int X; // Секретный ключ
int Y; // Открытый ключ
int p; // Простое число p
int g;   // Первообразный корень g

__fastcall TForm8::TForm8(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------


// Функция для преобразования символа в его цифровое значение
int charToValue(const char& ch)
{
    return (int)ch - (int)'а' + 1;
}

// Функция для преобразования цифрового значения в символ
char valueToChar(const int& value)
{
    return (char)((int)'а' + value - 1);
}


//господь бог я скоро повешусь
int modPow(int base, int exponent, int modulus)
{
    if (modulus == 1)
        return 0;

    int result = 1;
    base %= modulus;

    while (exponent > 0)
    {
        if (exponent % 2 == 1)
            result = (result * base) % modulus;

        exponent >>= 1;
        base = (base * base) % modulus;
    }

    return result;
}

std::vector<std::pair<int, int>> encrypt(const AnsiString& message, int k, int Y)
{
    std::string narrowMessage = message.c_str();

    std::vector<std::pair<int, int>> encrypted;
    for (const char& ch : narrowMessage)
    {
        int m = charToValue(ch);

        if (m <= 0 || m >= p)
        {
            ShowMessage("Некорректный символ: " + AnsiString(ch));
            continue;
        }

        int a = modPow(g, k, p);
        int b = (m * modPow(Y, k, p)) % p;

        encrypted.push_back(std::make_pair(a, b));
    }
    return encrypted;
}

std::string decrypt(const std::vector<std::pair<int, int>>& encrypted, int X)
{
    std::string decrypted;
    for (const auto& pair : encrypted)
    {
        int a = pair.first;
        int b = pair.second;

        int M = (b * modPow(a, p - 1 - X, p)) % p;

        char ch = valueToChar(M);
        decrypted += ch;
    }
    return decrypted;
}
void __fastcall TForm8::Button1Click(TObject *Sender)
{
  AnsiString message = Memo1->Lines->Text;
    p = StrToInt(Edit2->Text);
    g = StrToInt(Edit1->Text);

    std::vector<std::pair<int, int>> encrypted = encrypt(message, k, Y);

	Memo2->Lines->Clear();
	for (const auto& pair : encrypted)
	{
		std::stringstream ss;
		ss << "(" << pair.first << ", " << pair.second << ")";
		Memo2->Lines->Add(ss.str().c_str());
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm8::Button2Click(TObject *Sender)
{
std::vector<std::pair<int, int>> encrypted;

    for (int i = 0; i < Memo2->Lines->Count; i++)
    {
        AnsiString line = Memo2->Lines->Strings[i].c_str();
        int pos1 = line.Pos("(");
        int pos2 = line.Pos(",");
        int pos3 = line.Pos(")");

        if (pos1 != 0 && pos2 != 0 && pos3 != 0)
        {
            int a = StrToInt(line.SubString(pos1 + 1, pos2 - pos1 - 1));
            int b = StrToInt(line.SubString(pos2 + 1, pos3 - pos2 - 1));

            if (a <= 0 || a >= p || b <= 0 || b >= p)
            {
				ShowMessage("Некорректное исходное сообщение.");
                return;
            }

            encrypted.push_back(std::make_pair(a, b));
		}
    }

	std::string decrypted = decrypt(encrypted, X);
	Memo3->Lines->Add(decrypted.c_str());

}
//---------------------------------------------------------------------------


void __fastcall TForm8::Button3Click(TObject *Sender)
{
  p=StrToInt(Edit2->Text);
   k = RandomRange(2, p - 2);
	g=StrToInt(Edit1->Text);

	if (k == 0 || k >= p)
	{
		ShowMessage("Некорректное значение к.");
		return;
	}
	Edit3->Text=k;



    // Генерация секретного ключа X
    X = RandomRange(2, p - 1);

	// Вычисление открытого ключа Y
	Y = static_cast<long long int>(std::pow(g, X)) % p;

    // Вывод значений X и Y
	EditX->Text = IntToStr(X);
	EditY->Text = IntToStr(Y);
}
//---------------------------------------------------------------------------

