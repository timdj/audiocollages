<?php
// download.php — geeft bestand alleen vrij na bevestigde betaling

$orderId  = preg_replace('/[^a-zA-Z0-9._-]/', '', $_GET['order'] ?? '');
$orderDir = __DIR__ . '/orders';
$orderFile = $orderDir . '/' . $orderId . '.json';

if (!$orderId || !file_exists($orderFile)) {
    http_response_code(403);
    die('Geen geldige order.');
}

$order = json_decode(file_get_contents($orderFile), true);

if ($order['status'] !== 'paid') {
    http_response_code(403);
    die('Betaling niet bevestigd. Status: ' . htmlspecialchars($order['status']));
}

// Bouw veilig bestandspad
$filePath = realpath(BASE_DIR . '/' . $order['file_path']);
$baseReal = realpath(BASE_DIR);

// Path traversal bescherming
if (!$filePath || strpos($filePath, $baseReal) !== 0 || !file_exists($filePath)) {
    http_response_code(404);
    die('Bestand niet gevonden.');
}

// Registreer download
$order['downloaded_at'] = date('c');
file_put_contents($orderFile, json_encode($order, JSON_PRETTY_PRINT));

// Stuur bestand
$ext  = strtolower(pathinfo($filePath, PATHINFO_EXTENSION));
$mime = [
    'wav' => 'audio/wav',
    'mp3' => 'audio/mpeg',
    'mp4' => 'video/mp4',
][$ext] ?? 'application/octet-stream';

header('Content-Type: ' . $mime);
header('Content-Disposition: attachment; filename="' . basename($filePath) . '"');
header('Content-Length: ' . filesize($filePath));
header('X-Content-Type-Options: nosniff');
readfile($filePath);
exit;
