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
