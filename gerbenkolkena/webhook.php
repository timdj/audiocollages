<?php
// webhook.php — Mollie stuurt hier een POST wanneer betaalstatus verandert
require __DIR__ . '/index.php'; // laadt defines

$mollieId = $_POST['id'] ?? '';
if (!$mollieId) { http_response_code(400); exit; }

// Zoek bijbehorende order
$orderDir = __DIR__ . '/orders';
$found    = null;
foreach (glob($orderDir . '/*.json') as $f) {
    $o = json_decode(file_get_contents($f), true);
    if ($o['mollie_id'] === $mollieId) { $found = $o; $foundFile = $f; break; }
}
if (!$found) { http_response_code(404); exit; }

// Haal status op bij Mollie
$ch = curl_init('https://api.mollie.com/v2/payments/' . $mollieId);
curl_setopt_array($ch, [
    CURLOPT_RETURNTRANSFER => true,
    CURLOPT_HTTPHEADER     => ['Authorization: Bearer ' . MOLLIE_KEY],
]);
$data   = json_decode(curl_exec($ch), true);
curl_close($ch);

$found['status']     = $data['status'] ?? 'unknown';
$found['updated_at'] = date('c');
file_put_contents($foundFile, json_encode($found, JSON_PRETTY_PRINT));

http_response_code(200);
echo 'OK';
