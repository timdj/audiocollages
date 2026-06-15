<?php
/**
 * audio_list.php
 * Zet dit bestand op de server, naast de map "audio/".
 * Geeft een JSON-array terug met alle audiobestanden in audio/.
 *
 * Mapstructuur:
 *   /
 *   ├── audio_list.php       ← dit bestand
 *   ├── radio_portal.html
 *   └── audio/
 *       ├── track1.mp3
 *       ├── track2.wav
 *       └── ...
 */

header('Content-Type: application/json; charset=utf-8');
header('Access-Control-Allow-Origin: *'); // sta cross-origin fetch toe (zelfde server = niet nodig, maar handig)

$audioDir = __DIR__ . '/audio/';
$allowed  = ['mp3','wav','ogg','flac','aac','m4a','opus','webm'];

if (!is_dir($audioDir)) {
    http_response_code(404);
    echo json_encode(['error' => 'Map "audio/" niet gevonden op de server.']);
    exit;
}

$files = [];
foreach (scandir($audioDir) as $name) {
    if ($name[0] === '.') continue;                         // skip . en ..
    $ext = strtolower(pathinfo($name, PATHINFO_EXTENSION));
    if (!in_array($ext, $allowed)) continue;
    if (!is_file($audioDir . $name)) continue;
    $files[] = [
        'name' => $name,
        'url'  => 'audio/' . rawurlencode($name),          // relatieve URL
        'size' => filesize($audioDir . $name),
    ];
}

// Sorteer op bestandsnaam
usort($files, fn($a, $b) => strnatcasecmp($a['name'], $b['name']));

echo json_encode([
    'count' => count($files),
    'files' => $files,
], JSON_UNESCAPED_UNICODE | JSON_UNESCAPED_SLASHES);
