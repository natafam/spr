//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;

// Zmienne globalne dla symulacji
const int initialChickens = 200;
const double feedCostPerKg = 1.9;
const double feedConsumptionPerChickenPerDay = 0.2;
const int simulationDays = 180;

//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
    : TForm(Owner)
{
}

// Funkcja do symulacji
void SimulateFarm(int &dayReaching200, double &totalFeedCost) {
    int currentDay = 1;
    int currentChickenCount = initialChickens;
    totalFeedCost = 0.0;

    dayReaching200 = -1;

    while (currentDay <= simulationDays) {
        // Codzienny koszt paszy
        double dailyFeedCost = currentChickenCount * feedConsumptionPerChickenPerDay * feedCostPerKg;
        totalFeedCost += dailyFeedCost;

        // Sprawdzenie, kiedy liczba kur ponownie osiąga 200 sztuk
        if (currentChickenCount == 200 && dayReaching200 == -1) {
            dayReaching200 = currentDay;
        }

        // Sprawdzanie, czy to dzień nieparzysty - lis atakuje
        if (currentDay % 2 == 1) {
            currentChickenCount -= 2;
        }

        // Sprawdzanie, czy to dzień 30, 60, 90 itd. - zakup kur
        if (currentDay % 30 == 0) {
            int additionalChickens = currentChickenCount * 0.2; // Zaokrąglenie w dół
            currentChickenCount += additionalChickens;
        }

        // Zwiększenie dnia
        currentDay++;
    }
}

// Obsługa przycisku "Symuluj"
void __fastcall TForm1::ButtonSimulateClick(TObject *Sender)
{
    int dayReaching200;
    double totalFeedCost;

    // Uruchamiamy symulację
    SimulateFarm(dayReaching200, totalFeedCost);

    // Wyświetlamy wyniki w Memo
    MemoResults->Lines->Clear();
    MemoResults->Lines->Add("Wyniki symulacji:");
    if (dayReaching200 != -1) {
        MemoResults->Lines->Add("a) Dzień, w którym liczba kur po raz pierwszy osiąga 200 sztuk: " + IntToStr(dayReaching200));
    } else {
        MemoResults->Lines->Add("a) Liczba kur nigdy nie osiąga 200 sztuk w ciągu 180 dni.");
    }
    MemoResults->Lines->Add("b) Łączna kwota wydana na paszę: " + FloatToStrF(totalFeedCost, ffFixed, 8, 2) + " zł");
}
