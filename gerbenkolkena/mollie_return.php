<?php
// mollie_return.php — klant keert terug na iDEAL-betaling

$orderId  = preg_replace('/[^a-zA-Z0-9._-]/', '', $_GET['order'] ?? '');
$orderDir = __DIR__ . '/orders';
$orderFile = $orderDir . '/' . $orderId . '.json';

if (!$orderId || !file_exists($orderFile)) {
    die('Order niet gevonden.');
}

$order = json_decode(file_get_contents($orderFile), true);

// Controleer status bij Mollie
$ch = curl_init('https://api.mollie.com/v2/payments/' . $order['mollie_id']);
curl_setopt_array($ch, [
    CURLOPT_RETURNTRANSFER => true,
    CURLOPT_HTTPHEADER     => ['Authorization: Bearer ' . MOLLIE_KEY],
]);
$response = json_decode(curl_exec($ch), true);
curl_close($ch);

$status = $response['status'] ?? 'unknown';

// Werk order bij
$order['status']     = $status;
$order['checked_at'] = date('c');
file_put_contents($orderFile, json_encode($order, JSON_PRETTY_PRINT));

$paid = ($status === 'paid');
?>
<!DOCTYPE html>
<html lang="nl">
<head>
<meta charset="UTF-8">
<meta name="viewport" content="width=device-width,initial-scale=1">
<title><?= SHOP_NAME ?> — Betaling</title>
<link href="https://fonts.googleapis.com/css2?family=Space+Mono:wght@400;700&family=Syne:wght@800&display=swap" rel="stylesheet">
<style>
body { background:#0a0a0a; color:#e8e8e0; font-family:'Space Mono',monospace;
       display:flex; align-items:center; justify-content:center; min-height:100vh; padding:2rem; }
.box { max-width:480px; width:100%; border:1px solid <?= $paid ? '#c8ff00' : '#ff4444' ?>;
       padding:3rem; text-align:center; }
h1 { font-family:'Syne',sans-serif; font-size:1.6rem;
     color:<?= $paid ? '#c8ff00' : '#ff4444' ?>; margin-bottom:1rem; }
p { color:#888; margin-bottom:1.5rem; font-size:.85rem; }
.dl-btn { display:inline-block; background:#c8ff00; color:#000; font-weight:700;
          padding:.75rem 2rem; text-decoration:none; border-radius:4px; font-family:'Space Mono',monospace; }
.back { display:inline-block; margin-top:1rem; color:#555; font-size:.75rem; text-decoration:none; }
.back:hover { color:#aaa; }
</style>
</head>
<body>
<div class="box">
<?php if ($paid): ?>
    <h1>✓ Betaling ontvangen</h1>
    <p>Bedankt! Je kunt <strong><?= htmlspecialchars($order['file_name']) ?></strong> nu downloaden.</p>
    <a class="dl-btn" href="index.php?action=download&order=<?= urlencode($orderId) ?>">⬇ Download bestand</a>
<?php elseif ($status === 'open' || $status === 'pending'): ?>
    <h1>⏳ Betaling in behandeling</h1>
    <p>De betaling is nog niet bevestigd. Ververs deze pagina over een moment.</p>
    <a class="dl-btn" href="index.php?action=mollie_return&order=<?= urlencode($orderId) ?>" style="background:#ff6b35;color:#fff">↻ Vernieuwen</a>
<?php else: ?>
    <h1>✕ Betaling mislukt</h1>
    <p>Status: <strong><?= htmlspecialchars($status) ?></strong>. Probeer het opnieuw of kies een andere betaalmethode.</p>
<?php endif; ?>
    <br><a class="back" href="index.php">← Terug naar de shop</a>
</div>
</body>
</html>
