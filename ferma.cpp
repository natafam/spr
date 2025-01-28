void SimulateFarm(int &dayReaching200, double &totalFeedCost) {
    int currentDay = 1;
    int currentChickenCount = initialChickens;
    totalFeedCost = 0.0;

    bool reached200Once = false; // Flaga do śledzenia, czy już osiągnięto 200 kur

    dayReaching200 = -1;

    while (currentDay <= simulationDays) {
        // Codzienny koszt paszy
        double dailyFeedCost = currentChickenCount * feedConsumptionPerChickenPerDay * feedCostPerKg;
        totalFeedCost += dailyFeedCost;

        // Sprawdzenie, czy liczba kur osiąga 200
        if (currentChickenCount == 200) {
            if (!reached200Once) {
                reached200Once = true; // Pierwsze osiągnięcie 200, ignorujemy
            } else if (dayReaching200 == -1) {
                dayReaching200 = currentDay; // Drugie osiągnięcie 200
                break; // Możemy przerwać symulację, bo znaleźliśmy odpowiedź
            }
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
