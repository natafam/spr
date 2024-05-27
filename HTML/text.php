Po kliknięciu "Sprawdź odpowiedzi" ma przekierowywać na stronę question.php, na której wyświetli się to konkretne pytanie, którego odpowiedzi chcemy sprawdzić.


Plik all-quesions.php, w którym użytkownik klika "Sprawdź odpowiedzi";
<?php
// Rozpoczęcie sesji
session_start();

// Sprawdzenie, czy użytkownik jest zalogowany
// if (!isset($_SESSION['user_id'])) {
//     header("Location: login.html");
//     exit();
// }

// Konfiguracja
$db_host = 'localhost';
$db_username = 'root';
$db_password = '';
$db_name = 'StudyMateMatch';

// Utworzenie połączenia
$conn = new mysqli($db_host, $db_username, $db_password, $db_name);

// Sprawdzenie połączenia
if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
}

// Ustawienie domyślnego warunku WHERE
$where_clause = "";

// Sprawdzenie, czy użytkownik wybrał przedmiot
if(isset($_GET['subject']) && !empty($_GET['subject'])) {
    $subject_filter = $_GET['subject'];
    $where_clause = " WHERE Q.Subject = ?";
}

// Aktualizacja zapytania SQL z uwzględnieniem filtra przedmiotu
$sql = "SELECT Q.Question_text, Q.Subject, Q.Question_datetime, U.User_nickname 
        FROM Questions Q 
        JOIN Users U ON Q.User_ID = U.User_ID"
        . $where_clause . 
        " ORDER BY Q.Question_datetime DESC";

// Przygotowanie zapytania
$stmt = $conn->prepare($sql);

// Dodanie wartości filtra przedmiotu, jeśli został wybrany
if(!empty($where_clause)) {
    $stmt->bind_param("s", $subject_filter);
}

// Wykonanie zapytania
$stmt->execute();
$result = $stmt->get_result();

/*
// Pobranie pytania zapisanych przez użytkownika
// $user_id = $_SESSION['user_id']; // Zakładamy, że user_id jest przechowywany w sesji
$sql = "SELECT Q.Question_text, Q.Subject, Q.Question_datetime, U.User_nickname 
        FROM Questions Q 
        JOIN Users U ON Q.User_ID = U.User_ID
        ORDER BY Q.Question_datetime DESC";
$stmt = $conn->prepare($sql);
// $stmt->bind_param("i", $user_id);
$stmt->execute();
$result = $stmt->get_result();
*/

// Zamknięcie połączenia
$conn->close();
?>

<section class="all-questions">

<div class="all-questions-heading">
    <h2 class="all-questions-h2">Wszystkie pytania naszej społeczności</h2>
    <p class="all-questions-paragraph">Tutaj znajdziesz pytania zadane przez innych użytkowników. Może i dla Ciebie okażą się pomocne!</p>
</div>


<form method="get" action="">
    <label for="subject"></label>

    <div class="quesion-sent-filter-box">
        <select name="subject" id="quesion-sent-subject">
            <option value="Wybierz przedmiot">Wybierz przedmiot</option>
            <option value="Matematyka">Matematyka</option>
            <option value="Polski">Polski</option>
            <option value="Angielski">Angielski</option>
            <option value="Biologia">Biologia</option>
            <option value="Fizyka">Fizyka</option>
            <option value="Chemia">Chemia</option>
            <option value="Geografia">Geografia</option>
            <option value="Historia">Historia</option>
            <option value="WOS">WOS</option>
            <option value="Religia">Religia</option>
            <option value="Informatyka">Informatyka</option>
            <option value="Plastyka">Plastyka</option>
            <option value="Historia sztuki">Historia sztuki</option>
            <option value="Muzyka">Muzyka</option>
            <option value="BiZ i PP">BiZ i PP</option>
            <option value="EdB i BHP">EdB i BHP</option>
            <option value="Niemiecki">Niemiecki</option>
            <option value="Hiszpański">Hiszpański</option>
            <option value="Włoski">Włoski</option>
            <option value="Francuski">Francuski</option>
            <option value="Rosyjski">Rosyjski</option>
            <option value="Inne języki obce">Inne języki obce</option>
        </select>

        <div class="all-questions-filter">
            <button type="submit" class="all-questions-submit button button-main">Filtruj</button>
        </div>
    </div>
</form>


<div class="all-questions-grid">

    <?php while ($row = $result->fetch_assoc()): ?>
        <div class="all-questions-item">
            <div class="all-questions-box question-box-check-root-class-name">
                <div class="question-box-content">
                    <div class="question-box-question">
                        <div class="question-box-details">

                            <span class="question-box-date">
                                <span>
                                    <?php 
                                    // Formatowanie daty
                                    $formatted_date = date("d.m.Y", strtotime($row['Question_datetime']));
                                    echo htmlspecialchars($formatted_date); 
                                    ?>
                                </span>
                            </span>

                            <span class="question-box-user">
                                <span><?php echo htmlspecialchars($row['User_nickname']); ?></span>
                            </span>

                            <span class="question-box-subject">
                                <span><?php echo htmlspecialchars($row['Subject']); ?></span>
                            </span>

                        </div>
                        <p class="question-box-question-text">
                            <span><?php echo htmlspecialchars($row['Question_text']); ?></span>
                        </p>
                    </div>
                    <div class="question-box-check-answer read-more">
                        <span class="question-box-check-span">
                            <a href="question.php?id=<?php echo $row['Question_ID']; ?>" class="question-box-check-span">Sprawdź odpowiedzi</a>
                        </span>
                        <img src="../Images/Icons/arrow-black.svg" class="question-box-check-image"/>
                    </div>
                </div>
            </div>
        </div>
    <?php endwhile; ?>

</div>

</section>



Plik quesion-handler.php, który obsługuje pytania:
<?php
// Start the session
session_start();

// Check if form is submitted
if ($_SERVER["REQUEST_METHOD"] == "POST") {
    // Database configuration
    $db_host = 'localhost';
    $db_username = 'root';
    $db_password = '';
    $db_name = 'StudyMateMatch';

    // Create connection
    $conn = new mysqli($db_host, $db_username, $db_password, $db_name);

    // Check connection
    if ($conn->connect_error) {
        die("Connection failed: " . $conn->connect_error);
    }

    // Sanitize input
    function sanitize_input($data) {
        global $conn;
        $data = trim($data);
        $data = stripslashes($data);
        $data = htmlspecialchars($data);
        $data = $conn->real_escape_string($data);
        return $data;
    }

    // Clean and retrieve question, subject, and user_id from form
    $question = sanitize_input($_POST['question']);
    $subject = sanitize_input($_POST['subject']);
    $date = date("Y-m-d H:i:s");
    
    // Check if user_id exists in session
    if (isset($_SESSION['User_ID'])) {
        $user_id = $_SESSION['User_ID']; // Retrieve user_id from session
    } else {
        // Handle the case when user_id is not set in session
        echo "Error: User_ID not set in session.";
        exit();
    }

    // Prepare SQL query
    $sql = "INSERT INTO Questions (Question_text, Subject, Question_datetime, User_ID) VALUES (?, ?, ?, ?)";
    $stmt = $conn->prepare($sql);
    $stmt->bind_param("sssi", $question, $subject, $date, $user_id);

    // Execute query
    if ($stmt->execute()) {
        // Redirect to confirmation page
        header("Location: ../HTML/question-sent.php");
        exit();
    } else {
        echo "Error: " . $sql . "<br>" . $conn->error;
    }

    // Close connection
    $conn->close();
}

?>



Plik question.php, do którego użytkownik ma zostać przekierowany i w którym mają się wyświetlić dane konkretnego, wybranego pytania:
Po kliknięciu "Sprawdź odpowiedzi" ma przekierowywać na stronę question.php, na której wyświetli się to konkretne pytanie, którego odpowiedzi chcemy sprawdzić.


Plik all-quesions.php, w którym użytkownik klika "Sprawdź odpowiedzi";
<?php
// Rozpoczęcie sesji
session_start();

// Sprawdzenie, czy użytkownik jest zalogowany
// if (!isset($_SESSION['user_id'])) {
//     header("Location: login.html");
//     exit();
// }

// Konfiguracja
$db_host = 'localhost';
$db_username = 'root';
$db_password = '';
$db_name = 'StudyMateMatch';

// Utworzenie połączenia
$conn = new mysqli($db_host, $db_username, $db_password, $db_name);

// Sprawdzenie połączenia
if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
}

// Ustawienie domyślnego warunku WHERE
$where_clause = "";

// Sprawdzenie, czy użytkownik wybrał przedmiot
if(isset($_GET['subject']) && !empty($_GET['subject'])) {
    $subject_filter = $_GET['subject'];
    $where_clause = " WHERE Q.Subject = ?";
}

// Aktualizacja zapytania SQL z uwzględnieniem filtra przedmiotu
$sql = "SELECT Q.Question_text, Q.Subject, Q.Question_datetime, U.User_nickname 
        FROM Questions Q 
        JOIN Users U ON Q.User_ID = U.User_ID"
        . $where_clause . 
        " ORDER BY Q.Question_datetime DESC";

// Przygotowanie zapytania
$stmt = $conn->prepare($sql);

// Dodanie wartości filtra przedmiotu, jeśli został wybrany
if(!empty($where_clause)) {
    $stmt->bind_param("s", $subject_filter);
}

// Wykonanie zapytania
$stmt->execute();
$result = $stmt->get_result();

/*
// Pobranie pytania zapisanych przez użytkownika
// $user_id = $_SESSION['user_id']; // Zakładamy, że user_id jest przechowywany w sesji
$sql = "SELECT Q.Question_text, Q.Subject, Q.Question_datetime, U.User_nickname 
        FROM Questions Q 
        JOIN Users U ON Q.User_ID = U.User_ID
        ORDER BY Q.Question_datetime DESC";
$stmt = $conn->prepare($sql);
// $stmt->bind_param("i", $user_id);
$stmt->execute();
$result = $stmt->get_result();
*/

// Zamknięcie połączenia
$conn->close();
?>

<section class="all-questions">

<div class="all-questions-heading">
    <h2 class="all-questions-h2">Wszystkie pytania naszej społeczności</h2>
    <p class="all-questions-paragraph">Tutaj znajdziesz pytania zadane przez innych użytkowników. Może i dla Ciebie okażą się pomocne!</p>
</div>


<form method="get" action="">
    <label for="subject"></label>

    <div class="quesion-sent-filter-box">
        <select name="subject" id="quesion-sent-subject">
            <option value="Wybierz przedmiot">Wybierz przedmiot</option>
            <option value="Matematyka">Matematyka</option>
            <option value="Polski">Polski</option>
            <option value="Angielski">Angielski</option>
            <option value="Biologia">Biologia</option>
            <option value="Fizyka">Fizyka</option>
            <option value="Chemia">Chemia</option>
            <option value="Geografia">Geografia</option>
            <option value="Historia">Historia</option>
            <option value="WOS">WOS</option>
            <option value="Religia">Religia</option>
            <option value="Informatyka">Informatyka</option>
            <option value="Plastyka">Plastyka</option>
            <option value="Historia sztuki">Historia sztuki</option>
            <option value="Muzyka">Muzyka</option>
            <option value="BiZ i PP">BiZ i PP</option>
            <option value="EdB i BHP">EdB i BHP</option>
            <option value="Niemiecki">Niemiecki</option>
            <option value="Hiszpański">Hiszpański</option>
            <option value="Włoski">Włoski</option>
            <option value="Francuski">Francuski</option>
            <option value="Rosyjski">Rosyjski</option>
            <option value="Inne języki obce">Inne języki obce</option>
        </select>

        <div class="all-questions-filter">
            <button type="submit" class="all-questions-submit button button-main">Filtruj</button>
        </div>
    </div>
</form>


<div class="all-questions-grid">

    <?php while ($row = $result->fetch_assoc()): ?>
        <div class="all-questions-item">
            <div class="all-questions-box question-box-check-root-class-name">
                <div class="question-box-content">
                    <div class="question-box-question">
                        <div class="question-box-details">

                            <span class="question-box-date">
                                <span>
                                    <?php 
                                    // Formatowanie daty
                                    $formatted_date = date("d.m.Y", strtotime($row['Question_datetime']));
                                    echo htmlspecialchars($formatted_date); 
                                    ?>
                                </span>
                            </span>

                            <span class="question-box-user">
                                <span><?php echo htmlspecialchars($row['User_nickname']); ?></span>
                            </span>

                            <span class="question-box-subject">
                                <span><?php echo htmlspecialchars($row['Subject']); ?></span>
                            </span>

                        </div>
                        <p class="question-box-question-text">
                            <span><?php echo htmlspecialchars($row['Question_text']); ?></span>
                        </p>
                    </div>
                    <div class="question-box-check-answer read-more">
                        <span class="question-box-check-span">
                            <a href="question.php?id=<?php echo $row['Question_ID']; ?>" class="question-box-check-span">Sprawdź odpowiedzi</a>
                        </span>
                        <img src="../Images/Icons/arrow-black.svg" class="question-box-check-image"/>
                    </div>
                </div>
            </div>
        </div>
    <?php endwhile; ?>

</div>

</section>



Plik quesion-handler.php, który obsługuje pytania:
<?php
// Start the session
session_start();

// Check if form is submitted
if ($_SERVER["REQUEST_METHOD"] == "POST") {
    // Database configuration
    $db_host = 'localhost';
    $db_username = 'root';
    $db_password = '';
    $db_name = 'StudyMateMatch';

    // Create connection
    $conn = new mysqli($db_host, $db_username, $db_password, $db_name);

    // Check connection
    if ($conn->connect_error) {
        die("Connection failed: " . $conn->connect_error);
    }

    // Sanitize input
    function sanitize_input($data) {
        global $conn;
        $data = trim($data);
        $data = stripslashes($data);
        $data = htmlspecialchars($data);
        $data = $conn->real_escape_string($data);
        return $data;
    }

    // Clean and retrieve question, subject, and user_id from form
    $question = sanitize_input($_POST['question']);
    $subject = sanitize_input($_POST['subject']);
    $date = date("Y-m-d H:i:s");
    
    // Check if user_id exists in session
    if (isset($_SESSION['User_ID'])) {
        $user_id = $_SESSION['User_ID']; // Retrieve user_id from session
    } else {
        // Handle the case when user_id is not set in session
        echo "Error: User_ID not set in session.";
        exit();
    }

    // Prepare SQL query
    $sql = "INSERT INTO Questions (Question_text, Subject, Question_datetime, User_ID) VALUES (?, ?, ?, ?)";
    $stmt = $conn->prepare($sql);
    $stmt->bind_param("sssi", $question, $subject, $date, $user_id);

    // Execute query
    if ($stmt->execute()) {
        // Redirect to confirmation page
        header("Location: ../HTML/question-sent.php");
        exit();
    } else {
        echo "Error: " . $sql . "<br>" . $conn->error;
    }

    // Close connection
    $conn->close();
}

?>



Plik question.php, do którego użytkownik ma zostać przekierowany i w którym mają się wyświetlić dane konkretnego, wybranego pytania:
<section class="question-questions">
    <div class="question-heading">
        <div class="question-content">

            <div class="question-box question-box-root-class-name2">
                <div class="question-box-content">
                    <div class="question-box-question">
                        <div class="question-box-details">
                            <span class="question-box-date"><span>01.01.2024</span></span>
                            <span class="question-box-user"><span>janek123</span></span>
                            <span class="question-box-subject"><span>Matematyka</span></span>
                        </div>
                        <p class="question-box-question-text">
                            <span>Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua.</span>
                        </p>
                    </div>
                </div>
            </div>

            <div class="answer-box answer-box-root-class-name2">
                <div class="answer-box-content">
                    <div class="answer-box-answer">
                        <div class="answer-box-details">
                            <span class="answer-box-date"><span>01.01.2024</span></span>
                            <span class="answer-box-user"><span>janek123</span></span>
                        </div>
                        <p class="answer-box-answer-text">
                            <span>Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua.</span>
                        </p>
                    </div>
                </div>
            </div>

            <div class="new-answer-box">
                <div class="question-answer">
                    <h2 class="answer-text">Dodaj swoją odpowiedź</h2>
                    <textarea placeholder="Tutaj jest miejsce na Twoją odpowiedź!" class="answer-textarea textarea"></textarea>
                    <div class="answer-lower">
                        <div class="answer-button">
                            <button class="new-answer-sent button button-main"><span>Dodaj odpowiedź</span></button>
                        </div>
                    </div>
                </div>
            </div>

        </div>
    </div>
</section>