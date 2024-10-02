// Zad. 1
fun main() {
    println("Podaj numer miesiąca (1-12):")
    val miesiac = readLine()?.toIntOrNull() ?: 0

    when (miesiac) {
        1, 2, 12 -> println("To jest zima.")
        3, 4, 5 -> println("To jest wiosna.")
        6, 7, 8 -> println("To jest lato.")
        9, 10, 11 -> println("To jest jesień.")
        else -> println("Niepoprawny numer miesiąca.")
    }
}

// Zad. 2
fun main() {
    // Przykładowa lista liczb
    val liczby = listOf(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12)

    println("Liczby podzielne przez 3:")
    for (liczba in liczby) {
        if (liczba % 3 == 0) {
            println(liczba)
        }
    }
}


// Całość
fun main() {
    println("podaj miesiac")
    val miesiac:Int = readln().toInt()

    println(when(miesiac) {
        1 -> "styczeń"
        2 -> "luty"
        3 -> "marzec"
        4 -> "kwiecień"
        5 -> "maj"
        6 -> "czerwiec"
        7 -> "lipiec"
        8 -> "sierpień"
        9 -> "wrzesień"
        10 -> "październik"
        11 -> "listopad"
        12 -> "grudzien"
        else -> "nieznany"
    })

    if(miesiac in 3..5) {
        println("wiosna")
    } else if(miesiac in 6..8) {
        println("lato")
    } else if(miesiac in 9..11) {
        println("jesień")
    } else if(miesiac == 12 || (miesiac in 1..2)) {
        println("zima")
    }

    val tablica = arrayOf(5,3,10,-6,0,-3,2,33,-22,50,42,99,100,-101,200, 4, -1, 1)

    var liczbaParzystych = 0
    for (element in tablica) {
        if(element%2==0) liczbaParzystych++
    }

    print("parzyste: $liczbaParzystych")
}
