<?php
// checkout.php — start Mollie iDEAL betaling
// Wordt geïnclude vanuit index.php (na POST)

if ($_SERVER['REQUEST_METHOD'] !== 'POST') {
    header('Location: index.php');
    exit;
}

$fileId   = preg_replace('/[^a-f0-9]/', '', $_POST['file_id']   ?? '');
$filePath = $_POST['file_path'] ?? '';
$fileName = $_POST['file_name'] ?? '';

if (!$fileId || !$filePath) {
    die('Ongeldig verzoek.');
}

// Valideer bestand bestaat
$fullPath = BASE_DIR . '/' . ltrim($filePath, '/');
if (!file_exists($fullPath)) {
    die('Bestand niet gevonden.');
}

// ── Mollie API ────────────────────────────────────────────────────────────────
$orderId    = uniqid('order_', true);
$returnUrl  = BASE_URL . '/index.php?action=mollie_return&order=' . urlencode($orderId);
$webhookUrl = BASE_URL . '/webhook.php';

$payload = json_encode([
    'amount'      => ['currency' => 'EUR', 'value' => '1.00'],
    'description' => 'Download: ' . $fileName,
    'redirectUrl' => $returnUrl,
    'webhookUrl'  => $webhookUrl,
    'method'      => 'ideal',
    'metadata'    => [
        'order_id'  => $orderId,
        'file_id'   => $fileId,
        'file_path' => $filePath,
        'file_name' => $fileName,
    ],
]);

$ch = curl_init('https://api.mollie.com/v2/payments');
curl_setopt_array($ch, [
    CURLOPT_POST           => true,
    CURLOPT_POSTFIELDS     => $payload,
    CURLOPT_RETURNTRANSFER => true,
    CURLOPT_HTTPHEADER     => [
        'Authorization: Bearer ' . MOLLIE_KEY,
        'Content-Type: application/json',
    ],
]);
$response = curl_exec($ch);
$httpCode = curl_getinfo($ch, CURLINFO_HTTP_CODE);
curl_close($ch);

if ($httpCode !== 201) {
    error_log('Mollie fout: ' . $response);
    echo '<p style="font-family:monospace;color:red;padding:2rem">Mollie is niet geconfigureerd. '
       . 'Voeg je live API-sleutel in bij MOLLIE_KEY in index.php. '
       . '<a href="index.php" style="color:#c8ff00">Terug</a></p>';
    exit;
}

$data = json_decode($response, true);

// Sla order op (simpele JSON-store per order)
$orderDir = __DIR__ . '/orders';
if (!is_dir($orderDir)) mkdir($orderDir, 0700, true);

file_put_contents(
    $orderDir . '/' . $orderId . '.json',
    json_encode([
        'order_id'   => $orderId,
        'mollie_id'  => $data['id'],
        'file_id'    => $fileId,
        'file_path'  => $filePath,
        'file_name'  => $fileName,
        'status'     => 'open',
        'created_at' => date('c'),
    ], JSON_PRETTY_PRINT)
);

// Doorsturen naar Mollie betaalpagina
header('Location: ' . $data['_links']['checkout']['href']);
exit;
